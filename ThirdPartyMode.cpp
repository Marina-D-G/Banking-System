#include "ThirdPartyMode.h"

ThirdPartyMode::ThirdPartyMode(BankSystem* _system, ThirdPartyEmployee* _user): Mode(_system), user(_user){}

void ThirdPartyMode::execute()
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
		else if (command == "send_check")
		{
			send_check();
		}
		else
		{
			std::cout << "This command does not exist, call help to see what you can do!\n";
		}
		std::cin >> command;
	}
	std::cout << std::endl;
}

void ThirdPartyMode::send_check()
{
	double amount;
	String code;
	String egn;
	std::cin >> amount;
	std::cin >> code;
	std::cin >> egn;
	std::cout << std::endl;
	try
	{
		Check* newCheck = user->send_check(amount, code);
		String message = "You have a check assigned to you by " + newCheck->getSignedBy();
		Message* newMessage = new Message(message);
		system->sendCheckToClient(newCheck, egn);
		system->sendMessageToClient(newMessage, egn);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}
}
