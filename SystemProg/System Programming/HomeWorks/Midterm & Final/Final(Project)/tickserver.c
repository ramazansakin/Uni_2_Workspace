/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : Jun 7th 2013
 * File       : Bil244_101044009_final_TickServer.c
 *
 * Description: 
 *          Sends tik to the clients connected.           
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc tickServer.c -lpthread
 *  $ ./a.out <numOfMaxClient>  <tickTime>
 *
 *********************************************************
 */

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
#define PORT_NUM 50001
#define HOST_NAME_LEN 5000
#define LOG_FILE "tickServer.log"

//Clients Destination
struct client{
    int des;
    int ID ;
};

//Global Variables
int server , maxClient ;
int numOfClient = 0,tickOfTikServer;
struct client *clients ;
FILE *logFile; //Build logFile

//Function Prototypes
int establish(unsigned short portNum); //Establish Connection
void killer(int sigNum); //Catches Ctrl+C signal and close everything safely
int acceptClients();     //Let clients to conect
int makeConnection(int s); //Builts connection
void *bridgeOfMessage(void *arg); //The Talk between clients and server

//Testing Program
int main(int argc, char const *argv[])
{
    if(argc != 3){ //Check the arguments whether they have taken correctly
        fprintf(stderr, "Usage : %s <numOfMaxClient>  <tickTime>\n",argv[0] );
        return 0 ;
    }

    //Open logFile
    logFile = fopen(LOG_FILE,"w"); 

    /*TIME**********************************************************************/
    time_t currTime;//Write to logFile the time that program started
    currTime = time(NULL);
    fprintf(logFile, "TICK SERVER ON\n###############################################\n");
    fprintf(logFile, "TickServer started at the time of %s", ctime(&currTime));
    /***************************************************************************/

    //Tick time of tickServer
    tickOfTikServer = atoi(argv[2]);

    //Num Of Max Client
    maxClient = atoi(argv[1]);
    clients = malloc(sizeof(struct client)*maxClient);

    //Get Connection
    if((server = establish(PORT_NUM)) < 0){
        perror("Establish");
        return 0 ;
    }
    fprintf(logFile, "Connection established.\n");

    struct sigaction sig ;//Ctrl+C Signal Handler
    sig.sa_handler = killer ;
    sig.sa_flags = 0;
    if ( (sigemptyset(&sig.sa_mask) == -1) || 
         (sigaction(SIGINT, &sig, NULL) == -1)) {
        perror("Failed to set SIGINT handler"); return 1;
    } //END of Ctrl+C Signal Handler
    /*******************/
    printf("TICK SERVER ON:\n\n");

    acceptClients();
    fclose(logFile);
    return 0;
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
        fprintf(logFile, "Client %d connected.\n",numOfClient);
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
    
    ++numOfClient; //Set Client ID
    write(t,&numOfClient, sizeof(int)); 
    --numOfClient;

    //If no error occured till now, connection is succesfull
    if(numOfClient != maxClient)
        printf("Connection established : Client %d is ON.\n",t-4);
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


//The Talk between clients and server
void *bridgeOfMessage(void *arg)
{
    struct client currentClient = *((struct client *) arg);
    
    char message[] = "tik"; //tik to send
    int tickTimeOfClients ; //Requists from clients

    //Get ticktime from clients
    read(currentClient.des, &tickTimeOfClients, sizeof(int));
    printf("Requested Tick Time : %d\n",tickTimeOfClients );

    //Build nanoseconds according to requists
    struct timespec sleepT;
    sleepT.tv_sec = 0; sleepT.tv_nsec = tickTimeOfClients;
    struct timespec sleepTickServer ;
    sleepTickServer.tv_sec = 0 ; sleepTickServer.tv_nsec = tickOfTikServer;

    //Send tik to clients
    while(1) 
    { 
        nanosleep(&sleepTickServer,NULL); //TickServer gets rest
        write(currentClient.des,message, sizeof(message)) ; //Send tik to clients
        nanosleep(&sleepT,NULL); //Takes rest according to tick time came from clients
    }

    return NULL;
}


//Catches Ctrl+C signal. Closes server and clients safely
void killer(int sigNum)
{
    int i=0; char killMessage[] = "kill";

    fprintf(stderr,"\nAll Clients has been Terminated..!\n");
    fprintf(logFile,"\nAll Clients has been Terminated..!\n");
    close(server); //Close socket
    exit(1);
}
