#include "pch.h"
#include <iostream>

template <class T>
class SmartPointer
{
	T *Ptr;
	unsigned *Reference_Count;

	void Remove_reference()
	{
		*Reference_Count--;
		if (Reference_Count == 0)
		{
			delete Ptr;
			free(Reference_Count);
			Ptr = NULL;
			Reference_Count = NULL;
		}
	}

public:
	SmartPointer()
	{
		Ptr = NULL;
		Reference_Count = NULL;
	}

	T Get()
	{
		return *Ptr;
	}

	void Set(T *ptr)
	{
		Ptr = ptr;
		Reference_Count = (unsigned*)malloc(sizeof(unsigned));
		*Reference_Count++;
	}

	void Release()
	{
		Remove_reference();
	}

	SmartPointer & operator=(SmartPointer &other)
	{
		if (*Reference_Count > 0)
		{
			Remove_reference();
		}
		if (this != &other)
		{
			Ptr = other.Ptr;
			Reference_Count = other.Reference_Count;
			*Reference_Count++;
		}
		return *this;
	}

	T* operator->()
	{
		return Ptr;
	}

	T operator*()
	{
		return *Ptr;
	}

	~SmartPointer()
	{
		Remove_reference();
	}
};

int main()
{
	SmartPointer<int> *ptr1 = new SmartPointer<int>();
	SmartPointer<int> *ptr2 = new SmartPointer<int>();

	ptr1->Set(new int(1));
	ptr2->Set(new int(2));

	printf("%i", *ptr1);
	printf("%s", "\n");
	printf("%i", *ptr2);
	printf("%s", "\n");

	printf("%i", ptr1->Get());
	printf("%s", "\n");
	printf("%i", ptr2->Get());
	printf("%s", "\n");

	ptr2 = ptr1;

	printf("%i", ptr2->Get());
	printf("%s", "\n");
	printf("%i", *ptr2);

	ptr1->Release();
	ptr2->Release();
}