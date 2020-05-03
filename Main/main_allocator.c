#include "main_cfg.h"

#if MAIN_ALLOCATOR_EN

#define MAIN_ALLOCATOR_CFG_POLY_INSTANTIATION_EN					1u

#define MAIN_ALLOCATOR_CFG_STACK_BACK_TRACE_EN						1u

#define MAIN_ALLOCATOR_CFG_CONCEPT_ALLOCATOR_EN						1u

#if (MAIN_ALLOCATOR_CFG_CONCEPT_ALLOCATOR_EN)

#define ALLOCATOR_TYPE												CONCEPT_ALLOCATOR

#endif // (MAIN_ALLOCATOR_CFG_CONCEPT_ALLOCATOR_EN)

void main_allocator_allocate(void **block);
void main_allocator_deallocate(void **block);

struct allocator_control_s
	*allocator_control_ptr = NULL;

struct allocator_s
	*allocator = { NULL };

struct allocator_s
	*block = NULL;

void main_allocator(void)
{
	printf("\r\n------------------------+ allocator demo start +------------------------\r\n");

	allocator_control_ptr
		= allocator_control_get_function_address_table(ALLOCATOR_TYPE);						/* Variables pointer to	the function address table of
																								specified container type		*/

	printf("\r\nallocator.init start \r\n");
	allocator_control_ptr->configuration.init(&allocator);

	printf("\r\nallocator.allocate start \r\n");
	block = allocator_control_ptr->allocate(allocator, 1, 1);
	printf("allocator.allocate:block %p \r\n", block);

	#if MAIN_ALLOCATOR_CFG_POLY_INSTANTIATION_EN

	struct allocator_s
		*allocator_second = { NULL };

	void *block_second = NULL;

	printf("\r\nallocator_second.init start \r\n");
	allocator_control_ptr->configuration.init(&allocator_second);

	printf("\r\nallocator_second.allocate start \r\n");
	block_second = allocator_control_ptr->allocate(allocator_second, 1, 1);
	printf("allocator.allocate:block %p \r\n", block_second);

	printf("\r\nallocator_second.deallocate start \r\n");
	allocator_control_ptr->deallocate(allocator_second, block_second);

	printf("\r\nallocator_second.destroy start \r\n");
	allocator_control_ptr->configuration.destroy(&allocator_second);

	#endif // MAIN_ALLOCATOR_CFG_POLY_INSTANTIATION_EN

	#if (!MAIN_ALLOCATOR_CFG_STACK_BACK_TRACE_EN)

	printf("\r\nallocator.deallocate start \r\n");
	allocator_control_ptr->deallocate(allocator, block);

	#endif // (MAIN_ALLOCATOR_CFG_STACK_BACK_TRACE_EN)

	main_allocator_allocate(&block);
	main_allocator_deallocate(&block);

	printf("\r\nallocator.destroy start \r\n");
	allocator_control_ptr->configuration.destroy(&allocator);

	printf("\r\n------------------------+ allocator demo end +------------------------\r\n");

	return;
}

void main_allocator_allocate(void **block)
{
	*block = allocator_control_ptr->allocate(allocator, 1, 1);
}

void main_allocator_deallocate(void **block)
{
	allocator_control_ptr->deallocate(allocator, *block);
}

#endif // MAIN_ALLOCATOR_EN