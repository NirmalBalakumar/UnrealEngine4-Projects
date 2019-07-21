#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//All values initialized to 0
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};


class FBullCowGame 
{
public:
    FBullCowGame();
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    bool IsGameWon() const;
    void Reset();   //TODO make a more rich return value.
    bool CheckGuessValidity(FString);   //TODO make a more rich return value.

    //counts bulls & cows, increases try number assuming valid guess
    FBullCowCount SubmitGuess(FString);

private:
    //see constructor for initialization
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
};