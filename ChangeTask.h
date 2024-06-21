#pragma once
#include "Task.h"
#include "Account.h"

class ChangeTask : public Task
{
public:
	ChangeTask(UserInfo& _clientInfo, String& _taskName, String& _oldBank, String& _newBank, Account* account);
	void setMessage() override;
	void validate();
	void setOldBankFlagTo(bool flag);

	bool isValidated();
	bool isTaskInOldBank();

	int getAccNumber() const;
	double getAccBalance() const;
	String& getBankName() const;
	Account* getAccount();

	Task* clone() const override;
private:
	String oldBank;
	String newBank;
	Account* account;
	bool validated_flag;
	bool oldBank_flag;
};