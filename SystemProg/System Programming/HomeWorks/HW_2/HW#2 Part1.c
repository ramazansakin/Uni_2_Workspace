#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
static int numOfDirectories=0 ;
int main(int argc, char const *argv[])
{

    char currDir[250];
    printf("\n\n\n########################################\n");
    //chdir("/home/sabri/Desktop/Test");
    getcwd(currDir,250);
    foo(currDir);
    printf("Number Of Directories (Except '.' and '..') : %d\n",numOfDirectories );
    printf("########################################\n\n");

    return 0;
}

int foo(char *currDir) 
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
            printf("PID %d : %s\n",getpid(), direntp->d_name);
        if(direntp->d_type == DT_DIR)
        {
            
            if(strcmp(direntp->d_name,".") !=0  && strcmp(direntp->d_name,"..") != 0)
            {
                numOfDirectories++;
                //Copies the path and searches in again
                sprintf(currentDir, "%s/%s", currDir, direntp->d_name);
                printf("current Directory : %s\n", currentDir);
                foo(currentDir);  
            }  
        }
    }
    while ((closedir(dirp) == -1) && (errno == EINTR)) ;

    return 0;
}
