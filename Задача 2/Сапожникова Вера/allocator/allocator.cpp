// allocator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Allocator
{
private:
	size_t * start;
	Allocator* first_part;
	Allocator* second_part;
	size_t value;
	size_t length;
	bool is_filled;

public:
	Allocator(size_t size)
	{
		start = &size;
		length = size;
		is_filled = false;
	}

	Allocator(size_t* start, size_t length)
	{
		this->start = start;
		this->length = length;
	}

	void Free(void *ptr)
	{
		if (first_part != nullptr)
		{
			if (first_part->start == ptr)
			{
				first_part = nullptr;
				return;
			}
			first_part->Free(ptr);
		}
		if (start == ptr)
			is_filled = false;
		if (second_part != nullptr)
		{
			if (second_part->start == ptr)
			{
				second_part = nullptr;
				return;
			}
			second_part->Free(ptr);
		}
	}

	void* Alloc(size_t size)
	{
		rsize_t half = length / 2;
		if (first_part == nullptr)
			first_part = new Allocator(start, half);
		if (second_part == nullptr)
			second_part = new Allocator(start + half, half);

		if (size > half)
		{
			is_filled = true;
			value = size;
			return start;
		}

		if (!first_part->is_filled)
			return first_part->Alloc(size);
		if (!second_part->is_filled)
			return second_part->Alloc(size);
	}

	void Dump()
	{
		if (first_part != nullptr)
			first_part->Dump();
		if (is_filled)
			cout << start << " " << value << endl;
		if (second_part != nullptr)
			second_part->Dump();
	}
};

int main()
{
	auto a = Allocator(512);
	a.Alloc(128);
	a.Alloc(32);
	a.Free(&a);
	a.Alloc(64);
	a.Alloc(32);
	a.Dump();
}

