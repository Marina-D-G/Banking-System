#include "Message.h"

Message::Message() : message("not_found"){}

Message::Message(String& newMessage)
{
	message = newMessage;
}

void Message::setMessage(String& newMessage)
{
	message = newMessage;
}

String& Message::getText()
{
	return message;
}
