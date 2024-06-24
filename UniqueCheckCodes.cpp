#include "UniqueCheckCodes.h"

static bool isSmallLetter(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

static bool isCapitalLetter(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

static bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

void UniqueCheckCodes::resize(size_t newCapacity)
{
    String* newCodes = new String[newCapacity];
    for (size_t i = 0; i < size; i++)
    {
        newCodes[i] = std::move(codes[i]);
    }
    delete[] codes;
    codes = newCodes;
    capacity = newCapacity;
}

UniqueCheckCodes::UniqueCheckCodes() : codes(nullptr), capacity(0), size(0) {}

UniqueCheckCodes::~UniqueCheckCodes()
{
    delete[] codes;
}

bool UniqueCheckCodes::isValidCode(const String& str) const
{
    if (str.getSize() != 3)
    {
        return false;
    }

    for (size_t i = 0; i < size; i++)
    {
        char ch = str[i];
        if (!isSmallLetter || !isCapitalLetter || !isDigit)
        {
            return false;
        }
    }
    return true;
}

bool UniqueCheckCodes::isUniqueString(const String& str) const
{
    for (size_t i = 0; i < size; i++)
    {
        if (codes[i] == str)
        {
            return false;
        }
    }
    return true;
}

bool UniqueCheckCodes::addCode(const String& _code)
{
    if (isValidCode(_code) && isUniqueString(_code))
    {
        if (size == capacity)
        {
            resize(capacity == 0 ? 1 : (capacity * 2));
        }
        codes[size++] = _code;
        return true;
    }
    return false;
}


