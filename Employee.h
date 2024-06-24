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
	Employee() = default;
	Employee(String& _firstName, String& _lastName, String& _egn, int _age, String& _password, String& _bankAssociated);
	Employee(UserInfo& _info, String& _bankAssociated, String& _password);
	
	void whoami() const override;
	void help() const override;

	void show_tasks();
	void view(Task* myTask);
	Account* approve(Task* myTask);

	Message* disapprove(Task* myTask, String& message);
	ChangeTask* validate(ChangeTask* myTask);

	void setTask(Task* newTask);
	void removeTaskAt(int ID);
	void disableTaskAt(int ID);
	size_t getNumTasks() const;
	Task* getTaskByID(int taskID);
	String& getBankName();

	void save(std::ofstream& ofs) override;
	void load(std::ifstream& ifs) override;

private:
	int nextTaskID;
	PolymorphicContainer<Task> tasks;
	String bankAssociated;

	void viewOpenTask(Task* task);
	void viewCloseTask(Task* task);
	void viewChangeTask(Task* task);

	Account* approveOpenTask(Task* task);
	Account* approveCloseTask(Task* task);
	Account* approveChangeTask(Task* task);

	Message* disapproveOpenTask(Task* task, String& message);
	Message* disapproveCloseTask(Task* task, String& message);
	Message* disapproveChangeTask(Task* task, String& message);
};

