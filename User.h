#pragma once
#include "Vector.hpp"
#include "String.h"
#include "UserInfo.h"

class User
{
public:
	User();
	User(String& _firstName, String& _lastName, int egn, int age, String& _password);
	virtual ~User() = default;

	void exit();
	virtual void whoami() const; //print full information for the user
	virtual void help() const = 0; //print which are the supported commands for the exact user

	UserInfo& getUserInfo();
protected:
	UserInfo persInfo;
	String password;
};

