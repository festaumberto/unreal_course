#include <iostream>
#include <string>
#include "MAIN.H"
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void GuessBack(FText inputGuess);
bool AskToPlayAgain();

void PrintGameSummary();

FBullCowGame BCGame;



int main() {

	bool playAgain = false;

	do {
		PrintIntro();
		PlayGame();
		playAgain = AskToPlayAgain();
	} while (playAgain);

	return 0;

}

void PlayGame()
{

	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	//constexpr int32 GUESSES = 5;

	//repeat the guess
	while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= BCGame.GetMaxTries())){
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		GuessBack(Guess);
	}

	PrintGameSummary();
	
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking of?\n";
	return;
}

FText GetValidGuess() {

	EWordStatus WordStatus;
	FText Guess = "";

	do {
		//get input from player
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << currentTry << " Give me your guess: ";
		
		std::getline(std::cin, Guess);

		WordStatus = BCGame.CheckGuessValidity(Guess);

		switch (WordStatus)
		{
		case EWordStatus::Not_Isogram: {
			std::cout << "Please enter an isogram word!" << std::endl;
			break;
		}
		case EWordStatus::Not_Lowercase: {
			std::cout << "Please enter a lowercase word!" << std::endl;
			break;
		}
		case EWordStatus::Wrong_Lenght: {
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " characters long word!" << std::endl;
			break;
		}
		default:
			break;
		}
	} while (WordStatus != EWordStatus::OK);

	return Guess;
}

void GuessBack(FText inputGuess) {

	std::cout << "Your guess: " << inputGuess << std::endl;
}

bool AskToPlayAgain() {
	std::cout << "Play again?";
	FText resp = "";
	std::getline(std::cin, resp);

	return (resp[0] == 'y') || (resp[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "YOU WIN!";
	}
	else {
		std::cout << "YOU LOSE!";
	}
	std::cout << std::endl;

}
