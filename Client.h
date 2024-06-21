#pragma once
#include "User.h"
#include "Message.h"
#include "Check.h"
#include "Account.h"
#include "Task.h"
#include "Bank.h"


class Client: public User
{
public:
	Client();
	Client(String& _firstName, String& _lastName, int _egn, int _age, String& _password);
	void help() const override; 

	void check_avl(Bank* _bank, int _accNumber);
	Task* open();
	Task* close(Account* account);
	void redeem(Account* _account, String& _checkCode);
	Task* change(String& _oldbank, String& _newBank, Account* _account);
	void list(Bank* _bank);
	void show_messages();

private:
	Vector<Message> messages;
	Vector<Check> checks;

	Check* findCheckByCode(String& code);
};

