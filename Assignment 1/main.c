/*    Name: Cameron Thompson
        ID: 0839150
      Date: September 29th, 2014
Assignment: Assignment 1         */
      
#include "carbon.c"
#include "newton.c"
#include "Ackermann.c"

#include <string.h>
#include <stdio.h>
#include <math.h>


int main()
{

	char prefix[7];
	char carbon[7] = "carbon";

	int input = 0;
	int i = 0;
	int x = 0;
	int m = 0;
	int n = 0;
	int ackermannReturn = 0;

	double e = 0;

	//loops until the user exits
	while (i < 1)
	{
		//Basic menu output
		printf("Please select which program you would like to run from the list by inputting the coresponding number:\n");
		printf("1. Carbon\n");
		printf("2. Ackermann\n");
		printf("3. Newton\n");
		printf("4. Exit\n");

		scanf("%d", &input);

		//Runs the specified program after recieving input
		if (input==1)
		{
			treeSplit(prefix, carbon);
		}
		else if (input == 2)
		{
			printf("Please input a value for m:");
			scanf("%d", &m);
			printf("Please input a value for n:");
			scanf("%d", &n);

			ackermannReturn = ackermannRecursive (m, n);
			printf("%d\n", ackermannReturn);

		}
		else if (input == 3)
		{
			printf("Choose between the two programs for Newton.\n");
			printf("1. Non-Recursive\n");
			printf("2. Recursive\n");

			scanf("%d", &input);

			printf("Please input a value for x:");
			scanf("%d", &x);
			printf("Please input a value for e:");
			scanf("%lf", &e);

			if (input==1)
			{
				newtonNonRecursive(x, e);
			}
			else if (input == 2)
			{

				newtonRecursiveFirstCall(x, e);
			}

		}
		else if (input == 4)
		{
			return (0);

		}
		else
		{
			printf("Please enter only numbers between 1 and 3.");
		}
	}

	return(0);
}