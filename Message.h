#pragma once
#include "String.h"

class Message
{
public:
	Message();
	Message(String& newMessage);
	void setMessage(String& newMessage);
	String& getText();
private:
	String message;
};

