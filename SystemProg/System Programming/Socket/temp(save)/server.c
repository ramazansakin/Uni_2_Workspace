//BISMILLAHIRRAHMANIRRAHIM

//Libraries
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <time.h>

//Macro Variables
#define PORT_NUM 50000
#define PORT_NUM_TICK 50001
#define HOST_NAME_LEN 5000
#define TEN_MILLION 100000000L

//For Many Clients
struct client{
    int des;
    int ID ;
};

struct data{
    int arr[10][10];
    int arr1[10];
 };

//Global Variables
int server , maxClient,tickServer ;
int numOfClient = 0 ;
struct client *clients ;
struct data readFile ;


//Function Prototypes
int establish(unsigned short portNum); //Establish Connection
void killer(int sigNum); //Catches Ctrl+C signal and close everything safely
int acceptClients();     //Let clients to conect
int makeConnection(int s); //Builts connection
void *bridgeOfMessage(void *arg); //The Talk between clients and server
int callSocket(char *hostname, unsigned short portnum);





void printMatrix(int N) {
    int i,j;
    
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j <= N; j++)
        {
            printf("%d\t",readFile.arr[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\n\n\n");
  
}









//Testing Program
int main(int argc, char const *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage : %s numOfMaxClient\n",argv[0] );
        return 0 ;
    }

    //Num Of Max Client
    maxClient = atoi(argv[1]);
    clients = malloc(sizeof(struct client)*maxClient);

    //Get Connection
    if((server = establish(PORT_NUM)) < 0){
        perror("Establish");
        return 0 ;
    }

    /*******************/
    //Show message flashy
    char buffer[1024],*c; struct timespec sleeptime;
    sleeptime.tv_sec = 0; sleeptime.tv_nsec = TEN_MILLION; 
    snprintf(buffer, 1024, "Socket has been built..\n");
    c = buffer ;
    while(*c != '\0'){
        fputc(*c,stderr); c++; nanosleep(&sleeptime,NULL);
    } //End flashy
    /*******************/
    struct sigaction sig ;//Ctrl+C Signal Handler
    sig.sa_handler = killer ;
    sig.sa_flags = 0;
    if ( (sigemptyset(&sig.sa_mask) == -1) || 
         (sigaction(SIGINT, &sig, NULL) == -1)) {
        perror("Failed to set SIGINT handler"); return 1;
    } //END of Ctrl+C Signal Handler
    /*******************/

    if ( ( tickServer = callSocket("127.0.0.1", (unsigned)(PORT_NUM_TICK) ) ) < 0) 
    {   
        perror("accept");
        exit( 1 );
    }
    
    printf("SERVER ON:\n\n");
      

    acceptClients();
    return 0;
}


/***************************************************************/
//Connect to tickServer
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

/*#############################################/*/









//The Talk between clients and server
void *bridgeOfMessage(void *arg)
{
    struct client currentClient = *((struct client *) arg);
    
    char *message = malloc(sizeof(char)*256);

    /********************************/
    int i,size,k ;
    //Get size of arr from client
    read(currentClient.des, &size, sizeof(int));

    //get Structure from client
    read(currentClient.des, &readFile, sizeof(struct data));
    printf("SIZE : %d\n",size);

    for(k=0; k<size; k++)
    {
        for (i = 0; i < size+1; ++i)
        {
            printf("%d  ",readFile.arr[k][i]);
        }
        printf("\n");
    }
    printf("----------\n");
    

    while(1) 
    {   //Get the message come from clients
        

        /*********************************/
        double scale;
        int p,i,j;
        for ( p = 0; p < size; p++) 
        {
            double divider = readFile.arr[p][p];
            for ( i = 0; i <= size; i++) 
            {
                if (i != p) 
                {
                    scale = readFile.arr[i][p];
                    for ( j = 0; j <= size; j++) 
                    {
                        readFile.arr[i][j] = (readFile.arr[p][j] * scale / divider) - readFile.arr[i][j];
                    
                    }
                    while(1)
                    {
                        read(currentClient.des, message, sizeof(char)*256  );

                        if( strcmp(message, "tik") == 0 )
                        {
                            printf("I got tick..\n"); break ;
                            

                        }
                    }
                    if(scale != 0)
                        fprintf(stderr,"R%d = R%d - (R%d*%.0f/%.0f)\n",i,i,p,scale,divider);


                    printMatrix(size);
                }
            }
        }

        for ( p = 0; p < size; p++) 
        {
            scale = readFile.arr[p][p];
            for ( j = 0; j <= size; j++) 
            {
                if (readFile.arr[p][j] != 0 && scale != 0)
                    readFile.arr[p][j] = readFile.arr[p][j] / scale;
                else
                    readFile.arr[p][j] = 0;

                readFile.arr1[p] = readFile.arr[p][size];
            }
        }

        printf("LAST FORM\n");
        for ( i=0; i<size; i++) 
            fprintf(stderr,"x%d = %d\t",i+1,readFile.arr1[i]);




        /******************************/






        
        if( strcmp(message, "i am killed") == 0 )
        {
            fprintf(stderr, "Disconnected : Client %d is OFF.\n", currentClient.ID);
            
            int i=0;
            for(i = 0; i < numOfClient ; i++)
            {
                if(clients[i].des == currentClient.des)
                {
                    clients[i].des =0;
                    clients[i].ID =0;
                    free(message);
                    return NULL;
                }
            }
        }

        while(1);

        
         
        
    }
    
    return NULL;
}



















































//Build connection between clients and server.Allows many clients
int acceptClients()
{
    while(numOfClient <= maxClient)
    {
        if ((clients[numOfClient].des = makeConnection(server)) < 0){
            if (errno == EINTR) // Make sure connection is ok
                continue;
            perror("Accept");
            return 0;
        }
        //Set Client IDs
        clients[numOfClient].ID = numOfClient+1;
    
        pthread_t tid; //Read messages from client
        pthread_create(&tid, NULL, bridgeOfMessage, &(clients[numOfClient]));
        
        ++numOfClient; //Increase num of client anytime a client connected
    }
    
    return 0;
}

//Let clients to connect server
int makeConnection(int s)
{
    int t; //Connecting to client
    if ( (t = accept(s,NULL,NULL)) < 0)
        return(-1);
    
    ++numOfClient; //Set Client ID and send it to client
    write(t,&numOfClient, sizeof(int)); 
    --numOfClient;

    //If no error occured till now, connection is succesfull
    if(numOfClient != maxClient)
        printf("Connection established : Client %d is ON.\n",t-3);
    if(numOfClient == maxClient)
        printf("Reached maximum number of clients..!\n");
    
    return t;
}



//Establish Connection
int establish(unsigned short portNum)
{
    char myHost[HOST_NAME_LEN];
    int scket ;
    struct sockaddr_in sa;
    struct hostent *hp;

    memset(&sa, 0, sizeof(struct sockaddr_in)); //Clear our address
    gethostname(myHost, HOST_NAME_LEN);         //Who are we?
    hp= gethostbyname(myHost);                  //Get our address info

    if(hp == NULL) //We don't exist
        return (-1);

    sa.sin_family= hp->h_addrtype; //Our host address
    sa.sin_port= htons(portNum); //Our port number

    //Build Socket
    if ((scket= socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return(-1);

    //Bind address to socket
    if (bind(scket, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) < 0){
        close(scket);
        return(-1); 
    }
    
    listen(scket, 5); //Max num of cliets in the queue
    
    return scket;
}

//Catches Ctrl+C signal. Closes server and clients safely
void killer(int sigNum)
{
    int i=0; char killMessage[] = "kill";
    
    //Kill awake clients one by one
    for(i=0; i<numOfClient; i++ )
        if( clients[i].des != 0 )
            write(clients[i].des, killMessage, sizeof(char)*5);

    close(server); //Close socket
    fprintf(stderr, "\nAll Clients has been Terminated..!\n");
    exit(1);
}