/*    Name: Cameron Thompson
        ID: 0839150
      Date: November 3rd, 2014
Assignment: Assignment 3         
  Question: Question 1      */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
	    int type; //0 for numbers & variables, 1 for symbols
	    float value;
	    int parity;
	    int variableNumber;
	    char* print;

	    struct node* leftChild;
	    struct node* rightChild;
	    struct node* nextInStack;
	} node;

//Creates a new node to be used
node* createNode(int type, float value, int parity, int variableNumber, char* print);

//Pushes a node onto the top of a stack
node* push(node* theHead, node* toBeAdded);

//Pops the first node off of a stack.
node* pop(node* theHead);

void inOrderPrint(node* theHead);

//Prints all the contents of the tree in preorder.
void preOrderPrint(node* theHead);

//Prints all the contents of the tree in postorder.
void postOrderPrint(node* theHead);

//Prints the menu
void printMenu();

//Search the tree for the specified variable, then replaces it with the new value.
void search(node* theHead, int searched, float newValue);

//Calculates the value of the heap
float calculate(node* theHead);

//Print the heap in a visual format
void printTree(node* theHead, int indent);

int main( int argc, char *argv[])
{
	char buf[201];
	char garbage[201];
	char temp[5];
	char tempPrint[5];

	char userSearchInput[15];
	int newSearch = 0;
	float newSearchValue = 0;

	int i = 0;
	int length = 0;
	int userInput = 0;

	float calculation = 0.0;

	int tempType = 0;
	float tempValue = 0;
	int tempParity = 0;
	int tempVariableNumber = 0;


	struct node* symbolStruct = NULL;
	struct node* numberStruct = NULL;
	struct node* tempStructPointer;

	strcpy(buf, argv[1]);

	length = strlen(buf);

	//Goes through the entire mathematical expression
	while (i < length)
	{
		if (buf[i] == '(')
		{
			tempType = 0;
			tempValue = 0.0;
			tempParity = 0;
			tempVariableNumber = 0;
			tempPrint[0] = '\0';
		}
		else if (buf[i] == '+')
		{
			tempType = 0;
			tempValue = 0.0;
			tempParity = 1;
			tempVariableNumber = 0;
			tempPrint[0] = '+';
			tempPrint[1] = '\0';
		}
		else if (buf[i] == '-')
		{
			tempType = 0;
			tempValue = 0.0;
			tempParity = 1;
			tempVariableNumber = 0;
			tempPrint[0] = '-';
			tempPrint[1] = '\0';
		}
		else if (buf[i] == '*')
		{
			tempType = 0;
			tempValue = 0.0;
			tempParity = 2;
			tempVariableNumber = 0;
			tempPrint[0] = '*';
			tempPrint[1] = '\0';
		}
		else if (buf[i] == '/')
		{
			tempType = 0;
			tempValue = 0.0;
			tempParity = 2;
			tempVariableNumber = 0;
			tempPrint[0] = '/';
			tempPrint[1] = '\0';
		}
		else if (buf[i] == ')')
		{
			tempType = 0;
			tempValue = 0.0;
			tempParity = 3;
			tempVariableNumber = 0;
			tempPrint[0] = '\0';
		}
		else if (isdigit(buf[i]))
		{
			strncpy(temp, &buf[i], 4);
			temp[4] = '\0';

			tempType = 1;
			tempValue = atof(temp);
			tempParity = 0;
			tempVariableNumber = 0;
			strcpy(tempPrint, temp);

			i = i + 3;
		}
		else if (buf[i] == 'x')
		{
			temp[0] = buf[(i+1)];
			temp[1] = '\0';

			tempType = 1;
			tempValue = 0.0;
			tempParity = 0;
			tempVariableNumber = atoi(temp);
			tempPrint[0] = 'x';
			tempPrint[1] = temp[0];
			tempPrint[2] = '\0';

			i = i + 1;
		}

		//Create a new node with the set values
		tempStructPointer = createNode(tempType, tempValue, tempParity, tempVariableNumber, tempPrint);

		if (tempType == 0)
		{
			//Special case if a right bracket
			if (buf[i] == ')')
			{
				//Goes until the symbol struct is empty or until it finds a left bracket
				while ((symbolStruct != NULL) && (symbolStruct->parity != 0))
				{
					tempStructPointer = symbolStruct->nextInStack;
					//Makes first number on stack be right child of symbol
					symbolStruct->rightChild = numberStruct;
					//Takes that number off the stack
					numberStruct = pop(numberStruct);

					//Makes 2nd number on stack be left child of symbol
					symbolStruct->leftChild = numberStruct;
					//Takes that number off stack
					numberStruct = pop(numberStruct);

					//Pushes this new 3 part tree onto the numbers stack
					numberStruct = push(numberStruct, symbolStruct);
					//Removes the symbol from the stack
					symbolStruct = tempStructPointer;
				}
				symbolStruct = pop(symbolStruct);
				//symbolStruct = push(symbolStruct, tempStructPointer);
			}
			else if (buf[i] == '(')
			{
				symbolStruct = push(symbolStruct, tempStructPointer);
			}
			else if (symbolStruct == NULL)
			{
				symbolStruct = push(symbolStruct, tempStructPointer);
			}
			else if (tempStructPointer->parity <= symbolStruct->parity)
			{
				//Makes first number on stack be right child of symbol
				symbolStruct->rightChild = numberStruct;
				//Takes that number off the stack
				numberStruct = pop(numberStruct);

				//Makes 2nd number on stack be left child of symbol
				symbolStruct->leftChild = numberStruct;
				//Takes that number off stack
				numberStruct = pop(numberStruct);

				//Pushes this new 3 part tree onto the numbers stack
				numberStruct = push(numberStruct, symbolStruct);
				//Removes the symbol from the stack
				symbolStruct = pop(symbolStruct);

				symbolStruct = push(symbolStruct, tempStructPointer);
			}
			else if (tempStructPointer->parity > symbolStruct->parity)
			{
				symbolStruct = push(symbolStruct, tempStructPointer);
			}
		}
		else if (tempType == 1)
		{
			numberStruct = push(numberStruct, tempStructPointer);
		}

		i++;
	}

	//Simple Menu loop
	while (i != 7)
	{
		printMenu();
		scanf("%d", &userInput);
		if (userInput == 1)
		{
			printTree(numberStruct, 0);
		}
		else if (userInput == 2)
		{
			preOrderPrint(numberStruct);
			printf("\n");
		}
		else if (userInput == 3)
		{
			inOrderPrint(numberStruct);
			printf("\n");
		}
		else if (userInput == 4)
		{
			postOrderPrint(numberStruct);
			printf("\n");
		}
		else if (userInput == 5)
		{
			printf("Enter input in the form of 'variable_name, new_value'\n");
			printf("variable_name should be in the form of xX and new value should be in the form of #.##\n");
			fgets(userSearchInput, 14, stdin);
			fgets(userSearchInput, 14, stdin);
			temp[0] = userSearchInput[1];
			temp[1] = '\0';
			newSearch = atoi(temp);

			strncpy(temp, &userSearchInput[4], 4);
			temp[4] = '\0';
			newSearchValue = atof(temp);

			search(numberStruct, newSearch, newSearchValue);

		}
		else if (userInput == 6)
		{
			calculation = calculate(numberStruct);
			printf("%.2f", calculation);
		}
		else if (userInput == 7)
		{
			exit(0);
		}
		else
		{
			printf("Bad input, try again");
			scanf("%s", &garbage[0]);
		}
	}

	return (0);
}

node* createNode(int type, float value, int parity, int variableNumber, char* print)
{
	node* holding = NULL;

	holding = malloc(sizeof(struct node));
    if (holding == NULL)
    {
        printf("out of memory: exiting upon keypress");
        getchar();
        exit(1);
    }

    holding->print = malloc(sizeof(char)*6);

    holding->type = type;
    holding->value = value;
    holding->parity = parity;
    holding->variableNumber = variableNumber;
    strcpy(holding->print, print);
    holding->leftChild = NULL;
    holding->rightChild = NULL;
    holding->nextInStack = NULL;

    return holding;
}

node* push(node* theHead, node* toBeAdded)
{
	if (toBeAdded != NULL)
	{
	    /*Has the new struct point to what the original head pointed at */
	    toBeAdded->nextInStack = theHead;
	    return (toBeAdded);
	}
	return NULL;
}

node* pop(node* theHead)
{
	if (theHead != NULL)
	{
		node* temp = NULL;
		temp = theHead->nextInStack;
		return (temp);
	}
	return NULL;
}

//Traverse the Heap in order and prints the nodes
void inOrderPrint(node* theHead)
{
	if (theHead->type != 1)
	{
		printf("(");
		inOrderPrint(theHead->leftChild);
	}
	printf("%s",theHead->print);
	if (theHead->type != 1)
	{
		inOrderPrint(theHead->rightChild);
		printf(")");
	}
}

//Traverse the Heap preOrder and prints the nodes
void preOrderPrint(node* theHead)
{
	printf("%s",theHead->print);
	if (theHead->type != 1)
	{
		preOrderPrint(theHead->leftChild);
	}
	if (theHead->type != 1)
	{
		preOrderPrint(theHead->rightChild);
	}
}

//Traverse the Heap postOrder and prints the nodes
void postOrderPrint(node* theHead)
{
	if (theHead->type != 1)
	{
		postOrderPrint(theHead->leftChild);
	}
	if (theHead->type != 1)
	{
		postOrderPrint(theHead->rightChild);
	}
	printf("%s",theHead->print);
}

//Prints the User Menu
void printMenu()
{
	printf("Type a number between 1-7 to select its corresponding action.\n");
	printf("1. Display\n");
	printf("2. Preorder\n");
	printf("3. Inorder\n");
	printf("4. Postorder\n");
	printf("5. Update\n");
	printf("6. Calculate\n");
	printf("7. Exit\n");
}

//Searches for the specified variable and then replaces its value with the new value
void search(node* theHead, int searched, float newValue)
{
	if (theHead->type != 1)
	{
		search(theHead->leftChild, searched, newValue);
	}
	if (theHead->type != 1)
	{
		search(theHead->rightChild, searched, newValue);
	}

	if (theHead->type == 1)
	{
		if (theHead->variableNumber == searched)
		{
			theHead->value = newValue;
		}
	}

}

//Traverses the heap while calculating the value of the heap
float calculate(node* theHead)
{
	float leftValue = 0;
	float rightValue = 0;

	if (theHead->type != 1)
	{
		leftValue = calculate(theHead->leftChild);
	}
	if (theHead->type != 1)
	{
		rightValue = calculate(theHead->rightChild);
	}
	if (theHead->type == 1)
	{
		return(theHead->value);
	}

	if (theHead->print[0] == '+')
	{
		return (leftValue + rightValue);
	}
	else if (theHead->print[0] == '-')
	{
		return (leftValue - rightValue);
	}
	else if (theHead->print[0] == '*')
	{
		return (leftValue * rightValue);
	}
	else if (theHead->print[0] == '/')
	{
		if (rightValue != 0)
		{
			return (leftValue / rightValue);

		}
		else
		{
			printf("Division by zero, now exiting");
		}
	}
	return 0;
}

//Prints the Heap in a nice visual format
void printTree(node* theHead, int indent)
{
	int i = 0;
	if (theHead->type != 1)
	{
		printTree(theHead->rightChild, (indent+1));
	}
	
	i = 0;
	while (i < (indent-1))
	{
		printf("     ");
		i++;
	}
	while(i < indent)
	{
		printf("-----");
		i++;
	}
	if (theHead->type == 0)
	{
		printf("[%s]\n", theHead->print);
	}
	if (theHead->type == 1)
	{
		printf("[%.2f]\n", theHead->value);
	}
	if (theHead->type != 1)
	{
		printTree(theHead->leftChild, (indent + 1));
	}
}