#include "Account.h"

Account::Account(): bankName("not_found"), number(0), amount(0.0){}

Account::Account(String& _bankName, double _amount): bankName(_bankName), amount(_amount), number(nextID++){}

String& Account::getBankName()
{
    return bankName;
}

int Account::getAccNumber()
{
    return number;
}

double Account::getAmount()
{
    return amount;
}

void Account::setAmount(double newAmount)
{
    amount += newAmount;
}

//void Account::getClientInfo() const
//{
//
//}
