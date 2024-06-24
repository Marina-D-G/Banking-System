#include "ClientMode.h"

ClientMode::ClientMode(BankSystem* _system, Client* _user): Mode(_system), user(_user){}

void ClientMode::execute()
{
	String command;
	std::cin >> command;

	while (command != "exit")
	{
		if (command == "whoami")
		{
			user->whoami();
		}
		else if (command == "help")
		{
			user->help();
		}
		else if (command == "check_avl")
		{
			check_avl();
		}
		else if (command == "open")
		{
			open();
		}
		else if (command == "close")
		{
			close();
		}
		else if (command == "redeem")
		{
			redeem();
		}
		else if (command == "change")
		{
			change();
		}
		else if (command == "list")
		{
			list();
		}
		else if (command == "messages")
		{
			user->show_messages();
		}
		else
		{
			std::cout << "This command does not exist, call help to see what you can do!\n\n";
		}
		std::cin >> command;
	}
	std::cout << std::endl;
}

void ClientMode::check_avl()
{
	String bankName;
	int accID;
	std::cin >> bankName;
	std::cin >> accID;
	std::cout << std::endl;
	try
	{
		Bank* bank = system->getBank(bankName);
		if (bank)
		{
			user->check_avl(bank, accID);
		}
		else
		{
			std::cout << "There is no bank with this name!\n\n";
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void ClientMode::open()
{
	String bankName;
	std::cin >> bankName;
	std::cout << std::endl;
	try
	{
		Task* newTask = user->open();
		system->getBank(bankName)->assignTask(std::move(newTask));
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void ClientMode::close()
{
	String bankName;
	int accID;
	std::cin >> bankName;
	std::cin >> accID;
	std::cout << std::endl;
	try
	{
		Account* account = system->getBank(bankName)->getAccountByID(accID);
		Task* newTask = user->close(account);
		system->getBank(bankName)->assignTask(std::move(newTask));
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void ClientMode::redeem()
{
	String bankName;
	int accID;
	String code;
	std::cin >> bankName;
	std::cin >> accID;
	std::cin >> code;
	try
	{
		Account* account = system->getBank(bankName)->getAccountByID(accID);
		user->redeem(account, code);
		std::cout << std::endl;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void ClientMode::change()
{
	String newBankName;
	String oldBankName;
	int accID;
	std::cin >> newBankName;
	std::cin >> oldBankName;
	std::cin >> accID;
	std::cout << std::endl;
	try
	{
		Account* account = system->getBank(oldBankName)->getAccountByID(accID);
		Task* newTask = user->change(newBankName, oldBankName, account);
		system->getBank(newBankName)->assignTask(std::move(newTask));
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void ClientMode::list()
{
	String bankName;
	std::cin >> bankName;
	std::cout << std::endl;
	try
	{
		Bank* bank = system->getBank(bankName);
		user->list(bank);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}
