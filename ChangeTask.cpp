#include "ChangeTask.h"

ChangeTask::ChangeTask(UserInfo& _clientInfo, String& _taskName, String& _newBank, String& _oldBank, Account* _account) : Task(_clientInfo, _taskName)
{
	oldBank = _oldBank;
	newBank = _newBank;
	account = _account;
	type = Type::CHANGE_TASK;
}

void ChangeTask::setMessage()
{
	if (!isValidated()&&!isTaskInOldBank())
	{
		String changeMessage = clientInfo.firstName + " wants to join " + newBank;
		taskMessage.setMessage(changeMessage);
		return;
	}
	if (!isValidated() && isTaskInOldBank())
	{
		String changeMessage = newBank + " asks if " + clientInfo.firstName + " is real user.";
		taskMessage.setMessage(changeMessage);
		return;
	}
	if (isValidated() && !isTaskInOldBank())
	{
		String changeMessage = clientInfo.firstName + " wants to join " + newBank + " (approved)";
		taskMessage.setMessage(changeMessage);
		return;
	}
}

void ChangeTask::validate()
{
	validated_flag = true;
}

void ChangeTask::setOldBankFlagTo(bool flag)
{
	oldBank_flag = flag;
}

bool ChangeTask::isValidated()
{
	return validated_flag;
}

bool ChangeTask::isTaskInOldBank()
{
	return oldBank_flag;
}

int ChangeTask::getAccNumber() const
{
	return account->getAccNumber();
}

double ChangeTask::getAccBalance() const
{
	return account->getAmount();
}

String& ChangeTask::getOldBankName() const
{
	return account->getBankName();
}

String& ChangeTask::getNewBankName() 
{
	return newBank;
}

Account* ChangeTask::getAccount()
{
	return account;
}

Task* ChangeTask::clone() const
{
	return new ChangeTask(*this);
}
