/*    Name: Cameron Thompson
        ID: 0839150
      Date: November 3rd, 2014
Assignment: Assignment 3         
  Question: Question 2      */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Compares the nodes of the tree using downHeap to turn it into a true heap
void downHeap(int *heap, int start);

int main()
{
    FILE* inputFile;
    char buf[201];
    char* inputField;
    int i = 0;
    int j = 0;
    int k = 0;
    int temp = 0;
    int data[20][10];
    int keys[21];

    inputFile = fopen("g.dat", "r");
    if (inputFile != NULL)
    {
    	j=0;
        /*Loops until fgets doesn't get anything more*/
        while ((fgets(buf,201, inputFile)!=NULL))
        {
        	i = 0;
        	inputField = strtok(buf, " ");
        	data[j][i] = atoi(inputField);
            //printf("%d ",data[j][i]);
            for (i = 1; i < 10; i++)
            {
                inputField = strtok(NULL, " ");
            	data[j][i] = atoi(inputField);
            }
            j++;
            
        }
    }
    else
    {
        //exit(0);
    }
    fclose(inputFile);

    //Creates a 2nd array based on the keys to make it easier to downHeap
    i = 1;
    for (i = 1; i < 21; i++)
    {
    	keys[i] = data[(i-1)][0] + data[(i-1)][1] + data[(i-1)][2];
    }

    //Downheaps the list until sorted
    i = 10;
    while (i != 0)
    {
        downHeap(keys, i);
        i--;
    }

    i = 1;

    //Printing out the downHeaped 20x10 array
    for (i = 1; i < 21; i++)
    {
    	k = 0;
    	while (k < 20)
    	{
    		if (keys[i] == (data[k][0] + data[k][1] + data[k][2]))
    		{
    			temp = k;
    		}
    		k++;
    	}
    	j = 0;
    	while ( j < 10)
    	{
    		printf("%d ",data[temp][j]);
    		j++;
    	}
    	printf("\n");
    }

    return(0);
}

//Compares the nodes of the tree using downHeap to turn it into a true heap
void downHeap(int *heap, int start)
{
	int parent = heap[start];
	int leftChild = 0;
	int rightChild = 0;
	int temp = 0;

	if (start != 10)
	{
		leftChild = heap[(start*2)];
		rightChild = heap[((start*2) + 1)];
	}
	else 
	{
		leftChild = heap[(start*2)];
		rightChild = 300;
	}

	if (((leftChild < rightChild) && (rightChild < parent)) || ((leftChild < parent) && (parent < rightChild)))
	{
		temp = parent;
		heap[start] = leftChild;
		heap[(start*2)] = temp;

		if (start < 6)
		{
			temp = start*2;
			downHeap(heap, temp);
		}
	}

	else if (((rightChild < leftChild) && (leftChild < parent)) || ((rightChild < parent) && (parent < leftChild)))
	{
		temp = parent;
		heap[start] = rightChild;
		heap[((start*2) + 1)] = temp;

		if (start < 6)
		{
			temp = start*2+1;
			downHeap(heap, temp);
		}
	}

}