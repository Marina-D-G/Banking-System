#include "Client.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"

static String OPEN_TASK_NAME = "Open request";
static String CLOSE_TASK_NAME = "Close request";
static String CHANGE_TASK_NAME = "Change request";

Client::Client(): User(){}

Client::Client(String& _firstName, String& _lastName, int _egn, int _age, String& _password): User(_firstName, _lastName, _egn, _age, _password){}

void Client::help() const
{
	std::cout << "You can:\n";
	std::cout << "1) Check availability (check_avl)\n";
	std::cout << "2) Open account (open)\n";
	std::cout << "3) Close account (close)\n";
	std::cout << "4) Cash a check (redeem)\n";
	std::cout << "5) Change account to other bank (change)\n";
	std::cout << "6) See all bank accounts (list)\n";
	std::cout << "7) See all messages (messages)\n";
}

void Client::check_avl(Bank* _bank, int _accNumber)
{
	for (int i = 0; i < _bank->getAccountCount(); i++)
	{
		if (_bank->getAccountAt(i)->getAccNumber() == _accNumber)
		{
			std::cout << _bank->getAccountAt(i)->getAccNumber() << "$\n";
			return;
		}
	}
	throw std::runtime_error("Wrong bank name or account number, try again!");
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
		throw std::runtime_error("You do not have a check with this code!");
	}
	_account->setAmount(myCheck->getTransferAmount());
	checks.remove(*myCheck);
	return;
	//logika za bankSystem
	/*for (size_t i = 0; i < _bank->getAccountCount(); i++)
	{
		if (_bank->getAccountAt(i)->getAccNumber() == _accNumber)
		{
			_bank->getAccountAt(i)->setAmount(myCheck->getTransferAmount());
			checks.remove(*myCheck);
			return;
		}
	}*/
	//throw std::runtime_error("Wrong bank name or account number, try again!");
}

Task* Client::change(String& _oldbank, String& _newBank, Account* _account)
{
	Task* changeTask = new ChangeTask(getUserInfo(), CHANGE_TASK_NAME, _oldbank, _newBank, _account);
	return changeTask;
}

void Client::list(Bank* bank)
{
	for (int i = 0; i < bank->getAccountCount(); i++)
	{
		std::cout << "*" << bank->getAccountAt(i)->getAccNumber() << std::endl;
	}
}

void Client::show_messages()
{
	for (size_t i = 0; i < messages.getSize(); i++)
	{
		std::cout << messages[i].getText();
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

