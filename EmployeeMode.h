#pragma once
#include "Mode.h"
#include "Employee.h"

class EmployeeMode : public Mode
{
public:
	EmployeeMode(BankSystem* _system, Employee* _user);
	void execute() override;
private:
	Employee* user;
	void view();
	void approve();
	void disapprove();
	void validate();

	void approveOpenTask(Task* myTask);
	void approveCloseTask(Task* myTask);
	void approveChangeTask(Task* myTask);
};

