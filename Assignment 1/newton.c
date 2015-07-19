#include <stdio.h>
#include <math.h> /* Make sure to compile with -lm*/

void newtonNonRecursive(int x, double e);
void newtonRecursiveFirstCall(int x, double e);
void newtonRecursive(int x, double e, double a);

/* This function uses Newton's method of finding a square root
	and does so through a loop and not through recursion*/
void newtonNonRecursive(int x, double e)
{
	int i = 0;
	double a = 0;

	a = x/2;

	while (i < 1)
	{
		//Checks to see if the value of 'a' is close enough to 'e' yet.
		if (fabs(a*a - x) <= e) 
		{
			printf("a is:%f\n", a);
			i = 1;
		}
		//else gets a new 'a' value and loops again
		else
		{
			a = ((x/a + a)/2);
		}
	}

}

/*Need a starting value for a so this function is used once for that purpose.*/
void newtonRecursiveFirstCall(int x, double e)
{
	double a;

	a = x/2;

	if (fabs(a*a - x) <= e) 
	{
		printf("a is:%f\n", a);
	}
	else
	{
		newtonRecursive(x, e, ((x/a + a)/2));
	}

}

/*Finds the square root through Newton's method and does so recursively*/
void newtonRecursive(int x, double e, double a)
{
	if (fabs(a*a - x) <= e) 
	{
		printf("a is:%f\n", a);
	}
	else
	{
		newtonRecursive(x, e, ((x/a + a)/2));
	}
}