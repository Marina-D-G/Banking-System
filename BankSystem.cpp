#include "BankSystem.h"
#include <fstream>

static bool onlyDigits(String& str)
{
	for (size_t i = 0; i < str.getSize(); i++)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}

BankSystem::BankSystem(): banks(), clients(), thirdPartyEmployees(), currentUser(nullptr), userType(TypeOfUser::NO_USER){}

void BankSystem::login(String& name, String& password)
{
	if (currentUser = searchInClients(name, password))
	{
		userType = TypeOfUser::CLIENT;
		return;
	}
	else if (currentUser = searchInTPEmployees(name, password))
	{
		userType = TypeOfUser::THIRD_PARTY_EMPLOYEE;
		return;
	}
	else if (currentUser = searchInBanks(name, password))
	{
		userType = TypeOfUser::EMPLOYEE;
		return;
	}
	else
	{
		throw std::runtime_error("There is no user with this username or password!\n");
	}
}

void BankSystem::signup(UserInfo& userInfo, String& type, String& password)
{
	userInfo.egn = validateEGN(userInfo.egn);
	if (type == "Client")
	{
		std::cout << std::endl;
		Client* newClient = new Client(userInfo, password);
		clients.push(std::move(*newClient));
	}
	else if (type == "Employee")
	{
		String bankName;
		std::cout << "Bank associated: ";
		std::cin >> bankName;
		std::cout << std::endl;
		Employee* newEmployee = new Employee(userInfo, bankName, password);
		getBank(bankName)->joinEmployee(newEmployee);
	}
	else if (type == "Third-party-employee")
	{
		std::cout << std::endl;
		ThirdPartyEmployee* newTPEmployee = new ThirdPartyEmployee(userInfo, password);
		thirdPartyEmployees.push(std::move(*newTPEmployee));
	}
	else
	{
		throw std::runtime_error("You can sign up only as client, employee or third-party employee!\n");
	}
}

void BankSystem::create_bank(String& bankName)
{
	for (size_t i = 0; i < banks.getSize(); i++)
	{
		if (bankName == banks[i].getBankName())
		{
			throw std::runtime_error("This bank already exists!\n");
			return;
		}
	}
	banks.push(Bank(bankName));
}

Bank* BankSystem::getBank(String& bankName)
{
	for (size_t i = 0; i < banks.getSize(); i++)
	{
		if (banks[i].getBankName() == bankName)
		{
			return &banks[i];
		}
	}
	return nullptr;
}

TypeOfUser BankSystem::getUserType()
{
	return userType;
}

User* BankSystem::getCurrentUser()
{
	return currentUser;
}

void BankSystem::sendMessageToClient(Message* message, String& egn)
{
	findClientByEgn(egn)->setMessage(std::move(message));
}

void BankSystem::sendCheckToClient(Check* check, String& egn)
{
	findClientByEgn(egn)->setCheck(std::move(check));
}

void BankSystem::save(const char* filename)
{
	std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);
	if (!ofs) 
	{
		throw std::runtime_error("Could not open file for writing!");
	}

	size_t bankCount = banks.getSize();
	ofs.write(reinterpret_cast<const char*>(&bankCount), sizeof(bankCount));
	for (size_t i = 0; i < bankCount; i++) 
	{
		banks[i].save(ofs);
	}

	size_t clientCount = clients.getSize();
	ofs.write(reinterpret_cast<const char*>(&clientCount), sizeof(clientCount));
	for (size_t i = 0; i < clientCount; i++)
	{
		clients[i].save(ofs);
	}

	size_t thirdPartyEmpCount = thirdPartyEmployees.getSize();
	ofs.write(reinterpret_cast<const char*>(&thirdPartyEmpCount), sizeof(thirdPartyEmpCount));
	for (size_t i = 0; i < thirdPartyEmpCount; i++)
	{
		thirdPartyEmployees[i].save(ofs);
	}

	ofs.close();
}

void BankSystem::load(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs)
	{
		return;
	}

	size_t bankCount = 0;
	ifs.read(reinterpret_cast<char*>(&bankCount), sizeof(bankCount));
	banks.resize(bankCount);
	for (size_t i = 0; i < bankCount; i++)
	{
		banks[i].load(ifs);
		banks.incrementSize();
	}

	size_t clientCount = 0;
	ifs.read(reinterpret_cast<char*>(&clientCount), sizeof(clientCount));
	clients.resize(clientCount);
	for (size_t i = 0; i < clientCount; i++)
	{
		clients[i].load(ifs);
		clients.incrementSize();
	}

	size_t emplCount = 0;
	ifs.read(reinterpret_cast<char*>(&emplCount), sizeof(emplCount));
	thirdPartyEmployees.resize(emplCount);
	for (size_t i = 0; i < emplCount; i++)
	{
		thirdPartyEmployees[i].load(ifs);
		thirdPartyEmployees.incrementSize();
	}

	ifs.close();
}

String& BankSystem::validateEGN(String& egn)
{
	if (egn.getSize() == 10 && onlyDigits(egn))
	{
		return egn;
	}
	else
	{
		std::cout << "Not valid EGN, try again (must be 10 digits): \n";
		std::cin >> egn;
		validateEGN(egn);
	}
}

Client* BankSystem::searchInClients(String& name, String& password)
{
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getUserInfo().firstName == name && clients[i].checkPassword(password))
		{
			return &clients[i];
		}
	}
	return nullptr;
}

Client* BankSystem::findClientByEgn(String& _egn)
{
	for (size_t i = 0; i < clients.getSize(); i++)
	{
		if (clients[i].getUserInfo().egn == _egn)
		{
			return &clients[i];
		}
	}
	return nullptr;
}

Employee* BankSystem::searchInBanks(String& name, String& password)
{
	for (int i = 0; i < banks.getSize(); i++)
	{
		for (int j = 0; j < banks[i].getEmployeeCount(); j++)
		{
			if (banks[i].getEmployeeAt(j)->getUserInfo().firstName == name && banks[i].getEmployeeAt(j)->checkPassword(password))
			{
				return banks[i].getEmployeeAt(j);
			}
		}
	}
	return nullptr;
}

ThirdPartyEmployee* BankSystem::searchInTPEmployees(String& name, String& password)
{
	for (size_t i = 0; i < thirdPartyEmployees.getSize(); i++)
	{
		if (thirdPartyEmployees[i].getUserInfo().firstName == name && thirdPartyEmployees[i].checkPassword(password))
		{
			return &thirdPartyEmployees[i];
		}
	}
	return nullptr;
}


