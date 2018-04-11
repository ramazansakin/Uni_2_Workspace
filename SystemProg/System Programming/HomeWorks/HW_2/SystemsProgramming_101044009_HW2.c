/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : April 2th 2013
 * File       : BIL244_101044009_HW#2.c
 *
 * Description of Part1 : 
 *          The Program searches the files in current directory. 
 *          If It accrosses a directory, It gets in and again searches
 *          for files except the current '.' and the previous '..' directory.
 *          And then prints the path and directories names.
 *
 * Description of Part2 :
 *          This part is designed on processes.The same results like in part1
 *          But the difference is that child only creates process and parent
 *          prints the directories names & files names.
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc -c system.c
 *  $ gcc system.o -o system
 *  $ ./system
 *
 *********************************************************
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

static int numOfDirectoriesFork=0 ; //Calculates number of dir for the part with fork
static int numOfDirectories=0 ; //Calculates number of dir for part with no fork
pid_t pid ; //Process PID
int main(int argc, char const *argv[])
{
    
    char currDir[250]; //Current Directory Name
    int selection ;

    printf("For -ls No Fork()   : 1\n");
    printf("For -ls with Fork() : 2\n");
    printf("Your Selection : ");
    scanf("%d",&selection);
    
    /*The part with no Fork*/
    if(selection ==1)
    {
        printf("\n########################################\n");
        printf("Please Give the Path : ");
        scanf("%s",currDir);
        if (currDir == NULL) 
        {
            perror("Failed to get current working directory");
            return 0;
        }
        printf("\n\nCurrent Directory : %s\n",currDir );
        searchDirectoryNoFork(currDir);
        printf("-----------------------------------------------\n");
        printf("Number Of Directories (Except '.' and '..') : %d\n",numOfDirectories );
        printf("########################################\n\n");
    }

    /*The part with fork*/
    else if(selection == 2)
    {
        printf("\n########################################\n");
        printf("Please Give the Path : ");
        scanf("%s",currDir);
        if (currDir == NULL) 
        {
            perror("Failed to get current working directory");
            return 1;
        }
        searchDirectoryFork(currDir);
        
        if(pid != 0)
        {
            printf("Number Of Directories (Except '.' and '..') : %d\n",numOfDirectoriesFork );
            printf("########################################\n\n");
        }
        wait(NULL); // Wait for child process
    }
    else
        printf("###Your Choice Must be 1 or 2 ###\n");
    
    return 0;
}

/*Searches files and directories with no fork*/
int searchDirectoryNoFork(char *currDir) 
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
                searchDirectoryNoFork(currentDir); /*Recursive Step*/ 
            }  
        }
    }
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;

    return 0;
}

/*Searches files and directories with fork*/
int searchDirectoryFork(char *currDir) 
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
        /*Only Parent can print the results*/
        if(strcmp(direntp->d_name,".") !=0  
            && strcmp(direntp->d_name,"..") != 0 && pid !=0)
            printf("PID %d PPID %d : %s\n",getpid(),getppid(), direntp->d_name);
        
        if(direntp->d_type == DT_DIR )
        {
            /*Only child can make process*/
            if(strcmp(direntp->d_name,".") !=0  
                && strcmp(direntp->d_name,"..") != 0 && pid == 0)
            {
                pid = fork();   
                numOfDirectoriesFork++;
                //Copies the path and searches in again
                sprintf(currentDir, "%s/%s", currDir, direntp->d_name);
                if(pid != 0)
                    printf("current Directory : %s\n", currentDir);
                searchDirectoryFork(currentDir); /*Recursive Step*/
            }  
        }   
    }
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;

    return 0;
}
