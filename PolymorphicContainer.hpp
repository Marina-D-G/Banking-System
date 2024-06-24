#pragma once
#include "PolymorphicPtr.hpp"
#include "Vector.hpp"

//from https://github.com/stoychoX/Object-oriented-programming-FMI/tree/main/Seminar-SE/Seminar14

template<class T>
class PolymorphicContainer
{
private:
	Vector<PolymorphicPtr<T>> data;
public:
	void add(T*);
	void remove(T*);
	void removeAt(int index);
	void disable(int index);

	PolymorphicPtr<T>& operator[](size_t idx);
	const PolymorphicPtr<T>& operator[](size_t idx) const;

	size_t getSize() const;

	void execute(size_t idx, void (*func)(T*));
	void execute(size_t idx, void (*func)(const T*)) const;
};

template<class T>
void PolymorphicContainer<T>::add(T* ptr)
{
	data.push(ptr);
}

template<class T>
void PolymorphicContainer<T>::remove(T* ptr)
{
	delete ptr;
	ptr = nullptr;
	data.remove(ptr);
}

template<class T>
void PolymorphicContainer<T>::removeAt(int index)
{
	data.removeAt(index-1);
}

template<class T>
void PolymorphicContainer<T>::disable(int index)
{
	data[index - 1] = nullptr;
	data.decrementSize();
}

template<class T>
inline PolymorphicPtr<T>& PolymorphicContainer<T>::operator[](size_t idx)
{
	return data[idx];
}

template<class T>
const PolymorphicPtr<T>& PolymorphicContainer<T>::operator[](size_t idx) const
{
	return data[idx];
}

template<class T>
size_t PolymorphicContainer<T>::getSize() const
{
	return data.getSize();
}

template<class T>
void PolymorphicContainer<T>::execute(size_t idx, void(*func)(T*))
{
	func(data[idx].get());
}

template<class T>
void PolymorphicContainer<T>::execute(size_t idx, void(*func)(const T*)) const
{
	func(data[idx].get());
}
