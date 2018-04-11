/***********************************************
* No more hands on !!!!!                       *
* You should study this stuff by yourselves    *
* EZ: 2012                                     *
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "operations.hpp"

int main (int argc, char **argv)
{
  int i,j,k;
 
   if (argc != 3)
   {
      printf("\n\nYour program name : \"%s\" \n",argv[0] );
      for(k =1 ; k< argc ; k++)
        printf("%d num: %s\n",k,argv[k] );
      printf("You have to write 3 arguments. Your arguments : %d\n",argc);
      printf ("Usage: 1: main  2: number1 3: number2 \n\n\n ");
      return 1;
   }
  
  i = atoi (argv[1]);
  j = atoi (argv[2]); 
  
   printf ("\n\nThe sum of two numbers %d and %d are %g\n", i, j, addTwoNumbers(i,j));
   printf ("When you multiply  %d and %d you get %g\n", i, j, multiplyTwoNumbers(i,j));
   printf ("and the result og %d divided by  %d is %g\n\n", i, j, divideTwoNumbers(i,j));
  
  return 0;
}
