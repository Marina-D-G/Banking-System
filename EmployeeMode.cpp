#include "EmployeeMode.h"
#pragma warning(disable: 4996)

static const int BUFFER_SIZE = 1024;

static const char* readStringFromConsole()
{
	char* buffer = new char[BUFFER_SIZE];
	char* result = new char[BUFFER_SIZE];

	while (true) 
	{
		std::cin.getline(buffer, BUFFER_SIZE);
		size_t len = std::strlen(buffer);

		if (len >= 2 && buffer[0] == '"' && buffer[len - 1] == '"') 
		{
			std::strncpy(result, buffer + 1, len - 2);
			result[len - 2] = '\0';
			break;
		}
		else 
		{
			std::cout << "The message should start and end with double quotes: ";
		}
	}
	delete[] buffer;
	return result;
}

EmployeeMode::EmployeeMode(BankSystem* _system, Employee* _user): Mode(_system), user(_user){}

void EmployeeMode::execute()
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
		else if (command == "tasks")
		{
			user->show_tasks();
		}
		else if (command == "view")
		{
			view();
		}
		else if (command == "approve")
		{
			approve();
		}
		else if (command == "disapprove")
		{
			disapprove();
		}
		else if (command == "validate")
		{
			validate();
		}
		else
		{
			std::cout << "This command does not exist, call help to see what you can do!\n";
		}
		std::cin >> command;
	}
	std::cout << std::endl;
}

void EmployeeMode::view()
{
	int taskID;
	std::cin >> taskID;
	std::cout << std::endl;
	Task* myTask = user->getTaskByID(taskID);
	try
	{
		user->view(myTask);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void EmployeeMode::approve()
{
	int taskID;
	std::cin >> taskID;
	std::cout << std::endl;
	Task* myTask = nullptr;
	try
	{
		myTask = user->getTaskByID(taskID);
		switch (myTask->getType())
		{
		case Type::OPEN_TASK:
			approveOpenTask(myTask);
			break;
		case Type::CLOSE_TASK:
			approveCloseTask(myTask);
			break;
		case Type::CHANGE_TASK:
			approveChangeTask(myTask);
			break;
		default:
			break;
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		if (std::strcmp(e.what(), "The task is validated for changing, not approved already") == 0)
		{
			//send the task approved to the new bank again
			ChangeTask* task = static_cast<ChangeTask*>(myTask);
			if (system->getBank(user->getBankName())->doesExist(task->getAccount()))
			{
				task->validate();
				task->setOldBankFlagTo(false);
				system->getBank(task->getNewBankName())->assignTask(task);
			}
		}
	}
}

void EmployeeMode::disapprove()
{
	int taskID;
	std::cin >> taskID;
	std::cout << std::endl;
	String message = readStringFromConsole();
	Task* myTask = nullptr;
	try
	{
		myTask = user->getTaskByID(taskID);
		Message* newMessage = user->disapprove(myTask, message);
		system->sendMessageToClient(newMessage, myTask->getClientInfo().egn);
		user->removeTaskAt(myTask->getIdx());
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

void EmployeeMode::validate()
{
	int taskID;
	std::cin >> taskID;
	std::cout << std::endl;
	Task* myTask = nullptr;
	try
	{
		myTask = user->getTaskByID(taskID);
		if (myTask->getType() == Type::CHANGE_TASK)
		{
			ChangeTask* task = static_cast<ChangeTask*>(myTask);
			task->setOldBankFlagTo(true);
			system->getBank(task->getOldBankName())->assignTask(task);
		}
		else
		{
			std::cout << "The task with this ID is not a change task!";
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

void EmployeeMode::approveOpenTask(Task* myTask)
{
	Account* newAccount = user->approve(myTask);
	String accID(newAccount->getAccNumber());
	system->getBank(user->getBankName())->openAccount(std::move(newAccount));
	String message = "You opened an account in " + user->getBankName() + "! Your account ID is " + accID;
	Message* toSend = new Message(message);
	system->sendMessageToClient(toSend, myTask->getClientInfo().egn);
	user->removeTaskAt(myTask->getIdx());
}

void EmployeeMode::approveCloseTask(Task* myTask)
{
	Account* accountToClose = user->approve(myTask);
	String accID(accountToClose->getAccNumber());
	system->getBank(user->getBankName())->closeAccount(accountToClose);
	String message = "You closed an account in " + user->getBankName() + accID;
	Message* toSend = new Message(message);
	system->sendMessageToClient(toSend, myTask->getClientInfo().egn);
	user->removeTaskAt(myTask->getIdx());
}

void EmployeeMode::approveChangeTask(Task* myTask)
{
	Account* accToChange = user->approve(myTask);
	String oldBankName(accToChange->getBankName());
	double moneyInAcc(accToChange->getAmount());
	system->getBank(oldBankName)->closeAccount(accToChange);
	Account* changedAccount = new Account(user->getBankName(), moneyInAcc);
	system->getBank(user->getBankName())->openAccount(std::move(changedAccount));

	String accID(changedAccount->getAccNumber());
	String message = "You changed your account to " + user->getBankName() + "! Your new account ID is " + accID;
	Message* toSend = new Message(message);
	system->sendMessageToClient(toSend, myTask->getClientInfo().egn);
	user->removeTaskAt(myTask->getIdx());
}
