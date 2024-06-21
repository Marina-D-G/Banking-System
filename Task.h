#pragma once
#include "String.h"
#include "Message.h"
#include "UserInfo.h"

enum class Type
{
	OPEN_TASK,
	CLOSE_TASK,
	CHANGE_TASK,
	NO_TYPE
};

class Task
{
public:
	Task(UserInfo& _clientInfo, String& _taskName);
	virtual Task* clone() const = 0;
	virtual ~Task() = default;

	virtual void setMessage() = 0;
	void setIndex(int _index);

	Type getType() const;
	int getIdx() const;
	String& getTaskName();
	UserInfo& getClientInfo();
	String& getMessage();

protected:
	Type type;
	int index;
	String taskName; 
	UserInfo clientInfo; 
	Message taskMessage;
};

