#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map
using int32 = int;


FBullCowGame::FBullCowGame(){Reset();}

int32 FBullCowGame::GetMaxTries()const{return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry()const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon()const{return bGameIsWon;}

bool FBullCowGame::IsIsogram(FString word)const
{	
	// treat 0 and 1 letter words as Isograms
	if (word.length() <= 1) { return true; }
	
	TMap<char, bool>LetterSeen;
	for (auto Letter: word)
	{	
		Letter = tolower(Letter);
		if (LetterSeen[Letter]){
			return false; 
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; 
}

bool FBullCowGame::IsLowerCase(FString word) const
{
	for (auto Letter : word) 
	{
		if (!islower(Letter)) { return false; }
	};
	
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{

	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;//TODO write function 
	}
	else if (Guess.length() != GetHiddenWordLength())//if the guess length is worng
	{
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}	
		// return an error
		//If the guess lengh is wrong
		// return an error
	//Otherwise
		//return OK

	return EGuessStatus::OK;
}//TODO make actual error

// receives a VALID guess, increments turn and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;	

	//loop through all letters in the hidden word													  
	int32 WordLength = GetHiddenWordLength();// assuming same length as guess

	for (int32 MHWChar = 0; MHWChar <WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar <WordLength; GChar++)
		{
			//if they match then	
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{//if they're in the same place
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //increment cows
				}
			}
						
		}
			
	}	
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}



void FBullCowGame::Reset() 
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
