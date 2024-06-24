#include <iostream>
#include "BankSystem.h"
#include "String.h"
#include "Mode.h"
#include "ClientMode.h"
#include "EmployeeMode.h"
#include "ThirdPartyMode.h"

static void executeByMode(BankSystem* system, Mode* mode)
{
	if (system->getUserType() == TypeOfUser::CLIENT)
	{
		mode = new ClientMode(system, static_cast<Client*>(system->getCurrentUser()));
		mode->execute();
		delete mode;
		mode = nullptr;
	}
	if (system->getUserType() == TypeOfUser::EMPLOYEE)
	{
		mode = new EmployeeMode(system, static_cast<Employee*>(system->getCurrentUser()));
		mode->execute();
		delete mode;
		mode = nullptr;
	}
	if (system->getUserType() == TypeOfUser::THIRD_PARTY_EMPLOYEE)
	{
		mode = new ThirdPartyMode(system, static_cast<ThirdPartyEmployee*>(system->getCurrentUser()));
		mode->execute();
		delete mode;
		mode = nullptr;
	}
}

static void create_bank(BankSystem& system)
{
	String bankName;
	std::cin >> bankName;
	std::cout << std::endl;
	try
	{
		system.create_bank(bankName);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}

static void signup(BankSystem& system)
{
	UserInfo user;
	String role;
	String password;
	std::cout << "First name: ";
	std::cin >> user.firstName;
	std::cout << "Last name: ";
	std::cin >> user.lastName;
	std::cout << "EGN: ";
	std::cin >> user.egn;
	std::cout << "Age: ";
	std::cin >> user.age;
	std::cout << "Role: ";
	std::cin >> role;
	std::cout << "Password: ";
	std::cin >> password;
	bool successful = false;
	while (!successful)
	{
		try
		{
			system.signup(user, role, password);
			successful = true;
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what();
			std::cin >> user.egn;
		}
	}
}

static bool login(BankSystem& system)
{
	String name, password;
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "Password: ";
	std::cin >> password;
	std::cout << std::endl;
	try
	{
		system.login(name, password);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
}

int main()
{
	BankSystem system;
	system.load("bankSystem.dat");
	String command;
	Mode* mode = nullptr;
	std::cin >> command;

	while (command != "exit")
	{
		if (command == "create_bank")
		{
			create_bank(system);
		}
		else if (command == "signup")
		{
			signup(system);
		}
		else if (command == "login")
		{
			if (login(system))
			{
				executeByMode(&system, mode);
			}
			else
			{
				std::cout << "Try to login with other account!\n\n";
			}
		}
		else
		{
			std::cout << "You can only create bank, sign up or login!\n\n";
		}
		std::cin >> command;
		if (command == "exit")
		{
			system.save("bankSystem.dat");
		}
	}
	std::cout << std::endl;
	return 0;
}