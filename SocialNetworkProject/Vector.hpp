#pragma once
#include<iostream>

const size_t DEFAULT_CAPACITY = 8;

template <typename T>
class Vector {
private:
	T* data;
	size_t size;
	size_t capacity;

	void copyFrom(const Vector& other);
	void free();
	void moveFrom(Vector&& other);
	void resize();
public:
	Vector();
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, size_t index);
	void pushAt(T&& element, size_t index);
	T& popBack();
	T& popAt(size_t index);
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	bool empty() const;
	void clear();
	bool contains(const T& element);
	void remove(const T& element);
};

template <typename T>
void Vector<T>::copyFrom(const Vector& other)
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
void Vector<T>::free()
{
	delete[] data;
	size = capacity = 0;
	data = nullptr;
}
template <typename T>
void Vector<T>::moveFrom(Vector&& other)
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	other.data = nullptr;
	other.size = other.capacity = 0;
}
template<typename T>
void Vector<T>::resize()
{
	if (capacity == 0)
		capacity = DEFAULT_CAPACITY;
	else
		capacity *= 2;

	T* newData = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = std::move(data[i]);
	}
	delete[] data;
	data = newData;
}


template <typename T>
Vector<T>::Vector()
{
	//not alocating data because we have
	//for example comments in the comment and recursion occurs
	//another way is to add constructor with unsigned argument 
	//which shows how much memory memory to be alocated
	data = nullptr;
	size = capacity = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}
template <typename T>
Vector<T>::Vector(Vector<T>&& other)
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
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		copyFrom(std::move(other));
	}
	return *this;
}
template <typename T>
Vector<T>::~Vector()
{
	free();
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return size;
}
template <typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
void Vector<T>::pushBack(const T& element)
{
	if (size == capacity)
	{
		resize();
	}
	data[size++] = element;
}
template <typename T>
void Vector<T>::pushBack(T&& element)
{
	if (size == capacity)
	{
		resize();
	}
	data[size++] = std::move(element);
}
template<typename T>
void Vector<T>::pushAt(const T& element, size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range("Error");

	if (size == capacity)
		resize();

	for (int i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = element;
	size++;
}
template<typename T>
void Vector<T>::pushAt(T&& element, size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range("Error");

	if (size == capacity)
		resize();

	for (int i = size; i > index; i--)
		data[i] = data[i - 1];

	data[index] = std::move(element);
	size++;
}
template <typename T>
T& Vector<T>::popBack()
{
	if (empty())
		throw std::out_of_range("Index out of range!");
	size--;
	return data[size];
}
template<typename T>
T& Vector<T>::popAt(size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range("Error");

	T result = data[index];
	for (size_t i = index; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
	return result;
}
template<typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index <0 || index > size - 1)
		throw std::out_of_range("Error");
	return data[index];
}
template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index <0 || index > size - 1)
		throw std::out_of_range("Error");
	return data[index];
}
template<typename T>
bool Vector<T>::empty() const
{
	return size == 0;
}
template<typename T>
void Vector<T>::clear()
{
	delete[] data;
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
	size = 0;
}
template<typename T>
bool Vector<T>::contains(const T& element)
{
	for (size_t i = 0; i < size; i++)
	{
		if (element == data[i])
		{
			return true;
		}
	}
	return false;
}
template<typename T>
void Vector<T>::remove(const T& element)
{
	for (size_t i = 0; i < size; i++)
	{
		if (element == data[i])
		{
			//move rest of the elements
			for (size_t j = i; j < size - 1; j++)
			{
				data[j] = data[j + 1];
			}
			size--;
			break;
		}
	}

}

