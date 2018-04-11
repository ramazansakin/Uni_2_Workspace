/*
 * Lecture    : Systems Programming
 * Author     : Sabri Mevis
 * ID         : 101044009
 * Department : Computer Engineering
 * E-Mail     : sabrimev@gmail.com
 * Date       : April 8th 2013
 * File       : BIL244_101044009_HW#3_Part1.c
 *
 * Description of Part1 : 
 *          A form of more function in linux.If input char is enter,
 *          shows one line and if entered input is space shows
 *          four lines.
 *          
 *
 ************************************
 *
 * How to compile
 *
 *  $ gcc -c system.c
 *  $ gcc system.o -o system
 *  $ ./system -3 test.txt    OR  $ ./system test.txt
 *
 *********************************************************
 */

//Library Declaration
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>

//Take a character and accept it instantly
//Similar to the getch() function in windows
char myGetch();

int main(int argc, char *argv[]) {
    
    int  i = 0;
    char instantChar , *status;
    char tempStr[1024];

    FILE *requestfd;
    
    //Open File that will be displayed
    requestfd = fopen("test.txt", "r");

    //Check number of arguments
    if(argc > 3 || argc < 2) { 
      /* name of server fifo is passed on the command line */
      fprintf(stderr, "Usage: %s logfile\n", argv[0]);
      return 1; 
    }

    if(argc == 3){
      while(i > atoi(argv[1])) 
      {
          if(requestfd == NULL)
            perror("Error opening file");

          else 
          {
            status = fgets(tempStr, 1024, requestfd);
            if(status != NULL)
              fprintf(stderr,"%s", tempStr);

            else
              break;
          }
          i--;
        }
    }

    //Till the end of file
    while(status != NULL) 
    { 
      i = 0; //Reload

      //Get an instant character from the user
      instantChar = myGetch(); 

      //If the coming char is space
      if(instantChar == ' ')
        while(i < 4) 
        {
          if(requestfd == NULL)
            perror("Error opening file");

          else 
          {
            status = fgets(tempStr, 1024, requestfd);
            if(status != NULL)
              fprintf(stderr,"%s", tempStr);

            else
              break;
          }
          i++;
        }
      i = 0; //Reload

      //If the coming char is enter
      if(instantChar == '\n')
        while(i < 1) 
        {
          if(requestfd == NULL)
            perror("Error opening file");
          else 
          {
            status = fgets(tempStr, 100, requestfd);
            if(status != NULL)
              fprintf(stderr,"%s", tempStr);

            else
              break;
          }
          i++;
        }
    }

    //Close the open file
    fclose(requestfd);
    return 1;
}


//Take a character and accept it instantly
//Similar to the getch() function in windows
char myGetch() 
{
    char ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}



