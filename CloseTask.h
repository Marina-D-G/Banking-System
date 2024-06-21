#pragma once
#include "Task.h"
#include "Account.h"

class CloseTask : public Task
{
public:
	//CloseTask() = default;
	CloseTask(UserInfo& _clientInfo, String& _taskName, Account* _account);
	void setMessage() override;

	int getAccNumber() const;
	double getAccBalance() const;
	String& getBankName() const;
	Account* getAccount();

	Task* clone() const override;
private:
	Account* account;
};

