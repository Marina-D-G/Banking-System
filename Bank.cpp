#include "Bank.h"
#include <fstream>

Bank::Bank(String& bankName)
{
	name = bankName;
	availableIdx = 0;
}

const String& Bank::getBankName() const
{
	return name;
}

size_t Bank::getAccountCount()
{
	return accounts.getSize();
}

Account* Bank::getAccountAt(int index)
{
	Account* ptrAcc = &accounts[index];
	return ptrAcc;
}

Account* Bank::getAccountByID(int accID)
{
	for (size_t i = 0; i < accounts[i].getAccNumber(); i++)
	{
		if (accounts[i].getAccNumber() == accID)
		{
			return &accounts[i];
		}
	}
	return nullptr;
}

size_t Bank::getEmployeeCount()
{
	return employees.getSize();
}

Employee* Bank::getEmployeeAt(int index)
{
	Employee* ptrEmpl = &employees[index];
	return ptrEmpl;
}

void Bank::assignTask(Task* task)
{
	employees[availableIdx].setTask(task);
	recalculateAvailableIdx();
}

void Bank::joinEmployee(Employee* newEmployee)
{
	employees.push(std::move(*newEmployee));
}

void Bank::openAccount(Account* newAcc)
{
	accounts.push(*newAcc);
}

void Bank::closeAccount(Account* oldAcc)
{
	accounts.remove(*oldAcc);
}

bool Bank::doesExist(Account* acc)
{
	for (size_t i = 0; i < accounts[i].getAccNumber(); i++)
	{
		if (accounts[i] == *acc)
		{
			return true;
		}
	}
	return false;
}

void Bank::save(std::ofstream& ofs)
{
	size_t nameLen = name.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	ofs.write(name.c_str(), nameLen);

	size_t empCount = employees.getSize();
	ofs.write(reinterpret_cast<const char*>(&empCount), sizeof(empCount));
	for (size_t i = 0; i < empCount; i++) 
	{
		employees[i].save(ofs);
	}

	size_t accCount = accounts.getSize();
	ofs.write(reinterpret_cast<const char*>(&accCount), sizeof(accCount));
	for (size_t i = 0; i < accCount; i++)
	{
	     accounts[i].save(ofs);
	}

	ofs.write(reinterpret_cast<const char*>(&availableIdx), sizeof(availableIdx));
}

void Bank::load(std::ifstream& ifs)
{
	size_t nameLen;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	char* nameBuffer = new char[nameLen];
	ifs.read(nameBuffer, nameLen);
	name = nameBuffer;
	delete[] nameBuffer; 

	size_t empCount;
	ifs.read(reinterpret_cast<char*>(&empCount), sizeof(empCount));
	employees.resize(empCount);
	for (size_t i = 0; i < empCount; i++)
	{
		employees[i].load(ifs);
		employees.incrementSize();
	}

	size_t accCount;
	ifs.read(reinterpret_cast<char*>(&accCount), sizeof(accCount));
	accounts.resize(accCount);
	for (size_t i = 0; i < accCount; i++)
	{
		accounts[i].load(ifs);
		accounts.incrementSize();
	}

	ifs.read(reinterpret_cast<char*>(&availableIdx), sizeof(availableIdx));
}

void Bank::recalculateAvailableIdx()
{
	size_t minTasks = employees[0].getNumTasks();
	for (int i = 0; i < employees.getSize(); i++)
	{
		if (employees[i].getNumTasks() < minTasks)
		{
			availableIdx = i;
		}
	}
}
