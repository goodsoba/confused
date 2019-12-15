/*
-Name: Brandon Tran
-Summary: Final Project. 
This code simulates a theater seating program. The user can use the program to view available seats,
either in the entire room or a single row. The user can also view the prices for each row and 
update the prices to fit their needs. The tickets can be bought and this will be shown through the 
seating charts. 
-I found many parts of this project to be difficult. The ones that gave me the most problems were the
file handling used to update the prices, usage of pointers with arrays, and various syntax errors that
I learned about while working on this program.
-It took roughly 20 hours to get to this point.
-Date Completed :12/6/2019
*/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Declaration of my variables and arrays.
int choice, rowChoice, colChoice, r, c;
double reference;
double updateprice = 0;
double totalTicketSales = 0;
double totalPrice = 0;
double cost = 0;
const int ROWS = 15;
const int COLS = 30;
char TAKEN = '*';
char EMPTY = '#';
char seats[ROWS][COLS];
double price[ROWS];
double newprice[ROWS];

// My function prototypes.
void displayMenu();
int getChoice();
void displaySeats(char seats[][COLS]);
void displayPrices(double price[]);
void updatePrices(double price[]);
void purchaseTicket(char seats[][COLS], double price[], double& totalPrice);
void displaySales(double totalTicketSales);

// Declaring my input and output file streams.
ofstream writetoFile;
ifstream readfromFile;

// The main body. First I assigned the char '#' to our seating array. Then I assigned
// my default seat prices for each row. I did this in the main body to avoid problems with
// our functions.

int main()
{
	for(r = 0; r < ROWS; r++)
	{	
	for( c = 0; c < COLS; c++)
	{
		if(*(newprice+r) == TAKEN || *(price+r) == TAKEN)
		{
			*(*(seats + r)+ c) = TAKEN;
		}
		else
		{
			*(*(seats + r)+ c) = EMPTY;
		}
	}
	}
	
	writetoFile.open("prices.txt");
	while (writetoFile)
	{
		for(int t = 0; t < 15; t++)
		{
			*(price + t) = 10.00; //Using loops to assign a value to array elements.
		}
		for(int i = 0; i < ROWS; i++)
		{
		writetoFile << setw(8) << (i + 1) << setw(10) << "$" << price[i] << endl;
		}
	writetoFile.close();
	}
	
	displayMenu(); // Displays our menu
	getChoice(); // Retrieves user input

	do // Our main functional loop. The program keeps running until the user quits.
	{
	switch (choice)
	{
		case 1: displaySeats(seats);
				break;
		case 2: displayPrices(price);
				break;
		case 3: updatePrices(price);
				break;
		case 4: purchaseTicket(seats,price,reference);
				break;
		case 5: displaySales(totalTicketSales);
				break;
		case 6: return 0;
				break;
		default: cout << "Invalid Choice.";
	}
	}while(choice != 6);
	return 0;
}

/**************************************************************************************************/
/**************************************************************************************************/
// Displays our menu.

void displayMenu()
	{
	cout << "\t\tC++ Theatre\n\n" << endl;
	cout << "\t1.  View Available Seats" << endl;
	cout << "\t2.  View Seating Prices" << endl;
	cout << "\t3.  Update Seating Prices" << endl;
	cout << "\t4.  Purchase a Ticket" << endl;
	cout << "\t5.  View Ticket Sales" << endl;
	cout << "\t6.  Quit" << endl;
	cout << "\tEnter your choice(1-6):" ;	
	}

/**************************************************************************************************/
/**************************************************************************************************/
// Gets our choice for the main menu. Input validation for a value not 1-6.

int getChoice()
	{
	cin >> choice;
		while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 )
		{
			cin >> choice;
				if(choice < 0 || choice > 6)
				{
				cout << "ERROR. Please re-enter a choice from 1 - 6.";
				cin.ignore();  // These lines allow me to ignore incorrect input
				cin.get();	   // and retrieve my choice again.
				main();
				}
		}
		return choice;
	}

/**************************************************************************************************/
/**************************************************************************************************/
// Displays my seating chart. Choosing 1 will show total amount of seats sold. Choosing 2 will 
// show how many seats are available in a selected row. Choosing 3 will show how many seats are
// available in the entire theater.

void displaySeats(char seats[ROWS][COLS])
{
	int choiceone, rowi;
	cout << "\n1.  See how many seats have been sold\n";
	cout << "2.  See how many seats are available in each row\n"; 
	cout << "3.  See how many seats are available in the auditorium\n";
	cout << "Enter your choice (1-3)";
	cin >> choiceone; //Input example
	
	if (choiceone == 1)
	{
		cout << "Amount of seats sold : " << totalTicketSales; //Output example
	}
	
	else if (choiceone == 2)
	{
		cout << "\n\nEnter a row to view available seating: ";
		cin >> rowi;
		cout << "\nRow " << " " << rowi << " ";
			for( c = 0; c < COLS; c++)
				{
				cout << *(*(seats + rowi)+0);
				}	
	}
	
	else if (choiceone == 3)
	{
		cout <<  "\n\t\tSeats" << endl;
		for(r = 0; r < ROWS; r++)
		{
			// This if/else statement is purely for alignment purposes.
			if (r >= 9) 
			cout << "\nRow " << (r + 1) << " ";
			else
			cout << "\nRow " << " " << (r + 1) << " ";
			
			for( c = 0; c < COLS; c++)
			{
				if(*(*(seats + rowChoice)+ colChoice) == TAKEN)
				{
				*(*(seats + r)+ c) = TAKEN;
				cout << *(*(seats + r)+ c);
				}
				else
				{
				*(*(seats + r)+ c) = EMPTY;
				cout << *(*(seats + r)+ c);
				}
			}
		}
	}
	
	cout << "\n\n\n\t*  =  Sold";
	cout << "\n\t#  =  Available";
	
	cout << "\n\n\nPress the Enter key to continue."; //These lines allows us to resume the program
	cin.ignore();									  // until we quit from the menu. I use this in
	cin.get();										  // all of my functions.
	main();
	
}
/**************************************************************************************************/
/**************************************************************************************************/
// This function displays the prices for each row. If option 3 from the menu hasn't been chosen yet
// this function will display default prices, which is $10.00. I utilize a file to read our data from.

void displayPrices(double price[ROWS])
{
	cout << "\n\nThese are the default seat pricings for each row.\n\n"<< endl;
	readfromFile.open("prices.txt");
	if(updateprice > 0)
	{
		while(readfromFile)
		{
			for(int i ; i < ROWS ; i++)
			{
			cout << setw(8) <<"Row:"<<(i + 1) << setw(10) <<"$";
			readfromFile >> *(newprice + i);
			cout << *(newprice + i);
			cout << endl;
			}
		}
	}
	else
	{
		for(int i = 0; i < ROWS; i++)
		{
		cout << setw(8) <<"Row:"<< (i + 1) << setw(10) <<"$"<< *(price + i) << endl;
		}
	}
	
	readfromFile.close();
	
	cout << "\n\n\nPress the Enter key to continue.\n\n\n";
	cin.ignore();
	cin.get();
	main();
}

/**************************************************************************************************/
/**************************************************************************************************/
// This functions allows us to set the prices for each of the rows. I utilize a file here as well
// to write our new prices to.

void updatePrices(double price[ROWS])
{
	
	writetoFile.open("prices.txt");
	if(writetoFile.is_open())
	{
	
	cout << "\n\n\nPlease enter the ticket price for each row.\n\n" << endl;
	writetoFile << "\n\n\nPlease enter the ticket prices for each row." << endl;
	
		for(int i = 0; i < ROWS; i++)
		{
		cout << "\tTicket price for row  " << (i + 1) << " : $" ;
		cin >> updateprice;
		*(newprice + i) = updateprice;
		writetoFile << *(newprice + i) << endl;
		cout << endl;
		}
	
	writetoFile.close();
	}
	else 
	{
	cout << "Unable to open file";
	}
	
	cout << "\n\n\nPress the Enter key to continue.\n\n\n";
	cin.ignore();
	cin.get();
	main();
}

/**************************************************************************************************/
/**************************************************************************************************/
// This is my largest function. First when called, we are asked to view the chart of available seats.
// This is option 1 on the main menu. After saying no the program asks us which row and seat number
// we want to purchase. The program input validates for values outside of our limits(15,30).
// After entering our numbers, the program tells us if the seat is available or not. If available,
// that ticket is purchased, and we are told our total amount of tickets solds and the cost of it.
// If totalTicketPrice reaches 450, then we have run out of seats.

void purchaseTicket(char seats[ROWS][COLS], double price[ROWS], double& totalPrice)
{
	char chartview, another;
	cout << "\n\n\tPurchase a ticket\n";
	cout << "\n\nDo you wish to view the chart of available seats before making your selections (y/n)?" ;
	cin >> chartview;

	if(chartview == 'y')
	{
		displaySeats(seats);
	}
	else 
	{
	do
	{
	while(totalTicketSales < 450)
	{
			
		cout << "\nPlease enter the row number of the ticket you would like to purchase: ";
		cin >> rowChoice;
		cout << "\nPlease enter the seat number of the ticket you would like to purchase: ";
		cin >> colChoice;
		
	//Input validation for values that are not integers.
	while(1)
	{
		if(!cin.fail())
		{
			break;
		}
		else if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "\nWrong input." << endl;
			cout << "\n\nPlease enter the row number(1-15) of the ticket you would like to purchase: "<< endl;
			cin >> rowChoice;
			cout << "\n\nPlease enter the seat number(1-30) of the ticket you would like to purchase: "<< endl;
			cin >> colChoice;
		}	
	}
	
	// Usage of pointers to access my array elements.
	if((rowChoice >= 0 && rowChoice < 16) && (colChoice >= 0 && colChoice < 31))
	{
		if(*(*(seats + rowChoice)+colChoice) == TAKEN)
		{
			cout << "\n\nThis ticket is already sold, please select another one." << endl;
		}
		else if  (*(*(seats + rowChoice)+colChoice) == EMPTY)
		{
			*(*(seats + rowChoice)+colChoice) = TAKEN;
			totalTicketSales++;
			totalPrice += *(price + rowChoice);
			cout << "\nThe price of that ticket is $" << price[rowChoice] << endl;
			cout << "\n\tTicket successfully purchased !" << endl;;
			cout << "\n\t\tYou have purchased a total of " << totalTicketSales 
			<< " ticket(s) for a total price of $" << totalPrice << "\n\n";
			break;
		}
	}
	else
	{
		cout << "\n\nPlease enter the row number(1-15) of the ticket you would like to purchase: "<< endl;
		cout << "\n\nPlease enter the seat number(1-30) of the ticket you would like to purchase: "<< endl;
	}
	
	}
	cout << "\nWould you like to purchase another ticket ?(Enter any key for YES, n / N for NO)";
	cin >> another;
		if(another == 'n' || another == 'N')
		{
			break;
		}
	if(totalTicketSales == 450)
	{
		cout << "Tickets are sold out !" << endl;
		break;
	}
	
	}while(another != 'n' || another != 'N');
	}

	cout << "\n\n\nPress the Enter key to continue.\n\n\n";
	cin.ignore();
	cin.get();
	main();
}
/**************************************************************************************************/
/**************************************************************************************************/
// This function simply displays the total amount of tickets sold.

void displaySales(double totalTicketSales)
{
	cout <<"Total amount of ticket sales: " << totalTicketSales << endl;
	
	cout << "\n\n\nPress the Enter key to continue.\n\n\n";
	cin.ignore();
	cin.get();
	main();
	
}
