#include "mem_test.h"

short mem_alloc = 0;

void* mem_calloc(size_t _Count, size_t _Size)
{
	void* ptr = calloc(_Count, _Size);

	if (ptr != NULL)
	{
		mem_alloc++;
	}

	return ptr;
}

void mem_free(void* _Block)
{
	free(_Block);

	mem_alloc--;
}

short mem_check(void)
{
	return mem_alloc;
}