/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : April 24th 2013
 * File       : Bil244_101044009_midterm_SERVER.c
 *
 * Description: 
 *          Gets orders from clients that connected. 
 *          It works with find,list,time,kill and exit or q
 *           
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc -c pipeclient.c
 *  $ gcc pipeclient.o -o pipeclient
 *  $ ./pipeclient fifoname
 *
 *********************************************************
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <termios.h>
#include <time.h>


#define FIFOARG 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)
#define BLKSIZE 256
#define MILLION 1000L
#define FLSIZE 10000

int serveToClient(char *PID);
static void signalCatch(int sigNum);

static int numOfDirectories=0 ; //Calculates number of dir for part with no fork
static volatile sig_atomic_t doneFlag =0;
int counterForDir =0 ;
int getClientPID;
char serverToClient[10] = "clientPID";
char clientPID[BLKSIZE] ;
char logFileName[BLKSIZE] = "SERVER_LogFile.log";
char lofFilestr[BLKSIZE][BLKSIZE];
FILE *logFile ;

int main (int argc, char *argv[]) 
{
  time_t currTime;
  int clientToServer, bytesread,numberOfClient=0,pidNo;   
  char buf[BLKSIZE] ;  
  struct sigaction act;
  act.sa_handler = signalCatch;
  act.sa_flags =0 ;

  //Building a logFile
   printf("LogFile built as\n");
   fprintf(stderr, "%s\n", logFileName );
   logFile = fopen(logFileName, "a");

   //Write to logFile the time that program started
   currTime = time(NULL);
   fprintf(logFile, "%s\n",logFileName);
   fprintf(logFile, "#######################################################\n");
   fprintf(logFile, "Server started at the time of %s\n", ctime(&currTime));
  
  //Handle ctrl-C signal
  if(sigaction(SIGINT,&act,NULL) == -1 || sigemptyset(&act.sa_mask) == -1)
    perror("Failed to set SIGINT to handle ctrl-C");
  

  if (argc != 2) {    /* name of server fifo is passed on the command line */
    fprintf(stderr, "Usage: %s fifoname > logfile\n", argv[0]);
    return 1; 
  }
  /******************************************************************/
  printf("SERVER ON:\n");
  /* create a named pipe to handle incoming requests */
  if ((mkfifo(argv[FIFOARG], 0666) == -1) && (errno != EEXIST)) {
    perror("Server failed to create a FIFO");
    return 1; 
  }
  fprintf(logFile, "Server has built fifo..\n");
  /* open a read/write communication endpoint to the pipe */
  if ((clientToServer = open(argv[FIFOARG], O_RDWR)) == -1) {
    perror("Server failed to open its FIFO");
    return 1;
  }
  /******************************************************************/

   /* create a named pipe to handle incoming requests */
  if ((mkfifo(serverToClient, 0666) == -1) && (errno != EEXIST)) {
    perror("Server failed to create a FIFO for signal");
    return 0; 
  }

  //Open the file to get the client pid
   if ((getClientPID = open(serverToClient, O_RDWR)) == -1) {
       perror("Server failed to open logSignal fifo for writing");
       return 0;
   }

   /******************************************************************/
   printf("*********\n");


  while(!doneFlag)
  {
    read(clientToServer, buf, BLKSIZE);

    if(strcmp(buf,"IamClient")==0)
    {
      
      if(read(getClientPID, clientPID, BLKSIZE) == -1)
        perror("Cannot get client PID");
      fprintf(logFile, "[%s]A client has connected..\n",clientPID);

      numberOfClient++;
      printf("%d.[%s] Client Connected\n",numberOfClient,clientPID);
      pidNo = fork();
      if(pidNo == 0)
      {
        serveToClient(clientPID);
        return 0 ;
      }
        
    }

    if(strcmp(buf,"clientLeave") == 0){
      printf("1 Client Leaved\n");
      numberOfClient--;
      printf("Client Left : %d\n",numberOfClient );
      fprintf(logFile, "A client has leaved..\n");
    }
    
    if(numberOfClient ==0)
    {
      fprintf(logFile, "There is no connected client. Server is terminating..\n");
      break;
    }
    
    //clean the string
    memset(buf, 0, sizeof(buf));

  }
  //Write to logFile the time that program started
  currTime = time(NULL);
  fprintf(logFile, "%s\n",logFileName);
  fprintf(logFile, "Server ended at the time of %s\n", ctime(&currTime));
  fprintf(logFile, "#######################################################\n");
  //wait();
  printf("SERVER OFF:\n");
  char tmp[20];
  sprintf(tmp,"%sClientFifo",clientPID);
  unlink(tmp);
  fclose(logFile);
  unlink(argv[FIFOARG]);
  unlink("clientPID");
  return 1; 
}


//Serves to client .acceps find,list,time,kill and quit
int serveToClient(char *PID)
{
  char fifoName[BLKSIZE], bufz[BLKSIZE];
  int serveToClient;
  FILE *logFilefork;
  char forkName[BLKSIZE] = "SERVER_LogFileFork.log";
  char logFileName[BLKSIZE] = "SERVER_LogFile.log";
  

  printf("  [%d]I am ready to serve client\n",getpid());
  sprintf(fifoName,"%sClientFifo",PID);
  logFilefork=fopen(forkName,"a");
  fprintf(logFilefork, "A child [%d] has built by server to serve client..\nCreated fifo name : %s..\n",getpid(),fifoName);
  fclose(logFilefork);
  /******************************************************************/
  /* create a named pipe to handle incoming requests */
  if ((mkfifo(fifoName, 0666) == -1) && (errno != EEXIST)) {
    perror("Server failed to create a FIFO");
    return 1; 
  }
  printf("  [%d]Fifo has built\n",getpid());
  /* open a read/write communication endpoint to the pipe */
  if ((serveToClient = open(fifoName, O_RDWR)) == -1) {
    perror("Server failed to open its FIFO");
    return 1;
  }


  /******************************************************************/
  
  printf("  [%d]Fifo has opened\n  Waiting for orders..\n",getpid());
  
  //Fill directory name in array as string
  char listDirName[FLSIZE][100];
  int i ,numberOfTarget=0;
  char search[20];
  int len;

  while(1) //Waiting for orders from client
  {
    FILE *logFilefork=fopen(forkName,"a");
    read(serveToClient,bufz,BLKSIZE);

    if(strcmp(bufz,"")     != 0 && 
       strcmp(bufz,"find") != 0 && 
       strcmp(bufz,"list") != 0 &&
       strcmp(bufz,"time") != 0 &&
       strcmp(bufz,"kill") != 0 &&
       strcmp(bufz,"exit") != 0 &&
       !isdirectory(bufz))
    {
      char temp[20];
      printf("\"%s\" is not an order..\n",bufz );
    }

    if(isdirectory(bufz))
    {
      fprintf(logFilefork, "[%d]DIR received from client : %s ..\n",getpid(),bufz);
      printf("DIR from client : %s\n",bufz );
      searchDirectory(bufz,listDirName);
    }
    
    //Find the target wanted by client
    if(strcmp(bufz,"find")==0)
    {
      
      sleep(1);
      printf("Target is being searched..\n");
      read(serveToClient,search,20);
      
      printf("Search : %s\n",search );

      for (i = 0; i < FLSIZE; ++i)
        if(strcmp(search,listDirName[i]) == 0)
          numberOfTarget++;
      printf("Number of target found : %d\n", numberOfTarget);
      printf("*********************************\n");
      fprintf(logFilefork, "[%d]I have searched for \"%s\"..\n",getpid(),search);
      memset(search, 0, sizeof(search));
      numberOfTarget =0 ;
    }



    

    //find the target and shows running time
    if(strcmp(bufz,"time")==0)
    {
      long timedif;
      struct timeval tpend;
      struct timeval tpstart;

      if (gettimeofday(&tpstart, NULL)) {
        fprintf(stderr, "Failed to get start time\n");
        return 1;
     }
      sleep(1);
      printf("Target is being searched..\n");
      read(serveToClient,search,20);

      printf("Search : %s\n",search );

      for (i = 0; i < FLSIZE; ++i)
        if(strcmp(search,listDirName[i]) == 0)
          numberOfTarget++;
      printf("Number of target found : %d\n", numberOfTarget);

      //Get the time that program worked in nanoseconds
     if (gettimeofday(&tpend, NULL)) {
        fprintf(stderr, "Failed to get end time\n");
        return 1;
     }
        timedif = MILLION*(tpend.tv_sec - tpstart.tv_sec) +
                                   tpend.tv_usec - tpstart.tv_usec;
     printf("Search took %ld*10^(-6) nanoseconds to find the target\n", timedif);
     fprintf(logFilefork, "[%d]I have searched and listed \"%s\" in %ld*10^(-6) nanoseconds..\n",getpid(),search,timedif);
     printf("*********************************\n");


      memset(search, 0, sizeof(search));
      numberOfTarget =0 ;
    }

    //List the target wanted by client
    if(strcmp(bufz,"list")==0)
    {
      sleep(1);
      printf("Target is being searched..\n");
      read(serveToClient,search,20);

      printf("List : %s\n\n",search );

      for (i = 0; i < FLSIZE; ++i)
        if(strcmp(search,listDirName[i]) == 0)
        {
          numberOfTarget++;
          printf("%d. Line : %s\n",i,search );
        }
          
      printf("Number of target found : %d\n", numberOfTarget);
      fprintf(logFilefork, "[%d]I have listed all \"%s\" in directory..\n",getpid(),search);
      memset(search, 0, sizeof(search));
      numberOfTarget =0 ;
      printf("*********************************\n");
    }
    //kill the desired target
    if(strcmp(bufz,"kill")==0)
    {
      
      sleep(1);
      printf("Target is being killed..\n");
      read(serveToClient,search,20);

      printf("[%d]killed : %s\n\n",getpid(),search );
      fprintf(logFilefork, "[%d]I have killed [%d]..\n",getpid(),getpid());
      if(kill(getpid(),SIGTERM) == -1)
        perror("Failed to kill child");
      printf("***This will not be printed..***\n");
      memset(search, 0, sizeof(search));
      printf("*********************************\n");
    }
    fclose(logFilefork);
    memset(bufz, 0, sizeof(bufz));
  }


}


//Catch ctrl-C signal
static void signalCatch(int sigNum)
{

  int len,getClientPID,clientPid ;
  char requestbuf[BLKSIZE] = "killYourParent", buf[BLKSIZE];
  FILE *logFile = fopen("SERVER_LogFile.log", "a");
  printf("ctrl-C catched %d\n",sigNum );
  fprintf(logFile, "I have got a kill signal %d..\n",sigNum);
  fclose(logFile);
  doneFlag = 1;
}

//Check whether the string is a path or not
int isdirectory(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      return 0;
   else
      return S_ISDIR(statbuf.st_mode);
}

//Search files subfiles in current directory
int searchDirectory(char *currDir,char listDirName[FLSIZE][100]) 
{   
    struct dirent *direntp;
    DIR *dirp;
    char currentDir[250];

    if ((dirp = opendir(currDir)) == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0){
          strcpy(listDirName[counterForDir],direntp->d_name);
          counterForDir++;
        }

        if(direntp->d_type == DT_DIR) //Check whether it is derectory
        {       
            if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
            {
                numOfDirectories++;
                //Copies the path and searches in again
                sprintf(currentDir, "%s/%s", currDir, direntp->d_name);
                searchDirectory(currentDir,listDirName); /*Recursive Step*/ 
            }  
        }
    }
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;

    return 0;
}

