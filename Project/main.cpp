/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <windows.h>
using FText = std::string;
using int32 = int;

void PlayGame();

void PrintIntro();
FText GetValidGuess();
// Play the game loop by doing these steps on each try: reset the data, get maxtries, 
//get a valid guess and print the result of that try.
void PlayGame();
void PrintGameSummary();
bool AskToPlay(void);


//Main Object that controls the game
FBullCowGame BCGame;

int main()
{	//set the prompt size
	HWND console = GetConsoleWindow();
	RECT r;
	//stores the console's current dimensions
	GetWindowRect(console, &r); 
	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 560, 600, TRUE);
	
	bool bPlayAgain = false;
	//Print introduction
	PrintIntro();
	//pause before starting game
	std::system("pause");
	do
	{		
		PlayGame(); 
		bPlayAgain = AskToPlay();
		std::cout << std::endl;
	} while (bPlayAgain);
}

/// Functions Definitions.
// just print introduction , explain the game and input limitatGetValidGuessions
void PrintIntro()
{	
	std::cout << "\n\n";
	std::cout << "	       ===================================\n";
	std::cout << "			 Bull and Cows \n";
	std::cout << "	       ===================================\n";
	std::cout << "			    ()___()\n";
	std::cout << "			    < O O >\n";
	std::cout << "			      | |\n";
	std::cout << "			     {o_o}\n";
	std::cout << "			      (!)\n";
	std::cout << "	       ===================================\n\n";
	std::cout << "	    Welcome to Bull and Cows, a fun word game!\n\n";
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "****************************************************************\n";
	std::cout << "An Isogram is a word or phrase without a repeating letter and/or\n";
	std::cout << " non-alphabetic letters.\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	std::cout << "****************************************************************\n";
	std::cout << "----------------------------------------------------------------\n";
	std::cout << std::endl;
	std::cout << "Let's start playing this challenging game!! \n";
	std::cout << "\n";
	
	std::cout << "\n\n";
	return;

}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{

		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries();
		std::cout <<". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a with no upper letters and lettters from a to z. \n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
		
		
	} while (Status != EGuessStatus::OK); //Keep looping until we get no errors
	return Guess;
}

bool AskToPlay()
{
	
	std::cout << "Do you want to play again with the same hidden word(y/n)? ";	
	FText Response="";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');	
	
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Loop asking for guesses whule the game is NOT won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//print number f bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " . Cows = " << BullCowCount.Cows << "\n\n";

	}
	
	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{	
		std::cout << "/////////     Well done - You Win!     //////////\n" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time \n" << std::endl;
	}
}
