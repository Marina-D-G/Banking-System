#pragma once
#include "User.h"
#include "Check.h"

class ThirdPartyEmployee: public User
{
public:
	ThirdPartyEmployee();
	ThirdPartyEmployee(String& _firstName, String& _lastName, String& _egn, int _age, String& _password);
	ThirdPartyEmployee(UserInfo& userInfo, String& _password);
	void help() const override;

	Check* send_check(double sum, String& code);

	void save(std::ofstream& ofs);
};

