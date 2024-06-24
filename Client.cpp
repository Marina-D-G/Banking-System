#include "Client.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"
#include <fstream>

static String OPEN_TASK_NAME = "Open request";
static String CLOSE_TASK_NAME = "Close request";
static String CHANGE_TASK_NAME = "Change request";

Client::Client(): User(){}

Client::Client(String& _firstName, String& _lastName, String& _egn, int _age, String& _password): User(_firstName, _lastName, _egn, _age, _password){}

Client::Client(UserInfo& info, String& password): User(info, password){}

void Client::help() const
{
	std::cout << "You can:\n";
	std::cout << "1) Check availability (check_avl)\n";
	std::cout << "2) Open account (open)\n";
	std::cout << "3) Close account (close)\n";
	std::cout << "4) Cash a check (redeem)\n";
	std::cout << "5) Change account to other bank (change)\n";
	std::cout << "6) See all bank accounts (list)\n";
	std::cout << "7) See all messages (messages)\n\n";
}

void Client::check_avl(Bank* _bank, int _accNumber)
{
	for (int i = 0; i < _bank->getAccountCount(); i++)
	{
		if (_bank->getAccountAt(i)->getAccNumber() == _accNumber)
		{
			std::cout << _bank->getAccountAt(i)->getAmount() << "$\n\n";
			return;
		}
	}
	throw std::runtime_error("Wrong bank name or account number, try again!\n");
}

Task* Client::open()
{
	Task* openTask = new OpenTask(getUserInfo(), OPEN_TASK_NAME);
	return openTask;
}

Task* Client::close(Account* account)
{
	Task* closeTask = new CloseTask(getUserInfo(), CLOSE_TASK_NAME, account);
	return closeTask;
}

void Client::redeem(Account* _account, String& _checkCode)
{
	Check* myCheck = findCheckByCode(_checkCode);
	if (!myCheck)
	{
		throw std::runtime_error("You do not have a check with this code!\n");
	}
	_account->setAmount(myCheck->getTransferAmount());
	checks.remove(*myCheck);
	return;
}

Task* Client::change(String& _newBank, String& _oldBank, Account* _account)
{
	Task* changeTask = new ChangeTask(getUserInfo(), CHANGE_TASK_NAME, _newBank, _oldBank, _account);
	return changeTask;
}

void Client::list(Bank* bank)
{
	for (int i = 0; i < bank->getAccountCount(); i++)
	{
		std::cout << "*" << bank->getAccountAt(i)->getAccNumber() << std::endl << std::endl;
	}
}

void Client::show_messages()
{
	for (size_t i = 0; i < messages.getSize(); i++)
	{
		std::cout << "[" << i+1 << "] " << messages[i].getText();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Client::setMessage(Message* message)
{
	messages.push(std::move(*message));
}

void Client::setCheck(Check* check)
{
	checks.push(std::move(*check));
}

void Client::save(std::ofstream& ofs)
{
	User::save(ofs);

	size_t messagesCount = messages.getSize();
	ofs.write(reinterpret_cast<const char*>(&messagesCount), sizeof(messagesCount));
	for (size_t i = 0; i < messagesCount; ++i)
	{
		messages[i].save(ofs);
	}

	size_t checkCount = checks.getSize();
	ofs.write(reinterpret_cast<const char*>(&checkCount), sizeof(checkCount));
	for (size_t i = 0; i < checkCount; ++i)
	{
		checks[i].save(ofs);
	}
}

void Client::load(std::ifstream& ifs)
{
	User::load(ifs);

	size_t messCount;
	ifs.read(reinterpret_cast<char*>(&messCount), sizeof(messCount));
	messages.resize(messCount);
	for (size_t i = 0; i < messCount; i++)
	{
		messages[i].load(ifs);
		messages.incrementSize();
	}

	size_t checkCount;
	ifs.read(reinterpret_cast<char*>(&checkCount), sizeof(checkCount));
	checks.resize(checkCount);
	for (size_t i = 0; i < checkCount; i++)
	{
		checks[i].load(ifs);
		checks.incrementSize();
	}
}

Check* Client::findCheckByCode(String& code)
{
	for (size_t i = 0; i < checks.getSize(); i++)
	{
		if (checks[i].getCode() == code)
		{
			return &checks[i];
		}
	}
	return nullptr;
}

