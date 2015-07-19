/*    Name: Cameron Thompson
        ID: 0839150
      Date: October 10th, 2014
Assignment: Assignment 2         
  Question: Question 2      */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct Numbers{
	    float value;
	    struct Numbers* next;
	} Numbers;

Numbers* mathOperations(Numbers* theHead, char operation);

Numbers* makeNumber(Numbers* theHead, int newInt);

Numbers * addToFront(Numbers * theListHead, Numbers * toBeAdded);

Numbers* delete(Numbers* theHead);




int main( int argc, char *argv[])
{
	int i = 0;
	double tempDouble = 0;
	char character;

	Numbers* head;
	head = NULL;


	if (argc != 2)
	{
		printf("Cannot run file, there should only be 2 commandline arguments.");
	}


	while ( i < strlen(argv[1]))
	{
		character = argv[1][i];
		//if ((character == '0') || (character == '1') || (character == '2') || (character == '3') || (character == '4') || (character == '5') || (character == '6') || (character == '7') || (character == '8') || (character == '9'))
		if (isdigit(character))
		{
			tempDouble = argv[1][i] - '0';
			head = makeNumber(head, tempDouble);
		}
		else if ((character == '+') || (character == '-') || (character == '*') || (character == '/'))
		{
			head = mathOperations(head, character);
		}
		i++;
	}
	printf("%.2f", head->value);

	return(0);
}

Numbers* mathOperations(Numbers* theHead, char operation)
{
	double a = 0;
	double b = 0;

	a = theHead->value;
	b = theHead->next->value;

	if (operation == '+')
	{
		b = b + a;
	}
	else if (operation == '-')
	{
		b = b-a;
	}
	else if (operation == '*')
	{
		b = b * a;
	}
	else if (operation == '/')
	{
		b = b/a;
	}

	theHead = delete(theHead);

	theHead->value = b;

	return (theHead);
}

Numbers* makeNumber(Numbers* theHead, int newInt)
{
	Numbers* holding;

	holding = malloc(sizeof(struct Numbers));
    if (holding == NULL)
    {
        printf("out of memory: exiting upon keypress");
        getchar();
        exit(1);
    }
    holding->value = newInt;
    holding->next = theHead;
    return holding;
}

Numbers * addToFront(Numbers * theListHead, Numbers * toBeAdded)
{
    /*Has the new struct point to what the original head pointed at */
    toBeAdded->next = theListHead;
    return (toBeAdded);
}

Numbers* delete(Numbers* theHead)
{
	Numbers* holding;

	holding = theHead->next;
	free(theHead);
	return(holding);
}