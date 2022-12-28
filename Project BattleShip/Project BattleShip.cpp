#include<iostream>
#include<ctime>
#include<cstdlib>
#include<stdlib.h>

using namespace std;

//Global Variables
int Array_Size;
int Background_Array[9][9];
int Input_Column_Index, Input_Row_Index;
int Frigate_Count = 0, Battleship_Count = 0, Carrier_Count = 0; //Count Will Be Used To Remember The Amount Of Hits
char Output_Array[9][9], Input[2];

//Functions
int Start_Menu();
void grid_size();
void Updated_Grid_Print();
void Initializing_Grid();
void Frigate_Assignment();
void Frigate_Assignment2();
void Carrier_Assignment();
void BattleShip_Assignment();
int Prompt_Statements();


void User_Input(char User_Index[]);

//These Are The Functions Involiving The Front End Game Mechanics
void Game_Mechanics(int shells);

void Final_Location_Ship();
void Win_Check();



int main()
{
	int SHELLS;
	int START = 1;

	do
	{
		START = Start_Menu();

		//This Is Used To End The Program In Case The User Exits;
		if (START == 2)
			return 0;
		else if (START == 3)
		{
			cout << " 1. Four Ships Have Been Hidden In Grid " << endl << endl;
			cout << " 2. A Carrier Ship Which Occupies 5 Spaces Has Been Hidden " << endl << endl;
			cout << " 3. A BattleShip Which Occupies 4 Spaces Has Been Hidden " << endl << endl;
			cout << " 4. Two Frigate Ships Which Occupies 2 Spaces Has Been Hidden " << endl << endl;
			cout << " 5. You Will Be Assigned Limited Number Of Shells To Complete The Task Of Destroying Them All" << endl << endl;
			cout << "  GoodLuck!!  " << endl << endl;
		}
	} while (START != 1);


	//For Taking Input Of The Size Of The Array (It will be an infinte loop until user enters a valid value)
	do {
		cout << "Enter the size of the required grid between 6 and 9: ";
		cin >> Array_Size;

		if (Array_Size >= 6 && Array_Size <= 9)
		{
			break;
		}
		else if (Array_Size < 6 || Array_Size > 9)
		{

			cout << endl << "Invalid Input" << endl;
			cout << endl << "Try Again!!!" << endl << endl;

		}

	} while (1);

	cout << endl << endl;

	Initializing_Grid();
	grid_size();

	cout << endl << endl;

	Carrier_Assignment();
	BattleShip_Assignment();
	Frigate_Assignment();
	Frigate_Assignment2();


	SHELLS = Prompt_Statements();

	Game_Mechanics(SHELLS);

	if (Frigate_Count == 4 && Carrier_Count >= 4 && Battleship_Count >= 3)
	{
		Final_Location_Ship();
		Win_Check();
		return 0;

	}

	Final_Location_Ship();
	Win_Check();
}


//This Is Program For The Start Menu
int Start_Menu()
{
	int choice;

	cout << "-------- WELCOME TO THE BATTLESHIP --------" << endl << endl << endl;
	cout << "-_-_-_-_-_-_-_-   1. START GAME   -_-_-_-_-_-_-_-_-" << endl << endl;
	cout << "-_-_-_-_-_-_-_-   2.    EXIT      -_-_-_-_-_-_-_-_-" << endl << endl;
	cout << "-_-_-_-_-_-_-_-   3. Instructions -_-_-_-_-_-_-_-_-" << endl << endl << endl;
	cout << "Enter Your Prefered Choice: ";

	cin >> choice;

	system("CLS");

	return choice;

}
//This Function Will Initilize The Grid With A 0 Value
void Initializing_Grid()
{
	for (int i = 0; i < Array_Size; i++)
	{
		for (int j = 0; j < Array_Size; j++)
		{
			Background_Array[i][j] = 0;
		}
	}
}

//This Function Prints The Grid And The Location
void grid_size()
{
	char ASCII = 65;
	char column_for_index[9][9];
	int row_for_index[9][9], INDEX_NUMBER = 1;

	//This Will Print The Index For Columns
	for (int k = 0; k < Array_Size; ++k)
	{
		if (ASCII == 65)
		{
			//This Will Put A Space Before The First Character (A) is Printed
			cout << "    ";
		}
		column_for_index[0][k] = ASCII;
		cout << ASCII << "   ";
		ASCII = ASCII + 1;
	}

	//This Will Initilize The Array To Print The Index For Rows
	for (int k = 0; k < Array_Size; ++k)
	{
		row_for_index[k][0] = INDEX_NUMBER;
		INDEX_NUMBER = INDEX_NUMBER + 1;
	}

	cout << endl;

	//This Will Initilize The Array To Print The Index For Rows
	for (int i = 0; i < Array_Size; i++)
	{
		cout << row_for_index[i][0] << "   "; //For Printing Row Index
		for (int j = 0; j < Array_Size; j++)
		{
			Output_Array[i][j] = '-';
			cout << Output_Array[i][j] << "   ";  //For Printing The Grid
		}
		cout << endl;
	}
}

//This Will Assign A Random Location On Grid For Carrier
void Carrier_Assignment()
{
	int random_Number_For_Carrier;
	int Vertical_Horizontal_Choice, RANDOM_NUMBER_CARRIER;

	srand(time(NULL));   //To Generate A Random Number Each Time

	do
	{
		random_Number_For_Carrier = rand() % Array_Size;
		RANDOM_NUMBER_CARRIER = random_Number_For_Carrier;

		//This Will Check if We Go Off Grid
		if (random_Number_For_Carrier + 1 < Array_Size)
		{
			if (random_Number_For_Carrier + 2 < Array_Size)
			{
				if (random_Number_For_Carrier + 3 < Array_Size)
				{
					if (random_Number_For_Carrier + 4 < Array_Size)
					{
						break;
					}
				}
			}
		}

	} while (1);

	RANDOM_NUMBER_CARRIER = random_Number_For_Carrier;

	Vertical_Horizontal_Choice = rand() % 2;   //To Randomnly choose whether the assignment should be Row(0) or Column(1)
	if (Vertical_Horizontal_Choice == 1)
	{
		for (int i = 0; i < 5; ++i) //Here the Space Is Being Assigned
		{
			Background_Array[random_Number_For_Carrier][RANDOM_NUMBER_CARRIER] = 2;
			RANDOM_NUMBER_CARRIER++;
		}
	}
	else
	{
		for (int i = 0; i < 5; ++i)
		{
			Background_Array[RANDOM_NUMBER_CARRIER][random_Number_For_Carrier] = 2;
			RANDOM_NUMBER_CARRIER++;
		}
	}
}

//This Will Assign A Random Location On Grid For BattleShip
void BattleShip_Assignment()
{
	int random_Number_For_Battleship;
	int Vertical_Horizontal_Choice, RANDOM_NUMBER_BATTLESHIP;

	srand(time(NULL));   //To Generate A Random Number Each Time

	do
	{
		random_Number_For_Battleship = rand() % Array_Size;
		RANDOM_NUMBER_BATTLESHIP = random_Number_For_Battleship;


		//This Will Check For Overlapping With Carrier
		if (Background_Array[random_Number_For_Battleship][RANDOM_NUMBER_BATTLESHIP] == 0)
		{
			if (Background_Array[random_Number_For_Battleship][RANDOM_NUMBER_BATTLESHIP + 1] == 0)
			{
				if (Background_Array[random_Number_For_Battleship][RANDOM_NUMBER_BATTLESHIP + 2] == 0)
				{
					if (Background_Array[random_Number_For_Battleship][RANDOM_NUMBER_BATTLESHIP + 3] == 0)
					{
						//This Will Check if Go Off Grid
						if (random_Number_For_Battleship + 1 < Array_Size)
						{
							if (random_Number_For_Battleship + 2 < Array_Size)
							{
								if (random_Number_For_Battleship + 3 < Array_Size)
								{

									break;

								}
							}
						}

					}

				}
			}
		}
	} while (1);

	RANDOM_NUMBER_BATTLESHIP = random_Number_For_Battleship;

	Vertical_Horizontal_Choice = rand() % 2;   //To Randomnly choose whether the assignment should be Row(0) or Column(1)
	if (Vertical_Horizontal_Choice == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			Background_Array[random_Number_For_Battleship][RANDOM_NUMBER_BATTLESHIP] = 3;
			RANDOM_NUMBER_BATTLESHIP++;
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			Background_Array[RANDOM_NUMBER_BATTLESHIP][random_Number_For_Battleship] = 3;
			RANDOM_NUMBER_BATTLESHIP++;
		}
	}
}


//This Will Assign A Random Location On Grid For Frigate
void Frigate_Assignment()
{
	int random_Number_For_Frigate;
	int Vertical_Horizontal_Choice, RANDOM_NUMBER_FRIGATE;

	srand(time(NULL));   //To Generate A Random Number Each Time

	do
	{
		random_Number_For_Frigate = rand() % Array_Size;
		RANDOM_NUMBER_FRIGATE = random_Number_For_Frigate;

		//This will check for overlapping
		if (Background_Array[random_Number_For_Frigate][RANDOM_NUMBER_FRIGATE] == 0)
		{
			if (Background_Array[random_Number_For_Frigate][RANDOM_NUMBER_FRIGATE + 1] == 0)
			{
				if (random_Number_For_Frigate + 1 < Array_Size) //This Will Check If We Go Off Grid
				{
					break;
				}
			}
		}
	} while (1);  //This Will Make So We Don't Go Off Grid

	Vertical_Horizontal_Choice = rand() % 2;   //To Randomly choose whether the assignment should be Row(0) or Column(1)
	if (Vertical_Horizontal_Choice == 1)
	{
		for (int i = 0; i < 2; ++i)
		{
			Background_Array[random_Number_For_Frigate][RANDOM_NUMBER_FRIGATE] = 1;
			RANDOM_NUMBER_FRIGATE++;
		}
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			Background_Array[RANDOM_NUMBER_FRIGATE][random_Number_For_Frigate] = 1;
			RANDOM_NUMBER_FRIGATE++;
		}
	}
}

//This Will Assign A Random Location On Grid For Frigate
void Frigate_Assignment2()
{
	int random_Number_For_Frigate;
	int Vertical_Horizontal_Choice, RANDOM_NUMBER_FRIGATE;

	srand(time(NULL));   //To Generate A Random Number Each Time

	do
	{
		random_Number_For_Frigate = rand() % Array_Size;
		RANDOM_NUMBER_FRIGATE = random_Number_For_Frigate;

		if (Background_Array[random_Number_For_Frigate][RANDOM_NUMBER_FRIGATE] == 0)
		{
			if (Background_Array[random_Number_For_Frigate][RANDOM_NUMBER_FRIGATE + 1] == 0)
			{
				{
					if (random_Number_For_Frigate + 1 < Array_Size) //This Will Check If We Go Off Grid
					{
						break;
					}

				}
			}
		}
	} while (1);

	RANDOM_NUMBER_FRIGATE = random_Number_For_Frigate;

	Vertical_Horizontal_Choice = rand() % 2;   //To Randomnly choose whether the assignment should be Row(0) or Column(1)
	if (Vertical_Horizontal_Choice == 1)
	{
		for (int i = 0; i < 2; ++i)
		{
			Background_Array[random_Number_For_Frigate][RANDOM_NUMBER_FRIGATE] = 1;
			RANDOM_NUMBER_FRIGATE++;
		}
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			Background_Array[RANDOM_NUMBER_FRIGATE][random_Number_For_Frigate] = 1;
			RANDOM_NUMBER_FRIGATE++;
		}
	}
}


//This is For Issuing The Initial Prompts and Also Initialized The Ammo In This
int Prompt_Statements()
{
	int Ammo;

	//My Roll No. Is BSEE-22-00815 But I Divided By Two Because The Game Becomes Unbeatable If I Divide By Five
	Ammo = (Array_Size * Array_Size) / 2;

	cout << "---- Four Ships Have Been Hidden In The Grid And You Have Been Given " << Ammo << " Shells To Destroy Them All ----" << endl;
	cout << endl << "---- Specify The Location Of The Ship According To The Grid Index ----" << endl;
	cout << endl << "---- Good Luck!! ----" << endl;

	return Ammo;
}

//This Function Will Get The Column Input
void User_Input(char User_Index[])
{
	int ASCII_INPUT, j;
	Input_Column_Index = 0;
	Input_Row_Index = 0;

	for (j = 0; j < 2; j++)
	{
		ASCII_INPUT = User_Index[j];

		if (ASCII_INPUT >= 65 && ASCII_INPUT <= 90)
		{
			for (int i = 65; i < User_Index[j]; ++i)
			{
				Input_Column_Index++;
			}
		}
		else if (ASCII_INPUT >= 97 && ASCII_INPUT <= 122)
		{
			for (int i = 97; i < User_Index[j]; ++i)
			{
				Input_Column_Index++;
			}
		}
		else if (ASCII_INPUT >= 49 && ASCII_INPUT <= 57)
		{
			for (int i = 49; i < User_Index[j]; ++i)
			{
				Input_Row_Index++;
			}
		}
	}
}


//This Function Will Print The Updated Grid
void Updated_Grid_Print()
{
	//This WIll Clear The Screen So The Output Looks More Clean
	system("CLS");


	char ASCII = 65;
	char column_for_index[1][9];
	int row_for_index[9][9], INDEX_NUMBER = 1;

	//This Will Print The Index For Columns
	for (int k = 0; k < Array_Size; ++k)
	{
		if (ASCII == 65)
		{
			//This Will Put A Space Before The First Character (A) is Printed
			cout << "    ";
		}
		column_for_index[0][k] = ASCII;
		cout << ASCII << "   ";
		ASCII = ASCII + 1;
	}

	//This Will Initilize The Array To Print The Index For Rows
	for (int k = 0; k < Array_Size; ++k)
	{
		row_for_index[k][0] = INDEX_NUMBER;
		INDEX_NUMBER = INDEX_NUMBER + 1;
	}

	cout << endl;

	for (int i = 0; i < Array_Size; i++)
	{
		cout << row_for_index[i][0] << "   "; //For Printing Row Index
		for (int j = 0; j < Array_Size; j++)
		{
			cout << Output_Array[i][j] << "   ";  //For Printing The Grid Again After Updation
		}
		cout << endl;
	}
}

//This Function Will Run The Whole Game
void Game_Mechanics(int shells)
{
	char Input_1;
	int Input_2;

	//To Execute The Game Until Shells Run Out
	for (int i = 1; i <= shells; ++i)
	{
		cout << endl << "Enter The Position You Want To Target: ";
		cin >> Input[0] >> Input[1];

		User_Input(Input);

		//All Of This Is Done In The Background Array
		/*From The Previous Functions We Know That 1 Is Put In The Place Of The Frigate, 2 Is Used In The Place of Carrier Ship and 3 is Used In The Place
		of Battleship*/

		//These Conditonal Statements Will Check For Hit or Miss.


		if (Background_Array[Input_Row_Index][Input_Column_Index] == 0)
		{
			//To Update The Array According To The Change

			Output_Array[Input_Row_Index][Input_Column_Index] = 'm';
			cout << endl;

			Updated_Grid_Print();

			cout << endl << "YOU MISSED (Remaining Shells " << shells - i << " )" << endl;
		}

		else if (Background_Array[Input_Row_Index][Input_Column_Index] == 1)
		{
			//To Update The Array According To The Change

			Output_Array[Input_Row_Index][Input_Column_Index] = 'f';
			Background_Array[Input_Row_Index][Input_Column_Index] = 0;
			++Frigate_Count;

			Updated_Grid_Print();

			cout << endl << "You Landed The Hit!!! (Remaining Shells " << shells - i << " )" << endl;
		}

		else if (Background_Array[Input_Row_Index][Input_Column_Index] == 2)
		{
			//To Update The Array According To The Change

			Output_Array[Input_Row_Index][Input_Column_Index] = 'c';
			Background_Array[Input_Row_Index][Input_Column_Index] = 0;

			++Carrier_Count; //To Check For 70% Structure

			Updated_Grid_Print();

			if (Carrier_Count == 4)
			{
				cout << endl << "You Have Destroyed A Carrier" << endl;
			}

			cout << endl << "You Landed The Hit!!! (Remaining Shells " << shells - i << " )" << endl;
		}
		else if (Background_Array[Input_Row_Index][Input_Column_Index] == 3)
		{
			//To Update The Array According To The Change

			Output_Array[Input_Row_Index][Input_Column_Index] = 'b';
			Background_Array[Input_Row_Index][Input_Column_Index] = 0;

			++Battleship_Count; //To Checck For 70% Structure

			Updated_Grid_Print();

			if (Battleship_Count == 3)
			{
				cout << endl << "You Have Destroyed A BattleShip" << endl;
			}

			cout << endl << "You Landed The Hit!!! (Remaining Shells " << shells - i << " )" << endl;
		}
		if (Frigate_Count == 4 && Carrier_Count == 4 && Battleship_Count == 3)
		{

			break;

		}
	}
}


//This Function Will Print The Location Of Ships
void Final_Location_Ship()
{
	char ASCII = 65;
	char column_for_index[9][9];
	int row_for_index[9][9], INDEX_NUMBER = 1;

	//To Finally Show The Places That Were Occupied
	cout << endl << "----- The Location Of The Ships -----" << endl << endl;

	for (int i = 0; i < Array_Size; i++)
	{
		for (int j = 0; j < Array_Size; j++)
		{
			if (Background_Array[i][j] == 1)
			{
				Output_Array[i][j] = 'f';
			}

			else if (Background_Array[i][j] == 2)
			{
				Output_Array[i][j] = 'c';
			}

			else if (Background_Array[i][j] == 3)
			{
				Output_Array[i][j] = 'b';
			}
		}
	}

	//This Will Print The Index For Columns
	for (int k = 0; k < Array_Size; ++k)
	{
		if (ASCII == 65)
		{
			//This Will Put A Space Before The First Character (A) is Printed
			cout << "    ";
		}

		column_for_index[0][k] = ASCII;

		cout << ASCII << "   ";
		ASCII = ASCII + 1;
	}

	//This Will Initilize The Array To Print The Index For Rows
	for (int k = 0; k < Array_Size; ++k)
	{
		row_for_index[k][0] = INDEX_NUMBER;
		INDEX_NUMBER = INDEX_NUMBER + 1;
	}

	cout << endl;

	for (int i = 0; i < Array_Size; i++)
	{
		cout << row_for_index[i][0] << "   "; //For Printing Row Index

		for (int j = 0; j < Array_Size; j++)
		{
			cout << Output_Array[i][j] << "   ";  //For Printing The Grid Again After Updation
		}
		cout << endl;
	}

}


//This Will Check If We Have Won
void Win_Check()
{
	if (Frigate_Count == 4 && Carrier_Count >= 4 && Battleship_Count >= 3)
	{
		cout << endl << "Congratulation You Have Won!!!" << endl;
	}
	else
	{
		cout << endl << "Unfortunately, You didn't get them all" << endl;
	}
}