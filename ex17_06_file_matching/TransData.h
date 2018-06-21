#pragma once
class TransData
{
public:
	TransData(int = 0, double = 0.0);
	~TransData(void);
	void setAccountNumber(int);
	int getAccountNumber() const
	{
		return accountNumber;
	}
	void setTransAmount(double);
	double getTransAmount() const
	{
		return transAmount;
	}
private:
	int accountNumber;
	double transAmount;
};

