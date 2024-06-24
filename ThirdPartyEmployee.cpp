#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee() : User() {}

ThirdPartyEmployee::ThirdPartyEmployee(String& _firstName, String& _lastName, String& _egn, int _age, String& _password): User(_firstName, _lastName, _egn, _age, _password) {}

ThirdPartyEmployee::ThirdPartyEmployee(UserInfo& userInfo, String& _password): User(userInfo, _password) {}

void ThirdPartyEmployee::help() const
{
	std::cout << "You can:\n";
	std::cout << "1) Send check (send_check)\n\n";
}

Check* ThirdPartyEmployee::send_check(double sum, String& code)
{
	Check* newCheck = new Check(code, sum, this->persInfo.firstName);
	return newCheck;
}

void ThirdPartyEmployee::save(std::ofstream& ofs)
{
	User::save(ofs);
}

