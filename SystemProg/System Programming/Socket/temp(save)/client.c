
 #include <errno.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <sys/wait.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <pthread.h>
    
 #define PORTNUM 50000
 #define PORTNUM2 50001
 #define MAXHOSTNAME 5000
 #define MAX_CHAT 256
 
 /*** function prototypes ***/
 int callSocket(char *hostname, unsigned short portnum);
 void *getMessage( void *parameter );
  void *getMessageTick( void *parameter );
 void terminator( int signo );

 int readMatris(char *argv);
 /*** end of function prototypes ***/

 struct data{
    int arr [10][10];
    int arr1[10];
 };
 
 /*** Global variables declarations ***/
 int istemci;
 int mathServer;
 int tickServer;
 int sizeOfArr= 3;
 struct data readFile ;
 /*** end of Global variables declarations ***/


//////////////////////////// ##################### ///////////////////// 
 int main(int argc, char* argv[] )
 {
    if( argc != 4 )
    {
        fprintf(stderr, "USAGE: %s tickTime data.txt IP \n", argv[0] );
        exit( 1 );
    }

    
    
    if ( ( mathServer = callSocket(argv[3], (unsigned)(PORTNUM) ) ) < 0) 
    {   
        perror("accept");
        exit( 1 );
    }
    
    if ( ( tickServer = callSocket(argv[3], (unsigned)(PORTNUM2) ) ) < 0) 
    {   
        perror("accept");
        exit( 1 );
    }
    
    readMatris(argv[2]);
    fprintf(stderr, "CLIENT ON :\n");
    
    // ctrl+c signal handler 
    struct sigaction act1;
    
    act1.sa_handler = terminator;        
    act1.sa_flags = 0;
    
    if ((sigemptyset(&act1.sa_mask) == -1) ||
          (sigaction(SIGINT, &act1, NULL) == -1)) {
        perror("Failed to set SIGINT handler");
        return 1;
    }
    int a = atoi(argv[1]);

    pthread_t tid[3];
    pthread_create(&tid[0], NULL, getMessage, NULL);
    pthread_create(&tid[1], NULL, getMessageTick,(void *)a);
    

    char *chat = malloc( sizeof( char )*MAX_CHAT );
    
    while( 1 )
    {
        gets( chat );
        if( strcmp(chat, "i am killed") == 0 )
        {
            fprintf(stderr, "WARNING: bu mesajı bu sekilde gonderemezsiniz\n");
            continue;
        }
        write( mathServer, chat, sizeof( char ) * MAX_CHAT );
    }
    
    return 0;
 }
//////////////////////////// ##################### /////////////////////

int readMatris(char *argv)
{
    FILE *inp ;
    int size,i,k ;
    inp = fopen(argv,"r");
    fscanf(inp,"%d",&size);
    printf("Size : %d\n",size );
    sizeOfArr = size;
    for(k=0; k<size; k++)
        for (i = 0; i < size; ++i)  
            fscanf(inp,"%d",&readFile.arr[k][i]);

    for (k = 0; k < size; ++k)
        fscanf(inp,"%d",&readFile.arr[k][size]);

    printf("__________\n");
    for(k=0; k<size; k++)
    {
        for (i = 0; i < size+1; ++i)
        {
            printf("%d  ",readFile.arr[k][i]);
        }
        printf("\n");
    }
    printf("----------\n");
    //for (i = 0; i < size; ++i)
        //printf("%d  ",readFile.arr1[i]);
}








 
 int callSocket(char *hostname, unsigned short portnum)
 {
    struct sockaddr_in sa;
    struct hostent *hp;
    int s;
    
    if ((hp= gethostbyname(hostname)) == NULL)
    { /* do we know the host's */
        errno= ECONNREFUSED; /* address? */
        return -1; /* no */
    } /* if gethostname */
    
    memset(&sa, 0 ,sizeof(sa));
    memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length ); /* set address */
    
    sa.sin_family= hp->h_addrtype;
    sa.sin_port= htons((u_short)portnum);
    
    if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) /* get socket */
        return -1;
    
    if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0)
    { /* connect */
        close( s );
        return -1;
    } /* if connect */
    
    int id;
    read(s, &id, sizeof(int));
    fprintf(stderr, "my id %d\n", id);
    return s;
 }/****************** end of callSocket function **********************/ 
 


 void *getMessage( void *parameter )
 {
    char *message = malloc( sizeof( char ) * MAX_CHAT );

    printf("GELDIM1\n");
    while(1)
    {
        read(mathServer, message, sizeof( char ) * MAX_CHAT );
        if( strcmp(message, "kill") == 0 )
        {
            fprintf(stderr, "killed by mathServer\n");
            exit( 1 );
        }
        //printf("INFO : %s\n",message );  
        
    }
    
    return NULL;
 }/********************** end of getMessage function ******************/

 void *getMessageTick( void *parameter )
 {
    int numberOfTick ;
    numberOfTick =(int)parameter;
    char tik[10];

    write(tickServer,&numberOfTick, sizeof(int));

    //Send size of arr to mathServer
    write(mathServer,&sizeOfArr, sizeof(int));
    
    //Send structure to mathServer
    write(mathServer,&readFile, sizeof(struct data));

    char git[] = "tik" ;
    while(1)
    {
        //Send structure to mathServer
        write(mathServer,git, sizeof(char)*256);
        read(tickServer,tik, sizeof(char)*10);
        if(strcmp(tik,"tik")==0)
            printf("I got tik: %s\n",tik);
    }
    
    return NULL;
 }/********************** end of getMessage function ******************/
 


 void terminator( int signo )
 {
    fprintf(stderr, "\ni am killed by user\n"); 
    char *killMessage = "i am killed";
    write(mathServer, killMessage, sizeof(char) * 12 );
    write(tickServer, killMessage, sizeof(char) * 12 );
    exit( 0 );
 }
