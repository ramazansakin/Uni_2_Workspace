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
int server , maxClient ;
int numOfClient = 0 ;
struct client *clients ;
struct data readFile ;

//Function Prototypes
int establish(unsigned short portNum); //Establish Connection
void killer(int sigNum); //Catches Ctrl+C signal and close everything safely
int acceptClients();     //Let clients to conect
int makeConnection(int s); //Builts connection
void *bridgeOfMessage(void *arg); //The Talk between clients and server


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
    
    printf("SERVER ON:\n\n");
      

    acceptClients();
    return 0;
}















//The Talk between clients and server
void *bridgeOfMessage(void *arg)
{
    struct client currentClient = *((struct client *) arg);
    
    char *message = malloc( sizeof(char)*256);

    /********************************/
    int i,size,k ;
    //Get size of arr from client
    read(currentClient.des, &size, sizeof(int));

    //get Structure from client
    read(currentClient.des, &readFile, sizeof(struct data));
    printf("SIZE : %d\n",size);

    for(k=0; k<size; k++)
    {
        for (i = 0; i < size; ++i)
        {
            printf("%d  ",readFile.arr[k][i]);
        }
        printf("\n");
    }
    printf("----------\n");
    for (i = 0; i < size; ++i)
        printf("%d  ",readFile.arr1[i]);
    
    /***********************/

    while(1) 
    {   //Get the message come from clients
        read(currentClient.des, message, sizeof(char)*256  );
        
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
        //printf("%s****\n",message);
        //messageOrganizator( message, ilgiliIstemci.des );
        
        if( strcmp(message, "tik") == 0 )
        {
            printf("I got tick..\n");
        }
        
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