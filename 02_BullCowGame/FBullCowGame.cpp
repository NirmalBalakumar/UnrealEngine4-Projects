#include "FBullCowGame.h"

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    
    const FString HIDDEN_WORD = "planet"; 
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    return;
}

bool FBullCowGame::IsGameWon() const
{

}

bool FBullCowGame::CheckGuessValidity(FString Guess)
{

}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{

    //Increment the turn number
    MyCurrentTry++;

    //Setup a return variable
    FBullCowCount BullCowCount;

    //Loop through all letters in the guess
    int32 HiddenWordLength = MyHiddenWord.length();
    for(int32 i = 0; i < HiddenWordLength; i++)
    {
        for(int32 j = 0; j < HiddenWordLength; j++)
        {
            if(MyHiddenWord[i] == Guess[j])
            {
                if(i == j) BullCowCount.Bulls++;
                else    BullCowCount.Cows++;
            }
        }
    }
    
    return BullCowCount;
}