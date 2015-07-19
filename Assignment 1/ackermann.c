/*    Name: Cameron Thompson
        ID: 0839150
      Date: September 29th, 2014
Assignment: Assignment 1         */

#include <stdio.h>

int ackermannRecursive (int m, int n);

/*Simple function containing all 3 parts of ackermann's function*/
int ackermannRecursive (int m, int n)
{
	if (m == 0)
	{
		return (n + 1);
	}
	else if (n == 0)
	{
		return ackermannRecursive(m-1, 1);
	}
	else
	{
		return ackermannRecursive((m-1), ackermannRecursive(m, (n-1)));
	}
}