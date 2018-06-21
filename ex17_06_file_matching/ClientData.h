#pragma once
#include <string>
using std::string;

class ClientData
{
public:
	ClientData(int = 0, string = "", string = "", double = 0.0);
	~ClientData(void);
	void setAccountNumber(int);
	int getAccountNumber() const
	{
		return accountNumber;
	}
	void setLastName(string);
	string getLastName() const
	{
		return lastName;
	}
	void setFirstName(string);
	string getFirstName() const
	{
		return firstName;
	}
	void setBalance(double);
	double getBalance() const
	{
		return balance;
	}
private:
	int accountNumber;
	char lastName[15];
	char firstName[10];
	double balance;
};

