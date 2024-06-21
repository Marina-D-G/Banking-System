#include "OpenTask.h"

OpenTask::OpenTask(UserInfo& _clientInfo, String& _taskName): Task(_clientInfo, _taskName)
{
	type = Type::OPEN_TASK;
}

void OpenTask::setMessage()
{
	String openMessage = clientInfo.firstName + " wants to create an account.";
	taskMessage.setMessage(openMessage);
}

Task* OpenTask::clone() const
{
	return new OpenTask(*this);
}
