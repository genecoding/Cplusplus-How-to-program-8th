#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::string;

bool isValidNum(string);
void generateWords(string);
void generateWordRecur(const char *[], int);
void writeWordToFile(char []);

const int WORDS = 3 * 3 * 3 * 3 * 3 * 4 * 3 * 4;
const int DIGITS = 7;
const char NUM[10][5] =
{{'\0'},  //NUM 0
 {'\0'},  //NUM 1
 {'A', 'B', 'C', '\0'},  //NUM 2
 {'D', 'E', 'F', '\0'},  //NUM 3
 {'G', 'H', 'I', '\0'},  //NUM 4
 {'J', 'K', 'L', '\0'},  //NUM 5
 {'M', 'N', 'O', '\0'},  //NUM 6
 {'P', 'Q', 'R', 'S', '\0'},  //NUM 7
 {'T', 'U', 'V', '\0'},  //NUM 8
 {'W', 'X', 'Y', 'Z', '\0'}};  //NUM 9

int main()
{
	char num[DIGITS+1];  //one more bit for '\0'.
	cout << "enter a 7-digit number: ";
	cin >> std::setw(DIGITS+1) >> num;

	//check entered number.
	while(!isValidNum(num)) {
		cout << "avoid digit 0 and 1, enter again: ";
		cin >> std::setw(DIGITS+1) >> num;
	}

	generateWords(num);

	return 0;
}

void generateWords(string num)
{
	//get corresponding phone letters according to numbers.
	const char *letterLists[DIGITS];
	for(int i = 0; i < DIGITS; i++) {
		switch(num[i]) {
		case '2':
			letterLists[i] = &NUM[2][0];
			break;
		case '3':
			letterLists[i] = &NUM[3][0];
			break;
		case '4':
			letterLists[i] = &NUM[4][0];
			break;
		case '5':
			letterLists[i] = &NUM[5][0];
			break;
		case '6':
			letterLists[i] = &NUM[6][0];
			break;
		case '7':
			letterLists[i] = &NUM[7][0];
			break;
		case '8':
			letterLists[i] = &NUM[8][0];
			break;
		case '9':
			letterLists[i] = &NUM[9][0];
			break;
		default:
			cerr << "invalid number" << endl;
			exit(1);
			break;
		}
	}

	///generate word recursively and output them to the file
	generateWordRecur(letterLists, 0);
}

void generateWordRecur(const char *letterLists[], int ctr)
{  //basically like tree's treversal
	static char word[DIGITS+1];

    if(ctr < DIGITS) {
		for(int i = 0; letterLists[ctr][i] != '\0'; i++) {
			word[ctr] = letterLists[ctr][i];
			generateWordRecur(letterLists, ctr+1);
		}
	} else {
		word[ctr] = '\0';
		writeWordToFile(word);
		//cout << word << endl;
	}
    
    return;
}

void writeWordToFile(char word[])
{
	ofstream outFile("phone_word.txt", std::ios::out | std::ios::app);  //append new word to the end of file

	if(!outFile) {
		cerr << "File can not be opened." << endl;
		exit(1);
	}

	outFile << word << endl;
}

bool isValidNum(string num)
{
	for(int i = 0; i < 7; i++) {
		if(num[i] == '0' || num[i] == '1')
			return false;
	}

	return true;
}