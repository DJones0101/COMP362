#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUMBER_OF_TURNS 30
#define BUY_OPTION 1
#define SELL_OPTION 2
#define END_TURN_OPTION 3
#define STARTING_MONEY 15.00
char **names;
float *prices;
int *inventory;
int number_of_listings;
float cash = STARTING_MONEY;
int turn;

int input(char *file_name);

void display_market();

void display_inventory();

void display_game_state();

void end_turn();

void sell();

void buy();

void menu();

void free_arrays();

int input(char *file_name)
{
	FILE *file_pointer = fopen(file_name, "r");
	if(file_pointer){

		// file opening was successful
		

		fscanf(file_pointer,"%d",&number_of_listings);
		printf("The number of stocks is : %d\n", number_of_listings);
		
		int listing;
		inventory = malloc(sizeof(int) *number_of_listings);
		prices = malloc(sizeof(float) *number_of_listings);
		names = malloc(sizeof(char*) *number_of_listings);

		for(listing = 0; listing < number_of_listings; listing++){
			inventory[listing] = 0;
			char temp_name[100];
			fscanf(file_pointer, "%s %f",temp_name, &prices[listing]);
			names[listing] = malloc(sizeof(char) *strlen(temp_name)+1);
			strcpy(names[listing], temp_name);
		}
		
		return 1;	
		
	}else{
		printf("something went wrong with opening the file\n");	
	}
	

	// return an error code if reading from the file was unsuccessful
	return 0;
}
void display_game_state()
{
	printf("TURN #%d",turn);
	printf("\n~~~~~~~~~~~~~~~~~The Market~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-11s\n","Stock Name","Stock Price" );
	display_market();
	printf("\n~~~~~~~~~~~~~~~~~Inventory~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-15s %-11s\n","Stock Name","Stock Quantity", "Stock Value" );
	display_inventory();
	printf("Your available cash: %-11.2f\n",cash);
}

void display_market()
{
	
	int listing;
	for(listing = 0; listing < number_of_listings; listing++){
		printf("%d) %-30s $%-7.2f\n", listing+1, names[listing], prices[listing]);	
	}
}

void display_inventory()
{
	int listing;
	for(listing = 0; listing < number_of_listings; listing++){
		printf("%d) %-30s %-15d $%-7.2f\n", listing+1, names[listing],inventory[listing], inventory[listing] * prices[listing]);	
	}
}

void menu()
{

		int choice;
				
		do{

		printf("\nOptions:\n");
		printf("1) Buy Stock\n");
		printf("2) Sell Stock\n");
		printf("3) End Turn\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);

		switch(choice){
			
			case BUY_OPTION: buy();break;
			case SELL_OPTION: sell();break;
			case END_TURN_OPTION: end_turn();break;
			default: printf("Invalid selection\n");break;	
		}
		
		}while(choice != END_TURN_OPTION );

		// Continue showing this menu until the end turn option is selected. (Hint use do-while loop)
		// Use a switch statement to call the appropriate method from the user's selection.
}

void buy()
{

	
	printf("\n~~~~~~~~~~~~~~~~~Buy Options~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-11s\n","Stock Name","Stock Price" );
	display_market();
	printf("Your available cash: %-11.2f\n",cash);
	printf("Enter the number of the stock you would like to invest in: ");
	int selection;
	scanf("%d", &selection);
	selection--;

	
	if (selection >= 0 && selection < number_of_listings)
		{
			if (prices[selection] <= cash)
			{
				int quantity;
				printf("Enter the amount of stock you wish to buy: ");
				scanf("%d", &quantity);
				
				if (quantity >= 0)
				{
					if (cash >= (quantity * prices[selection]) )
					{
						inventory[selection] += quantity;
						cash -= quantity * prices[selection];

						printf("Your available cash after the transaction: %-11.2f\n",cash);
					}
					else
					{
						printf("You do not have enough money to purchase that quantity\n");
					}
				}
				else
				{
					printf("The quantity must be positive.\n");
				}
			}
			else
			{
				printf("Not enough cash to purchase any of that stock.\n");
			}
		}
		else
		{
			printf("Invalid selection.\n");
		}
}

void sell()
{
	printf("\n~~~~~~~~~~~~~~~~~Sell Options~~~~~~~~~~~~~~~~~\n");
	printf("%-30s %-15s %-11s\n","Stock Name","Stock Quantity", "Stock Value" );
	display_inventory();
	printf("Enter the number of the stock you would like to sell from: ");
	int selection;
	scanf("%d", &selection);
	selection--;


	if (selection >= -1 && selection < number_of_listings)
	{
		if (inventory[selection] > 0)
		{
			int quantity;
			printf("Enter the quantity of stock you wish to sell: ");
			scanf("%d", &quantity);

			if (quantity <= inventory[selection])
			{
				inventory[selection] -= quantity;
				cash += quantity * prices[selection];

				printf("Your available cash after the transaction: %-11.2f\n",cash);
			}
			else
			{
				printf("You do not have that much of this stock.\n");
			}
		}
		else
		{
			printf("You do not own any of this stock.\n");
		}
	}
	else
	{
		printf("Invalid selection\n");
	}

}

void end_turn()
{
	printf("Turn ended\n");
	printf("Market prices will change\n");
	
	int listing;
	for(listing = 0; listing < number_of_listings; listing++){
		prices[listing] = (prices[listing] * ((rand() % 50) +75.00) /100);	
	}


}
void free_arrays()
{	int listing;
	for(listing = 0; listing < number_of_listings; listing++){
		free(inventory);
		free(prices);
		free(names);	
	}
}

int main()
{	
	// Completed for you
	srand(time(NULL));
	if (! input("input.txt"))
	{
		printf("Error reading in the input\n");
		return -1;
	}
	turn = 0;
	while( turn != NUMBER_OF_TURNS)
	{
		display_game_state();
		menu();
	}
	display_game_state();
	free_arrays();
	return 0;
}
