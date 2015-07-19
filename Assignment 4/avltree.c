/*    Name: Cameron Thompson
        ID: 0839150
      Date: November 23rd, 2014
Assignment: Assignment 4    */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
	struct node* leftChild;
	struct node* rightChild;
	char* word;
	int height;
	int frequency;
} node;

void printMenu();
void printBanner();

node* LLRotate(node* z);
node* RRRotate(node* z);
node* LRRotate(node* z);
node* RLRotate(node* z);

int search(node* current, char* term);
int findHeight(node* current);
int findSize(node* current);
void findAll(node* current, int number);
node* insert(char* word, node* current, int type);
node* createNode(char* word);
node* delete(char* word, node* current);
node* findReplacement(node* current);

int main()
{
	FILE* inputFile;
	int i = 0;
	int j =0;
	int number = 0;
	int userInput = 0;
	int resultHeight = 0;
	int resultSize = 0;
	//char* find = NULL;
	char find[401];
	char buf[1001];
	char garbage[401];
	char* stringFile;
	char* insertWord;
	int numberOfWords = 0;
	char space;

	node* head = NULL;

	

	printBanner();

	/*Looping the menu until quitting*/
	while (i != 7)
	{
		printMenu();
		scanf("%d", &userInput);
		if (userInput == 1)
		{
			printf("filename: ");
			stringFile = malloc(sizeof(char)*50);
			scanf("%s", stringFile);
			inputFile = fopen(stringFile, "r");
		    if (inputFile != NULL)
		    {
		    	j=0;
		        /*Loops until fgets doesn't get anything more*/
		        while ((fgets(buf,1001, inputFile)!=NULL))
		        {
		        	numberOfWords = 0;
		        	//Making sure the line isn't just blank.
		        	if (buf[0] != '\n')
		        	{
		        		//Just a whole bunch of stuff to make sure all the input is proper
		        		//and formatted correctly etc, etc.

		        		j = 0;
			        	space = buf[j];
			        	while(space == ' ')
			        	{
			        		j++;
			        		space = buf[j];
			        	}
			        	
			        	numberOfWords = 0;

		        		while(space != '\0')
			        	{
			        		if((space == ' ') && (buf[j+1] != ' ') && (buf[j+1] != '\0') && (buf[j+1] != '\n'))
			        		{
			        			numberOfWords++;
			        		}
			        		if (space == '\n')
			        			buf[j] = '\0';
			        		j++;
			        		space = buf[j];
			        	}
			        	//Tokenize the input line of the file based on spaces
			        	insertWord = strtok(buf, " ");
			        	//Insert the word into the list
			        	head = insert(insertWord, head, 0);
			        	j = 0;
			        	//Loops until the string is tokenized, inserting it each time.
			            while(j < (numberOfWords))
			            {
			                insertWord = strtok(NULL, " ");
			                if (strlen(insertWord) > 0)
			                {
								head = insert(insertWord, head, 0);
			                }
			        		j++;
			            }
		        	}
		        }
		    }
		    else
		    {
		    	printf("File not found, now exiting");
		        exit(0);
		    }
		    fclose(inputFile);
		    free(stringFile);
		}
		else if (userInput == 2)
		{
			//Takes user input of a key to find, then goes to find it
			printf("find key: ");
			scanf("%s", find);
			//If the key is not found it informs the user
			if (search(head, find) == 0)
			{
				printf("no_such_key\n");
			}
		}
		else if (userInput == 3)
		{
			//Takes a key from the user and inserts it into the tree
			printf("insert key: ");
			scanf("%s", find);
			head = insert(find, head, 1);
		}
		else if (userInput == 4)
		{
			//Removes the specified key from the tree
			//if it is found inside the key
			printf("remove key: ");
			scanf("%s", find);
			head = delete(find, head);
		}
		else if (userInput == 5)
		{
			//Finds height and number of nodes of the tree
			resultHeight = findHeight(head);
			resultSize = findSize(head);
			printf("height: %d, size: %d\n", resultHeight, resultSize);
		}
		else if (userInput == 6)
		{
			//Shows all nodes with >= given frequency
			printf("frequency: ");
			scanf("%d", &number);
			findAll(head, number);
		}
		//exit
		else if (userInput == 7)
		{
			exit(0);
		}
		//small amount of user proofing
		else
		{
			printf("Bad input, try again\n");
			scanf("%s", &garbage[0]);
		}
	}
	return (0);
}

/*Printing banner at the start of the program with name
and student number.*/
void printBanner()
{
	printf("****************************************************\n");
	printf("*	Cameron Thompson	0839150		   *\n");
	printf("*       Welcome to the avl tree program            *\n");
	printf("****************************************************\n");
}

/*Prints out the menu each time the menu loops*/
void printMenu()
{
	printf("Type a number between 1-7 to select its corresponding action.\n");
	printf("1. Initialization\n");
	printf("2. Find\n");
	printf("3. Insert\n");
	printf("4. Remove\n");
	printf("5. Check Height and Size\n");
	printf("6. Find All (above a given frequency)\n");
	printf("7. Exit\n");
	printf("avl/> ");
}

/*Balances the tree if it is left left weighted*/
node* LLRotate(node* z)
{
	node* y = NULL;

	y = z->leftChild;
	z->leftChild = y->rightChild;
	y->rightChild = z;

	return(y);
}
/*Balances the tree if it is right right weighted*/
node* RRRotate(node* z)
{
	node* y = NULL;

	y = z->rightChild;
	z->rightChild = y->leftChild;
	y->leftChild = z;

	return(y);
}
/*Balances the tree if it is left right weighted*/
node* LRRotate(node* z)
{
	z->leftChild = RRRotate(z->leftChild);
	return(LLRotate(z));
}
/*Balances the tree if it is right left weighted*/
node* RLRotate(node* z)
{
	z->rightChild = LLRotate(z->rightChild);
	return(RRRotate(z));
}
/*Searches the tree from the head in alphabetical order
to find the term that is searched. If found it prints
the key and the frequency, else prints cant find the key*/
int search(node* current, char* term)
{
	if (strcmp(current->word, term) > 0)
	{
		if (current->leftChild == NULL)
		{
			return (0);
		}
		else
		{
			return (search(current->leftChild, term));
		}
	}
	else if (strcmp(current->word, term) == 0)
	{
		printf("key: %s, frequency: %d\n", current->word, current->frequency);
		return (1);
	}
	else if (strcmp(current->word, term) < 0)
	{
		if (current->rightChild == NULL)
		{
			return (0);
		}
		else
		{
			return (search(current->rightChild, term));
		}
	}
	return(0);
}
/*Finds height of the specified node by looking at the 
height of all the nodes below it*/
int findHeight(node* current)
{
	int leftHeight = 0;
	int rightHeight = 0;

	if (current == NULL)
		return(0);

	if (current->leftChild != NULL)
	{
		leftHeight = findHeight(current->leftChild);
	}
	
	if (current->rightChild != NULL)
	{
		rightHeight = findHeight(current->rightChild);
	}
	
	if ((current->leftChild == NULL) && (current->rightChild == NULL))
	{
		return (0);
	}

	if (leftHeight > rightHeight)
	{
		return (leftHeight + 1);
	}
	else
	{
		return (rightHeight + 1);
	}
}
/*Finds number of nodes in the tree*/
int findSize(node* current)
{
	int size = 0;

	if (current->leftChild != NULL)
	{
		size = findSize(current->leftChild);
	}
	
	if (current->rightChild != NULL)
	{
		size = size + findSize(current->rightChild);
	}
	
	if ((current->leftChild == NULL) && (current->rightChild == NULL))
	{
		return (1);
	}

	return(size + 1);
}
/*Finds all nodes that have >= a given frequency*/
void findAll(node* current, int number)
{
	if (current->frequency >= number)
	{
		printf("key: %s, frequency: %d\n", current->word, current->frequency);
	}

	if (current->leftChild != NULL)
	{
		findAll(current->leftChild, number);
	}
	if (current->rightChild != NULL)
	{
		findAll(current->rightChild, number);
	}
}

/*Insert a node into the tree, and then balances the tree*/
node* insert(char* word, node* current, int type)
{
	if (current == NULL)
	{
		current = createNode(word);
		if (type == 1)
			printf("key: %s, frequency: %d\n", current->word, current->frequency);
	}
	else if(strcmp(word, current->word) == 0)
	{
		current->frequency++;
		if (type == 1)
			printf("key: %s, frequency: %d\n", current->word, current->frequency);
		return(current);
	}
	else if(strcmp(word, current->word) < 0)
	{
		current->leftChild = insert(word, current->leftChild, type);
		if (findHeight(current->leftChild) - findHeight(current->rightChild) == 2)
		{
			if (strcmp(word, current->leftChild->word) < 0)
			{
				current = LLRotate(current);
			}
			else
			{
				current = LRRotate(current);
			}
		}
	}
	else if(strcmp(word, current->word) > 0)
	{
		current->rightChild = insert(word, current->rightChild, type);
		if (findHeight(current->rightChild) - findHeight(current->leftChild) == 2)
		{
			if (strcmp(word, current->rightChild->word) > 0)
			{
				current = RRRotate(current);
			}
			else
			{
				current = RLRotate(current);
			}
		}
	}

	current->height = findHeight(current);
	return(current);
}
/*Creates a node struct and initializes its values*/
node* createNode(char* word)
{
	node* holding = NULL;

	holding = malloc(sizeof(struct node));
    if (holding == NULL)
    {
        printf("out of memory: exiting upon keypress");
        getchar();
        exit(1);
    }

    holding->word = malloc(sizeof(char)*50);
    strcpy(holding->word, word);
    holding->leftChild = holding->rightChild = NULL;
    holding->height = 0;
    holding->frequency = 1;

    return holding;
}
/*Takes the specified word and looks for it in the tree.
If the node is not found, then it tells you no such key exists
if it is found the frequency is reduced by 1. If the frequency
is now 0, then it removes the node from the tree. After removing,
it rebalances the tree.*/
node* delete(char* word, node* current)
{
	node* temp = NULL;

	if (current == NULL)
	{
		printf("no_such_key\n");
		return (current);
	}
	else if(strcmp(word, current->word) == 0)
	{
		if ((current->leftChild == NULL) && (current->rightChild == NULL))
		{
			current->frequency--;
			if (current->frequency == 0)
			{
				free(current);
				printf("key: %s, frequency: %d\n", word, 0);
				return(NULL);
			}
			printf("key: %s, frequency: %d\n", word, current->frequency);
			return(current);
		}
		else if (current->leftChild == NULL)
		{
			current->frequency--;
			if (current->frequency == 0)
			{
				temp = current;
				current = current->rightChild;
				printf("key: %s, frequency: %d\n", word, 0);
				free(temp);
				return(current);
			}
			printf("key: %s, frequency: %d\n", word, current->frequency);
			return(current);
		}
		else if (current->rightChild == NULL)
		{
			current->frequency--;
			if (current->frequency == 0)
			{
				temp = current;
				current = current->leftChild;
				printf("key: %s, frequency: %d\n", word, 0);
				free(temp);
				return(current);
			}
			printf("key: %s, frequency: %d\n", word, current->frequency);
			return(current);
		}
		else
		{
			temp = findReplacement(current->leftChild);
			temp->leftChild = current->leftChild;
			temp->rightChild = current->rightChild;
			free(current);
			return (temp);
		}
	}
	else if(strcmp(word, current->word) < 0)
	{
		current->leftChild = delete(word, current->leftChild);
		if (findHeight(current->leftChild) - findHeight(current->rightChild) == 2)
		{
			if (strcmp(word, current->leftChild->word) < 0)
			{
				current = LLRotate(current);
			}
			else
			{
				current = LRRotate(current);
			}
		}
	}
	else if(strcmp(word, current->word) > 0)
	{
		current->rightChild = delete(word, current->rightChild);
		if (findHeight(current->rightChild) - findHeight(current->leftChild) == 2)
		{
			if (strcmp(word, current->rightChild->word) > 0)
			{
				current = RRRotate(current);
			}
			else
			{
				current = RLRotate(current);
			}
		}
	}
	else
	{
		printf("no_such_key\n");
		return (NULL);
	}
	return(current);
}
/*Finds the replacement for a node that is to be deleted.*/
node* findReplacement(node* current)
{
	node* temp;
	if (current->rightChild != NULL)
	{
		if (current->rightChild->rightChild == NULL)
		{
			temp = current->rightChild;
			current->rightChild = current->rightChild->leftChild;
			return(temp);
		}
		else
		{
			return(findReplacement(current->rightChild));
		}
	}
	else
	{
		temp = current;
		current = current->leftChild;
		return(temp);
	}
}

/*int search(node* current, char* term)
{
	if (strcmp(current->word, term) == 0)
	{
		printf("key: %s, frequency: %d\n", current->word, current->frequency);
		return (1);
	}
	if (current->leftChild != NULL)
	{
		return (search(current->leftChild, term));
	}
	
	if (current->rightChild != NULL)
	{
		return (search(current->rightChild, term));
	}
	return(0);
}*/