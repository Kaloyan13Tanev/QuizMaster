#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class Vector
{
	T* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void resize(size_t newCapacity);

public:
	Vector();
	Vector(size_t size);
	Vector(size_t size, const T& rhs);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other) noexcept;
	~Vector();

	void push_back(const T& rhs);
	void push_back(T&& rhs);
	void pop_back();

	void insert(size_t indx, const T& rhs);
	void insert(size_t indx, T&& rhs);
	void removeAt(size_t indx);
	bool remove(const T& value);
	bool contains(const T& value) const;

	void shrink_to_fit();
	void clear();

	const T& operator[](size_t indx) const;
	T& operator[](size_t indx);
	const T& front() const;
	const T& back() const;
	bool isEmpty() const;
	size_t getSize() const;
	size_t getCapacity() const;
};

template<typename T>
void Vector<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity]{};
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
void Vector<T>::resize(size_t newCapacity)
{
	if (newCapacity < size)
	{
		throw std::invalid_argument("Invalid new capacity!");
	}

	if (newCapacity == capacity)
	{
		return;
	}

	T* temp = new T[newCapacity]{};
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = std::move(data[i]);
	}

	delete[] data;
	capacity = newCapacity;
	data = temp;
}

template<typename T>
Vector<T>::Vector() : Vector(8)
{}

template<typename T>
Vector<T>::Vector(size_t n)
{
	capacity = n == 0 ? 1 : n;
	size = 0;
	data = new T[capacity]{};
}

template<typename T>
Vector<T>::Vector(size_t n, const T& rhs) : Vector(n)
{
	for (size_t i = 0; i < n; i++)
	{
		data[i] = rhs;
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
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

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::push_back(const T& rhs)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = rhs;
}

template<typename T>
void Vector<T>::push_back(T&& rhs)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = std::move(rhs);
}

template<typename T>
void Vector<T>::pop_back()
{
	if (isEmpty())
	{
		throw std::logic_error("Array is empty!");
	}

	size--;
}

template<typename T>
void Vector<T>::insert(size_t indx, const T& rhs)
{
	// if want to all for insert at end do > instead of >=
	if (indx >= size)
	{
		throw std::out_of_range("Given index is out of the bounds of the vector");
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	for (size_t i = size; i > indx; i--)
	{
		data[i] = std::move(data[i - 1]);
	}
	data[indx] = rhs;
	size++;
}

template<typename T>
void Vector<T>::insert(size_t indx, T&& rhs)
{
	if (indx >= size)
	{
		throw std::out_of_range("Given index is out of the bounds of the vector");
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	for (size_t i = size; i > indx; i--)
	{
		data[i] = std::move(data[i - 1]);
	}
	data[indx] = std::move(rhs);
	size++;
}

template<typename T>
void Vector<T>::removeAt(size_t indx)
{
	if (indx >= size)
	{
		throw std::out_of_range("Given index is out of the bounds of the vector");
	}

	for (size_t i = indx; i < size - 1; i++)
	{
		data[i] = std::move(data[i + 1]);
	}

	size--;
}

template<typename T>
bool Vector<T>::remove(const T& value)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value)
		{
			removeAt(i);
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::contains(const T& value) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	resize(size == 0 ? 1 : size);
}

template<typename T>
void Vector<T>::clear()
{
	size = 0;
}

template<typename T>
const T& Vector<T>::operator[](size_t indx) const
{
	if (indx >= size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return data[indx];
}

template<typename T>
T& Vector<T>::operator[](size_t indx)
{
	if (indx >= size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return data[indx];
}

template<typename T>
const T& Vector<T>::front() const
{
	if (isEmpty())
	{
		throw std::logic_error("Array is empty!");
	}

	return data[0];
}

template<typename T>
const T& Vector<T>::back() const
{
	if (isEmpty())
	{
		throw std::logic_error("Array is empty");
	}

	return data[size - 1];
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
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