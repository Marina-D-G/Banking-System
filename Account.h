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
	friend bool operator==(const Account& lhs, const Account& rhs);
	friend bool operator!=(const Account& lhs, const Account& rhs);

	void save(std::ofstream& ofs);
	void load(std::ifstream& ifs);

private:
	String bankName;
	int number;
	double amount;
};




