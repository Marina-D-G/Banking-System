#include "String.h"
#include <cstring>
#pragma warning(disable:4996)

static int lenOfNum(int num)
{
	int count = 0;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return count;
}

static int reverseInt(int num) 
{
	int reversed = 0;
	while (num != 0) {
		int digit = num % 10;      
		reversed = reversed * 10 + digit;  
		num /= 10;    
	}
	return reversed;
}

static char* intToString(int num)
{
	int len = lenOfNum(num) + 1;
	char* str = new char[len] {};
	num = reverseInt(num);
	for (int i = 0; i < len - 1; i++)
	{
		str[i] = ((num % 10) + '0');
		num /= 10;
	}
	str[len - 1] = '\0';
	return str;
}

String::String(): String(""){}

String::String(const char* str)
{
	size = strlen(str);
	capacity = calcCapacity(size);
	data = new char[capacity];
	strcpy(data, str);
}

String::String(int num) : String(intToString(num)){};

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

String::String(String&& other) noexcept
{
	moveFrom(std::move(other));
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

String::~String()
{
	free();
}

size_t String::getCapacity() const
{
	return capacity;
}

size_t String::getSize() const
{
	return size;
}

const char* String::c_str() const
{
	return data;
}

String& String::operator+=(const String& other)
{
	if (size + other.size < capacity)
	{
		strcat(data, other.data);
		size += other.size;
		return *this;
	}

	size += other.size;
	capacity = calcCapacity(size);

	char* newData = new char[capacity];
	strcpy(newData, data);
	strcat(newData, other.data);

	delete[]data;
	data = newData;
	return *this;
}

char& String::operator[](size_t idx)
{
	if (idx > size)
	{
		throw std::logic_error("Invalid index\n");
	}
	return data[idx];
}

const char& String::operator[](size_t idx) const
{
	if (idx > size)
	{
		throw std::logic_error("Invalid index\n");
	}
	return data[idx];
}

void String::copyFrom(const String& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity];
	strcpy(data, other.data);
}

void String::moveFrom(String&& other)
{
	size = other.size;
	capacity = other.capacity;
	other.size = other.capacity = 0;

	data = other.data;
	other.data = nullptr;
}

void String::free()
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

size_t String::calcCapacity(size_t _size) const
{
	if (_size < 16)
	{
		return 16;
	}
	return _size + _size / 2;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[1024]{};
	is >> buff;
	str = buff;
	return is;
}

String operator+(const String& lhs, const String& rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}

bool operator==(const String& lhs, const String& rhs)
{
	return (strcmp(lhs.data, rhs.data) == 0);
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}
