#include "ClientData.h"


ClientData::ClientData(int accountNumberValue, string lastNameString, string firstNameString, double balanceValue)
{
	setAccountNumber(accountNumberValue);
	setLastName(lastNameString);
	setFirstName(firstNameString);
	setBalance(balanceValue);
}

ClientData::~ClientData(void)
{
}

void ClientData::setAccountNumber(int accountNumberValue)
{
	accountNumber = accountNumberValue;
}

void ClientData::setLastName(string lastNameString)
{
	int length = lastNameString.size();
	length = (length < 15 ? length : 14);
	lastNameString.copy(lastName, length);
	lastName[length] = '\0';
}
void ClientData::setFirstName(string firstNameString)
{
	int length = firstNameString.size();
	length = (length < 10 ? length : 9);
	firstNameString.copy(firstName, length);
	firstName[length] = '\0';
}

void ClientData::setBalance(double balanceValue)
{
	balance = balanceValue;
}
