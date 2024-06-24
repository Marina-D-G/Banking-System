#pragma once
#include <utility>
#include <stdexcept>

//from https://github.com/stoychoX/Object-oriented-programming-FMI/tree/main/Seminar-SE/Seminar14

template<class T>
class PolymorphicPtr
{
private:
	T* ptr = nullptr;

	void free();
	void copyFrom(const PolymorphicPtr&);
	void move(PolymorphicPtr&&);

public:
	PolymorphicPtr() = default;

	PolymorphicPtr(T*);

	PolymorphicPtr(const PolymorphicPtr&);
	PolymorphicPtr(PolymorphicPtr&&) noexcept;

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	operator bool() const;

	T* get();
	const T* get() const;

	void reset();
	void reset(T*);

	PolymorphicPtr& operator=(const PolymorphicPtr&);
	PolymorphicPtr& operator=(PolymorphicPtr&&) noexcept;

	~PolymorphicPtr();
};

template<class T>
void PolymorphicPtr<T>::free()
{
	delete ptr;
	ptr = nullptr;
}

template<class T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr& other)
{
	ptr = other ? other.ptr->clone() : nullptr;
}

template<class T>
void PolymorphicPtr<T>::move(PolymorphicPtr&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

template<class T>
PolymorphicPtr<T>::PolymorphicPtr(T* p) : ptr(p) {}

template<class T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr& other)
{
	copyFrom(other);
}

template<class T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr&& other) noexcept
{
	move(std::move(other));
}

template<class T>
T* PolymorphicPtr<T>::operator->()
{
	return ptr;
}

template<class T>
const T* PolymorphicPtr<T>::operator->() const
{
	return ptr;
}

template<class T>
T& PolymorphicPtr<T>::operator*()
{
	if (get())
		return *ptr;
	throw std::runtime_error("Cannot get\n");
}

template<class T>
const T& PolymorphicPtr<T>::operator*() const
{
	if (get())
		return *ptr;
	throw std::runtime_error("Cannot get\n");
}

template<class T>
PolymorphicPtr<T>::operator bool() const
{
	return (ptr != nullptr);
}

template<class T>
T* PolymorphicPtr<T>::get()
{
	return ptr;
}

template<class T>
const T* PolymorphicPtr<T>::get() const
{
	return ptr;
}

template<class T>
void PolymorphicPtr<T>::reset()
{
	free();
}

template<class T>
void PolymorphicPtr<T>::reset(T* p)
{
	free();
	ptr = p;
}

template<class T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template<class T>
PolymorphicPtr<T>::~PolymorphicPtr()
{
	free();
}