#pragma once
#include "String.h"

class UniqueCheckCodes
{
public:
    UniqueCheckCodes();
    UniqueCheckCodes(const UniqueCheckCodes& other) = delete;
    ~UniqueCheckCodes();

    bool addCode(const String& _code);

private:
    String* codes;
    size_t capacity;
    size_t size;

    void resize(size_t newCapacity);
    bool isValidCode(const String& str) const;
    bool isUniqueString(const String& str) const;
};

