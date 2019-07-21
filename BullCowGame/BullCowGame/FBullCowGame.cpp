#pragma once
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }	//Default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const 
{
	//Braced intialized sytax
	Tmap<int32, int32> WordLenghtToMaxtries{ {3,4} , {4,7} , {5,10} , {6,16} , {7,20} };
	return WordLenghtToMaxtries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()	//Constructor
{
    constexpr int32 MAX_TRIES = 5;
    MyMaxTries = MAX_TRIES;
    
    const FString HIDDEN_WORD = "plane";	//This must be an Isogram
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //Assuming same length as guess
    									  
	//Loop through all letters in the guess
    for(int32 HWChar = 0; HWChar < WordLength; HWChar++)
    {
        for(int32 GWChar = 0; GWChar < WordLength; GWChar++)
        {
            if(MyHiddenWord[HWChar] == Guess[GWChar])
            {
                if(HWChar == GWChar) BullCowCount.Bulls++;
                else    BullCowCount.Cows++;
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

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//Treat 0 and 1 letter words as Isograms
	if (Guess.length() < 2) { return true;  }

	Tmap<char, bool> LetterSeen;	//Setup map (Hash Table)
	for (auto Letter : Guess)		//Ranged For loop (Foreach Loop), Auto decides the type
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])		//If Letter is in the map
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;	//Add the Letter to the map as seen
		}
	}
	return true;	//For example in case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length() < 1) { return true; }

	for (auto Letter : Guess)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}
