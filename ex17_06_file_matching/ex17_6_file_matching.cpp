#include "ClientData.h"
#include "TransData.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ostream;

int enterMainChoice();
void maintainOldMast();
void maintainTransDat();
void submitTransaction();

void createOldMast();  //create a new oldmast.dat
void initializeOldMast(fstream &, int, string, string, double);  //initialize with some examples
void showAllAccounts(fstream &);  //print all account data on the screen
void updateAccount(fstream &);
void newAccount(fstream &);
void deleteAccount(fstream &);
void outputAccount(ostream &, const ClientData &);

void createTransDat();  //create a new trans.dat
void initializeTrans(fstream &, int, double);  //initialize with some examples
void showAllTrans(fstream &);  //print all transaction data on the screen
void updateTrans(fstream &);
void newTrans(fstream &);
void deleteTrans(fstream &);
void outputTrans(ostream &, const TransData &);

void createNewMast();  //create a new newmast.dat

int enterChoice();
int getAccount(const char * const);

enum MainChoices{ACCOUNT = 1, TRANSACTION, SUBMIT, FIN};
enum Choices{PRINT = 1, UPDATE, NEW, DELETE, END};

int main()
{
	int mainChoice;
	while((mainChoice = enterMainChoice()) != FIN) {
		switch(mainChoice) {
		case ACCOUNT:
			maintainOldMast();  //maintain oldmast.dat
			break;
		case TRANSACTION:
			maintainTransDat();  //maintain trans.dat
			break;
		case SUBMIT:
			submitTransaction();  //submit transactions and output newmast.dat
			break;
		default:
			cerr << "Invalid choice." << endl;
			break;
		}
	}

	return 0;
}

int enterMainChoice()
{
	cout << "\nenter your choice" << endl
		 << "1 - maintain account data." << endl
		 << "2 - maintain transaction data." << endl
		 << "3 - submit transactions." << endl
		 << "4 - end program\n? ";

	int mainChoice;
	cin >> mainChoice;
	return mainChoice;
}

void maintainOldMast()
{
	fstream inOutOldMast("oldmast.dat", std::ios::in | std::ios::out | std::ios::binary);
	while(!inOutOldMast) {  //note that there are many another reasons than file didn't exist may cause open file failed.
		//create a new file and initialize oldmast.dat
		createOldMast();  
		inOutOldMast.open("oldmast.dat", std::ios::in | std::ios::out | std::ios::binary);
		initializeOldMast(inOutOldMast, 100, "Alan", "Jones", 348.17);
		initializeOldMast(inOutOldMast, 300, "Mary", "Smith", 27.19);
		initializeOldMast(inOutOldMast, 500, "Sam", "Sharp", 0.0);
		initializeOldMast(inOutOldMast, 700, "Suzy", "Green", -14.22);
	}

	int choice;
	while((choice = enterChoice()) != END) {
		switch(choice) {
		case PRINT:
			showAllAccounts(inOutOldMast);
			break;
		case UPDATE:
			updateAccount(inOutOldMast);
			break;
		case NEW:
			newAccount(inOutOldMast);
			break;
		case DELETE:
			deleteAccount(inOutOldMast);
			break;
		default:
			cerr << "Invalid choice." << endl;
			break;
		}
	
		inOutOldMast.clear();
	}
}

void maintainTransDat()
{
	fstream inOutTransDat("trans.dat", std::ios::in | std::ios::out | std::ios::binary);
	while(!inOutTransDat) {  //note that there are many another reasons than file didn't exist may cause open file failed.
		//create a new file and initialize trans.dat
		createTransDat();  
		inOutTransDat.open("trans.dat", std::ios::in | std::ios::out | std::ios::binary);
		initializeTrans(inOutTransDat, 100, 27.14);
		initializeTrans(inOutTransDat, 300, 62.11);
		initializeTrans(inOutTransDat, 400, 100.56);
		initializeTrans(inOutTransDat, 900, 82.17);
	}

	int choice;
	while((choice = enterChoice()) != END) {
		switch(choice) {
		case PRINT:
			showAllTrans(inOutTransDat);
			break;
		case UPDATE:
			updateTrans(inOutTransDat);
			break;
		case NEW:
			newTrans(inOutTransDat);
			break;
		case DELETE:
			deleteTrans(inOutTransDat);
			break;
		default:
			cerr << "Invalid choice." << endl;
			break;
		}
	
		inOutTransDat.clear();
	}
}

void submitTransaction()
{
	fstream inOutNewMast("newmast.dat", std::ios::in | std::ios::out | std::ios::binary);
	if(!inOutNewMast) {
		createNewMast();
	}

	ifstream inOldMast("oldmast.dat", std::ios::in | std::ios::binary);
	if(!inOldMast) {
		cerr << "oldmast.dat can not be opened." << endl;
		exit(1);
	}

	ifstream inTransDat("trans.dat", std::ios::in | std::ios::binary);
	if(!inTransDat) {
		cerr << "trans.dat can not be opened." << endl;
		exit(1);
	}

	ClientData oldData, newData;
	TransData trans;
	for(int i = 0; i < 1000; i++) {
		inOldMast.seekg((i) * sizeof(ClientData));
		inOldMast.read(reinterpret_cast<char*>(&oldData), sizeof(ClientData));
		inTransDat.seekg((i) * sizeof(TransData));
		inTransDat.read(reinterpret_cast<char*>(&trans), sizeof(TransData));
		inOutNewMast.seekg((i) * sizeof(ClientData));
		inOutNewMast.read(reinterpret_cast<char*>(&newData), sizeof(ClientData));

		int oldDataAccount = oldData.getAccountNumber();
		int transAccount = trans.getAccountNumber();
		double transaction;
		if(oldDataAccount != 0) {
			if(oldDataAccount == transAccount) {  //there is a new transacation.
				transaction = oldData.getBalance() + trans.getTransAmount();
			} else {  //no new transaction
				transaction = oldData.getBalance();
			}

			newData.setAccountNumber(oldDataAccount);
			newData.setLastName(oldData.getLastName());
			newData.setFirstName(oldData.getFirstName());
			newData.setBalance(transaction);

			inOutNewMast.seekp((i) * sizeof(ClientData));
			inOutNewMast.write(reinterpret_cast<const char*>(&newData), sizeof(ClientData));
		} else {  //oldDataAccount == 0
			if(transAccount != 0) {  //there is a transaction in trans.dat, but no account data in oldmast.dat
				cerr << "Unmatched transaction record for account number #" << i+1 << endl;
			}
		}
	}

	showAllAccounts(inOutNewMast);
}

void createOldMast()
{
	ofstream outOldMast("oldmast.dat", std::ios::out | std::ios::binary);

	if(!outOldMast) {
		cerr << "oldmast.dat can not be created." << endl;
		exit(1);
	}

	ClientData blankClient;
	for(int i = 0; i < 1000; i++) {
		outOldMast.write(reinterpret_cast<const char*>(&blankClient), sizeof(ClientData));
	}
}

void initializeOldMast(fstream &oldMastData, int accountNumber, string lastName, string firstName, double balance)
{
	ClientData client;

	oldMastData.seekg((accountNumber-1) * sizeof(ClientData));
	oldMastData.read(reinterpret_cast<char*>(&client), sizeof(ClientData));
	
	client.setAccountNumber(accountNumber);
	client.setLastName(lastName);
	client.setFirstName(firstName);
	client.setBalance(balance);

	oldMastData.seekp((accountNumber-1) * sizeof(ClientData));
	oldMastData.write(reinterpret_cast<const char*>(&client), sizeof(ClientData));
}

void showAllAccounts(fstream &mastData)
{
	/*
	ifstream inMast(filename, std::ios::in | std::ios::binary);

	if(!inMast) {
		cerr << filename << " can not be opened." << endl;
		exit(1);
	}
	*/

	cout << std::left << setw(10) << "Account" << setw(16)
		<< "Last Name" << setw(11) << "First Name" << std::left
		<< setw(10) << std::right << "Balance" << endl;

	mastData.seekg(0);

	ClientData client;
	mastData.read(reinterpret_cast<char *>(&client), sizeof(ClientData));

	int count = 0;
	while(!mastData.eof()) {
		if(client.getAccountNumber() != 0)
			outputAccount(cout, client);

		mastData.read(reinterpret_cast<char *>(&client), sizeof(ClientData));
		count++;
	}
}

void updateAccount(fstream &updateAccount)
{
	int accountNumber = getAccount("Enter account number");

	updateAccount.seekg((accountNumber-1) * sizeof(ClientData));

	ClientData client;
	updateAccount.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

	if(client.getAccountNumber() != 0) {
		outputAccount(cout, client);

		cout << "\nEnter charge(+) or payment(-): ";
		double transaction;
		cin >> transaction;

		double oldBalance = client.getBalance();
		client.setBalance(oldBalance + transaction);
		outputAccount(cout, client);

		updateAccount.seekp((accountNumber-1) * sizeof(ClientData));
		updateAccount.write(reinterpret_cast<const char*>(&client), sizeof(ClientData));
	} else{
		cerr << "Account #" << accountNumber << " has no information." << endl;
	}
}

void newAccount(fstream &insertAccount)
{
	int accountNumber = getAccount("Enter new account number");

	insertAccount.seekg((accountNumber-1) * sizeof(ClientData));

	ClientData client;
	insertAccount.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

	if(client.getAccountNumber() == 0) {
		string lastName;
		string firstName;
		double balance;
		
		cout << "Enter last name, first name, balance\n? ";
		cin >> setw(15) >> lastName;
		cin >> setw(20) >> firstName;
		cin >> balance;
	
		client.setAccountNumber(accountNumber);
		client.setLastName(lastName);
		client.setFirstName(firstName);
		client.setBalance(balance);
		
		insertAccount.seekp((accountNumber-1) * sizeof(ClientData));
		insertAccount.write(reinterpret_cast<const char*>(&client), sizeof(ClientData));
	} else{
		cerr << "Account #" << accountNumber << " already contains information." << endl;
	}
}

void deleteAccount(fstream &deleteAccount)
{
	int accountNumber = getAccount("Enter account number to delete");

	deleteAccount.seekg((accountNumber-1) * sizeof(ClientData));

	ClientData client;
	deleteAccount.read(reinterpret_cast<char*>(&client), sizeof(ClientData));

	if(client.getAccountNumber() != 0) {
		ClientData blankClient;
		
		deleteAccount.seekp((accountNumber-1) * sizeof(ClientData));
		deleteAccount.write(reinterpret_cast<const char*>(&blankClient), sizeof(ClientData));

		cout << "Account #" << accountNumber << " deleted." << endl;
	} else{
		cerr << "Account #" << accountNumber << " is empty." << endl;
	}
}

void outputAccount(ostream &output, const ClientData &record)
{
	output << std::left << setw(10) << record.getAccountNumber() 
		<< setw(16) << record.getLastName()
		<< setw(11) << record.getFirstName()
		<< setw(10) << std::setprecision(2) << std::right << std::fixed
		<< std::showpoint << record.getBalance() << endl;
}

void createTransDat()
{
	fstream outTransDat("trans.dat", std::ios::out | std::ios::binary);

	if(!outTransDat) {
		cerr << "trans.dat can not be created." << endl;
		exit(1);
	}

	TransData blankTrans;
	for(int i = 0; i < 1000; i++) {
		outTransDat.write(reinterpret_cast<const char*>(&blankTrans), sizeof(TransData));
	}
}

void initializeTrans(fstream &transDat, int accountNumber, double balance)
{
	TransData trans;
	
	transDat.seekg((accountNumber-1) * sizeof(TransData));
	transDat.read(reinterpret_cast<char*>(&trans), sizeof(TransData));
	
	trans.setAccountNumber(accountNumber);
	trans.setTransAmount(balance);

	transDat.seekp((accountNumber-1) * sizeof(TransData));
	transDat.write(reinterpret_cast<const char*>(&trans), sizeof(TransData));
}

void showAllTrans(fstream &transDat)
{
	/*
	ifstream inTransDat("trans.dat", std::ios::in | std::ios::binary);

	if(!inTransDat) {
		cerr << "trans.dat can not be opened." << endl;
		exit(1);
	}
	*/

	cout << std::left << setw(10) << "Account" << std::left
		<< setw(10) << std::right << "TransAmount" << endl;

	transDat.seekg(0);

	TransData trans;
	transDat.read(reinterpret_cast<char *>(&trans), sizeof(TransData));

	while(!transDat.eof()) {
		if(trans.getAccountNumber() != 0)
			outputTrans(cout, trans);

		transDat.read(reinterpret_cast<char *>(&trans), sizeof(TransData));
	}
}

void updateTrans(fstream &updateTrans)
{
	int accountNumber = getAccount("Enter account number");

	updateTrans.seekg((accountNumber-1) * sizeof(TransData));

	TransData trans;
	updateTrans.read(reinterpret_cast<char*>(&trans), sizeof(TransData));

	if(trans.getAccountNumber() != 0) {
		outputTrans(cout, trans);

		cout << "\nEnter charge(+) or payment(-): ";
		double transaction;
		cin >> transaction;

		double oldAmount = trans.getTransAmount();
		trans.setTransAmount(oldAmount + transaction);
		outputTrans(cout, trans);

		updateTrans.seekp((accountNumber-1) * sizeof(TransData));
		updateTrans.write(reinterpret_cast<const char*>(&trans), sizeof(TransData));
	} else{
		cerr << "Account #" << accountNumber << " has no information." << endl;
	}
}

void newTrans(fstream &insertTrans)
{
	int accountNumber = getAccount("Enter new account number");

	insertTrans.seekg((accountNumber-1) * sizeof(TransData));

	TransData trans;
	insertTrans.read(reinterpret_cast<char*>(&trans), sizeof(TransData));

	if(trans.getAccountNumber() == 0) {
		double amount;
		
		cout << "Enter transaction amount\n? ";
		cin >> amount;
	
		trans.setAccountNumber(accountNumber);
		trans.setTransAmount(amount);
		
		insertTrans.seekp((accountNumber-1) * sizeof(TransData));
		insertTrans.write(reinterpret_cast<const char*>(&trans), sizeof(TransData));
	} else{
		cerr << "Account #" << accountNumber << " already contains information." << endl;
	}
}

void deleteTrans(fstream &deleteTrans)
{
	int accountNumber = getAccount("Enter account number to delete");

	deleteTrans.seekg((accountNumber-1) * sizeof(TransData));

	TransData trans;
	deleteTrans.read(reinterpret_cast<char*>(&trans), sizeof(TransData));

	if(trans.getAccountNumber() != 0) {
		TransData blankTrans;
		
		deleteTrans.seekp((accountNumber-1) * sizeof(TransData));
		deleteTrans.write(reinterpret_cast<const char*>(&blankTrans), sizeof(TransData));

		cout << "Account #" << accountNumber << " deleted." << endl;
	} else{
		cerr << "Account #" << accountNumber << " is empty." << endl;
	}
}

void outputTrans(ostream &output, const TransData &record)
{
	output << std::left << setw(10) << record.getAccountNumber() 
		<< setw(10) << std::setprecision(2) << std::right << std::fixed
		<< std::showpoint << record.getTransAmount() << endl;
}

void createNewMast()
{
	ofstream outNewMast("newmast.dat", std::ios::out | std::ios::binary);

	if(!outNewMast) {
		cerr << "newmast.dat can not be created." << endl;
		exit(1);
	}

	ClientData blankClient;
	for(int i = 0; i < 1000; i++) {
		outNewMast.write(reinterpret_cast<const char*>(&blankClient), sizeof(ClientData));
	}
}

int enterChoice()
{
	cout << "\nenter your choice" << endl
		 << "1 - print out the dat file on the screen." << endl
		 << "2 - update an account." << endl
		 << "3 - add an new account." << endl
		 << "4 - delete an account." << endl
		 << "5 - end program\n? ";

	int choice;
	cin >> choice;
	return choice;
}

int getAccount(const char * const prompt)
{
	int accountNumber;

	do{
		cout << prompt << " (1 to 1000): ";
		cin >> accountNumber;
	} while(accountNumber < 1 || accountNumber >1000);

	return accountNumber;
}