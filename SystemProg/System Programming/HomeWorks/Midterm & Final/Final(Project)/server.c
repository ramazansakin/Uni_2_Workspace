/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : Jun 7th 2013
 * File       : Bil244_101044009_final_MathServer.c
 *
 * Description: 
 *          get the matris from clients and reduce them using gauss jordan method.           
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc mathServer.c -lpthread
 *  $ ./a.out <numOfMaxClient> <tickTime>
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
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>


//Macro Variables
#define PORT_NUM 50000
#define PORT_NUM_TICK 50001
#define HOST_NAME_LEN 5000
#define TEN_MILLION 100000000L
#define LOG_FILE "mathServer.log"

//For Many Clients
struct client{
    int des;
    int ID ;
};

//Keep the matris
struct data{
    double arr[20][20];
    double arr1[20];
    int size ;
 };

//Global Variables
int server , maxClient,tickServer ;
int numOfClient = 0,tickTime = 5;
struct client *clients ;
struct data readFile[10] ; //Matrisses
int count = 0 ; //Num of matris came from client
FILE *logFile; //Build logFile


//Function Prototypes
int establish(unsigned short portNum); //Establish Connection
void killer(int sigNum); //Catches Ctrl+C signal and close everything safely
int acceptClients();     //Let clients to conect
int makeConnection(int s); //Builts connection
void *bridgeOfMessage(void *arg); //The Talk between clients and server
int callSocket(char *hostname, unsigned short portnum);


//Show the status of matrix row operation
void printMatrix(int N) 
{
    int i,j;
    for ( i = 0; i < N; i++){
        for ( j = 0; j <= N; j++)
            printf("%.3f\t",readFile[count].arr[i][j]);
        printf("\n");
    }
    printf("\n\n\n");
}


//Testing Program
int main(int argc, char const *argv[])
{
    if(argc != 3){ //Check the arguments whether they have taken correctly
        fprintf(stderr, "Usage : %s <numOfMaxClient> <tickTime>\n",argv[0] );
        return 0 ;
    }
    logFile = fopen(LOG_FILE,"w"); //Open logFile

    /*TIME**********************************************************************/
    time_t currTime;//Write to logFile the time that program started
    currTime = time(NULL);
    fprintf(logFile, "MATHSERVER ON\n#######################################################\n");
    fprintf(logFile, "MathServer started at the time of %s", ctime(&currTime));
    /***************************************************************************/

    //Convert ticlTime to integer
    tickTime = atoi(argv[2]);

    //Num Of Max Client
    maxClient = atoi(argv[1]);
    clients = malloc(sizeof(struct client)*maxClient);

    //Get Connection
    if((server = establish(PORT_NUM)) < 0){
        perror("Establish");
        return 0 ;
    }
    fprintf(logFile, "Connection established.\n");

    //Ctrl+C Signal Handler
    struct sigaction sig ;
    sig.sa_handler = killer ;
    sig.sa_flags = 0;
    if ( (sigemptyset(&sig.sa_mask) == -1) || 
         (sigaction(SIGINT, &sig, NULL) == -1)) {
        perror("Failed to set SIGINT handler"); return 1;
    } //END of Ctrl+C Signal Handler
    /*******************/

    //Connect to tickServer
    if ( ( tickServer = callSocket("127.0.0.1", (unsigned)(PORT_NUM_TICK) ) ) < 0) {   
        perror("accept");
        exit( 1 );
    }   fprintf(logFile, "Server has connected to tickServer.\n");
    
    printf("SERVER ON:\n\n");

    //Wait for clients and do their job
    acceptClients();

    fclose(logFile);
    return 0;
}


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
    
    return s;
 }//End of callSocket function


//Build connection between clients and server.Allows many clients
int acceptClients()
{
    //Num of max client that can connect mathServer
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
        fprintf(logFile,"Client %d Connected.",numOfClient);
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
    
    return t; //Establish Connection
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
    count++;
    char *message = malloc(sizeof(char)*256);
    char *sendOperation = malloc(sizeof(char)*256);

    /********************************/
    int i,size,k,clientToServer ;
    //Get size of arr from client
    read(currentClient.des, &size, sizeof(int));
    fprintf(logFile, "size of Array : %d got from client.\n",size);

    //get Structure from client
    read(currentClient.des, &readFile[count], sizeof(struct data));
    fprintf(logFile, "Got the matris from client.\n");

    //Send tick time to tickServer
    write(tickServer,&tickTime,sizeof(int));
    fprintf(logFile, "TickTime : %d has sent to tickServer.\n",tickTime);

    //Show the matrix taken from client
    for(k=0; k<size; k++){
        for (i = 0; i < size+1; ++i)
            printf("%.2f  ",readFile[count].arr[k][i]);
        printf("\n");
    } printf("----------\n");

   //Do row operations
   double scale; int p,j;
   for ( p = 0; p < size; p++) 
   {
        double divider = readFile[count].arr[p][p];
        for ( i = 0; i <= size; i++) 
            if (i != p) 
            {
                scale = readFile[count].arr[i][p];
                for ( j = 0; j <= size; j++) 
                    readFile[count].arr[i][j] = (readFile[count].arr[p][j] * scale / divider) - readFile[count].arr[i][j];

                //Take messages from tickServer
                read(tickServer, message, sizeof(char)*256  );
                printf("Message from tickServer: %s\n", message);
                
                if( strcmp(message, "die") == 0 )
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
                //Send row operation to client
                sprintf(sendOperation,"R%d = R%d - (R%d*%.0f/%.0f)\n",i,i,p,scale,divider);
                write(currentClient.des,sendOperation,sizeof(char)*256);
                fprintf(logFile, "Row Operation : %s",sendOperation);
                
                //Show row operations
                printf("Row Operation : %s\n", sendOperation);
                printMatrix(size);
            }
        }

        for ( p = 0; p < size; p++) 
        {   //Get x values
            scale = readFile[count].arr[p][p];
            for ( j = 0; j <= size; j++) 
            {
                if (readFile[count].arr[p][j] != 0 && scale != 0)
                    readFile[count].arr[p][j] = readFile[count].arr[p][j] / scale;
                else
                    readFile[count].arr[p][j] = 0;

                readFile[count].arr1[p] = readFile[count].arr[p][size];
            }
        }

        //The x values
        printf("LAST FORM\n"); fprintf(logFile, "LAST FORM :\n");
        for ( i=0; i<size; i++)
        {
            fprintf(stderr,"x%d = %.3f\n",i+1,readFile[count].arr1[i]);
            fprintf(logFile,"x%d = %.3f\n",i+1,readFile[count].arr1[i]);
        } fprintf(logFile,"\n");
            
    return NULL;
}

//Catches Ctrl+C signal. Closes server and clients safely
void killer(int sigNum)
{
    int i=0; char killMessage[] = "kill";
    
    //Kill awake clients one by one
    for(i=0; i<numOfClient; i++ )
        if( clients[i].des != 0 ) //Kill all clients connected
            write(clients[i].des, killMessage, sizeof(char)*5);

    close(server); //Close socket
    fprintf(stderr, "\nAll Clients has been Terminated..!\n");
    fprintf(logFile,"All Clients has been terminated.\nSERVER OFF\n");
    fclose(logFile); //Close logFile
    exit(1);
}