#pragma once
#include "User.h"
#include "Task.h"
#include "OpenTask.h"
#include "CloseTask.h"
#include "ChangeTask.h"
#include "PolymorphicContainer.hpp"

class Employee: public User
{
public:
	Employee() = default; //???
	Employee(String& _firstName, String& _lastName, int _egn, int _age, String& _password, String& _bankAssociated);
	void whoami() const override;
	void help() const override;

	void show_tasks();
	void view(int taskID);
	Account* approve(int taskID);

	void disapprove(int taskID, String& message);
	void validate(int taskID);

	void setTask(Task* newTask);
	size_t getNumTasks() const;

private:
	PolymorphicContainer<Task> tasks;
	String bankAssociated; //??? da ne se podava na konstruktora a bankata e prosto da znae sistemata kude da zapishe employeeto 

	void viewOpenTask(Task* task);
	void viewCloseTask(Task* task);
	void viewChangeTask(Task* task);

	Account* approveOpenTask(Task* task);
	Account* approveCloseTask(Task* task);
	Account* approveChangeTask(Task* task);
};

