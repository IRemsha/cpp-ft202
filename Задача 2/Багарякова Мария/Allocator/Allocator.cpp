#include "pch.h"
#include <iostream>

using namespace std;

class Allocator
{
	struct Block
	{
		size_t size = 0;
		bool is_taken = false;
		Block* previous_block;
		Block* buddy_block;
		Block* next_left_block;
		Block* next_right_block;
	};

	Block* start;

	void block_initialise(Block* block, size_t block_size, Block* previous, Block* buddy)
	{
		block->size = block_size;
		block->previous_block = previous;
		block->buddy_block = buddy;
		block->next_left_block = NULL;
		block->next_right_block = NULL;
	}

	void print_dumps(Block* block)
	{
		if (block != nullptr)
		{
			print_dumps(block->next_left_block);
			if (block->next_left_block == NULL && block->next_right_block == NULL)
			{
				printf("%s", "Block size: ");
				printf("%i", block->size);
				printf("%s", "\n");
				printf("%s", "Taken: ");
				if (block->is_taken)
				{
					printf("%s", "yes\n");
				}
				else
				{
					printf("%s", "no\n");
				}
			}
			print_dumps(block->next_right_block);
		}
	}

public:
	Allocator(size_t allocator_size)
	{
		start = new Block();
		block_initialise(start, allocator_size, NULL, NULL);
	}

	void* Alloc(size_t alloc_size)
	{
		Block* current_block = start;
		size_t current_size = current_block->size;
		void* result = nullptr;
		while (true)
		{
			if (current_size / 2 < 1)
			{
				throw exception("Allocator is overflowed");
			}
			if (alloc_size <= current_size)
			{
				if (alloc_size > current_size / 2)
				{
					current_block->is_taken = true;
					if (current_block->buddy_block->is_taken)
					{
						current_block->previous_block->is_taken = true;
						current_block->buddy_block->previous_block->is_taken = true;
					}
					result = current_block;
					break;
				}
				if (current_block->next_left_block == NULL && current_block->next_right_block == NULL)
				{
					Block* left_block = new Block();
					Block* right_block = new Block();
					block_initialise(left_block, current_size / 2, current_block, right_block);
					block_initialise(right_block, current_size / 2, current_block, left_block);
					current_block->next_left_block = left_block;
					current_block->next_right_block = right_block;
				}
				if (!current_block->next_left_block->is_taken)
				{
					current_size = current_size / 2;
					current_block = current_block->next_left_block;
				}
				else if (!current_block->next_right_block->is_taken)
				{
					current_size = current_size / 2;
					current_block = current_block->next_right_block;
				}
				else
					throw exception("Allocator is overflowed");
			}
			else
				throw exception("Allocator is overflowed");
		}
		return result;
	}

	void Free(void *ptr)
	{
		Block* block = (Block*)ptr;
		if (block == start)
		{
			start->is_taken = false;
			start->next_left_block = NULL;
			start->next_right_block = NULL;
			return;
		}
		if (block->buddy_block->is_taken)
		{
			block->is_taken = false;
		}
		else
		{
			Block* current_block = block;
			while (!current_block->buddy_block->is_taken)
			{
				delete current_block->buddy_block;
				Block* previous = current_block->previous_block;
				delete current_block;
				current_block = previous;
				current_block->next_left_block = NULL;
				current_block->next_right_block = NULL;
				previous->is_taken = false;
				if (current_block == start || current_block->is_taken)
				{
					break;
				}

			}
		}
	}

	void Dump()
	{
		print_dumps(start);
	}
};

int main()
{
	Allocator* alloc = new Allocator(64);
	void* result1 = alloc->Alloc(8);
	void* result2 = alloc->Alloc(8);
	void* result3 = alloc->Alloc(8);
	printf("%s", "add three 8 sized blocks to 64 block\n");
	alloc->Dump();
	alloc->Free(result2);
	printf("%s", "free the second block\n");
	alloc->Dump();
	alloc->Free(result3);
	printf("%s", "free the third block\n");
	alloc->Dump();
	alloc->Free(result1);
	printf("%s", "free the first block\n");
	alloc->Dump();
	return 0;
}
