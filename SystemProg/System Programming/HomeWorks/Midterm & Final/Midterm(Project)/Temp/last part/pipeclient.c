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
#define FIFOARG 1
#define BLKSIZE 100

void writePid();

int main (int argc, char *argv[]) 
{
   time_t currTime;
   pid_t pid = getpid() ;
   int len,i=0;
   char requestbuf[PIPE_BUF];  
   int clinetToServer,signalFile;
   char logFileName[ PATH_MAX ];
   char buf[BLKSIZE];


   //Building a logFile
   printf("LogFile built as\n");
   sprintf(logFileName, "clientLogFile_%ld.log", (long) getpid() );
   fprintf(stderr, "%s\n", logFileName );
   FILE* logFile = fopen(logFileName, "w");
    
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

   writePid();
   
   while(1) //Commanding on server
   {
      printf("Write the message to server : ");  
      scanf("%s",requestbuf); 

      if(strcmp(requestbuf,"exit")==0)
         break ;

      len = strlen(requestbuf);
      if (write(clinetToServer, requestbuf, len) != len) {
         perror("Client failed to write");
         return 1;
      }

      memset(requestbuf, 0, sizeof(buf));
   } 
   write(clinetToServer, "clientLeave", 12);

   //Get the client finish time
   currTime = time(NULL);
   fprintf(logFile, "Client ended at the time of %s", ctime(&currTime));
   fprintf(logFile, "#######################################################\n");
   close(clinetToServer);
   fclose(logFile);

   return 0; 
}


void writePid()
{
   char PID[10];
   pid_t mypid = getpid();
   sprintf(PID,"%d",mypid);
   int fildes = open("clientPID", O_RDWR );
   write(fildes, PID, 10);

   close( fildes );
   
   return;
}


