#include "CloseTask.h"

CloseTask::CloseTask(UserInfo& _clientInfo, String& _taskName, Account* _account): Task(_clientInfo, _taskName)
{
	type = Type::CLOSE_TASK;
	account = _account;
}

void CloseTask::setMessage()
{
	String closeMessage = clientInfo.firstName + " wants to close an account."; //with id 2903, problem sus string + int
	taskMessage.setMessage(closeMessage);
}

int CloseTask::getAccNumber() const
{
	return account->getAccNumber();
}

double CloseTask::getAccBalance() const
{
	return account->getAmount();
}

String& CloseTask::getBankName() const
{
	return account->getBankName();
}

Account* CloseTask::getAccount()
{
	return account;
}

Task* CloseTask::clone() const
{
	return new CloseTask(*this);
}
