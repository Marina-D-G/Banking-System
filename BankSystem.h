#pragma once
#include "Vector.hpp"
#include "Bank.h"
#include "Client.h"
#include "Employee.h"
#include "ThirdPartyEmployee.h"

enum class TypeOfUser
{
	CLIENT,
	EMPLOYEE,
	THIRD_PARTY_EMPLOYEE,
	NO_USER
};

class BankSystem
{
public:
	BankSystem();
	void login(String& name, String& password);
	void signup(UserInfo& userInfo, String& type, String& Password);
	void create_bank(String& bankName);
	
	Bank* getBank(String& bankName);
	TypeOfUser getUserType();
	User* getCurrentUser();
	void sendMessageToClient(Message* message, String& egn);
	void sendCheckToClient(Check* check, String& egn);

	void save(const char* filename);
	void load(const char* filename);
private:
	Vector<Bank> banks; // will be filled with command create_banks
	User* currentUser; // will be set when login 
	TypeOfUser userType;
	Vector<Client> clients;
	Vector<ThirdPartyEmployee> thirdPartyEmployees;

	String& validateEGN(String& egn);
	Client* searchInClients(String& name, String& password);
	Client* findClientByEgn(String& _egn);
	ThirdPartyEmployee* searchInTPEmployees(String& name, String& password);
	Employee* searchInBanks(String& name, String& password);
};

