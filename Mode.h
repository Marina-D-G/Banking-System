#pragma once
#include "BankSystem.h"

class Mode
{
public:
	Mode(BankSystem* _system);
	virtual void execute() = 0;
	virtual ~Mode();
protected:
	BankSystem* system;
};

