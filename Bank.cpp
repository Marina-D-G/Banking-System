#include "Bank.h"

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
	return &accounts[index];
}

void Bank::assignTask(Task* task)
{
	employees[availableIdx].setTask(task);
	recalculateAvailableIdx();
}

void Bank::openAccount(Account* newAcc)
{
	accounts.push(*newAcc);
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
