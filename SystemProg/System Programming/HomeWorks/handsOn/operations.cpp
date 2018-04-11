
#include <cassert>
#include "operations.hpp"


/* function addTwoNumbers */
double addTwoNumbers (int i, int j) 
{
	return (0.0 + i + j);
}

/* function addTwoNumbers */
double multiplyTwoNumbers (int i, int j) 
{
	return 1.0*i*j;
}

/* function addTwoNumbers */
double divideTwoNumbers (int i, int j) 
{
  // j should be non-zero.
  assert (j != 0);

  return (i/j);
}

