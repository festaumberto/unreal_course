#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Lenght
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	void Reset(); // TODO arricchire il ritorno
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	EWordStatus CheckGuessValidity(FString);
	bool IsGameWon() const;

	int32 GetHiddenWordLenght() const;

	FBullCowCount SubmitGuess(FString);

private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};