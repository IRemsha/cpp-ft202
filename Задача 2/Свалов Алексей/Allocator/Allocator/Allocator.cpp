#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::cerr;
using std::malloc;


class Block
{
public:
	Block *next;
	Block *prev;
	int *pointer = NULL;
	int block_start_index;
	bool is_empty;
	int size;

	// конструктор
	Block(int size_t) {
		pointer = (int*)malloc(size_t);
		size = size_t;
		is_empty = true;
	}

	// деструктор
	~Block()
	{
		free(pointer);
	}

};


class Allocator
{
private:
	Block *pointer;
	int allocator_size;
	int blocks_amount;
public:
	// конструктор
	Allocator(int size_t) {
		this->allocator_size = (int)pow(2, ceil(log2(size_t)));
		cout << "Allocator Size: ";
		cout << this->allocator_size << endl;
		cout << endl;
		this->pointer = new Block(1);
		Block * block = new Block(this->allocator_size);
		this->pointer->prev = pointer;
		this->pointer->next = block;
		block->prev = pointer;
		block->next = block;
		this->pointer->block_start_index;
		this->blocks_amount = 1;
	}

	// выделить кусок памяти нужного размера
	void* Alloc(int size_t) {
		int default_block_size = this->allocator_size;
		int needed_block = this->allocator_size + 1;
		int memory_size = size_t;
		while (memory_size <= default_block_size) {
			needed_block = default_block_size;
			default_block_size /= 2;
		}
		Block *suitable_block = MinSuitableBlockFinder(needed_block);
		if (suitable_block == NULL) {
			cerr << memory_size << " <- No free block available for this amount of data";
			exit(1);
		}

		int block_size = suitable_block->size;
		while (block_size != needed_block) {
			suitable_block = SplitBlock(suitable_block);
			block_size = suitable_block->size;
		}
		suitable_block->is_empty = false;
		return suitable_block->pointer;
	}

	// освободить выделенный кусок памяти
	void Free(void *ptr) {
		Block *block = pointer;
		for (int i = 0; i < blocks_amount; i++) {
			block = block->next;
			if (block->pointer == ptr) {
				block->is_empty = true;
				break;
			}
		}
		bool flag = true;
		while(flag) {
			int size = block->size;
			int offset_index = block->block_start_index / size;
			if (offset_index % 2 == 0) {
				Block* maybe_buddy = block->next;
				if (maybe_buddy->is_empty && maybe_buddy->size == size && 
					maybe_buddy->block_start_index / size - 1 == offset_index) {
					block = MergeBlocks(block, maybe_buddy);
				}
				else {
					flag = false;
				}
			}
			else {
				Block* maybe_buddy = block->prev;
				if (maybe_buddy->is_empty && maybe_buddy->size == size 
					&& maybe_buddy->block_start_index / size + 1 == offset_index) {
					block = MergeBlocks(maybe_buddy, block);
				}
				else {
					flag = false;
				}
			}
		}
	}

	// тестовый метод Dump, выводящий где какие блоки и какие из них заняты
	void Dump() {
		Block *block = pointer;
		cout << "Allocator blocks:" << endl;
		for (int i = 0; i < blocks_amount; i++) {
			block = block->next;
			cout << i + 1;
			cout << " Block size: ";
			cout << block->size;
			cout << ", ";
			if (block->is_empty)
				cout << "free" << endl;
			else
				cout << "not free" << endl;
		};
	}

	// находим минимальный подходящий блок
	Block* MinSuitableBlockFinder(int needed_block) {
		Block* block = pointer;
		Block* suitable_block = NULL;
		int min_suitable_block_size = allocator_size + 1;
		for (int i = 0; i < blocks_amount; i++) {
			block = block->next;
			int block_size = block->size;
			if (block->is_empty) {
				if (needed_block <= block_size && block_size < min_suitable_block_size) {
					min_suitable_block_size = block_size;
					suitable_block = block;
				}
			}
		};
		return suitable_block;
	}

	// разделяем блок на двойников
	Block* SplitBlock(Block* block) {
		int buddy_sizes = block->size / 2;
		Block* prev_block = block->prev;
		Block* next_block = block->next;
		Block* left_block = new Block(buddy_sizes);
		Block* right_block = new Block(buddy_sizes);
		prev_block->next = left_block;
		next_block->prev = right_block;
		left_block->next = right_block;
		left_block->prev = prev_block;
		right_block->next = next_block;
		right_block->prev = left_block;
		left_block->block_start_index = block->block_start_index;
		right_block->block_start_index = block->block_start_index + buddy_sizes;
		delete block;
		this->blocks_amount += 1;
		return left_block;
	}

	// сливаем двойников в один блок
	Block* MergeBlocks(Block* block, Block* buddy) {
		int new_size = block->size * 2;
		Block* prev_block = block->prev;
		Block* next_block = buddy->next;
		Block* new_block = new Block(new_size);
		prev_block->next = new_block;
		next_block->prev = new_block;
		new_block->next = next_block;
		new_block->prev = prev_block;
		new_block->block_start_index = block->block_start_index;
		buddy->next = NULL;
		block->prev = NULL;
		delete buddy;
		delete block;
		this->blocks_amount -= 1;
		return new_block;
	}

	// деструктор
	~Allocator()
	{
		free(pointer);
	}

};

int main()
{
	Allocator allocator = Allocator((int)pow(2, 8));
	cout << "Operation 1: Alloc 20" << endl;
	void *ptr1 = allocator.Alloc(20);
	allocator.Dump();
	cout << endl;
	cout << "Operation 2: Alloc 8" << endl;
	void *ptr2 = allocator.Alloc(8);
	allocator.Dump();
	cout << endl;
	cout << "Operation 3: Alloc 47" << endl;
	void *ptr3 = allocator.Alloc(47);
	allocator.Dump();
	cout << endl;
	cout << "Operation 4: Alloc 31" << endl;
	void *ptr4 = allocator.Alloc(31);
	allocator.Dump();
	cout << endl;
	cout << "Operation 5: Free 8 ptr2" << endl;
	allocator.Free(ptr2);
	allocator.Dump();
	cout << endl;
	cout << "Operation 6: Free 31 ptr4" << endl;
	allocator.Free(ptr4);
	allocator.Dump();
	cout << endl;
	cout << "Operation 7: Alloc 128" << endl;
	void *ptr5 = allocator.Alloc(128);
	allocator.Dump();
	cout << endl;
	return 0;
}
