#ifndef __MEM_TEST_H
#define __MEM_TEST_H

#include "stdio.h"
#include "stdbool.h"
#include "malloc.h"
#include "string.h"
#include "stdarg.h"

void* mem_calloc(size_t _Count, size_t _Size);
void mem_free(void* _Block);
short mem_check(void);

#endif // __MEM_TEST_H