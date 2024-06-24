#include "Check.h"
#include <fstream>

Check::Check(): code("not_found"), transferAmount(0.0), signedBy("not_found"){}

Check::Check(String& _code, double _transferAmount, String& _signedBy)
{
	if (uniqueCodes.addCode(_code))
	{
		code = _code;
	}
	else
	{
		throw std::runtime_error("The code is not valid, try with another one!\n");
	}
	if (_transferAmount>0.0)
	{
		transferAmount = _transferAmount;
	}
	else
	{
		throw std::runtime_error("The amount of money is not valid, try with another one!\n");
	}
	signedBy = _signedBy;
}

const String& Check::getCode() const
{
	return code;
}

double Check::getTransferAmount() const
{
	return transferAmount;
}

String& Check::getSignedBy()
{
	return signedBy;
}

void Check::save(std::ofstream& ofs)
{
	size_t codeLen = code.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen));
	ofs.write(code.c_str(), codeLen);

	ofs.write(reinterpret_cast<const char*>(&transferAmount), sizeof(transferAmount));

	size_t nameLen = signedBy.getSize() + 1;
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	ofs.write(signedBy.c_str(), nameLen);
}

void Check::load(std::ifstream& ifs)
{
	size_t codeLen;
	ifs.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));
	char* codeBuffer = new char[codeLen];
	ifs.read(codeBuffer, codeLen);
	code = codeBuffer;
	delete[] codeBuffer;

	ifs.read(reinterpret_cast<char*>(&transferAmount), sizeof(transferAmount));

	size_t nameLen;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
	char* nameBuffer = new char[nameLen];
	ifs.read(nameBuffer, nameLen);
	signedBy = nameBuffer;
	delete[] nameBuffer;
}

bool operator==(const Check& lhs, const Check& rhs)
{
	if (lhs.getCode() == rhs.getCode() && lhs.getTransferAmount() == rhs.getTransferAmount())
	{
		return true;
	}
	return false;
}

bool operator!=(const Check& lhs, const Check& rhs)
{
	return !(lhs == rhs);
}