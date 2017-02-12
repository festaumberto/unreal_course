#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	constexpr int32 MAX_TRIES = 8;

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess)) {
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) {
		return EWordStatus::Wrong_Lenght;
	}else
		return EWordStatus::OK;
}

bool FBullCowGame::IsGameWon() const
{

	return bGameWon;
}
int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}
//received a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString input)
{
	// increment the turn number
	MyCurrentTry++;
	//setup a return variable 
	FBullCowCount toReturn;
	//loop through letters in the guess
	for (int32 i = 0; i < MyHiddenWord.length(); i++) {
		//compare letters against the hidden word
		for (int32 j = 0; j < MyHiddenWord.length(); j++) {
			//if they match then
			if (MyHiddenWord[i] == input[j]) {
				//if they are in the same place
				if (i == j) {
					//increment bulls
					toReturn.Bulls++;
				}else {
					//increment cows
					toReturn.Cows++;
				}
			}
		}
	}

	if (toReturn.Bulls == MyHiddenWord.length())
		bGameWon = true;
	else
		bGameWon = false;

	return toReturn;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
		return true;

	TMap<char,bool> LetterSeen;
	for (auto Letter : Guess) {

		Letter = tolower(Letter);

		if (LetterSeen[Letter] == true)
			return false;
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length() == 0)
		return true;

	for (auto Letter : Guess) {
		if (!islower(Letter))
			return false;
	}

	return true;
}
