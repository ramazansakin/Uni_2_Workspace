#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "restart.h"
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <termios.h>


#define FIFOARG 1
#define FIFO_PERMS (S_IRWXU | S_IWGRP| S_IWOTH)
#define BLKSIZE 256

int serveToClient(char *PID);
static void signalCatch(int sigNum);

static int numOfDirectories=0 ; //Calculates number of dir for part with no fork
static volatile sig_atomic_t doneFlag =0;
int counterForDir =0 ;
int getClientPID;
char serverToClient[10] = "clientPID";
char clientPID[BLKSIZE] ;

int main (int argc, char *argv[]) 
{
  int clientToServer, bytesread,numberOfClient=0,pidNo;   
  char buf[BLKSIZE] ;  
  struct sigaction act;
  act.sa_handler = signalCatch;
  act.sa_flags =0 ;
  
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

  //Open the file to get the signal from server
   if ((getClientPID = open(serverToClient, O_RDWR)) == -1) {
       perror("Server failed to open logSignal fifo for writing");
       return 0;
   }

   /******************************************************************/
   printf("*********\n");



  while(!doneFlag)
  {
    read(clientToServer, buf, BLKSIZE);

    if(isdirectory(buf))
      searchDirectory(buf);

    if(strcmp(buf,"IamClient")==0)
    {
      if(read(getClientPID, clientPID, BLKSIZE) == -1)
        perror("Cannot get client PID");

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
    }
    
    if(numberOfClient ==0)
      break;

    if (strcmp("",buf)!=0 && strcmp(buf,"IamClient") !=0 && strcmp(buf,"clientLeave")!=0)
    {
      printf("\n***************\n");
      printf("Received: %s\n", buf);
      printf("***************\n");
    }

     

    memset(buf, 0, sizeof(buf));
 
   
  }
  printf("SERVER OFF:\n");

  unlink(argv[FIFOARG]);
  unlink("clientPID");
  return 1; 
}


//Serves to client .acceps find,list,time,kill and quit
int serveToClient(char *PID)
{
  char fifoName[BLKSIZE], bufz[BLKSIZE];
  int serveToClient;
  printf("  [%d]I am ready to serve client\n",getpid());
  sprintf(fifoName,"%sClientFifo",PID);

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
  

  /******************************************************************/

  printf("  [%d]Fifo has opened\n  Waiting for orders..\n",getpid());
  
  //Fill directory name in array as string
  char listDirName[1250][100];
  int i ,numberOfTarget=0;


  while(1) //Waiting for orders from client
  {
    read(serveToClient,bufz,BLKSIZE);

    if(isdirectory(bufz))
    {
      printf("DIR from client : %s\n",bufz );
      searchDirectory(bufz,listDirName);
    }
    
    //Find the target wanted by client
    if(strcmp(bufz,"find")==0)
    {
      char search[20];
      sleep(1);
      printf("Target is being searched..\n");
      read(serveToClient,search,20);

      printf("Search : %s\n",search );

      for (i = 0; i < 1250; ++i)
        if(strcmp(search,listDirName[i]) == 0)
          numberOfTarget++;
      printf("Number of target found : %d\n", numberOfTarget);
      memset(search, 0, sizeof(search));
      numberOfTarget =0 ;
    }
  
    if(strcmp(bufz,"heldlo") == 0)
    {
      printf("Its ok\n");
      return 0 ;
    }

    memset(bufz, 0, sizeof(bufz));


  }

}



static void signalCatch(int sigNum)
{
  int len,getClientPID,clientPid ;
  char requestbuf[BLKSIZE] = "killYourParent", buf[BLKSIZE];
  printf("ctrl-C catched %d\n",sigNum );


  doneFlag = 1;
}


int isdirectory(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      return 0;
   else
      return S_ISDIR(statbuf.st_mode);
}


int searchDirectory(char *currDir,char listDirName[1250][100]) 
{   
    struct dirent *direntp;
    DIR *dirp;
    char currentDir[250];

    if ((dirp = opendir(currDir)) == NULL) 
    {
        perror("Failed to open directory");
        return 1;
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0){
          //printf("PID %d\t  : %s\n",getpid(), direntp->d_name);
          //sprintf(listDirName[counterForDir][100],"%s",direntp->d_name);
          strcpy(listDirName[counterForDir],direntp->d_name);
          counterForDir++;
        }
            

        if(direntp->d_type == DT_DIR)
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

