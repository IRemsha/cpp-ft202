#include <iostream>

using namespace std;

template <class T>
class SmartPointer
{
	T* ptr;
	size_t* ref_c;

public:

	SmartPointer()
	{
		ptr = NULL;
		ref_c = NULL;
	}

	void set(T* ptr)
	{
		this->ptr = ptr;
		ref_c = new size_t(1);
	}

	T get()
	{
		return *ptr;
	}

	void release()
	{
		if (ptr) {
			--(*ref_c);
			if (ref_c == 0)
			{
				delete ptr;
				delete ref_c;
				ptr = NULL;
				ref_c = NULL;
			}
		}
	}

	~SmartPointer()
	{
		release();
	}


	T* operator->()
	{
		return ptr;
	}

	T operator*()
	{
		return *ptr;
	}

	SmartPointer& operator=(SmartPointer& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
			ref_c = other.ref_c;
			(*ref_c)++;
		}
		return *this;
	}

};

int main()
{
	SmartPointer<int>* ptr1 = new SmartPointer<int>();
	SmartPointer<int>* ptr2 = new SmartPointer<int>();
	ptr1->set(new int(1));
	ptr2->set(new int(2));
	SmartPointer<int> res = *ptr1;
	printf("%i", *ptr1);
	printf("%s", "\n");
	cout << ptr1->get() << endl << ptr2->get() << endl;
	ptr2 = ptr1;
	cout<< ptr2->get()<<endl;
	printf("%i", *ptr2);
	ptr1->release();
	ptr2->release();

}