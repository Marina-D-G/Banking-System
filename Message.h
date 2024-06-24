#pragma once
#include "String.h"

class Message
{
public:
	Message();
	Message(String& newMessage);
	void setMessage(String& newMessage);
	String& getText();

	void save(std::ofstream& ofs);
	void load(std::ifstream& ifs);
private:
	String message;
};

