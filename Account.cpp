#include "Account.h"
#include <fstream>

int Account::nextID = 1;

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

void Account::save(std::ofstream& ofs)
{
    size_t nameLen = bankName.getSize();
    ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    ofs.write(bankName.c_str(), nameLen);

    ofs.write(reinterpret_cast<const char*>(&number), sizeof(number));

    ofs.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
}

void Account::load(std::ifstream& ifs)
{
    size_t nameLen;
    ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    char* nameBuffer = new char[nameLen];
    ifs.read(nameBuffer, nameLen);
    bankName = nameBuffer;
    delete[] nameBuffer;

    ifs.read(reinterpret_cast<char*>(&number), sizeof(number));
    ifs.read(reinterpret_cast<char*>(&amount), sizeof(amount));
}

bool operator==(const Account& lhs, const Account& rhs)
{
    return lhs.bankName == rhs.bankName && lhs.nextID == rhs.nextID && lhs.number == rhs.number;
}

bool operator!=(const Account& lhs, const Account& rhs)
{
    return !(lhs == rhs);
}
