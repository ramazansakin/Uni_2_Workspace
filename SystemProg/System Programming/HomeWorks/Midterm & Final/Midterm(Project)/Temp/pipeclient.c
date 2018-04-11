#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include "restart.h"
#include <signal.h>
#include <time.h>
#define FIFOARG 1
#define BLKSIZE 100

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
   
   char buf[BLKSIZE];
   struct sigaction act;
   act.sa_handler = signalCatch;
   act.sa_flags =0 ;

   if(sigaction(SIGINT,&act,NULL) == -1 || sigemptyset(&act.sa_mask) == -1)
      perror("Failed to set SIGINT to handle ctrl-C in client");


   //Building a logFile
   printf("LogFile built as\n");
   sprintf(logFileName,"clientLogFile_%d.log",getpid() );
   fprintf(stderr, "%s\n", logFileName );
   logFile = fopen(logFileName, "w");
    
   //Write to logFile the time that program started
   currTime = time(NULL);
   fprintf(logFile, "%s\n",logFileName);
   fprintf(logFile, "#######################################################\n");
   fprintf(logFile, "Client started at the time of %s\n", ctime(&currTime));
      

   if (argc != 2) {  /* name of server fifo is passed on the command line */
      fprintf(stderr, "Usage: %s fifoname\n", argv[0]);
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

   writePid(); //Writing PID to the file to let the server read it

   int readMessage;
   char fifoName[BLKSIZE], bufz[BLKSIZE];
   char temp[20];
   sprintf(fifoName,"%dClientFifo",getpid());

   printf("Waiting for server to built fifo..\n");
   sleep(1); //Wait for server to built file
   //Open the file that built by server and check if it is available
   if ((readMessage = open(fifoName, O_RDWR)) == -1) {
      perror("Client failed to open fifo for writing");
      return 1; 
   }

   printf("fifo file name : %s\n",fifoName );
   

   if (write(readMessage, "/home/sabri/Desktop/Test", 25) ==-1) {
         perror("Client failed to write directory");
         return 1;
      }
 
   while(!doneFlag) //Commanding on server
   {
      printf("Write your message to server : ");  
      scanf("%s",requestbuf); 
     

      len = strlen(requestbuf);
      if (write(readMessage, requestbuf, len) != len) {
         perror("Client failed to write");
         return 1;
      }

      if(strcmp(requestbuf,"find")==0)
      {
         char findStr[20];
         scanf("%s",findStr);
         printf("WANTED FILE NAME: %s\n", findStr);
         len = strlen(findStr);
         if (write(readMessage, findStr, len) != len) {
            perror("Client failed to write directory");
            return 1;
         }  
         memset(findStr, 0, sizeof(findStr));
      }
      else if(strcmp(requestbuf,"exit")!=0)
      {
         
         scanf("%s",temp);
      }
       if(strcmp(requestbuf,"exit")==0 || strcmp(requestbuf,"q")==0)
         break ;
      

      

      //clean fifo
      memset(requestbuf, 0, sizeof(buf));
   } 

  
      
     
   

   //Tell the server that client leaving
   write(clinetToServer, "clientLeave", 12);

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


