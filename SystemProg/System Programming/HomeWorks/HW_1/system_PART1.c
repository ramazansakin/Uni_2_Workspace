/*
 * Author : Sabri Mevis
 * ID     : 101044009
 * E-Mail : sabrimev@gmail.com
 * Date   : March 19th 2013
 * File   : system_HW01_Part1.c
 * 
 * Description : Searches and Prints the targets in file
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc -c system.c
 *  $ gcc system.o -o system
 *  $ ./system file.txt sabri ali veli ahmet ... etc.
 *
 *********************************************************
*/

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
  
  FILE *inp ;
  char str[100][15] ;
  int i=0,k=2,d=0,status=1, 
      numberOfTarget[100] ={0};

  inp = fopen(argv[1],"r") ; /*Open File*/

  /*Check whether file opened properly or not*/
  if (inp == NULL)
  {
    printf("\n#######################################################\n");
    printf("##|  ERROR.. CANNOT ACCESS FİLE                      ##\n");
    printf("##|  Make sure that the file name is like \"file.txt\" ##\n");
    printf("#######################################################\n\n");
    return 0 ;
  }

  /*Make sure that the target submitted*/
  if (argc ==2)
  {
    printf("\nWill you NOT search anything in file?\n\n");
    return 0 ;
  }

  /*Information about program*/
  printf("\n\n############################################################\n");
  printf("Running Program Name : \"%s\"\n",argv[0] );
  printf("The name of folder that cantains targets : \"%s\"\n\n",argv[1] );

  
  /*Find the targets given in file*/
  for (i = 0; status != EOF; ++i)
  {
    
    status = fscanf(inp,"%s",str[i]); /*Read in file*/

    for(k=2;k < argc;k++)             /*Find all the targets given*/
    {
      if(strcmp(str[i],argv[k]) ==0)  /*Compare strings*/
      {
        numberOfTarget[k] +=1;        /*Count targets in file*/ 
      } 
    } //end for
  } //end for

  /*Show Number of targets found*/
  for (k = 2; k < argc; k++)
  {
    printf("Number Of \"%s\" : %d  \n",argv[k],numberOfTarget[k] );
  }
  
  return 0;
}
