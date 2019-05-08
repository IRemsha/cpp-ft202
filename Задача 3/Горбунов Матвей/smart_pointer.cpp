#include <iostream>

using namespace std;

template <class T>
class Smart_Pointer
{
	T* value;
	int* count;

public:
	Smart_Pointer()
	{
		this->value = nullptr;
		this->count = 1;
	}

	T get()
	{
		return *value;
	}

	void set(T *new_value)
	{
		release();
		this->value = new_value;
		this->count = new int(1);
	}
	
	void release()
	{
		if (value == nullptr)
			return;
		*count--;
		if (count == 0)
		{
			delete this->count;
			delete this->value;
			this->value = nullptr;
			this->count = nullptr;
		}
		this->value = nullptr;
		this->count = nullptr;
	}

	T& operator*()
	{
		return *value;
	}

	T* operator->()
	{
		return value;
	}

	Smart_Pointer& operator=(Smart_Pointer &other)
	{
		this->value = other.value;
		this->count = other.count;
		*count++;
		return *this;
	}

	~Smart_Pointer()
	{
		release();
	}

};


int main()
{
	Smart_Pointer<int> sm_ptr_1;
	Smart_Pointer<int> sm_ptr_2;

	sm_ptr_1.set(new int(1));
	sm_ptr_2.set(new int(2));

	cout << sm_ptr_1.get() << ", " << &sm_ptr_1 << "\n";
	cout << sm_ptr_2.get() << ", " << &sm_ptr_2 << "\n";

	sm_ptr_1 = sm_ptr_2;
	cout << sm_ptr_1.get() << ", " << &sm_ptr_1 << "\n";

	sm_ptr_1.release();
}

