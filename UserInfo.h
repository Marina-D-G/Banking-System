#pragma once
#include "String.h"

struct UserInfo
{
	UserInfo() = default;
	UserInfo(String& _firstName, String& _lastName, int _egn, int _age);
	String firstName;
	String lastName;
	int egn;
	int age;
};