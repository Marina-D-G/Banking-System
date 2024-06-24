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
	Account* getAccountByID(int accID);
	size_t getEmployeeCount();
	Employee* getEmployeeAt(int index);
	void assignTask(Task* task); 

	void joinEmployee(Employee* newEmployee);
	void openAccount(Account* newAcc);
	void closeAccount(Account* oldAcc);
	bool doesExist(Account* acc);

	void save(std::ofstream& ofs);
	void load(std::ifstream& ifs);
private:
	String name;
	Vector<Employee> employees;
	Vector<Account> accounts;
	int availableIdx; //index of the least busy employee

	void recalculateAvailableIdx();
};

