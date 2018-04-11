/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : April 10th 2013
 * File       : BIL244_101044009_HW#3_Part2.c
 *
 * Description of Part2 : 
 *          The Program searches the files in current directory. 
 *          If It accrosses a directory, It gets in and again searches
 *          for files except the current '.' and the previous '..' directory.
 *          And then prints the path and directories names.
 *          Child Process writes the name of files in a fifo
 *          Parent Process reads the name of files from fifo and prints them.
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc -c system.c
 *  $ gcc system.o -o system
 *  $ ./system fifo
 *
 *********************************************************
 */


/*Library Declarations*/
#include <errno.h>
#include <fcntl.h>  
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

#define BUFSIZE 256
#define FIFO_PERM  (S_IRUSR | S_IWUSR)


//Finds all files and directories in a current directory
//Parent process reads files names
//Child Process writes files names
int searchForFiles(char *currDir,char *fifoName,int childpid) ;

//Calculates number of directories
static int numOfDirectories=0 ; 

//Test Function
int main (int argc, char *argv[]) {
  pid_t childpid; 
  int fd;

  //command line has pipe name
  if (argc != 2) {  
    fprintf(stderr, "Usage: %s pipename\n", argv[0]);
    return 1; 
  }

  //create a named pipe
  if (mkfifo(argv[1], FIFO_PERM) == -1) { 
    if (errno != EEXIST) {
      fprintf(stderr, "[%ld]:failed to create named pipe %s: %s\n", 
           (long)getpid(), argv[1], strerror(errno));
      return 1; 
    }
  }

  //open a read/write communication endpoint to the pipe
  if ((fd = open(argv[1], O_RDWR)) == -1) {
    perror("Server failed to open its FIFO");
    return 1;
  }
  
  //Make process
  if ((childpid = fork()) == -1){
    perror("Failed to fork");
    return 1;
  } 

  //Search Directories
  searchForFiles("/home/sabri/Desktop/Test",argv[1],childpid);
   
  if(childpid !=0) //Parent can print num of directories
    printf("\nNumber Of Directories : %d\n\n\n",numOfDirectories );

  wait(NULL);// Wait for child Process
}
 
    
//Finds all files and directories in a current directory
//Parent process reads files names
//Child Process writes files names
int searchForFiles(char *currDir,char *fifoName,int childpid) 
{   
    struct dirent *direntp;
    DIR *dirp;
    char currentDir[BUFSIZE];
    char name[BUFSIZE];

    //Open Directory
    int fd = open(fifoName,O_RDWR);


    if ((dirp = opendir(currDir)) == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0 && childpid ==0)
          write(fd, direntp->d_name, BUFSIZE);

        if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0 && childpid !=0){
          read(fd, name, BUFSIZE);
          printf("PID[%d] PPID[%d]: %s\n",getpid(),getppid(), name);
        }   

        //Do this if the file is directory
        if(direntp->d_type == DT_DIR)
        {
          //handle exception for current '.' and previous '..' directories
          if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
          {
            numOfDirectories++;
            //Copies the path and searches in again
            sprintf(currentDir, "%s/%s", currDir, direntp->d_name);
            printf("\nCurrent Directory : %s\n", currentDir);
            searchForFiles(currentDir,fifoName,childpid);  
          }  
        }
    }

    //Close directory
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;

    return 0;
}
