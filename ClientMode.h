#pragma once
#include "Mode.h"
#include "Client.h"

class ClientMode : public Mode
{
public:
	ClientMode(BankSystem* _system, Client* _user);
	void execute() override;
private:
	Client* user;
	void check_avl();
	void open();
	void close();
	void redeem();
	void change();
	void list();
};

