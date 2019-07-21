#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//To make syntax Unreal friendly
using FText = std::string;

//Function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	//Instantiate a new game, reused for each plays

//Entry point of application
int32 main()
{
    bool bPlayAgain = false;
    do{
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);

	return 0;	//Exit the application
}

void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()<< " letter isogram I'm thinking of?\n";
}

//Plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
		
        //Submit valid Guess to the game and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << "\tCows = " << BullCowCount.Cows << "\n";
    }

	PrintGameSummary();
	return;
}

FText GetValidGuess()	//Loop continuously until the user gives a valid guess
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
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
			std::cout << "Please enter all lowercse letters.\n\n";
			break;
		default:
			//Assume that the default case is OKAY
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again (y/n)?\n";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "\nWELL DONE YOU WON!!\n\n\n";
	else
		std::cout << "\nBETTER LUCK NEXT TIME\n\n\n";
}
