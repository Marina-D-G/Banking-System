#pragma once
#include "Mode.h"
#include "ThirdPartyEmployee.h"

class ThirdPartyMode : public Mode
{
public:
	ThirdPartyMode(BankSystem* _system, ThirdPartyEmployee* _user);
	void execute() override;
private:
	ThirdPartyEmployee* user;
	void send_check();
};

