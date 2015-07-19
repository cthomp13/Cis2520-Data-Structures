/*    Name: Cameron Thompson
        ID: 0839150
      Date: October 10th, 2014
Assignment: Assignment 2         
  Question: Question 1      */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct carInfo{
	    int mileage;
	    char * licensePlate;
	    int returnDate;
	    int type;

	    struct carInfo* next;
	} carInfo;

/*Creates a struct of type carInfo out of the given data. Then returns a pointer to that struck.*/
carInfo* createCar(carInfo* theHead, int newMileage, char * newLicensePlate, int newReturnDate, int newType);

/*Find the correct posistion for the data that is sent in the list of availible cars. Then uses the createCar
function to create a struct and place it in its sorted posistion.*/
carInfo* findPosistion(carInfo* theHead, int newMileage, char * newLicensePlate, int newReturnDate, int newType);

/*Adds the designated struct to the front of the designated list.*/
carInfo* addToFront(carInfo* theHead, carInfo* toBeAdded);

/*Adds to the back of the linked list.*/
carInfo* addToBack(carInfo* theHead, carInfo* toBeAdded);

/*Adds after a specified point in the struct.*/
void addAfter(carInfo* thisPosistion, carInfo* toBeAdded);

/*Searches the list to see if the designated license plate is in there,
and if so where in the struct.*/
carInfo* searchList(carInfo* theHead, char* searchedLicensePlate);

/*Removes the struck from the list so it can be added to a different one*/
carInfo* deleteFromList(carInfo* previous, carInfo* toBeDeleted);

/*Prints the entirety of the designated list*/
void printList(carInfo* theHead);

/*Calculates the difference between two dates in form yymmdd*/
int differenceInDate(int firstDate, int secondDate);

/*Sorts the rented list by order of return date.*/
carInfo* sortRentedList(carInfo* theHead);

int main( int argc, char *argv[])
{
    FILE* inputFile;
    char buf[201];
    char garbage[20];
    int i = 0;
    int tempMileage = 0;
    char * temp;
    char tempLicensePlate[201];
    int tempReturnDate = 0;
    int tempType = 0;
    char menuSelection;
    float rate = 0;
    int milesAdded = 0;
    float totalIncome = 0;

    carInfo* availibleHead = NULL;
    carInfo* rentedHead = NULL;
    carInfo* repairHead = NULL;
    carInfo* newCar = NULL;
    carInfo* holding = NULL;

    inputFile = fopen("cars.txt", "r");
    if (inputFile != NULL)
    {
        /*Loops until fgets doesn't get anything more*/
        while ((fgets(buf,201, inputFile)!=NULL))
        {
            if ( i == 0)
            {
            	tempMileage = atoi(buf);
            }
            else if (i == 1)
            {
            	strcpy(tempLicensePlate, buf);
            }
            else if (i == 2)
            {
            	tempReturnDate = atoi(buf);
            }
            else if (i == 3)
            {
            	tempType = atoi(buf);
            }
            
            i++;

            if (i == 4)
            {
                //The type of struct it is designates which list it will join.
                if (tempType == 0)
                {
                    availibleHead = findPosistion(availibleHead, tempMileage, tempLicensePlate, tempReturnDate, tempType);
                }
                else if (tempType == 1)
                {
                    newCar = createCar(repairHead, tempMileage, tempLicensePlate, tempReturnDate, tempType);
                    rentedHead = addToFront(rentedHead, newCar);
                }
                else if (tempType == 2)
                {
                    newCar = createCar(repairHead, tempMileage, tempLicensePlate, tempReturnDate, tempType);
                    repairHead = addToFront(repairHead, newCar);
                }
                i = 0;
            }
            
        }
    }
    else
    {
        exit(0);
    }
    fclose(inputFile);

    //After all data imported, sorts the rented cars list
    rentedHead = sortRentedList(rentedHead);

    i = 0;

    temp = malloc(sizeof(char)*9);

    while (i == 0)
    {
        printf("Select from the following list of options by inputting the corresponding number.\n");
        printf("1. Add a new car to the availible-for-rent list.\n");
        printf("2. Add a returned car to the availible-for-rent list.\n");
        printf("3. Add a returned car to the repair list.\n");
        printf("4. Transfer a car from the repair list to the availible-for-rent list.\n");
        printf("5. Rent the first availible car.\n");
        printf("6. Print all the lists.\n");
        printf("7. Exit. \n");
        printf("Please choose an option: ");
        menuSelection = fgetc(stdin);

        if (menuSelection == '1')
        {
            printf("PLease insert a mileage: ");
            scanf("%d", &tempMileage);
            printf("Please insert a license plate: ");
            scanf("%s", tempLicensePlate);
            strcat(tempLicensePlate, "\n");
            tempReturnDate = 000000;
            tempType = 0;

            //Creates a new struct to join the availible for rent list, and places it in posistion based on mileage.
            availibleHead = findPosistion(availibleHead, tempMileage, tempLicensePlate, tempReturnDate, tempType);

            printf("The new car has been added to the list of availible cars.\n");
        }
        else if (menuSelection == '2')
        {
            printf("PLease insert a mileage: ");
            scanf("%d", &tempMileage);
            printf("Please insert a license plate: ");
            scanf("%s", temp);

            //Finds where in the rented cars list the designated car is in, the deletes it from the list and returns a pointer to the deleted struct.
            holding = searchList(rentedHead, temp);

            if (holding == NULL)
            {
                printf("error finding that license plate, please try again.\n");
            }
            else
            {
                holding->type = 0;
                holding->returnDate = 0;
                availibleHead = findPosistion(availibleHead, tempMileage, holding->licensePlate, holding->returnDate, holding->type);

                rate = 40;
                milesAdded = tempMileage - holding->mileage - 100;
                if (milesAdded > 0)
                {
                    rate = rate + (milesAdded * .15);
                }
                printf("Your rate for that trip is: %.2f\n", rate);

                totalIncome = totalIncome + rate;

            }
            printf("The returned car has been added to the list of availible cars.\n");

        }
        else if (menuSelection == '3')
        {
            printf("PLease insert a mileage: ");
            scanf("%d", &tempMileage);
            printf("Please insert a license plate: ");
            scanf("%s", temp);

            //Finds where in the rented car list the car is, and deletes it from that list, then returns a pointer to that struct.
            holding = searchList(rentedHead, temp);

            if (holding == NULL)
            {
                printf("error finding that license plate, please try again.");
            }
            else
            {
                holding->type = 2;
                holding->returnDate = 0;
                addToFront(repairHead, holding);


                rate = 40;
                milesAdded = tempMileage - holding->mileage - 100;
                if (milesAdded > 0)
                {
                    rate = rate + (milesAdded * .15);
                }
                printf("Your rate for that trip is: %.2f\n", rate);

                totalIncome = totalIncome + rate;
            }
            printf("The returned car has been added to the cars under repair.\n");
        }
        else if (menuSelection == '4')
        {
            printf("Please insert a license plate: ");
            scanf("%s", temp);

            //Finds the car in the repair list, deletes it from that list and returns a pointer to that car.
            holding = searchList(repairHead, temp);

            if (holding == NULL)
            {
                printf("error finding that license plate, please try again.");
            }
            else
            {
                holding->type = 0;
                availibleHead = findPosistion(availibleHead, holding->mileage, holding->licensePlate, holding->returnDate, holding->type);
            }
            free(holding->licensePlate);
            free(holding);
            printf("The specified car has been added to the list of availible cars.\n");
        }
        else if (menuSelection == '5')
        {
            //Rents the car at the front of the availible linked list, and then updates information 
            //and changes which list the car belongs to.
            printf("You have rented a car with the following information:\n");
            printf("Mileage: %d\n", availibleHead->mileage);
            printf("License Plate: %s\n", availibleHead->licensePlate);
            printf("Please enter expected return date in form of 'yymmdd'\n");
            scanf("%d", &tempReturnDate);

            availibleHead->returnDate = tempReturnDate;
            availibleHead->type = 1;
            holding = availibleHead;
            availibleHead = holding->next;

            rentedHead = addToFront(rentedHead, holding);
            rentedHead = sortRentedList(rentedHead);

            fgets(garbage,20, inputFile);

            printf("The first availible car has been rented.\n");


        }
        else if (menuSelection == '6')
        {
            printList(availibleHead);
            printList(rentedHead);
            printList(repairHead);
        }
        else if (menuSelection == '7')
        {
            //Writing the values of all the lists to the file.
            inputFile = fopen("cars.txt", "w");
            if (inputFile != NULL)
            {
                i = 0;

                while (i < 3)
                {
                    if (i == 0)
                        holding = availibleHead;

                    if (i == 1)
                        holding = rentedHead;

                    if (i == 2)
                        holding = repairHead;

                    if (holding != NULL)
                    {
                        fprintf(inputFile, "%d\n", holding->mileage);
                        fprintf(inputFile, "%s", holding->licensePlate);
                        fprintf(inputFile, "%d\n", holding->returnDate);
                        fprintf(inputFile, "%d\n", holding->type);

                        while (holding->next != NULL)
                        {
                            holding = holding->next;
                            
                            fprintf(inputFile, "%d\n", holding->mileage);
                            fprintf(inputFile, "%s", holding->licensePlate);
                            fprintf(inputFile, "%d\n", holding->returnDate);
                            fprintf(inputFile, "%d\n", holding->type);
                        }
                    }

                    i++;
                }
            }
            else
            {
                printf("There appears to be an error in opening the file");
            }
            fclose(inputFile);

            //Freeing all of the memory
            while (availibleHead != NULL)
            {
                holding = availibleHead->next;

                free(availibleHead->licensePlate);
                free(availibleHead);

                availibleHead = holding;

            }
            while (rentedHead != NULL)
            {
                holding = rentedHead->next;

                free(rentedHead->licensePlate);
                free(rentedHead);

                rentedHead = holding;

            }
            while (repairHead != NULL)
            {
                holding = repairHead->next;

                free(repairHead->licensePlate);
                free(repairHead);

                repairHead = holding;

            }

            printf("The total Income from this session was: %.2f", totalIncome);

            exit(0);
        }
        menuSelection = fgetc(stdin);
    }

    return(0);
}

carInfo* createCar(carInfo* theHead, int newMileage, char * newLicensePlate, int newReturnDate, int newType)
{
	carInfo* holding = NULL;

	holding = malloc(sizeof(struct carInfo));
    if (holding == NULL)
    {
        printf("out of memory: exiting upon keypress");
        getchar();
        exit(1);
    }

    holding->licensePlate = malloc(sizeof(char)*(strlen(newLicensePlate)+1));

    holding->mileage = newMileage;
    strcpy(holding->licensePlate, newLicensePlate);
    holding->returnDate = newReturnDate;
    holding->type = newType;
    holding->next = NULL;
    //theHead = addToFront(theHead, holding);

    return holding;
}

carInfo* findPosistion(carInfo* theHead, int newMileage, char * newLicensePlate, int newReturnDate, int newType)
{
	carInfo* currentItem = NULL;
	carInfo* nextItem = NULL;
    carInfo* newCar = NULL;

	if (theHead == NULL)
	{
		newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
        theHead = addToFront(theHead, newCar);
        return(theHead);
	}

	//currentItem = malloc(sizeof(struct carInfo));
	//nextItem = malloc(sizeof(struct carInfo));

	currentItem = theHead;
	nextItem = currentItem->next;

	if (nextItem == NULL)
	{
		if (newMileage <= currentItem->mileage)
		{
			newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
            theHead = addToFront(theHead, newCar);
            return(theHead);
		}
		else
		{
            newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
			theHead->next = newCar;
            return(theHead);
		}
	}

    //if the new mileage is less than the mileage of the first item, add it to the front of the list.
	if (newMileage <= currentItem->mileage)
	{
		newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
        theHead = addToFront(theHead, newCar);
        return(theHead);
	}
	else
	{
		while (nextItem->next != NULL)
		{
			if ((newMileage >= currentItem->mileage) && (newMileage <= nextItem->mileage))
			{
                newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
				addAfter(currentItem, newCar);
                return(theHead);
			}
			else
			{
				currentItem = nextItem;
				nextItem = currentItem->next;
			}
		}
	}

	if (nextItem->next == NULL)
	{
		/*if (newMileage <= currentItem->mileage)
		{
			// add before current
		}
		else */
        //Add to the 2nd last posistion
        if ((newMileage >= currentItem->mileage) && (newMileage <= nextItem->mileage))
		{
			newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
            addAfter(currentItem, newCar);
            return(theHead);
		}
        //Add to the end of the list
		else
		{
            newCar = createCar(theHead, newMileage, newLicensePlate, newReturnDate, newType);
			addAfter(nextItem, newCar);
            return(theHead);
		}
	}

    return(theHead);

}

carInfo* addToFront(carInfo* theHead, carInfo* toBeAdded)
{
    /*Has the new struct point to what the original head pointed at */
    toBeAdded->next = theHead;
    return (toBeAdded);
}

carInfo* addToBack(carInfo* theHead, carInfo* toBeAdded)
{
    carInfo*  temp;
    
    /*If statement checking if the list is empty or not*/
    if (theHead != NULL)
    {
        /*Saving the value of head*/
        temp = theHead;
        
        /*Finding the end of the list*/
        while (theHead->next != NULL)
        {
            theHead = theHead->next;
        }
        
        /*Adding the struct to the end of the list*/
        theHead->next = toBeAdded;
        
        return(temp);
    }
    else
    {
        return(toBeAdded);
    }
}

void addAfter(carInfo* thisPosistion, carInfo* toBeAdded)
{
    toBeAdded->next = thisPosistion->next;
    thisPosistion->next = toBeAdded;
}

carInfo* searchList(carInfo* theHead, char* searchedLicensePlate)
{
    carInfo* temp;
    carInfo* check;

    check = theHead;
    temp = check->next;

    //Loops until it finds the specified license plate
    while (check != NULL)
    {
        if (strncmp(check->licensePlate, searchedLicensePlate, 5) == 0)
        {
            temp->next = deleteFromList(temp, check);
            return (check);
        }

        temp = check;
        check = temp->next;
    }

    //Prints an error if the license plate cannot be found.
    return(check);
}

carInfo* deleteFromList(carInfo* previous, carInfo* toBeDeleted)
{
    carInfo* temp;
    if ((previous != NULL) && (toBeDeleted != NULL))
    {
        temp = toBeDeleted->next;
        return(temp);

    }
    else if (toBeDeleted == NULL)
    {
        //previous->next = NULL;
        return(NULL);
    }
    return (toBeDeleted);
}

void printList(carInfo* theHead)
{
    if (theHead != NULL)
    {
        printf("Mileage: %d\n", theHead->mileage);
        printf("License Plate: %s", theHead->licensePlate);
        printf("Return Date: %d\n", theHead->returnDate);
        printf("Type: %d\n\n", theHead->type);

        while (theHead->next != NULL)
        {
            theHead = theHead->next;
            
            printf("Mileage: %d\n", theHead->mileage);
            printf("License Plate: %s", theHead->licensePlate);
            printf("Return Date: %d\n", theHead->returnDate);
            printf("Type: %d\n\n", theHead->type);
            
        }
    }
}

int differenceInDate(int firstDate, int secondDate)
{
    int year1 = 0;
    int year2 = 0;
    int month1 = 0;
    int month2 = 0;
    int day1 = 0;
    int day2 = 0;

    char temp[3];
    char temp2[7];

    sprintf(temp2, "%d", firstDate);

    temp[0] = temp2[0];
    temp[1] = temp2[1];
    temp[2] = '\0';
    year1 = atoi(temp);

    temp[0] = temp2[2];
    temp[1] = temp2[3];
    temp[2] = '\0';
    month1 = atoi(temp);

    temp[0] = temp2[4];
    temp[1] = temp2[5];
    temp[2] = '\0';
    day1 = atoi(temp);

    sprintf(temp2, "%d", secondDate);

    temp[0] = temp2[0];
    temp[1] = temp2[1];
    temp[2] = '\0';
    year2 = atoi(temp);

    temp[0] = temp2[2];
    temp[1] = temp2[3];
    temp[2] = '\0';
    month2 = atoi(temp);

    temp[0] = temp2[4];
    temp[1] = temp2[5];
    temp[2] = '\0';
    day2 = atoi(temp);

    if (year1 < year2)
    {
        return(1);
    }
    else if (year2 < year1)
    {
        return(2);
    }

    if (month1 < month2)
    {
        return(1);
    }
    else if (month2 < month1)
    {
        return(2);
    }

    if (day1 < day2)
    {
        return(1);
    }
    else if (day2 < day1)
    {
        return(2);
    }

    return(1);

}

carInfo* sortRentedList(carInfo* theHead)
{
    carInfo* current = NULL;
    carInfo* previous = NULL;
    carInfo* next = NULL;

    int i = 0;

    while (i == 0)
    {
        i = 1;
        previous = theHead;
        current = previous->next;

        if (differenceInDate(previous->returnDate, current->returnDate) == 2)
        {
            theHead = current;
            previous->next = current->next;
            current->next = previous;

            previous = theHead;
            current = previous->next;
            i = 0;
        }

        next = current->next;
        
        while (next != NULL)
        {
            if (differenceInDate(current->returnDate, next->returnDate) == 2)
            {
               previous->next = next;
               current->next = next->next;
               next->next = current;

               previous = next;
               next = current->next;

               i = 0;
            }
            else
            {
                previous = current;
                current = previous->next;
                next = current->next;

            }
        }

    }

    return(theHead);

}