#pragma once

template <class T>
class smart_ptr
{
	T* ptr;
	size_t* counter;

public:

	explicit smart_ptr(T* obj)
	{
		set(obj);
	}

	T* operator->()
	{
		return ptr;
	}

	T operator*()
	{
		return get();
	}

	void set(T* new_obj)
	{
		release();
		ptr = new_obj;
		counter = new size_t();
		*counter = 1;
	}

	T get()
	{
		return *ptr;
	}

	smart_ptr& operator=(const smart_ptr& other)
	{
		release();
		counter = other.counter;
		(*counter)++;
		ptr = other.ptr;
		return *this;
	}

	~smart_ptr()
	{
		release();
	}

	void release()
	{
		if (!ptr)
			return;
		
		(*counter)--;
		if (*counter == 0)
		{
			delete ptr;
			delete counter;
		}
		ptr = nullptr;
		counter = nullptr;	
	}
};