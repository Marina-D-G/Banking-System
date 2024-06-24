#pragma once
#include "String.h"

struct UserInfo
{
	UserInfo() = default;
	UserInfo(String& _firstName, String& _lastName, String& _egn, int _age);
	String firstName;
	String lastName;
	String egn;
	int age;
};