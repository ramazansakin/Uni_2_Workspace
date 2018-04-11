/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : April 24th 2013
 * File       : Bil244_101044009_midterm_CLIENT.c
 *
 * Description: 
 *          Orders to server.it works for list,
 *          find,kill,time and exit orders
 *           
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc -c pipeclient.c
 *  $ gcc pipeclient.o -o pipeclient
 *  $ ./pipeclient fifoname /home/sabri/Desktop/
 *
 *********************************************************
 */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#define FIFOARG 1
#define BLKSIZE 100
#define MILLION 1000L

void writePid();
static void signalCatch(int sigNum);
static volatile sig_atomic_t doneFlag =0;
char logFileName[ PATH_MAX ];
FILE* logFile ;

int main (int argc, char *argv[]) 
{
   time_t currTime;
   pid_t pid = getpid() ;
   int len,i=0;
   char requestbuf[PIPE_BUF];  
   int clinetToServer,signalFile;
   long timedif;
   struct timeval tpend;
   struct timeval tpstart;

   char buf[BLKSIZE];
   struct sigaction act;
   act.sa_handler = signalCatch;
   act.sa_flags =0 ;

   if (gettimeofday(&tpstart, NULL)) {
      fprintf(stderr, "Failed to get start time\n");
      return 1;
   }

   //Catch signal
   if(sigaction(SIGINT,&act,NULL) == -1 || sigemptyset(&act.sa_mask) == -1)
      perror("Failed to set SIGINT to handle ctrl-C in client");

   //Building a logFile
   printf("LogFile built as\n");
   sprintf(logFileName,"CLIENT_LogFile_%d.log",getpid() );
   fprintf(stderr, "%s\n", logFileName );
   logFile = fopen(logFileName, "w");
    
   //Write to logFile the time that program started
   currTime = time(NULL);
   fprintf(logFile, "%s\n",logFileName);
   fprintf(logFile, "#######################################################\n");
   fprintf(logFile, "Client started at the time of %s", ctime(&currTime));
      

   if (argc != 3) {  /* name of server fifo is passed on the command line */
      fprintf(stderr, "Usage: %s fifoname Path\n", argv[0]);
      return 1; 
   }
   

   //Open the file that built by server and check if it is available
   if ((clinetToServer = open(argv[FIFOARG], O_WRONLY)) == -1) {
       perror("Client failed to open log fifo for writing");
       return 1; 
   }

   


   //Tell the server that I am coming
   write(clinetToServer, "IamClient", 10);
   if (write(signalFile, &pid, sizeof(pid_t)) == -1) {
         perror("Client failed to write");
         return 1;
   }
   fprintf(logFile, "Client asked server that it is coming to order..\n");
   writePid(); //Writing PID to the file to let the server read it

   int readMessage;
   char fifoName[BLKSIZE], bufz[BLKSIZE];
   char temp[20];
   sprintf(fifoName,"%ldClientFifo",(long)getpid());

   printf("Waiting for server to built fifo..\n");
   sleep(3); //Wait for server to built file
   //Open the file that built by server and check if it is available
   if ((readMessage = open(fifoName, O_RDWR)) == -1) {
      perror("Client failed to open fifo for writing");
      return 1; 
   }
   fprintf(logFile, "Client opens fifo file to connect server..\n");

   printf("fifo file name : %s\n",fifoName );

   if (write(readMessage, argv[2], 250) ==-1) {
         perror("Client failed to write directory");
         return 1;
      }
   fprintf(logFile, "Client sent directory path to the server..\n");
 
   while(!doneFlag) //Commanding on server
   {
      printf("=> ");  
      scanf("%s",requestbuf); 

      if(strcmp(requestbuf,"exit")==0 || strcmp(requestbuf,"q")==0)
      {
         fprintf(logFile, "Client wants to leave..\n");
         break ;
      }
         

      len = strlen(requestbuf);
      if (write(readMessage, requestbuf, len+1) != len+1) {
         perror("Client failed to write");
         return 1;
      }

      //Find wanted target
      if(strcmp(requestbuf,"find")==0)
      {
         char findStr[20];
         scanf("%s",findStr);
         printf("Target: %s\n", findStr);
         fprintf(logFile, "Client has sent \"find %s\" order to server..\n",findStr);
         len = strlen(findStr);
         if (write(readMessage, findStr, len+1) != len+1) {
            perror("Client failed ");
            return 1;
         }  
         memset(findStr, 0, sizeof(findStr));
      }
      //List wanted target
      else if(strcmp(requestbuf,"list")==0)
      {
         char findStr[20];
         scanf("%s",findStr);
         printf("Target: %s\n", findStr);
         fprintf(logFile, "Client has sent \"list %s\" order to server..\n",findStr);
         len = strlen(findStr);
         if (write(readMessage, findStr, len+1) != len+1) {
            perror("Client failed");
            return 1;
         }  
         memset(findStr, 0, sizeof(findStr));
      }
      //show in how many nanoseconds the target found
      else if(strcmp(requestbuf,"time")==0)
      {
         char findStr[20];
         scanf("%s",findStr);
         printf("Target: %s\n", findStr);
         fprintf(logFile, "Client has sent \"time %s\" order to server..\n",findStr);
         len = strlen(findStr);
         if (write(readMessage, findStr, len+1) != len+1) {
            perror("Client failed");
            return 1;
         }  
         memset(findStr, 0, sizeof(findStr));
      }

      else if(strcmp(requestbuf,"kill")==0)
      {
         char findStr[20];
         scanf("%s",findStr);
         printf("Target: %s\n", findStr);
         fprintf(logFile, "Client has sent \"kill %s\" order to server..\n",findStr);
         len = strlen(findStr);
         if (write(readMessage, findStr, len+1) != len+1) {
            perror("Client failed");
            return 1;
         }
         
         printf("Client has killed the thread that was serving.\n");
         printf("CLIENT OFF\n");
         break;  
         memset(findStr, 0, sizeof(findStr));
      }

      //Its just a temp to handle the second value
      else if(strcmp(requestbuf,"exit")!=0 &&
              strcmp(requestbuf,"list")==0 ||
              strcmp(requestbuf,"kill")==0 ||
              strcmp(requestbuf,"find")==0 ||
              strcmp(requestbuf,"time")==0 &&
            !doneFlag)
      {
         scanf("%s",temp);
      }

      //clean fifo
      memset(requestbuf, 0, sizeof(buf));
   } 

  

   //Tell the server that client leaving
   write(clinetToServer, "clientLeave", 12);
   fprintf(logFile, "Client is leaving.. \n");

   //Get the time that program worked in nanoseconds
   if (gettimeofday(&tpend, NULL)) {
      fprintf(stderr, "Failed to get end time\n");
      return 1;
   }
      timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
                                 tpend.tv_usec - tpstart.tv_usec;
   fprintf(logFile,"The client took %ld*10^(-6) nanoseconds\n", timedif);

   //Get the client finish time
   currTime = time(NULL);
   fprintf(logFile, "Client ended at the time of %s", ctime(&currTime));
   fprintf(logFile, "#######################################################\n");

   


   close(clinetToServer);
   fclose(logFile);
   remove(fifoName);

   return 0; 
}


void writePid()
{
   char PID[10];
   int fildes;
   pid_t mypid = getpid();
   sprintf(PID,"%d",mypid);
   fprintf(logFile, "Client PID has sent to server : %d\n",getpid());
   fildes = open("clientPID", O_RDWR );
   write(fildes, PID, 10);

   close( fildes );
   return;
}


static void signalCatch(int sigNum)
{
   doneFlag = 1;
   fprintf(logFile, "Client got a kill signal SIG : %d\n",sigNum);
   printf("ctrl-C catched \"%d\" in client\n",sigNum );
}


