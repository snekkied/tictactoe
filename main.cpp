#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
using namespace std;

// Menu options - +1 automatically added to each unspecified option
enum MenuChoice {
	PVP = 1,
	PVC,
	QUIT,
	NO_CHOICE = -1
};

char gridSquare[10] = { 'o','1','2','3','4','5','6','7','8','9' }; //grid contents
char mark;

int displayMenu();
int checkWin();
void board();
int playTicTacToe();
int compTicTacToe();
void displayQuit();

int main()
{
	int choice = NO_CHOICE;

	do {
		// Display MENU & get input (1/2/3)
		system("cls");
		choice = displayMenu();

		if (choice == MenuChoice::PVP)
		{
			system("cls");
			playTicTacToe();
		}
		else if (choice == MenuChoice::PVC)
		{
			system("cls");
			compTicTacToe();
		}

	} while (choice != QUIT);
	//loops while player choice isnt QUIT_GAME

	system("cls");

	//display quit message
	displayQuit();
}

int displayMenu()
{
	int choice = NO_CHOICE;

	string error = "";

	do
	{
		cout << "        =============================\n";
		cout << "        ||  Welcome to TICTACTOE!  ||\n";
		cout << "        =============================\n\n" << endl;

		cout << "\t   1) Player Vs Player\n" << endl;
		cout << "\t   2) Player Vs AI\n" << endl;
		cout << "\t   3) Exit Game\n\n" << endl;

		if (error.empty() == false)
		{
			cout << error << "\n\n";    //display error
			error = "";                 //clear the error
		}

		cout << "  Enter the number of your choice (1/2/3) > ";
		cin >> choice;
		cout << "\n";

		if (choice < 1 || choice > 3)
		{
			error = "   {ERROR: INVALID NUMBER. PLEASE CHOOSE EITHER 1, 2 OR 3.}";
			system("cls");
		}
		else
		{
			//clear the error on a correct choice
			error.clear();
		}

	} while (error.empty() == false);

	// check if valid choice
	// show error and get choice again if invalid - LOOP

	return choice;
}

void displayQuit()
{
	cout << "Bye, you quit!\n\n";
}

int playTicTacToe()
{
	int player = 1, i = 0, choice;

	char mark; //mark the player's position on the board

	do
	{
		board();
		player = (player % 2) ? 1 : 2; //swaps between players

		cout << "    Player " << player << ", enter a number: ";
		cin >> choice;

		mark = (player == 1) ? 'X' : 'O';

		if (choice == 1 && gridSquare[1] == '1')
			gridSquare[1] = mark;

		else if (choice == 2 && gridSquare[2] == '2')
			gridSquare[2] = mark;

		else if (choice == 3 && gridSquare[3] == '3')
			gridSquare[3] = mark;

		else if (choice == 4 && gridSquare[4] == '4')
			gridSquare[4] = mark;

		else if (choice == 5 && gridSquare[5] == '5')
			gridSquare[5] = mark;

		else if (choice == 6 && gridSquare[6] == '6')
			gridSquare[6] = mark;

		else if (choice == 7 && gridSquare[7] == '7')
			gridSquare[7] = mark;

		else if (choice == 8 && gridSquare[8] == '8')
			gridSquare[8] = mark;

		else if (choice == 9 && gridSquare[9] == '9')
			gridSquare[9] = mark;

		else //error if move is invalid
		{
			cout << "ERROR! Invalid Move; Try Again.";

			player--;
			cin.ignore();
			cin.get();
		}

		i = checkWin();
		player++;
	} while (i == -1);

	board();

	if (i == 1)
		cout << "Congratulations! Player " << --player << " wins!";
	else
		cout << "It's a draw!";

	cin.ignore();
	cin.get();

	return 0;
}

int compChoice(int choice)
{
	//horizontal
	if (gridSquare[1] == gridSquare[2])
		choice = 3;

	else if (gridSquare[2] == gridSquare[3])
		choice = 1;

	else if (gridSquare[4] == gridSquare[5])
		choice = 6;

	else if (gridSquare[5] == gridSquare[6])
		choice = 4;

	else if (gridSquare[7] == gridSquare[8])
		choice = 9;

	else if (gridSquare[8] == gridSquare[9])
		choice = 7;

	else if (gridSquare[1] == gridSquare[3])
		choice = 2;

	else if (gridSquare[4] == gridSquare[6])
		choice = 5;

	else if (gridSquare[7] == gridSquare[9])
		choice = 8;


	//vertical
	else if (gridSquare[1] == gridSquare[4])
		choice = 7;

	else if (gridSquare[4] == gridSquare[7])
		choice = 1;

	else if (gridSquare[2] == gridSquare[5])
		choice = 8;

	else if (gridSquare[5] == gridSquare[8])
		choice = 2;

	else if (gridSquare[3] == gridSquare[6])
		choice = 9;

	else if (gridSquare[6] == gridSquare[9])
		choice = 3;

	else if (gridSquare[1] == gridSquare[7])
		choice = 4;

	else if (gridSquare[2] == gridSquare[8])
		choice = 5;

	else if (gridSquare[3] == gridSquare[9])
		choice = 6;


	//diagonal
	else if (gridSquare[1] == gridSquare[5])
		choice = 9;

	else if (gridSquare[5] == gridSquare[9])
		choice = 1;

	else if (gridSquare[3] == gridSquare[5])
		choice = 7;

	else if (gridSquare[5] == gridSquare[7])
		choice = 3;

	else if (gridSquare[1] == gridSquare[9])
		choice = 5;

	else if (gridSquare[3] == gridSquare[7])
		choice = 5;

	//centre
	else choice = 5;

	return choice;
}

int compTicTacToe()
{
	int player = 1, i = 0, choice{}, choiceAI{ compChoice(choice) };

	char mark; //mark the player's position on the board

	do
	{
		board();

		if (player % 2 == 1)
			player = 1;
		else player = 2;

		if (player == 2)
		{
			cout << "    It's Player " << player << "'s turn! Press enter to continue.";

			choiceAI = compChoice(choice);
			
			mark = 'O';

			int turn = 1;
			int placed = 0;

			while (placed == 0)
			{
				if (choiceAI == 1 && gridSquare[1] == '1')
				{
					if (gridSquare[1] == mark)
						choiceAI++, player--;
					else gridSquare[1] = mark, placed = 1;
				}
					
				else if (choiceAI == 2 && gridSquare[2] == '2')
				{
					if (gridSquare[2] == mark)
						choiceAI++, player--;
					else gridSquare[2] = mark, placed = 1;
				}

				else if (choiceAI == 3 && gridSquare[3] == '3')
				{
					if (gridSquare[3] == mark)
						choiceAI++, player--;
					else gridSquare[3] = mark, placed = 1;
				}

				else if (choiceAI == 4 && gridSquare[4] == '4')
				{
					if (gridSquare[4] == mark)
						choiceAI++, player--;
					else gridSquare[4] = mark, placed = 1;
				}

				else if (choiceAI == 5 && gridSquare[5] == '5')
				{
					if (gridSquare[5] == mark)
						choiceAI++, player--;
					else gridSquare[5] = mark, placed = 1;
				}

				else if (choiceAI == 6 && gridSquare[6] == '6')
				{
					if (gridSquare[6] == mark)
						choiceAI++, player--;
					else gridSquare[6] = mark, placed = 1;
				}

				else if (choiceAI == 7 && gridSquare[7] == '7')
				{
					if (gridSquare[7] == mark)
						choiceAI++, player--;
					else gridSquare[7] = mark, placed = 1;
				}

				else if (choiceAI == 8 && gridSquare[8] == '8')
				{
					if (gridSquare[8] == mark)
						choiceAI++, player--;
					else gridSquare[8] = mark, placed = 1;
				}

				else if (choiceAI == 9 && gridSquare[9] == '9')
				{
					if (gridSquare[9] == mark)
						choiceAI--, player--;
					else gridSquare[9] = mark, placed = 1;
				}
			}

			i = checkWin();
			player++;

			board();
		}

		else if (player == 1)
		{
			cout << "    Player " << player << ", enter a number: ";
			cin >> choice;

			mark = 'X';

			if (choice == 1 && gridSquare[1] == '1')
				gridSquare[1] = mark;

			else if (choice == 2 && gridSquare[2] == '2')
				gridSquare[2] = mark;

			else if (choice == 3 && gridSquare[3] == '3')
				gridSquare[3] = mark;

			else if (choice == 4 && gridSquare[4] == '4')
				gridSquare[4] = mark;

			else if (choice == 5 && gridSquare[5] == '5')
				gridSquare[5] = mark;

			else if (choice == 6 && gridSquare[6] == '6')
				gridSquare[6] = mark;

			else if (choice == 7 && gridSquare[7] == '7')
				gridSquare[7] = mark;

			else if (choice == 8 && gridSquare[8] == '8')
				gridSquare[8] = mark;

			else if (choice == 9 && gridSquare[9] == '9')
				gridSquare[9] = mark;

			else //error if move is invalid
			{
				cout << "ERROR! Invalid Move; Try Again.";

				player--;
				cin.ignore();
				cin.get();
			}

			i = checkWin();
			player++;
		}
	} while (i == -1);

	board();

	if (i == 1)
		cout << "Congratulations! Player " << --player << " wins!";
	else
		cout << "It's a draw!";

	cin.ignore();
	cin.get();

	return 0;
}

int checkWin()
{
	//1 = Game is over w/ result
	//-1 = Game is in progress
	//0 = Game is over w/ no result (draw)

	//check horizontal wins
	if (gridSquare[1] == gridSquare[2] && gridSquare[2] == gridSquare[3])
		return 1;

	else if (gridSquare[4] == gridSquare[5] && gridSquare[5] == gridSquare[6])
		return 1;

	else if (gridSquare[7] == gridSquare[8] && gridSquare[8] == gridSquare[9])
		return 1;

	//check vertical win
	else if (gridSquare[1] == gridSquare[4] && gridSquare[4] == gridSquare[7])
		return 1;

	else if (gridSquare[2] == gridSquare[5] && gridSquare[5] == gridSquare[8])
		return 1;

	else if (gridSquare[3] == gridSquare[6] && gridSquare[6] == gridSquare[9])
		return 1;

	//check diagonal win
	else if (gridSquare[1] == gridSquare[5] && gridSquare[5] == gridSquare[9])
		return 1;

	else if (gridSquare[3] == gridSquare[5] && gridSquare[5] == gridSquare[7])
		return 1;

	//otherwise loss
	else if (gridSquare[1] != '1' && gridSquare[2] != '2' && gridSquare[3] != '3'
		&& gridSquare[4] != '4' && gridSquare[5] != '5' && gridSquare[6] != '6'
		&& gridSquare[7] != '7' && gridSquare[8] != '8' && gridSquare[9] != '9')
		return 0;

	else
		return -1;
}

void board() //draws the board
{
	system("cls");

	cout << "\n\t" << "== TIC TAC TOE ==" << "\n\n";

	cout << "  PLAYER 1 = [X] || PLAYER 2 = [O]" << "\n\n" << endl;

	cout << "\t     |     |     " << endl;

	cout << "\t  " << gridSquare[1] << "  |  " << gridSquare[2] << "  |  " << gridSquare[3] << endl;

	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;

	cout << "\t  " << gridSquare[4] << "  |  " << gridSquare[5] << "  |  " << gridSquare[6] << endl;

	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;

	cout << "\t  " << gridSquare[7] << "  |  " << gridSquare[8] << "  |  " << gridSquare[9] << endl;

	cout << "\t     |     |     \n" << endl << endl;
}
