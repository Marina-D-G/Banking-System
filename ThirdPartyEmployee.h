#pragma once
#include "User.h"
#include "Check.h"

class ThirdPartyEmployee: public User
{
public:
	ThirdPartyEmployee();
	ThirdPartyEmployee(String& _firstName, String& _lastName, int _egn, int _age, String& _password);
	void help() const override;

	Check* send_check(double sum, String& code);
private:
	//???
};

