#include "User.h"
#include <fstream>

User::User()
{
	persInfo.firstName = "not_found";
	persInfo.lastName = "not_found";
	persInfo.egn = "not_found";
	persInfo.age = 0;
	password = "not_found";
}

User::User(String& _firstName, String& _lastName, String& _egn, int _age, String& _password)
{
	persInfo.firstName = _firstName;
	persInfo.lastName = _lastName;
	persInfo.egn = _egn;
	persInfo.age = _age;
	password = _password;
}

User::User(UserInfo& _info, String& _password)
{
	persInfo.firstName = _info.firstName;
	persInfo.lastName = _info.lastName;
	persInfo.egn = _info.egn;
	persInfo.age = _info.age;
	password = _password;
}

void User::whoami() const
//print full information for the user
{
	std::cout << "You are " << persInfo.firstName << " " << persInfo.lastName << ". " << std::endl;
	std::cout << "(EGN: " << persInfo.egn << ", Age: " << persInfo.age << ")" << std::endl << std::endl;
}

UserInfo& User::getUserInfo() 
{
	return persInfo;
}

bool User::checkPassword(String& other)
{
	return password == other;
}

void User::save(std::ofstream& ofs)
{
	size_t firstName = persInfo.firstName.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&firstName), sizeof(firstName));
	ofs.write(persInfo.firstName.c_str(), firstName);

	size_t lastName = persInfo.lastName.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&lastName), sizeof(lastName));
	ofs.write(persInfo.lastName.c_str(), lastName);

	int age = persInfo.age;
	ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));

	size_t egnLen = persInfo.egn.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&egnLen), sizeof(egnLen));
	ofs.write(persInfo.egn.c_str(), egnLen);

	size_t passLen = password.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&passLen), sizeof(passLen));
	ofs.write(password.c_str(), passLen);
}

void User::load(std::ifstream& ifs)
{
	size_t firstNameLen;
	ifs.read(reinterpret_cast<char*>(&firstNameLen), sizeof(firstNameLen));
	char* firstNameBuffer = new char[firstNameLen];
	ifs.read(firstNameBuffer, firstNameLen);
	persInfo.firstName = firstNameBuffer;
	delete[] firstNameBuffer;

	size_t lastNameLen;
	ifs.read(reinterpret_cast<char*>(&lastNameLen), sizeof(lastNameLen));
	char* lastNameBuffer = new char[lastNameLen];
	ifs.read(lastNameBuffer, lastNameLen);
	persInfo.lastName = lastNameBuffer;
	delete[] lastNameBuffer;

	ifs.read(reinterpret_cast<char*>(&persInfo.age), sizeof(persInfo.age));

	size_t egnLen;
	ifs.read(reinterpret_cast<char*>(&egnLen), sizeof(egnLen));
	char* egnBuffer = new char[egnLen];
	ifs.read(egnBuffer, egnLen);
	persInfo.egn = egnBuffer;
	delete[] egnBuffer;

	size_t passLen;
	ifs.read(reinterpret_cast<char*>(&passLen), sizeof(passLen));
	char* passBuffer = new char[passLen];
	ifs.read(passBuffer, passLen);
	password = passBuffer, passLen;
	delete[] passBuffer;
}
