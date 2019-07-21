#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int32 main()
{
    bool bPlayAgain = false;
    do{
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
    constexpr int32 WORD_LENGTH = 5;
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
}

void PlayGame()
{
    BCGame.Reset;
    int32 MaxTries = BCGame.GetMaxTries();

    //TODO change for to while loop
    for (int32 i = 0; i < MaxTries; i++)
    {
        FText Guess = GetGuess(); //TODO make loop checking valid

        //Submit valid Guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

        //Print the number of Bulls and Cows
        std::cout << "\nBulls = " << BullCowCount.Bulls;
        std::cout << "\nCows = " << BullCowCount.Cows;
    }

    //TODO summarise the game   
}

FText GetGuess()
{
    int32 CurrentTry = BCGame.GetCurrentTry();
    std::cout << "Try " << CurrentTry << "Enter your guess: ";
    FText Guess = "";
    std::getline(std::cin, Guess);
    return Guess;
}

bool AskToPlayGame()
{
    std::cout << "Do you want to play again (y/n)?\n";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}