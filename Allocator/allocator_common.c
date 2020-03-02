/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "allocator_common.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This struct is the allocator structure module
 */

struct allocator_s {
	/* @brief RESERVED This variables will record the identity code of allocator type.					*/
	enum allocator_type_e	allocator_type_id;

	struct {
		/* @brief This variables will record the size of allocator allocated.						    */
		ALLOCATOR_SIZE_TYPEDEF size;
	}info;

	struct {
		/* @brief This variables will point to the exception handler of lack of memory.			        */
		void (*lack_of_memory)(void *allocator);
	}exception;

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	/* @brief This variables will used to record the link status.										*/
	STACK_BACK_TRACE_LINK_TYPEDEF_PTR capture_stack_back_trace_link;

	#endif
};

struct memory_control_s {
	/* @brief This variables will record which memory block is available by check bit.					*/
	int available[ALLOCATOR_GLOBAL_CFG_MEMORY_POOL_SIZE / sizeof(int) * 8];

	/* @brief This variables will point to the address of memory pool.					                */
	void *memory_pool_ptr;

	/* @brief This variables will point to the next allocate entry point address.					    */
	void *entry_point_ptr;

	/* @brief This variables will record the size of allocator memory pool.						        */
	ALLOCATOR_SIZE_TYPEDEF memory_pool_size;
};

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This array will contain all the universal vector functions address.
 */

void *allocator_common_function_address_tables[] =
{
	(void *)&allocator_control_configuration_init,							/* No.0 : initialize */

	(void *)&allocator_control_configuration_destroy,						/* No.1 : destroy */

	(void *)&allocator_control_configuration_exception,						/* No.3 : exception */

	(void *)&allocator_control_allocate,									/* No.4 : allocate */

	(void *)&allocator_control_deallocate									/* No.5 : deallocate */
};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the allocator struct.
 *
 * @param allocator the allocator
 * @param lack_of_memory the pointer to the exception handler of lack of heap memory
 *
 * @return NONE
 */

errno_t allocator_control_configuration_init(ALLOCATOR_COMMON_TYPEDEF_PPTR allocator,
										 void (*lack_of_memory)(void *))
{
	assert(allocator);

	struct allocator_s
		*allocator_alloced = (struct allocator_s *)calloc(1, sizeof(struct allocator_s));			/* Malloc #1 */

	if (NULL == allocator_alloced) {
		return 1;
	}

	allocator_alloced->allocator_type_id = ALLOCATOR_COMMON;                                       /* Assign the allocator struct */
	allocator_alloced->info.size = 0u;
	allocator_control_configuration_exception(allocator_alloced, lack_of_memory);

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_link_init(&allocator_alloced->capture_stack_back_trace_link, 256);

	#endif

	(*allocator) = allocator_alloced;

	return 0;
}

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return NONE
 */

void allocator_control_configuration_destroy(ALLOCATOR_COMMON_TYPEDEF_PPTR allocator)
{
	assert(allocator);

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	printf("allocator.destroy:memory free status : %d \r\n", (*allocator)->info.size);

	if (0 < (*allocator)->info.size) {
		printf("\r\n-----------------------------------stack trace string table begin-----------------------------------\r\n");
		STACK_BACK_TRACE_TYPEDEF_PPTR stack_back_trace_tmp = malloc(sizeof(void *));
		if (NULL == stack_back_trace_tmp) {
			return;
		}

		debug_capture_stack_back_trace_link_get_trace_ptr((*allocator)->capture_stack_back_trace_link, stack_back_trace_tmp);

		printf("\r\n-----------------------------------stack trace mark string table begin-----------------------------------\r\n");
		debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 0));

		printf("\r\n-----------------------------------stack trace link string table begin-----------------------------------\r\n");
		debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 1));

		printf("\r\n-----------------------------------stack trace string table end-----------------------------------\r\n");
	}

	debug_capture_stack_back_trace_link_destroy(&(*allocator)->capture_stack_back_trace_link);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

	free((*allocator));																	            /* Free #1 */

	(*allocator) = NULL;
}

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 * @param lack_of_memory the pointer to the exception handler of lack of heap memory
 *
 * @return NONE
 */

void allocator_control_configuration_exception(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
											  void (*lack_of_memory)(void *))
{
	assert(allocator);

	if (NULL == lack_of_memory) {
		allocator->exception.lack_of_memory = allocator_control_exception_default_lack_of_memory;
	} else {
		allocator->exception.lack_of_memory = lack_of_memory;
	}
}

/**
 * @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
 *  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).
 *
 * @param allocator the allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return return the pointer point to the uninitialized storage which allocated
 */

void *allocator_control_allocate(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
								 ALLOCATOR_SIZE_TYPEDEF count, ALLOCATOR_SIZE_TYPEDEF size)
{
	assert(allocator);

	void
		*block_alloced = calloc(count, size);                           /* Malloc #2 : allocates the storage to block_alloced */

	if (NULL == block_alloced) {
		allocator->exception.lack_of_memory(allocator);

		return NULL;
	}

	allocator->info.size += count;

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_link_mark(allocator->capture_stack_back_trace_link, 1);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

	return (void *)block_alloced;
}

/**
 * @brief This function will deallocates the storage referenced by the pointer block,
 *  which must be a pointer obtained by an earlier call to allocate().
 *
 * @param allocator the allocator
 * @param block the pointer to the blocks
 * @param count the amount of block
 *
 * @return NONE
 */

void allocator_control_deallocate(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
								  void *block, ALLOCATOR_SIZE_TYPEDEF count)
{
	assert(allocator);

	allocator->info.size -= count;

	free(block);																	            /* Free #2 */

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_link_link(allocator->capture_stack_back_trace_link, 1);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)
}

/**
 * @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage.
 *
 * @param allocator the allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return NONE
 */

void allocator_control_memory_alloc(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
									void *block, ALLOCATOR_SIZE_TYPEDEF size)
{
	assert(allocator);

	allocator->info.size++;

	free(block);																	            /* Free #1 */
}