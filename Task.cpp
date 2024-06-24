#include "Task.h"

Task::Task(UserInfo& _clientInfo, String& _taskName): clientInfo(_clientInfo), taskName(_taskName) {}

void Task::setIndex(int _index)
{
	index = _index;
}

Type Task::getType() const
{
	return type;
}

int Task::getIdx() const
{
	return index;
}

String& Task::getTaskName() 
{
	return taskName;
}

UserInfo& Task::getClientInfo()
{
	return clientInfo;
}

String& Task::getMessage()
{
	return taskMessage.getText();
}
