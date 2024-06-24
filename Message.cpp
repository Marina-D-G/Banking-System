#include "Message.h"
#include <fstream>

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

void Message::save(std::ofstream& ofs)
{
	size_t messLen = message.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&messLen), sizeof(messLen));
	ofs.write(message.c_str(), messLen);
}

void Message::load(std::ifstream& ifs)
{
	size_t nameLen;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	char* nameBuffer = new char[nameLen];
	ifs.read(nameBuffer, nameLen);
	message = nameBuffer;
	delete[] nameBuffer;
}
