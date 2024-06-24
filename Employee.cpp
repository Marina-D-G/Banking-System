#include "Employee.h"
#include <fstream>

static const int BUFFER_SIZE = 1024;

static void viewBasicInfo(Task* task)
{
	std::cout << task->getTaskName() << " from:\n";
	std::cout << "Name: " << task->getClientInfo().firstName << " " << task->getClientInfo().lastName << std::endl;
	std::cout << "EGN: " << task->getClientInfo().egn << std::endl;
	std::cout << "Age: " << task->getClientInfo().age << std::endl;
}

static void printType(Task* task)
{
	switch (task->getType())
	{
	default:
	case Type::OPEN_TASK:
		std::cout << "Open - ";
		break;
	case Type::CLOSE_TASK:
		std::cout << "Close - ";
		break;
	case Type::CHANGE_TASK:
		std::cout << "Change - ";
		break;
	}
}

Employee::Employee(String& _firstName, String& _lastName, String& _egn, int _age, String& _password, String& _bankAssociated) : User(_firstName, _lastName, _egn, _age, _password), bankAssociated(_bankAssociated) 
{
	nextTaskID = 1;
}

Employee::Employee(UserInfo& _info, String& _bankAssociated, String& _password): User(_info, _password), bankAssociated(_bankAssociated) 
{
	nextTaskID = 1;
}

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
	std::cout << "5) Ask a validation (validate)\n\n";
}

void Employee::show_tasks()
{
	bool* checked = new bool[BUFFER_SIZE] {0};
	for (size_t i = 0; i < tasks.getSize(); i++)
	{
		if (!checked[tasks[i]->getIdx()])
		{
			std::cout << "[" << tasks[i]->getIdx() << "] - ";
			printType(tasks[i].get());
			std::cout << tasks[i]->getMessage() << std::endl;
			checked[tasks[i]->getIdx()] = true;
		}
	}
	std::cout << std::endl;
	delete[] checked;
}

void Employee::view(Task* myTask)
{
	if (myTask->getType() == Type::OPEN_TASK)
	{
		viewOpenTask(myTask);
	}
	if (myTask->getType() == Type::CLOSE_TASK)
	{
		viewCloseTask(myTask);
	}
	if (myTask->getType() == Type::CHANGE_TASK)
	{
		viewChangeTask(myTask);
	}
}

Account* Employee::approve(Task* myTask)
{
	if (myTask->getType() == Type::OPEN_TASK)
	{
		return approveOpenTask(myTask);
	}
	if (myTask->getType() == Type::CLOSE_TASK)
	{
		return approveCloseTask(myTask);
	}
	if (myTask->getType() == Type::CHANGE_TASK)
	{
		return approveChangeTask(myTask);
	}
	return nullptr;
}

Message* Employee::disapprove(Task* myTask, String& message)
{
	if (myTask->getType() == Type::OPEN_TASK)
	{
		return disapproveOpenTask(myTask, message);
	}
	if (myTask->getType() == Type::CLOSE_TASK)
	{
		return disapproveCloseTask(myTask, message);
	}
	if (myTask->getType() == Type::CHANGE_TASK)
	{
		return disapproveChangeTask(myTask, message);
	}
	return nullptr;
}

ChangeTask* Employee::validate(ChangeTask* myTask)
{
	if (!myTask->isTaskInOldBank())
	{
		throw std::runtime_error("The task should be validated by the old bank!\n");
	}
	myTask->validate();
	return myTask;
}

void Employee::setTask(Task* newTask)
{
	newTask->setIndex(nextTaskID++);
	newTask->setMessage();
	tasks.add(newTask);
}

void Employee::removeTaskAt(int ID)
{
	tasks.removeAt(ID);
}

void Employee::disableTaskAt(int ID)
{
	tasks.disable(ID);
}

size_t Employee::getNumTasks() const
{
	return tasks.getSize();
}

Task* Employee::getTaskByID(int taskID)
{
	for (int i = 0; i < tasks.getSize(); i++)
	{
		if (tasks[i]->getIdx() == taskID)
		{
			return tasks[i].get();
		}
	}
	throw std::runtime_error("There is no task with this index!\n");
}

String& Employee::getBankName()
{
	return bankAssociated;
}

void Employee::save(std::ofstream& ofs)
{
	User::save(ofs);

	size_t nameLen = bankAssociated.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	ofs.write(bankAssociated.c_str(), nameLen);
}

void Employee::load(std::ifstream& ifs)
{
	User::load(ifs);

	size_t nameLen;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	char* nameBuffer = new char[nameLen];
	ifs.read(nameBuffer, nameLen);
	bankAssociated = nameBuffer;
	delete[] nameBuffer;
}

void Employee::viewOpenTask(Task* task)
{
	viewBasicInfo(task);
	std::cout << std::endl;
}

void Employee::viewCloseTask(Task* task)
{
	CloseTask* closeTask = static_cast<CloseTask*>(task);
	viewBasicInfo(closeTask);
	std::cout << "Bank: " << closeTask->getBankName()<< std::endl;
	std::cout << "Account number: " << closeTask->getAccNumber() << std::endl;
	std::cout << "Balance: " << closeTask->getAccBalance() << "$\n\n";
}

void Employee::viewChangeTask(Task* task)
{
	ChangeTask* changeTask = static_cast<ChangeTask*>(task);
	if (!changeTask->isTaskInOldBank())
	{
		viewBasicInfo(changeTask);
		std::cout << "Bank: " << changeTask->getOldBankName() << std::endl;
		std::cout << std::endl;
		return;
	}
	if (changeTask->isTaskInOldBank())
	{
		viewBasicInfo(changeTask);
		std::cout << "Account number: " << changeTask->getAccNumber() << std::endl;
		std::cout << "Balance: " << changeTask->getAccBalance() << "$\n\n";
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
		String exceptionMessage =  "Cannot proceed - please make sure " + changeTask->getClientInfo().firstName + " " + changeTask->getClientInfo().lastName + " is real user by asking the bank!\n\n";
		throw std::runtime_error(exceptionMessage.c_str());
	}
	if (!changeTask->isValidated() && changeTask->isTaskInOldBank())
	{
		changeTask->validate();
		changeTask->setOldBankFlagTo(false); //return to new bank
		throw std::runtime_error("The task is validated for changing, not approved already");
	}
	if (changeTask->isValidated() && !changeTask->isTaskInOldBank())
	{
		return changeTask->getAccount();
	}
	return nullptr;
}

Message* Employee::disapproveOpenTask(Task* task, String& message)
{
	String _message = "Your Open request was not approved by " + persInfo.firstName + " " + persInfo.lastName + ". Reason: " + message;
	Message* newMessage = new Message(_message);
	return newMessage;
}

Message* Employee::disapproveCloseTask(Task* task, String& message)
{
	String _message = "Your Close request was not approved by " + persInfo.firstName + " " + persInfo.lastName + ". Reason: " + message;
	Message* newMessage = new Message(_message);
	return newMessage;
}

Message* Employee::disapproveChangeTask(Task* task, String& message)
{
	String _message = "Your Change request was not approved by " + persInfo.firstName + " " + persInfo.lastName + ". Reason: " + message;
	Message* newMessage = new Message(_message);
	return newMessage;
}


