#include "User.h"

User::User()
{
	persInfo.firstName = "not_found";
	persInfo.lastName = "not_found";
	persInfo.egn = 0;
	persInfo.age = 0;
	password = "not_found";
}

User::User(String& _firstName, String& _lastName, int _egn, int _age, String& _password)
{
	persInfo.firstName = _firstName;
	persInfo.lastName = _lastName;
	persInfo.egn = _egn;
	persInfo.age = _age;
	password = _password;
}

void User::exit()
{
	//exit the profile, make current user nullptr(optional?)
}

void User::whoami() const
//print full information for the user
{
	std::cout << "You are " << persInfo.firstName << " " << persInfo.lastName << ". " << std::endl;
	std::cout << "(EGN: " << persInfo.egn << ", Age: " << persInfo.age << ")" << std::endl;
}

UserInfo& User::getUserInfo() 
{
	return persInfo;
}
