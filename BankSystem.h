#pragma once
#include "Vector.hpp"
#include "Bank.h"
#include "Client.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"

class BankSystem
{
public:
	void login();
	void signup();
	void create_bank(String& bankName);
	//getters??
private:
	Vector<Bank> banks; // wiil be filled with command create_banks
	User* currentUser; // will be set when login //here should be used static cast?
	Vector<Client> clients;
	Vector<ThirdPartyEmployee> thirdPartyEmployees;

	//Vector<User*> users; //will be filled with command signup (dynamic memory, heterogenic container!!!)????
};

