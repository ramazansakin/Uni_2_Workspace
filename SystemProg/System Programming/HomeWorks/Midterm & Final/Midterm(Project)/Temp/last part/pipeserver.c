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
static int numOfDirectories=0 ; //Calculates number of dir for part with no fork
static volatile sig_atomic_t doneFlag =0;

static void signalCatch(int sigNum);
int signalFile;
char serverToClient[10] = "clientPID";
char clientPID[BLKSIZE] ;

int main (int argc, char *argv[]) 
{
  int clientToServer, bytesread,numberOfClient=0;   
  char buf[BLKSIZE] ;  
  struct sigaction act;
  act.sa_handler = signalCatch;
  act.sa_flags =0 ;
  
  


  if(sigaction(SIGINT,&act,NULL) == -1 || sigemptyset(&act.sa_mask) == -1)
    perror("Failed to set SIGINT to handle ctrl-C");
  

  if (argc != 2) {    /* name of server fifo is passed on the command line */
    fprintf(stderr, "Usage: %s fifoname > logfile\n", argv[0]);
    return 1; 
  }

  printf("SERVER ON:\n");
  /* create a named pipe to handle incoming requests */
  if ((mkfifo(argv[FIFOARG], 0666) == -1) && (errno != EEXIST)) {
    perror("Server failed to create a FIFO");
    return 1; 
  }

   /* create a named pipe to handle incoming requests */
  if ((mkfifo(serverToClient, 0666) == -1) && (errno != EEXIST)) {
    perror("Server failed to create a FIFO for signal");
    return 0; 
  }

   
  /* open a read/write communication endpoint to the pipe */
  if ((clientToServer = open(argv[FIFOARG], O_RDWR)) == -1) {
    perror("Server failed to open its FIFO");
    return 1;
  }

  //Open the file to get the signal from server
   if ((signalFile = open(serverToClient, O_RDWR)) == -1) {
       perror("Server failed to open logSignal fifo for writing");
       return 0;
   }
   printf("*********\n");



  while(!doneFlag)
  {
    read(clientToServer, buf, BLKSIZE);
 


    if(isdirectory(buf))
      searchDirectory(buf);

    if(strcmp(buf,"IamClient")==0){
      if(read(signalFile, clientPID, BLKSIZE) == -1)
        perror("Cannot get client PID");
      showPID(clientPID);
      numberOfClient++;
      printf("%d.[%s] Client Connected\n",numberOfClient,clientPID);
    }

    if(strcmp(buf,"clientLeave")==0){
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

showPID(char *clientPID)
{
  printf("Client PID : %s\n", clientPID);
}

static void signalCatch(int sigNum)
{
  int len,signalFile,clientPid ;
  char requestbuf[BLKSIZE] = "killYourParent", buf[BLKSIZE];
  printf("ctrl-C catched %d\n",sigNum );
/*
  //Open the file to get the signal from server
   if ((signalFile = open(serverToClient, O_RDWR)) == -1) {
       perror("Client failed to open log fifo for writing");
       exit(1); 
   }


  if (read(signalFile, buf, BLKSIZE) ==-1) {
    perror("Client failed to write");
    exit(1);
  }

  clientPid = atoi(buf);
  printf("buf : %s\n",buf );
  
  if( kill(clientPid, SIGKILL ) == -1 )
    {
      perror("failed to terminate client");
      exit( 1 );
    }
*/

  doneFlag = 1;
}


int isdirectory(char *path) {
   struct stat statbuf;

   if (stat(path, &statbuf) == -1)
      return 0;
   else
      return S_ISDIR(statbuf.st_mode);
}


int searchDirectory(char *currDir) 
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
        if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
            printf("PID %d\t  : %s\n",getpid(), direntp->d_name);

        if(direntp->d_type == DT_DIR)
        {       
            if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
            {
                numOfDirectories++;
                //Copies the path and searches in again
                sprintf(currentDir, "%s/%s", currDir, direntp->d_name);
                printf("Current Directory : %s\n", currentDir);
                searchDirectory(currentDir); /*Recursive Step*/ 
            }  
        }
    }
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;

    return 0;
}

