#pragma once
#include "Task.h"

class OpenTask : public Task
{
public:
	OpenTask(UserInfo& _clientInfo, String& _taskName);
	void setMessage() override;

	Task* clone() const override;
private:
};

