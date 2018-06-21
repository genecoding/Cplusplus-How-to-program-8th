#include "TransData.h"


TransData::TransData(int accountValue, double transValue)
{
	setAccountNumber(accountValue);
	setTransAmount(transValue);
}


TransData::~TransData(void)
{
}

void TransData::setAccountNumber(int accountValue)
{
	accountNumber = accountValue;
}

void TransData::setTransAmount(double transValue)
{
	transAmount = transValue;
}