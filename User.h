#pragma once
#include "Vector.hpp"
#include "String.h"
#include "UserInfo.h"

class User
{
public:
	User();
	User(String& _firstName, String& _lastName, String& egn, int age, String& _password);
	User(UserInfo& _info, String& password);
	virtual ~User() = default;

	virtual void whoami() const; //print full information for the user
	virtual void help() const = 0; //print which are the supported commands for the exact user

	UserInfo& getUserInfo();
	bool checkPassword(String& other);

	virtual void save(std::ofstream& ofs);
	virtual void load(std::ifstream& ifs);

protected:
	UserInfo persInfo;
	String password;
};

