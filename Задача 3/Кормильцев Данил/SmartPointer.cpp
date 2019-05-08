#include "pch.h"
#include <iostream>
using namespace std;

template <class T> class smart_pointer
{

protected:
	T* object_ref;
	unsigned* counter;

public:
	smart_pointer()
	{
		object_ref = nullptr;
		counter = nullptr;
	}

	smart_pointer(T* object)
	{
		this->object_ref = object;
		counter = new unsigned(1);
	}

	smart_pointer(smart_pointer<T>& other)
	{
		this->object_ref = other.object_ref;
		this->counter = other.counter;
		(*counter)++;
	}

	~smart_pointer()
	{
		Release();
	}

	T Get()
	{
		return *object_ref;
	}

	void Set(T* new_object)
	{
		Release();
		object_ref = new_object;
		counter = new unsigned(1);
	}

	void Release()
	{
		(*counter)--;
		if (counter == 0)
		{
			delete object_ref;
			delete counter;
			object_ref = nullptr;
			counter = nullptr;
		}
	}

	smart_pointer<T>& operator=(smart_pointer<T> & other) {
		if (counter != nullptr && *counter > 0)
		{
			Release();
		}
		if (this != &other)
		{
			object_ref = other.object_ref;
			counter = other.counter;
			(*counter)++;
		}
		return *this;
	}

	T* operator ->()
	{
		return object_ref;
	}

	T operator *()
	{
		return *object_ref;
	}
};

int main()
{
	smart_pointer<int> pointer_1(new int(1));
	cout << "Pointer 1 value: " << pointer_1.Get() << endl;
	smart_pointer<int> pointer_2{};
	smart_pointer<int> pointer_3{};
	pointer_2 = pointer_1;
	pointer_3 = pointer_2;
	cout << "Pointer 2 value: " << pointer_2.Get() << endl;
	cout << "Pointer 3 value: " << pointer_3.Get() << endl;
	pointer_3.Set(new int(2));
	cout << "Value is set" << endl;
	cout << "Pointer 1 value: " << pointer_1.Get() << endl;
	cout << "Pointer 2 value: " << pointer_2.Get() << endl;
	cout << "Pointer 3 value: " << pointer_3.Get() << endl;
}

