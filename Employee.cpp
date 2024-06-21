#include "Employee.h"

static void viewBasicInfo(Task* task)
{
	std::cout << task->getTaskName() << " from:\n";
	std::cout << "Name: " << task->getClientInfo().firstName << " " << task->getClientInfo().lastName << std::endl;
	std::cout << "EGN: " << task->getClientInfo().egn << std::endl;
	std::cout << "Age: " << task->getClientInfo().age << std::endl;
}

Employee::Employee(String& _firstName, String& _lastName, int _egn, int _age, String& _password, String& _bankAssociated) : User(_firstName, _lastName, _egn, _age, _password), bankAssociated(_bankAssociated) {}

void Employee::whoami() const
{
	User::whoami();
	std::cout << "You are an employee at " << bankAssociated << std::endl;
}

void Employee::help() const
{
	std::cout << "You can:\n";
	std::cout << "1) See your tasks (tasks)\n";
	std::cout << "2) See task details (view)\n";
	std::cout << "3) Approve task (approve)\n";
	std::cout << "4) Disapprove task (disapprove)\n";
	std::cout << "5) Ask a validation (validate)\n";
}

void Employee::show_tasks()
{
	for (size_t i = 0; i < tasks.getSize(); i++)
	{
		std::cout << "[" << tasks[i]->getIdx() << "] - " << tasks[i]->getMessage() << std::endl;
	}
}

void Employee::view(int taskID)
{
	for (int i = 0; i < tasks.getSize(); i++)
	{
		if (tasks[i]->getIdx() == taskID)
		{
			if (tasks[i]->getType() == Type::OPEN_TASK)
			{
				viewOpenTask(tasks[i].get());
			}
			if (tasks[i]->getType() == Type::CLOSE_TASK)
			{
				viewCloseTask(tasks[i].get());
			}
			if (tasks[i]->getType() == Type::CHANGE_TASK)
			{
				viewChangeTask(tasks[i].get());
			}
		}
	}
	throw std::runtime_error("There is no task with this index!");
}

Account* Employee::approve(int taskID)
{
	for (int i = 0; i < tasks.getSize(); i++)
	{
		if (tasks[i]->getIdx() == taskID)
		{
			if (tasks[i]->getType() == Type::OPEN_TASK)
			{
				approveOpenTask(tasks[i].get());
			}
			if (tasks[i]->getType() == Type::CLOSE_TASK)
			{
				approveCloseTask(tasks[i].get());
			}
			if (tasks[i]->getType() == Type::CHANGE_TASK)
			{
				approveChangeTask(tasks[i].get());
			}
		}
	}
	throw std::runtime_error("There is no task with this index!");
}

void Employee::validate(int taskID)
{

}

void Employee::setTask(Task* newTask)
{
	tasks.add(newTask);
}

size_t Employee::getNumTasks() const
{
	return tasks.getSize();
}

void Employee::viewOpenTask(Task* task)
{
	viewBasicInfo(task);
}

void Employee::viewCloseTask(Task* task)
{
	CloseTask* closeTask = static_cast<CloseTask*>(task);
	viewBasicInfo(closeTask);
	std::cout << "Bank: " << closeTask->getBankName()<< std::endl;
	std::cout << "Account number: " << closeTask->getAccNumber() << std::endl;
	std::cout << "Balance: " << closeTask->getAccBalance();
}

void Employee::viewChangeTask(Task* task)
{
	ChangeTask* changeTask = static_cast<ChangeTask*>(task);
	if (!changeTask->isTaskInOldBank())
	{
		viewBasicInfo(changeTask);
		std::cout << "Bank: " << changeTask->getBankName() << std::endl;
		return;
	}
	if (changeTask->isTaskInOldBank())
	{
		viewBasicInfo(changeTask);
		std::cout << "Account number: " << changeTask->getAccNumber() << std::endl;
		std::cout << "Balance: " << changeTask->getAccBalance();
		return;
	}
}

Account* Employee::approveOpenTask(Task* task)
{
	Account* newAccount = new Account(bankAssociated, 0);
	return newAccount;
}

Account* Employee::approveCloseTask(Task* task)
{
	CloseTask* closeTask = static_cast<CloseTask*>(task);
	return closeTask->getAccount();
}

Account* Employee::approveChangeTask(Task* task)
{
	ChangeTask* changeTask = static_cast<ChangeTask*>(task);
	if (!changeTask->isValidated() && !changeTask->isTaskInOldBank())
	{
		String exceptionMessage =  "Cannot proceed - please make sure " + changeTask->getClientInfo().firstName + changeTask->getClientInfo().lastName + "is real user by asking the bank!";
		throw std::runtime_error(exceptionMessage.c_str());
	}
	if (!changeTask->isValidated() && changeTask->isTaskInOldBank())
	{
		changeTask->validate();
		changeTask->setOldBankFlagTo(false); //return to new bank
		throw std::runtime_error("The task is only validated for changing"); //or return nullptr //or throw Task???
	}
	if (changeTask->isValidated() && !changeTask->isTaskInOldBank())
	{
		return changeTask->getAccount();
	}
	//return nullptr;
}


