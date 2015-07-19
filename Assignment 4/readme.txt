/*    Name: Cameron Thompson
        ID: 0839150
      Date: November 23rd, 2014
Assignment: Assignment 4         */


******************Purpose***********************
This program will take input from a user specified data file
use these strings as keys and then create an avl with these keys.
From there you can before basic AVL tree commands.

*********** How to Run The Program *************
First type "make"

Then type "./avltree"

*************** Limitations ********************
The input string for reading each line of the file is 1001 
characters long. If the line is longer than that, it 
may affect the behavior of the program such as creating 
new words and nodes based on those words. If the size of
the tree isn't correct, this is probably the reason.

If you very strongly attempt to continously give bad input
on the menu loop, you will eventually cause the program
to run in an undesired way (skipping instructions, etc.).

If attempting to use menu options 2,5, or 6 before initialising 
the tree with data, the program will segmentation fault
and proceed to crash.

***************Sample Output******************
Sample output running the program with the Data
file provided on Moodle.


***************************************************
*		Cameron Thompson  0839150	  *
*	Welcome to the avl tree program		  *
***************************************************
Type a number between 1-7 to select its corresponding action.
1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 1
filename: A4_data_file.dat
Type a number between 1-7 to select its corresponding action.
1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 5
height: 12, size: 1483
Type a number between 1-7 to select its corresponding action.
1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 6
frequency: 4000
key: flr117, frequency: 7458
key: flr2910, frequency: 9790
key: flr549, frequency: 5590
Type a number between 1-7 to select its corresponding action.
1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
avl/> 7

Sample Output finished
***************Notes**************************
Command 5 on the menu gives the height and size.
I am assuming from the guideline that the size
is equal to the number of nodes, as this is 
what the guideline conveyed.