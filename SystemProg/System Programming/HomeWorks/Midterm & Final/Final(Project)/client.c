/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : Jun 7th 2013
 * File       : Bil244_101044009_final_CLIENT.c
 *
 * Description: 
 *          Reads matris from file and send it to mathServer to solve           
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc client.c -lpthread
 *  $ ./a.out <tickTime> <data.txt> <IP>
 *
 *********************************************************
 */

//Libraries
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
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>

//Makro Variables
#define PORTNUM 50000  //To connect MathServer
#define PORTNUM2 50001 //To connect tickServer
 
//Function prototypes
int buildConnection(char *hostName, unsigned short portnum);
void *listenKillMessage( void *parameter );
void *connectToTickServer( void *parameter );
void *rowOperation(void * arg);
void killer( int sigNum );
int readMatris(char *argv);

//Get the matris
struct data {
   double arr[20][20] ; // A matris in file
   double arr1[20][20]; // B one column matris in file
   int size; //Size of matris nxn
};

//Global Variables
int mathServer;
int tickServer,sizeOfArr;
struct data readFile ;
char logFileName[25];
FILE *logFile;


//Test Function
int main(int argc, char* argv[] )
{
    //Build the log file name
    sprintf(logFileName,"Client[%d].log",(int)getpid());
    logFile = fopen(logFileName,"w"); //Open logFile
    /*TIME**********************************************************************/
    time_t currTime;//Write to logFile the time that program started
    currTime = time(NULL);
    fprintf(logFile, "CLIENT ON\n#######################################################\n");
    fprintf(logFile, "Client started at the time of %s", ctime(&currTime));
    /***************************************************************************/
    if( argc != 4 ){ //Check the arguments
        fprintf(stderr, "USAGE: %s <tickTime> <data.txt> <IP> \n", argv[0] );
        exit( 1 );
    }
   
   //Build Socket for mathServer
   if ( ( mathServer = buildConnection(argv[3], (unsigned)(PORTNUM) ) ) < 0) {   
       perror("accept");
       exit( 1 );
   }  fprintf(logFile, "Connected to mathServer.\n");


   //Build socket for tickServer
   if ( ( tickServer = buildConnection(argv[3], (unsigned)(PORTNUM2) ) ) < 0) {   
       perror("accept");
       exit( 1 );
   }  fprintf(logFile, "Connected to TickServer.\n");


   //Get matris from data file
   readMatris(argv[2]);
   fprintf(logFile, "Matris has been read from data file.\n");
   
   fprintf(stderr, "CLIENT ON :\n");
   
   //Ctrl+C signal handler ***********************/
   struct sigaction act1;
   act1.sa_handler = killer;        
   act1.sa_flags = 0;
   if ((sigemptyset(&act1.sa_mask) == -1) ||
         (sigaction(SIGINT, &act1, NULL) == -1)) {
       perror("Failed to set SIGINT handler");
       return 1;
   }//Ctrl+C signal handler end  *****************/

   //Convert tick Time to integer
   int a = atoi(argv[1]);
   /*Thread*************************************************************/
   pthread_t tid[3]; //Start Conversation between math and tick servers
   pthread_create(&tid[0], NULL, listenKillMessage, NULL);
   pthread_create(&tid[1], NULL, connectToTickServer,(void *)a);
   pthread_join(tid[0],NULL); //Wait for thread to end
   pthread_join(tid[1],NULL); //Wait for thread to end
   /*End thread*********************************************************/

   fclose(logFile);
   return 0;
}

//Build connection and connect to servers
int buildConnection(char *hostName, unsigned short portnum)
{
   struct sockaddr_in sa;
   struct hostent *hp;
   int s; //Socket descriptor

   //Get hostName
   if ((hp= gethostbyname(hostName)) == NULL){ 
      //Do we know the host
      errno= ECONNREFUSED; //Address
      return -1; 
   }
    
   memset(&sa, 0 ,sizeof(sa));
   memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length ); //Set address
    
   sa.sin_family= hp->h_addrtype;
   sa.sin_port= htons((u_short)portnum);
    
   if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) //et socket
       return -1;
    
   if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0){
       close( s );
       return -1;
   }

   return s; //Send the descriptor of socket
}


//Check whether we got a kill signal from mathServer
void *listenKillMessage( void *parameter )
{
   char *message = malloc( sizeof( char ) * 256 );
   int k = 0,j=0,i;
   char *a ;
   while(1)
   {    //Check the row operation
        read(mathServer, message, sizeof(char)*256);

        if( strcmp(message, "kill") == 0 )
        {  //If mathServer dies it also dies
           fprintf(stderr, "\nkilled by mathServer\n");
           fprintf(logFile, "Client has been killed by MathServer.\nCLIENT OFF\n");
           fclose(logFile); exit(1);
        }
        a = message ;
        
        if(j != 0 && *a =='R') //Get row operation from mathServer
          fprintf(stderr,"\nRow Oper :%s",message );

        j++;
   }
   return NULL;
} //End of listenKillMessage

//Bridge of messages between client and servers
void *connectToTickServer( void *parameter )
{
   int numberOfTick ;
   numberOfTick =(int)parameter;
   char tik[10];

   //Send tick time to tickServer
   write(tickServer,&numberOfTick, sizeof(int));
   fprintf(logFile, "TickTime : %d has sent to tickServer.\n",numberOfTick );

   //Send size of arr to mathServer
   write(mathServer,&sizeOfArr, sizeof(int));
   fprintf(logFile, "size of Array : %d has sent to mathServer.\n",sizeOfArr);
    
   //Send structure to mathServer
   write(mathServer,&readFile, sizeof(struct data));
   fprintf(logFile, "Data structure has been sent to mathServer.\n");

   char git[] = "tik" ;
   char getRowOper[250];
   while(1)
   {   
      //Send structure to mathServer
      write(mathServer,git, sizeof(char)*256);

      //Get number of tick. It waits in tickServer
      read(tickServer,tik, sizeof(char)*256);
   }

   return NULL;
} //end of connectToTickServer


//Read matrisses from Data file
int readMatris(char *argv)
{
    char arr,arr1,temp; int row = 0,column = 0;
    int i,j,k;
    
    FILE * inp = fopen(argv, "r");
    arr = fgetc(inp); //Read the name of first matris

    //Count number of columns
    while( (temp = fgetc(inp)) != ';'){      
        if(temp == '\n')
            ++row;
    }
    row++; //the size of matris
    readFile.size = row; //Keep the size
    row = 0;
    rewind(inp); //The size calculated come back to head
    
    //Read the elements
    while( (temp = fgetc(inp)) != ';')
    {    
        if( temp <= 57 && temp >= 48)
        { //eğer sayı yakalarsan             
            readFile.arr[row][column] = (double)(temp-48);              
            temp = fgetc(inp);
            temp = fgetc(inp);
            readFile.arr[row][column] += ( (double)(temp-48) / 10 );
            column++;
        }
        else if( temp == '\n' ){        
            row++;          
            column = 0;
        }
    }
    row = readFile.size; row = 0;

    //Read the equation
    while( (temp = fgetc(inp)) != ';' )
    {
        if( temp <= 57 && temp >= 48)
        {   //Check whether its integer                        
            readFile.arr1[row][0] = (double)(temp-48);               
            temp = fgetc(inp);//burada '.' işareti var'
            temp = fgetc(inp);//burada '.' dan sonraki sayı var
            readFile.arr1[row][0] += ( (double)(temp-48) / 10 );
            row++;
        }
    }
    sizeOfArr = readFile.size ; //Copy the size of matris

    for(i = 0; i < row; ++i) //Combine matrisses
        readFile.arr[i][row] = readFile.arr1[i][0]; 

    //Show the matris
    printf("Matris : \n__________\n"); 
    for(k=0; k<readFile.size; k++)
    {   //Print the matris
        for (i = 0; i <= readFile.size; ++i)
            printf("%.1f  ",readFile.arr[k][i]);
        printf("\n");
    }
    printf("----------\n");
} // End of readMatris


//Ctrl+C signal Handler
void killer(int sigNum)
{
   fprintf(stderr, "\nClient has killed by User.\n"); 
   fprintf(logFile,"Client has been terminated by User, SigNum[%d].\nCLIENT OFF\n",sigNum);
   fclose(logFile); 
   exit(1);
}
