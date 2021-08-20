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

char board[3][3] =
{
	{ gridSquare[1], gridSquare[2], gridSquare[3] },
	{ gridSquare[4], gridSquare[5], gridSquare[6] },
	{ gridSquare[7], gridSquare[8], gridSquare[9] }
};

int displayMenu();
int checkWin();
void boardGS();
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
		boardGS();
		player = (player % 2) ? 1 : 2; //swaps between players

		cout << "    Player " << player << ", enter a number: ";
		cin >> choice;

		mark = (player == 1) ? 'X' : 'O';

		if (choice == 1 && gridSquare[1] == '1')
			board[0][0] = mark;

		else if (choice == 2 && gridSquare[2] == '2')
			board[0][1] = mark;

		else if (choice == 3 && gridSquare[3] == '3')
			board[0][2] = mark;

		else if (choice == 4 && gridSquare[4] == '4')
			board[1][0] = mark;

		else if (choice == 5 && gridSquare[5] == '5')
			board[1][1] = mark;

		else if (choice == 6 && gridSquare[6] == '6')
			board[1][2] = mark;

		else if (choice == 7 && gridSquare[7] == '7')
			board[2][0] = mark;

		else if (choice == 8 && gridSquare[8] == '8')
			board[2][1] = mark;

		else if (choice == 9 && gridSquare[9] == '9')
			board[2][2] = mark;

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

	boardGS();

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
	else choice = rand() % 9;

	return choice;
}

struct  Move
{
	int row, column;
};

char p1 = 'X', p2 = 'O';

//are there any moves left on the board? returns false if no.
bool areMovesLeft(char board[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == '_')
				return true;
	return false;
}

//returns value based on who is winning
int evaluateWinner(char eBoard[3][3])
{
	//check rows for x/o victory
	for (int row = 0; row < 3; row++)
	{
		if (eBoard[row][0] == eBoard[row][1] && eBoard[row][1] == eBoard[row][2])
		{
			if (eBoard[row][0] == p1)
				return +10;
			else if (eBoard[row][0] == p2)
				return -10;
		}
	}

	//check columns for x/o victory
	for (int column = 0; column < 3; column++)
	{
		if (eBoard[0][column] == eBoard[1][column] && eBoard[1][column] == eBoard[2][column])
		{
			if (eBoard[0][column] == p1)
				return +10;
			else if (eBoard[0][column == p2])
				return -10;
		}
	}

	//check diagonals for x/o victory
	if (eBoard[0][0] == eBoard[1][1] && eBoard[1][1] == eBoard[2][2])
	{
		if (eBoard[0][0] == p1)
			return +10;
		else if (eBoard[0][0] == p2)
			return -10;
	}

	if (eBoard[0][2] == eBoard[1][1] && eBoard[1][1] == eBoard[2][0])
	{
		if (eBoard[0][2] == p1)
			return +10;
		else if (eBoard[0][2] == p2)
			return -10;
	}

	//if none have won, return 0
	return 0;
}

//minimax function considers all ways the game can go and returns the board value
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluateWinner(board);

	//if player has won
	if (score == 10) 
		return score;

	//if AI has won
	if (score == -10)
		return score;

	//draw
	if (areMovesLeft(board) == false)
		return 0;

	//if player's move
	if (isMax)
	{
		int best = -1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == '_')
				{
					//make move
					board[i][j] = p1;

					best = max(best, minimax(board, depth + 1, !isMax));

					//undo move
					board[i][j] = '_';
				}
			}
		}

		return best;
	}

	//if AI's move
	else
	{
		int best = 1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == '_')
				{
					board[i][j] = p2;

					best = min(best, minimax(board, depth + 1, !isMax));

					board[i][j] = '_';
				}
			}
		}

		return best;
	}
}

Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.column = -1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == '_')
			{
				board[i][j] = p1;

				int moveVal = minimax(board, 0, false);

				board[i][j] = '_';

				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.column = j;
					bestVal = moveVal;
				}
			}
		}
	}

	return bestMove;
}

int compTicTacToe()
{
	int player = 1, i = 0, choice, choiceAI;

	char mark; //mark the player's position on the board

	do
	{
		boardGS();

		if (player % 2 == 1)
			player = 1;
		else player = 2;

		if (player == 2)
		{
			cout << "    It's Player " << player << "'s turn! Press enter to continue.";

			choiceAI = compChoice(choice);

			Move bestMove = findBestMove(board);

			if (bestMove.column == 0 && bestMove.row == 0) choiceAI = 1;
			else if (bestMove.column == 1 && bestMove.row == 0) choiceAI = 2;
			else if (bestMove.column == 2 && bestMove.row == 0) choiceAI = 3;
			else if (bestMove.column == 0 && bestMove.row == 1) choiceAI = 4;
			else if (bestMove.column == 1 && bestMove.row == 1) choiceAI = 5;
			else if (bestMove.column == 2 && bestMove.row == 1) choiceAI = 6;
			else if (bestMove.column == 0 && bestMove.row == 2) choiceAI = 7;
			else if (bestMove.column == 1 && bestMove.row == 2) choiceAI = 8;
			else if (bestMove.column == 2 && bestMove.row == 2) choiceAI = 9;
			
			mark = 'O';

			int turn = 1;
			int placed = 0;

			while (placed == 0)
			{
				if (choiceAI == 1 && gridSquare[1] == '1')
					board[0][0] = mark, placed = 1;

				else if (choiceAI == 2 && gridSquare[2] == '2')
					board[0][1] = mark, placed = 1;

				else if (choiceAI == 3 && gridSquare[3] == '3')
					board[0][2] = mark, placed = 1;

				else if (choiceAI == 4 && gridSquare[4] == '4')
					board[1][0] = mark, placed = 1;

				else if (choiceAI == 5 && gridSquare[5] == '5')
					board[1][1] = mark, placed = 1;

				else if (choiceAI == 6 && gridSquare[6] == '6')
					board[1][2] = mark, placed = 1;

				else if (choiceAI == 7 && gridSquare[7] == '7')
					board[2][0] = mark, placed = 1;

				else if (choiceAI == 8 && gridSquare[8] == '8')
					board[2][1] = mark, placed = 1;

				else if (choiceAI == 9 && gridSquare[9] == '9')
					board[2][2] = mark, placed = 1;

			}

			i = checkWin();
			player++;

			boardGS();
		}

		else if (player == 1)
		{
			cout << "    Player " << player << ", enter a number: ";
			cin >> choice;

			mark = 'X';

			if (choice == 1 && gridSquare[1] == '1')
				board[0][0] = mark;

			else if (choice == 2 && gridSquare[2] == '2')
				board[0][1] = mark;

			else if (choice == 3 && gridSquare[3] == '3')
				board[0][2] = mark;

			else if (choice == 4 && gridSquare[4] == '4')
				board[1][0] = mark;

			else if (choice == 5 && gridSquare[5] == '5')
				board[1][1] = mark;

			else if (choice == 6 && gridSquare[6] == '6')
				board[1][2] = mark;

			else if (choice == 7 && gridSquare[7] == '7')
				board[2][0] = mark;

			else if (choice == 8 && gridSquare[8] == '8')
				board[2][1] = mark;

			else if (choice == 9 && gridSquare[9] == '9')
				board[2][2] = mark;

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

	boardGS();

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
	if (board[0][0] == board[0][1] && board[0][1] == board[0][2])
		return 1;

	else if (board[1][0] == board[1][1] && board[1][1] == board[1][2])
		return 1;

	else if (board[2][0] == board[2][1] && board[2][1] == board[2][2])
		return 1;

	//check vertical win
	else if (board[0][0] == board[1][0] && board[1][0] == board[2][0])
		return 1;

	else if (board[0][1] == board[1][1] && board[1][1] == board[2][1])
		return 1;

	else if (board[0][2] == board[1][2] && board[1][2] == board[2][2])
		return 1;

	//check diagonal win
	else if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
		return 1;

	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
		return 1;

	//otherwise loss
	else if (board[0][0] != '1' && board[0][1] != '2' && board[0][2] != '3'
		&& board[1][0] != '4' && board[1][1] != '5' && board[1][2] != '6'
		&& board[2][0] != '7' && board[2][1] != '8' && board[2][2] != '9')
		return 0;

	else
		return -1;
}

void boardGS() //draws the board
{
	system("cls");

	cout << "\n\t" << "== TIC TAC TOE ==" << "\n\n";

	cout << "  PLAYER 1 = [X] || PLAYER 2 = [O]" << "\n\n" << endl;

	cout << "\t     |     |     " << endl;

	cout << "\t  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;

	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;

	cout << "\t  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;

	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;

	cout << "\t  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;

	cout << "\t     |     |     \n" << endl << endl;
}
