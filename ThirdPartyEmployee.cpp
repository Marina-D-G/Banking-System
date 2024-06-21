#include "ThirdPartyEmployee.h"

ThirdPartyEmployee::ThirdPartyEmployee() : User() {}

ThirdPartyEmployee::ThirdPartyEmployee(String& _firstName, String& _lastName, int _egn, int _age, String& _password): User(_firstName, _lastName, _egn, _age, _password) {}

void ThirdPartyEmployee::help() const
{
	std::cout << "You can:\n";
	std::cout << "1) Send check (send_check)\n";
}

Check* ThirdPartyEmployee::send_check(double sum, String& code)
{
	Check* newCheck = new Check(code, sum, this->persInfo.firstName);
	return newCheck;
}

