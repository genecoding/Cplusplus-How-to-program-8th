#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using std::string;
using std::ifstream;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;

const int GUESS_TIMES = 7;
const char HANGMAN[][4] =
{{' ', '0', ' '},
 {'/', '|', '\\'},
 {' ', '|', ' '},
 {'/', ' ', '\\'}};

string pickAWord();
bool guessTheWord(string);
bool checkTheGuess(string, string &, char);
void printHangman(int);
void showAllGuesses(string);
void showResult(int, string);

int main()
{
	srand(time(0));
	string word;
	bool hitWord;
	char conti;

	do{
		word = pickAWord();
		hitWord = guessTheWord(word);

		if(hitWord)
			cout << "Congratulations!!! You guessed my word.";
		else 
			cout << "Fail!!! You died.";

		cout << " The word is " << word << ".\nPlay again? Y/N: ";
		cin >> conti;
	} while(conti == 'y' || conti == 'Y');

	return 0;
}

bool guessTheWord(string word)
{
	int len = word.length();
	int guessTimes = 0;
	int wrongTimes = 0;
	string guessedWord(len, 'X');  //initialize user's guess as "XXX...X"
	char guessedAlph;
	string allGuessedAlph;
	bool hitAlph;

	do{
		cout << "Guess the word\t" << guessedWord << endl;
		cin >> guessedAlph;
		guessedAlph = tolower(guessedAlph);

		//check if the guess repeat
		if(allGuessedAlph.find(guessedAlph) != std::string::npos) {  //repeat guess
			cout << "You have guessed it." << endl;
			showResult(wrongTimes, allGuessedAlph);
			continue;
		} else
			allGuessedAlph += guessedAlph;

		//check if the guess hit
		hitAlph = checkTheGuess(word, guessedWord, guessedAlph);
		guessTimes++;

		if(hitAlph)
			cout << "Yes, you got it!" << endl;
		else {
			cout << "No, it's wrong!" << endl;
			wrongTimes++;
		}
			
		showResult(wrongTimes, allGuessedAlph);

		if(word == guessedWord)
			return true;
	} while(wrongTimes < GUESS_TIMES);

	return false;
}

void showResult(int wrongTimes, string allGuessedAlph)
{
	printHangman(wrongTimes);
	showAllGuesses(allGuessedAlph);
	cout << endl;
}

bool checkTheGuess(string word, string &guessedWord, char guessedAlph)
{
	bool hit = false;
	int len = word.length();

	for(int i = 0; i < len; i++) {
		if(tolower(word[i]) == guessedAlph) {
			guessedWord[i] = guessedAlph;
			hit = true;
		}
	}

	return hit;
}

void printHangman(int ctr)
{
	int times = 0;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 3; j++) {
			if(times < ctr && HANGMAN[i][j] != ' ') {  //print the body part
				cout << HANGMAN[i][j];
				times++;
			} else
				cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void showAllGuesses(string allGuessedAlph)
{
	cout << "All your guesses: ";
	for(int i = 0; i < allGuessedAlph.length(); i++)
		cout << allGuessedAlph[i] << ' ';

	cout << endl;
}

string pickAWord()
{
	ifstream inFile("3000 voc.txt", std::ios::in);
	if(!inFile) {
		cerr << "File cannot be opened." << endl;
		exit(1);
	}

	//pick a vocabulary randomly
	string voc;
	int n = (rand() % 3000) +1;
	
	//read n times to get the n-th vocabulary
	for(int i = 0; i < n; i++) {
		inFile >> voc;
	}

	return voc;
}

