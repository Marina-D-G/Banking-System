#pragma once
#include "String.h"
#include "UniqueCheckCodes.h"

static UniqueCheckCodes uniqueCodes;

class Check
{
public:
	Check();
	Check(String& _code, double _transferAmount, String& _signedBy);
	const String& getCode() const;
	double getTransferAmount() const;

	friend bool operator==(const Check& lhs, const Check& rhs);
	friend bool operator!=(const Check& lhs, const Check& rhs);

private:
	String code;
	double transferAmount;
	String signedBy;
};

