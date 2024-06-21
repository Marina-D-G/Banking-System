#include "Check.h"

Check::Check(): code("not_found"), transferAmount(0.0), signedBy("not_found"){}

Check::Check(String& _code, double _transferAmount, String& _signedBy)
{
	if (uniqueCodes.addCode(_code))
	{
		code = _code;
	}
	else
	{
		throw std::runtime_error("The code is not valid, try with another one!");
	}
	if (_transferAmount>0.0)
	{
		transferAmount = _transferAmount;
	}
	else
	{
		throw std::runtime_error("The amount of money is not valid, try with another one!");
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