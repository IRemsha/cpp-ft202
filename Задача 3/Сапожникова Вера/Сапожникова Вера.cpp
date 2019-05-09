#include <iostream>

using namespace std;

template <class T>
class SmartPointer
{
	T* ptr;
	unsigned* ref_counter;

public:

	SmartPointer()
	{
		ptr = NULL;
		ref_counter = NULL;
	}

	void set(T* ptr)
	{
		this->ptr = ptr;
		ref_counter = (unsigned*)malloc(sizeof(unsigned));
		(*ref_counter)++;
	}

	T get()
	{
		return *ptr;
	}

	void release()
	{
		if (ptr) {
			--(*ref_counter);
			if (ref_counter == 0)
			{
				delete ptr;
				free(ref_counter);
				ptr = NULL;
				ref_counter = NULL;
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
		release();
		if (this != &other)
		{
			ptr = other.ptr;
			ref_counter = other.ref_counter;
			(*ref_counter)++;
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
	printf("%i", *ptr1);
	printf("%s", "\n");
	printf("%i", *ptr2);
	printf("%s", "\n");
	cout << ptr1->get() << endl << ptr2->get() << endl;
	ptr2 = ptr1;
	cout<< ptr2->get()<<endl;
	printf("%i", *ptr2);
	ptr1->release();
	ptr2->release();

}