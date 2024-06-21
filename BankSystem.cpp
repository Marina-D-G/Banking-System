#include "BankSystem.h"

void BankSystem::create_bank(String& bankName)
{
	for (size_t i = 0; i < banks.getSize(); i++)
	{
		if (bankName == banks[i].getBankName())
		{
			std::cout << "This bank already exists!\n";
			return;
		}
	}
	banks.push(Bank(bankName));
}
