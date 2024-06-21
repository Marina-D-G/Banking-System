#pragma once
#include "String.h"
#include "Vector.hpp"
#include "Employee.h"
#include "Account.h"

class Bank
{
public:
	Bank() = default;
	Bank(String& bankName);
	const String& getBankName() const;
	size_t getAccountCount();
	Account* getAccountAt(int index);
	void assignTask(Task* task); //shte slojim tozi task na indexa na employeeto koeto e naj-malko zaeto, preizchislqwame indexa ako trqbva

	void openAccount(Account* newAcc);
private:
	String name;
	Vector<Employee> employees;
	Vector<Account> accounts;
	int availableIdx; //index of the least busy employee

	void recalculateAvailableIdx();
};

