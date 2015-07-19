#include <stdio.h>
#include <string.h>
#define STRINGLENGTH 7

void treeSplit(char prefix[STRINGLENGTH], char remaining[STRINGLENGTH]);

void treeSplit( char prefix[STRINGLENGTH], char remaining[STRINGLENGTH])
{
	int i = 0;
	int j =0;
	char holdingString[STRINGLENGTH];
	char tempRemaining[STRINGLENGTH] = "carbon";

	//If remaining is 1 character long, then it is at the end of the tree and prints
	if (strlen(remaining) == 1)
	{
		printf("%s%s\n", prefix, remaining);
	}
	else
	{
		i = 0;
		//Runs while i < the layer of the tree being looked at
		while (i <= strlen(tempRemaining))
		{
			//Making sure to save prefix before editing it
			strcpy(holdingString, prefix);
			j = strlen(holdingString);

			//Moves the null character in holdingString over 1 and then copies in the next character into the spot.
			holdingString[(j+1)] = holdingString[j];
			holdingString[j] = remaining[i];

			strcpy(tempRemaining, remaining);
			j = i;

			//taking the used character out of the string of remaining characters.
			while (j < (strlen(tempRemaining)))
			{
				tempRemaining[j] = tempRemaining[j+1];
				j++;
			}
			//calls the function again and continues down the tree.
			treeSplit(holdingString, tempRemaining);
			i++;
		}
	}

}