#pragma once
#include "String.h"

class Account
{
public:
	static int nextID;
	Account();
	Account(String& _bankName, double _amount);

	String& getBankName();
	int getAccNumber();
	double getAmount();

	void setAmount(double newAmount);

private:
	String bankName;
	int number;
	double amount;
};

int Account::nextID = 1;



