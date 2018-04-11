/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : May 4th 2013
 * File       : Bil244_101044009_HW4.c
 *
 * Description: 
 *          Lists all files under directories and sub directories using pthread.
 *          Its a form of ls in unix.
 *			My Path : /home/sabri/Desktop/Test
 ************************************
 *
 * How to compile
 *
 *  $ gcc -system.c -lpthread
 *  $ ./a.out
 *
 *********************************************************
 */

/*Libraries*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <error.h>

/*Number of targets*/
static int numOfDirectories=0 ;
static int numOfFiles=0 ;

/*list all files under directories and sub directories*/
void *lsThread(void *currDir) ;

int main(int argc, char *argv[])
{
	/*Check whether the correct arguments has come*/
    if(argc != 2){
    	printf("Usage : ./a.out path\n");
    	return 0 ;
    }
    printf("\n\n\n########################################\n");
    lsThread(argv[1]);
    printf("\nNumber Of Directories (Except '.' and '..') : %d\n",numOfDirectories );
    printf("Number Of Files : %d\n",numOfFiles);
    printf("########################################\n\n\n");

    return 0;
}

/*list all files under directories and sub directories*/
void *lsThread(void *currDir) 
{   
    struct dirent *direntp;
    DIR *dirp;
    char currentDir[250];
    pthread_t thread ;
    int error; /*Thread built or not*/

    /*Open the directory given by user*/
    if ((dirp = opendir(currDir)) == NULL) 
    {
        perror("Failed to open directory");
        exit(1);
    }

    /*read all files in a directory*/
    while ((direntp = readdir(dirp)) != NULL)
    {
    	/*Print file names except . and .. directories*/
        if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
        {
        	numOfFiles++;
        	printf("%d. File : %s\n",numOfFiles, direntp->d_name);
        }
            
        if(direntp->d_type == DT_DIR) /*If its directory*/
        {
            if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
            {
                numOfDirectories++;
                //Copies the path and searches in again
                sprintf(currentDir, "%s/%s", (char *)currDir, direntp->d_name);
                printf("current Directory : %s\n", (char *)currentDir);
                
                /*Thread Creation*/
                if(error = pthread_create(&thread,NULL,lsThread,(char *)currentDir)){
                	fprintf(stderr, "Failed to build thread : %s\n",strerror(error) );
                } 
                /*Wait for the thread*/
                if(error = pthread_join(thread,NULL)){ 
                	fprintf(stderr, "Failed to join thread : %s\n",strerror(error) );
                } 
            }  
        }
    }
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;   
}
