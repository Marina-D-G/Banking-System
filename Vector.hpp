#pragma once
#include <utility>
#include "String.h"

template <typename T>
class Vector
{
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void free();
    void copyFrom(const Vector<T>& other);
    void moveFrom(Vector<T>&& other);
    void resize(size_t newCapacity);

public:
    Vector();
    Vector(size_t dataSize);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other) noexcept;
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other) noexcept;
    ~Vector();

    bool empty() const;
    void clear();

    Vector<T>& operator+=(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);

    size_t getSize() const;
    size_t getCapacity() const;

    void push(const T& element);
    void push(T&& element);
    void remove(const T& elem);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
    {
        for (int i = 0; i < v.size; i++)
            os << v[i] << " ";

        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector<T>& v)
    {
        for (int i = 0; i < v.size; i++)
            is >> v[i];

        return is;
    }
};

template<typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs);

template<typename T>
Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs);

template <typename T>
Vector<T>::Vector() : Vector(8) {}

template <typename T>
Vector<T>::Vector(size_t dataSize) : capacity(dataSize)
{
    data = new T[capacity];
}

template <typename T>
void Vector<T>::free()
{
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.data = nullptr;
    other.size = other.capacity = 0;
}

template <typename T>
void Vector<T>::resize(size_t newCapacity)
{
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; i++)
    {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
    moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    free();
}

template<typename T>
bool Vector<T>::empty() const
{
    return size == 0;
}

template<typename T>
void Vector<T>::clear()
{
    size = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other)
{
    for (int i = 0; i < size; i++)
    {
        data[i] += other.data[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other)
{
    for (int i = 0; i < size; i++)
    {
        data[i] -= other.data[i];
    }
    return *this;
}

template<typename T>
size_t Vector<T>::getSize() const
{
    return size;
}

template<typename T>
size_t Vector<T>::getCapacity() const
{
    return capacity;
}

template<typename T>
void Vector<T>::push(T&& element)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }
    data[size++] = std::move(element);
}

template<typename T>
void Vector<T>::push(const T& element)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }
    data[size++] = element;
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
    if (index > size)
    {
        throw std::logic_error("Invalid index!");
    }
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
    if (index > size)
    {
        throw std::logic_error("Invalid index!");
    }
    return data[index];
}

template<typename T>
void Vector<T>::remove(const T& elem)
{
    for (size_t i = 0; i < size; i++)
    {
        if (data[i] == elem)
        {
            for (size_t j = i; j < size - 1; j++)
            {
                data[j] = std::move(data[j + 1]);
            }
            size--;
            return;
        }
    }
}

template<typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs)
{
    Vector<T> result(lhs);
    result += rhs;
    return result;
}

template<typename T>
Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs)
{
    Vector<T> result(lhs);
    result -= rhs;
    return result;
}
