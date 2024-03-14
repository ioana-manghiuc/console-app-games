#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

// algorithm chooses a random word from file as the answer
std::string ChooseWord(std::ifstream& file)
{
	std::mt19937 rng(std::time(0)); 
	if (!file.is_open()) {
		std::cerr << "Error opening file.\n" << std::endl;
		return "";
	}

	std::vector<std::string> words;
	std::string line;
	while (std::getline(file, line)) {
		words.push_back(line);
	}

	std::uniform_int_distribution<int> dist(0, words.size() - 1);
	return words[dist(rng)];
}

// forms a word with _ * answer.length()
// this word will be used to track user progress 

std::string FormGuess(const std::string& answer)
{
	std::string guess = "";
	for (int i = 0; i < answer.length(); i++)
	{
		guess = guess + "_";
	}
	return guess;
}

// counts appearance of user input in case the letter appears multiple times

int CountLetterAppearance(const std::string& answer, char letter)
{
	int count = 0;
	for (int i = 0; i < answer.length(); i++)
	{
		for (int i = 0; i < answer.length(); i++)
		{
			if (answer[i] == letter)
			{
				count++;
			}
		}
	}
	return count;
}

//plays game by looking for user input in answer string and handling all cases
// 1. letter is found => replaced in guess string as many times as it appears, read input again
// 2. letter is wrong => number of tries decreseas, read input again
// 3. tries > 0 but guess == answer => game won
// 4. tries == 0 but guess != answer => game lost

void PlayHangman(const std::string& answer, std::string guess)
{
	int tries = 6;
	std::string usedLetters = "";

	while (tries != 0)
	{
		char userInput;
		std::cout << "\nEnter a letter: "; std::cin >> userInput;

		if (usedLetters.find(userInput) != std::string::npos)
		{
			std::cout << "You already guessed that letter. Try a different one!\n";
			continue;
		}

		usedLetters += userInput;

		if (CountLetterAppearance(answer, userInput) > 0)
		{
			for (int i = 0; i < answer.length(); i++)
			{
				if (answer[i] == userInput)
				{
					guess[i] = userInput;
				}
			}
			std::cout << guess << "\n";
		}
		else if (CountLetterAppearance(answer, userInput) == 0)
		{
			tries--;
			std::cout << "The letter " << userInput << " is wrong! Try again.\nTries left: " << tries << "\n";
		}
		if (guess == answer)
		{
			std::cout << "\nCONGRATULATIONS - YOU WON!! :D \nYou guessed the word: " << answer << "\n";
			break;
		}
	}
	if (tries == 0)
	{
		std::cout << "\nSorry, it seems you didn't get it right.\nAnswer: " << answer << "\nBetter luck next time! <3\n";
	}
}

int main()
{
	std::ifstream file("words.txt");
	std::string answer = ChooseWord(file);
	std::string guess = FormGuess(answer);
	std::cout << "You have " << guess.length() << " letters to guess!\n" << guess << "\n";
	PlayHangman(answer, guess);

	return 0;
}