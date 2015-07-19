/*    Name: Cameron Thompson
        ID: 0839150
      Date: November 3rd, 2014
Assignment: Assignment 3         */

****Q1****
******************Purpose***********************
This program will take a fully parenthesized
mathematical expression and turn it into a heap.
This heap can later be edited and reprinted multiple ways.
*********** How to Run The Program *************
First type "make"

The program requires  2 command line arguments.
"./q1" and a mathematical expression. 

After you enter command line arguments 
the program will then come to a menu loop.
You will then input the single digit number
associated with the action you wish to take.
*************** Limitations ********************
The mathematical expression MUST be to the
following standards for the program to run:
	Fully parenthasized
	No unknown characters (spaces, comas ETC.)
	Variables in the form "xX" where X is a single digit.
	Numbers in the form "0.00"

You will be able to cause issues if after you choose 
option 5 (update) from the menu loop and then do not
enter your selection in the form:
"xX, 0.00" where X is a single digit number.

Entering the Wrong Input for the Menu multiple times will send the menu into an infininte loop.

***************Sample Output******************
*This is after given the command line arguments
	'./q1 "(5.00+5.00)"'

Type a number between 1-7 to select its corresponding action.
1.Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit
*I gave the input "2"
2
+5.005.00
Type a number between 1-7 to select its corresponding action.
1.Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit
*I gave the input "7"
*Program Ended

****Q2****
******************Purpose***********************
This program will take a data file filled with a
20x10 array, turn it into a heap of 20 objects
and then sort that heap using the downHeap method.
*********** How to Run The Program *************
The program requires  no command line arguments.
You only need to type "make" and then type "./q2"

*************** Limitations ********************
The "f.dat" textfile must be set up in the following order:
	a 2 digit number followed by a space
	10 numbers per line with a newline character
	at the end of each line.

***************Sample Output******************
*This is using a slightly modified version of 
the example "f.dat" file.

16 14 27 99 29 99 79 45 59 19
12 0 68 68 49 68 74 32 9 30 
50 9 6 44 59 87 32 36 36 46
43 27 20 59 4 84 10 42 43 2
80 30 16 65 40 3 44 4 32 60
25 41 11 88 15 39 88 69 31 49
43 27 68 96 70 98 85 13 25 47
3 60 76 23 14 81 82 0 38 4
47 17 44 32 33 54 60 33 51 87
41 82 53 40 29 84 24 61 87 20
99 37 50 93 57 6 29 91 92 39
81 14 42 21 9 69 5 30 20 91
2 37 97 53 36 54 69 68 38 43
83 82 43 11 21 4 8 97 93 14
50 90 37 86 42 44 48 64 41 1
96 89 75 0 63 24 54 20 20 24
88 56 59 88 39 30 44 59 49 72
90 90 90 82 52 53 5 3 68 64
9 83 22 90 74 56 64 75 67 55
41 62 82 46 69 42 74 68 79 28

*Program Ended