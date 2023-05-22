/* 
============================================================================ 
FILE        : ShopCatalog.cpp
AUTHOR      : Sigaya, Kathryn Marie P.
DESCRIPTION : This program simulates a shop catalog where the user can input items (as a seller)
			  and buy items from the said list (as a customer).
COPYRIGHT   : December 3, 2019
REVISION HISTORY  
Date:               By:          Description: 

============================================================================
*/ 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct syapiAccountSeller{
	char username[5];
	int PIN[80];
	char nameProduct[80][80];
	float productPrice[80];
	char priceBySort [80][80];
};
struct syapiAccountSeller syapiSeller;
	
struct syapiAccountBuyer{
	char customerName[80];
	char itemBuy[80][80];
	float itemPrice[80];
	int itemQuantity, buyMore;
};
struct syapiAccountBuyer syapiBuyer;

struct filePointers{
	FILE *fptProducts;
	FILE *fptPrices;
	FILE *fptReceipt;
	FILE *fptPricebySort;
};
struct filePointers fptrs;

struct temporary{
	char bufferPrices[80], bufferProducts[80][80], bufferReceipt[100];
};
struct temporary temp;

struct choices{
	int menuChoice, sortChoice, catalogChoice, buyerChoice;
};
struct choices choice;

void mainMenu();

void syapiVendorMenu(char *inputName);

void syapiCatalogInput(int i, int numberOfItems);

void syapiCatalogAdd(int i, int numberOfItems);

void catalogDisplay();

void sortMenu();

void sortingAlpha(int i, int sort, int j, char* tempchar);

void sortingPricesDescending(int i, int sort, int j, float tempnum, float* sortPrices);

void sortingPricesAscending(int i, int sort, int j, float tempnum, float* sortPrices);

void makeCustReceipt(int i, int buyMore, float total);

void displayReceipt();

/*
============================================================================
FUNCTION    : main
DESCRIPTION : This is the main function.
ARGUMENTS   : int i - variable for incrementing while reading through files and for loops
			  int j - variable used in arrays at for loops
			  int sort - variable used as the limit for the for loops in price/item sorting
			  float total = 0 - variable for calculating the total purchase of the customer
			  float sortPrices[80] - variable for storing the sorted prices
			  char inputName[5] = "kath"- variable to be used as a 'username'
			  float tempnum - variable for temporarily storing a number from the price sorting section
			  char tempchar[80] - variable for temporarily storing a string from the product sorting section
RETURNS     : (no return) void
===========================================================================
*/
int main(){
	//declaration of variables
	int i, j, sort;
	float total = 0;
	float sortPrices[80];

	char inputName[5] = "kath"; //the 'username' for this program
	float tempnum; // this variable is used for price sorting
	char tempchar[80]; // this variable is used for item sorting
	
	//do while loop here
	do{
	i = 0, j = 0, sort = 0;
	syapiBuyer.buyMore = 0;
	total = 0;
	system("cls");
	mainMenu(); //performs the void function mainMenu
	scanf("%d", &choice.menuChoice);
	system("cls");
	
	switch(choice.menuChoice){ //switch case for the menu choice
		case 1: { // menuChoice case 1 if the user is a seller
				system("cls");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("=== Syapi Seller Log In ===\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("Enter the username: ");
				scanf("%s", &syapiSeller.username);
				printf("Enter the PIN: ");
				scanf("%d", &syapiSeller.PIN[80]);
				
				if ((strcmp(inputName, syapiSeller.username) == 0) && syapiSeller.PIN[80] == 123){ // condition if the username and pin are both correct
					printf("\n     Login successful!    \n");
					printf("---------------------------");
					getch();
					system("cls");
					syapiVendorMenu(inputName); //performs the void functions syapiVendorMenu
					
					while (1){ //infinite loop if the user made a mistake in the input, i.e. catalog != 1 and 2. it will break if they will input 1 or 2
					printf("Input: ");
					scanf("%d", &choice.catalogChoice);
						if (choice.catalogChoice == 1 || choice.catalogChoice == 2){
							system("cls");
							break;
						}
					}
					
					switch (choice.catalogChoice){ //switch case for the catalog choice
						case 1: { //catalogChoice case 1: append (add) from the existing catalog
							system("cls");
							printf("How many items will you add to the current catalog?: ");
							scanf("%d", &syapiBuyer.itemQuantity);

							syapiCatalogAdd(i, syapiBuyer.itemQuantity); //performs the void function syapiCatalogAdd
							
							printf("\nInputs successful!\n\n");
							getch();	
							system("cls");
							printf("These are the updated contents of your Syapi catalog:\n\n");
							catalogDisplay(); //performs the void function catalogDisplay
							break;
						}
				
						case 2: { //catalogChoice case 2: creating/overwriting the text file
							system("cls");
							printf("=== Creating New Catalog ===\n");
							printf("How many items will you add to the new catalog?: ");
							scanf("%d", &syapiBuyer.itemQuantity);

							syapiCatalogInput(i, syapiBuyer.itemQuantity); //performs the void function syapiCatalogInput
						
							printf("\nInputs successful!\n\n");
							getch();	
							system("cls");
							printf("These are the new contents of your Syapi catalog:\n\n");
							catalogDisplay();
							break;		
							}
							
							default:{
								printf("Wrong input. Logging out...\n");
								break;
							}
						} //end of catalogChoice switch case
					}
						else { //else condition if the username and password are wrong
						printf("\nLog in failed. Please try again.");
					}
					printf("\n---------------------------");
					printf("\nPress any key to exit.");
					getch();
					break;			
			}
			
		case 2: { // menuChoice case 2 if the user is a customer
				system("cls");
				printf("<<<<<<<<<<<<<<<<<<<<<<<<\n");
				printf("== Syapi Shop Catalog ==\n");
				printf(">>>>>>>>>>>>>>>>>>>>>>>>\n");
				printf("Input your name: ");
				scanf(" %[^\n]s", &syapiBuyer.customerName);
				sortMenu(); //display for sorting menu
				printf("Input: ");
				scanf("%d", &choice.sortChoice);
				system("cls");
				
			switch(choice.sortChoice){ //switch case for the choice of sorting
				case 1:{ //sortChoice case 1: the names of the items are to be arranged in alphabetical order
						fptrs.fptProducts = fopen("products.txt", "r"); // opens the products.txt file
						
 						while (fgets(temp.bufferProducts[i], 80, fptrs.fptProducts)){ //puts the data from the text file to the array
 							i++;
						}
						
						fclose(fptrs.fptProducts);
							
						sort = i; //the value of i will be stored to sort
							
						//sorting of the items in the array (alphabetical)
						sortingAlpha(i, sort, j, tempchar);
						
						printf("There are %d items in all.\nHere are the names in alphabetical order:\n", sort);
						for (i = 0; i < sort; i++){
							printf("%s", temp.bufferProducts[i]);
						}
						break;
					}
					
				case 2:{ // sortChoice case 2: the prices are to be arranged from highest to lowest
						fptrs.fptPricebySort = fopen("pricebysort.txt", "r");
						while ((fscanf (fptrs.fptPricebySort, "%f\n", &sortPrices[i])) != EOF){ //puts the data in the text file to the array
 							i++;																//the & is important because the array decays into a pointer
						}
						fclose(fptrs.fptPricebySort);
						
						sort = i;
						
						//sorting the prices from highest to lowest (descending order)
						sortingPricesDescending(i, sort, j, tempnum, sortPrices);
						
						printf("There are %d items in all.\nHere are the prices from highest to lowest:\n", sort);
						for (i = 0; i < sort; i++){
							printf("Php %.2f\n", sortPrices[i]);
						}
							break;
						}
					
				case 3:{ //sortChoice case 3: the prices are to be arranged from lowest to highest
						fptrs.fptPricebySort = fopen ("pricebysort.txt", "r");
						while ((fscanf (fptrs.fptPricebySort, "%f\n", &sortPrices[i])) != EOF){
 							i++;																
						}															
						fclose(fptrs.fptPricebySort);
						
						sort = i;
						
						//sorting the int array from lowest to highest (ascending order)
						sortingPricesAscending(i, sort, j, tempnum, sortPrices);
						
						printf("There are %d items in all. Here are the prices from lowest to highest:\n", sort);
						for (i = 0; i < sort; i++){
							printf("Php %.2f\n", sortPrices[i]);
						}
							break;
						}
					
				default: { //sortChoice default case if they input any number other than 1, 2, and 3
					break; 
					}
				}	//end of sortChoice switch case
				
			printf("-----------------------------\n");
			printf("These are the items for sale:\n");
			printf("-----------------------------\n");
			catalogDisplay(); //performs the void function catalogDisplay
 			printf("\nWhat will you buy? Please write the name of the item and the price.\n");
 				
 			//for loop for customer buying input
 			for (i = 0 ;; i++){	
				printf("\nName of item #%d: ", i+1);
				scanf(" %[^\n]s", &syapiBuyer.itemBuy[i]); //[^\n] means to include whitespaces
				printf("Price of item '%s': Php ", syapiBuyer.itemBuy[i]);
				scanf("%f", &syapiBuyer.itemPrice[i]);
				printf("\nThe item '%s' was added to the cart! Will you buy more?\nPress [1] if yes, [any number] if no.", syapiBuyer.itemBuy[i]);
				printf("\nInput: ");
				scanf("%d", &choice.buyerChoice);
				
				if (choice.buyerChoice == 1){ //if the user inputs 1 i.e. they want to buy more
					syapiBuyer.buyMore++;
					continue; // continues the for loop
					}
					
				else {
					break; //breaks the for loop
				}
			}	//end of customer buying input loop

			system("cls");
			printf("---------------------\n");
			printf("== Syapi Check Out ==\n");
			printf("---------------------\n");
			printf("Thank you for shopping with us!\nYou have bought %d items in all.\n", syapiBuyer.buyMore+1);
			getch();
			printf("---------------------\n");
			printf("\nYour receipt is as follows:\n\n");
			
 			makeCustReceipt(i, syapiBuyer.buyMore, total); //performs the void function makeCustReceipt
 			displayReceipt(); //performs the void function displayReceipt
 			printf("Press any key to exit.\n");
			getch();
	
			break;			
		}
		
	case 3: { //breaks the menuChoice switch case
		break; 
	}	
		
	default: { //menuChoice default case if the number inputted is greater than 3 or less than 1
			printf("Wrong input. Please try again.");
			getch(); 
			break;
		}
	} // end of menuChoice switch case
}	while (choice.menuChoice != 3); // end of menuChoice switch case; breaks the loop if menuChoice != 3

	system("cls");	
	printf("\n-------------------------------\n");
	printf("Thank you for shopping with us!\n");
	printf("-------------------------------\n");
	
	return 0; //end of the program
}

/*
============================================================================
FUNCTION    : mainMenu
DESCRIPTION : Displays the main menu of the shop catalog program.
ARGUMENTS   : none
RETURNS     : (no return) void
===========================================================================
*/
void mainMenu(){
	printf("=====================================\n");
	printf("========= Welcome to Syapi! =========\n");
	printf("=====================================\n");
	printf("Please choose an option from the choices below:\n");
	printf("Press [1] if you are a vendor and want to add items.\n");
	printf("Press [2] if you are a customer who wants to buy from the shop.\n");
	printf("Press [3] if you want to quit.\n");
	printf("Input your choice: ");
	return;
}

/*
============================================================================
FUNCTION    : syapiVendorMenu
DESCRIPTION : Displays the user's vendor menu.
ARGUMENTS   : char *inputName - pointer to the set 'username' of this program,
			  i.e. "kath".
RETURNS     : (no return) void
===========================================================================
*/
void syapiVendorMenu(char *inputName){
	printf("==========================\n");
	printf("== Syapi Vendor Catalog ==\n");
	printf("==========================\n");
	printf("Welcome, Syapi vendor %s!\n\n", inputName);
	printf("Will you add new items or create a new catalog?\nPress [1] to add new items.\nPress [2] to create new catalog.\n");
	return;	
}
/*
============================================================================
FUNCTION    : syapiCatalogInput
DESCRIPTION : Displays the input process for the catalog if the user enters '2'
			  which is to write a new catalog.  
ARGUMENTS   : int i - variable used for the for loops
			  int numberOfItems - variable used as the limit for the for loops
RETURNS     : (no return) void
===========================================================================
*/
void syapiCatalogInput(int i, int numberOfItems){
	//opening the text files
	fptrs.fptProducts = fopen("products.txt", "w");
	fptrs.fptPrices = fopen("prices.txt", "w");
	fptrs.fptPricebySort = fopen("pricebysort.txt", "w");
	
		for (i = 0; i < numberOfItems; i++){
			printf("Input the name of item %d: ", i+1);
			scanf(" %[^\n]s", &syapiSeller.nameProduct[i]); //the [^\n] is used to include whitespaces
			fprintf(fptrs.fptProducts,"%s\n", syapiSeller.nameProduct[i]);
			printf("Input the price of item %d: Php ", i+1);
			scanf("%f", &syapiSeller.productPrice[i]);
			fprintf(fptrs.fptPricebySort,"%.2f\n", syapiSeller.productPrice[i]);
			fprintf(fptrs.fptPrices, "%s: Php %.2f\n", syapiSeller.nameProduct[i], syapiSeller.productPrice[i]);
			printf("\n");
		}
	//closing of the text files			
	fclose(fptrs.fptProducts);
	fclose(fptrs.fptPrices);
	fclose(fptrs.fptPricebySort);
		return;
}
/*
============================================================================
FUNCTION    : syapiCatalogAdd
DESCRIPTION : Displays the adding/appending process for the catalog if the user
		 	  inputs '1' on the vendor menu, which is to add new items.  
ARGUMENTS   : int i - variable used for the for loops
			  int numberOfItems - variable used as the limit for the for loops
RETURNS     : (no return) void
===========================================================================
*/
void syapiCatalogAdd(int i, int numberOfItems){
	fptrs.fptProducts = fopen("products.txt", "a");
	fptrs.fptPrices = fopen("prices.txt", "a");
	fptrs.fptPricebySort = fopen("pricebysort.txt", "a");

	for (i = 0; i < numberOfItems; i++){
		printf("Input the name of item %d: ", i+1);
		scanf(" %[^\n]s", &syapiSeller.nameProduct[i]); //the [^\n] is used to include whitespaces
		fprintf(fptrs.fptProducts,"%s\n", syapiSeller.nameProduct[i]);
		printf("Input the price of item %d: Php ", i+1);
		scanf("%f", &syapiSeller.productPrice[i]);
		fprintf(fptrs.fptPricebySort,"%.2f\n", syapiSeller.productPrice[i]);
		fprintf(fptrs.fptPrices, "%s: Php %.2f\n", syapiSeller.nameProduct[i], syapiSeller.productPrice[i]);
		printf("\n");
	}
	
	fclose(fptrs.fptProducts);
	fclose(fptrs.fptPrices);
	fclose(fptrs.fptPricebySort);
	return;
}
/*
============================================================================
FUNCTION    : catalogDisplay
DESCRIPTION : Displays the updated/created item catalog.  
ARGUMENTS   : none
RETURNS     : (no return) void
===========================================================================
*/
void catalogDisplay(){
		fptrs.fptPrices = fopen("prices.txt", "r");
 		while (fgets(temp.bufferPrices, 80, fptrs.fptPrices) != NULL){ // while ((fscanf(fptPrices, "%[^\n]s", bufferPrices)) != EOF) || for scanf equivalent
 			printf("%s", temp.bufferPrices);
 		}
 		fclose(fptrs.fptPrices);
 		return;
}
/*
============================================================================
FUNCTION    : sortMenu
DESCRIPTION : Displays the sorting menu where the user is presented choices
			  as to what type of sorting they want.
ARGUMENTS   : none
RETURNS     : (no return) void
===========================================================================
*/
void sortMenu(){
	printf("\nWelcome, customer %s!\nWhat type of sorting do you want for browsing the catalog?\n\n", syapiBuyer.customerName);
	printf("Press [1] for sorting the catalog in alphabetical order.\n");
	printf("Press [2] for sorting the catalog from the highest price to the lowest price. (Descending order)\n");
	printf("Press [3] for sorting the catalog from the lowest price to the highest price. (Ascending order)\n");
	printf("Press [any number] if you don't want the sorting.\n");
	return;
}
/*
============================================================================
FUNCTION    : sortingAlpha
DESCRIPTION : Sorts the names of the items/products in alphabetical order.
ARGUMENTS   : int i - variable used for the outer for loop
			  int sort - variable used for limiting the for loop
			  int j variable used for the inner for loop
			  char* tempchar - pointer variable used for temporarily storing swapped item names
RETURNS     : (no return) void
===========================================================================
*/
void sortingAlpha(int i, int sort, int j, char* tempchar){
	for(i = 0; i < sort; i++){
		for(j= i + 1; j < sort; j++){
			if(strcmp(temp.bufferProducts[i], temp.bufferProducts[j]) > 0){
				strcpy(tempchar, temp.bufferProducts[i]);
				strcpy(temp.bufferProducts[i], temp.bufferProducts[j]);
				strcpy(temp.bufferProducts[j], tempchar);
				}
			}
		}
}
/*
============================================================================
FUNCTION    : sortinsPricesDescending
DESCRIPTION : Sorts the prices of the products from highest to lowest.
ARGUMENTS   : int i - variable used for the outer for loop
			  int sort - variable used for limiting the for loop
			  int j variable used for the inner for loop
			  float tempnum = variable used for temporarily storing swapped price elements
			  char* sortPrices - pointer variable used for storing the swapped price elements
RETURNS     : (no return) void
===========================================================================
*/
void sortingPricesDescending(int i, int sort, int j, float tempnum, float* sortPrices){
	for (i = 0; i < sort; i++){
		for (j = i + 1; j < sort; j++){
			if (sortPrices[i] < sortPrices[j]){
				tempnum =  sortPrices[i];
				sortPrices[i] = sortPrices[j];
				sortPrices[j] = tempnum;
			}
		}
	}
}
/*
============================================================================
FUNCTION    : sortinsPricesAscending
DESCRIPTION : Sorts the prices of the products from lowest to highest.
ARGUMENTS   : int i - variable used for the outer for loop
			  int sort - variable used for limiting the for loop
			  int j variable used for the inner for loop
			  float tempnum = variable used for temporarily storing swapped price elements
			  char* sortPrices - pointer variable used for storing the swapped price elements
RETURNS     : (no return) void
===========================================================================
*/
void sortingPricesAscending(int i, int sort, int j, float tempnum, float* sortPrices){
	for (i = 0; i < sort; i++){
		for (j = i + 1; j < sort; j++){
			if (sortPrices[i] > sortPrices[j]){
				tempnum =  sortPrices[i];
				sortPrices[i] = sortPrices[j];
				sortPrices[j] = tempnum;
			}
		}
	}
}
/*
============================================================================
FUNCTION    : makeCustReceipt
DESCRIPTION : Creates a text file to be used as a receipt.
ARGUMENTS   : int i - variable used for the for loops
			  buyMore - variable used for showing how many items the user bought
			  total - variable used to calculate and show the total
RETURNS     : (no return) void
===========================================================================
*/
void makeCustReceipt(int i, int buyMore, float total){
	fptrs.fptReceipt = fopen("receipt.txt", "w");
			
	fprintf(fptrs.fptReceipt, "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
	fprintf(fptrs.fptReceipt, "=== Syapi 12.12 Winterfest Sale ===\n");
	fprintf(fptrs.fptReceipt, "***********************************\n");
	fprintf(fptrs.fptReceipt,"Customer receipt for Syapi Buyer %s.\n", syapiBuyer.customerName);
	fprintf(fptrs.fptReceipt, "\nItems added to cart:\n");
	
	for (i = 0; i <= buyMore; i++){
		fprintf(fptrs.fptReceipt, "%d. %s @ Php %.2f\n", i + 1, syapiBuyer.itemBuy[i], syapiBuyer.itemPrice[i]);
		total += syapiBuyer.itemPrice[i];
	}
		
	fprintf(fptrs.fptReceipt, "\nThe total for customer %s's purchase is: Php %.2f\n", syapiBuyer.customerName, total);
	fprintf(fptrs.fptReceipt, "\n\nThis serves as an official receipt.\n");
	fprintf(fptrs.fptReceipt, "\n***********************************\n");
	
	fclose(fptrs.fptReceipt);
 	
 	return;
}
/*
============================================================================
FUNCTION    : displayReceipt
DESCRIPTION : Displays the created receipt.txt file from the void function makeCustReceipt.
ARGUMENTS   : none
RETURNS     : (no return) void
===========================================================================
*/
void displayReceipt(){
	fptrs.fptReceipt = fopen("receipt.txt", "r");
		while (fgets(temp.bufferReceipt, 100, fptrs.fptReceipt) != NULL){ //while ((fscanf(fptPrices, "%[^\n]", bufferPrices)) != EOF)
 			printf("%s", temp.bufferReceipt);
 		}
 	fclose(fptrs.fptReceipt);
 	
 	return;
}
