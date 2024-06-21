#pragma once
#include <iostream>

class String
{
public:
    String();
    String(const char* str);
    String(const String& other);
    String& operator=(const String& other);
    String(String&& other) noexcept;
    String& operator=(String&& other) noexcept;
    ~String();

    size_t getCapacity() const;
    size_t getSize() const;

    const char* c_str() const;

    String& operator+=(const String& other);

    char& operator[](size_t idx);
    const char& operator[](size_t idx) const;

    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);
    friend String operator+(const String& lhs, const String& rhs);

    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);

private:
    char* data;
    size_t size;
    size_t capacity;

    void copyFrom(const String& other);
    void moveFrom(String&& other);
    void free();
    size_t calcCapacity(size_t _size) const;
};

//bool operator<(const String& lhs, const String& rhs);
//bool operator<=(const String& lhs, const String& rhs);
//bool operator>(const String& lhs, const String& rhs);
//bool operator>=(const String& lhs, const String& rhs);
