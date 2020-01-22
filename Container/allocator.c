/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "allocator.h"

#include "debug_capture_stack_back_trace.h"

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

struct allocator_t {
	struct {
		/* @brief This variables will record the size of allocator allocated.						    */
		ALLOCATOR_SIZE_TYPEDEF size;
	}info;

	/* @brief This variables will point to the address of allocator memory pool.					    */
	void *memory_pool;

	struct {
		/* @brief This variables will point to the exception handler of lack of memory.			        */
		void (*lack_of_memory)(void);
	}exception;

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	/* @brief This variables will used to record the stack back trace.			                        */
	STACK_BACK_TRACE_TYPEDEF_PTR capture_stack_back_trace;

	/* @brief This variables will used to record the link status.										*/
	STACK_BACK_TRACE_LINK_TYPEDEF_PTR capture_stack_back_trace_link;

	#endif
};

struct memory_control_t {
	/* @brief This variables will record which memory block is available by check bit.					*/
	int available[ALLOCATOR_CFG_MEMORY_POOL_SIZE / sizeof(int) * 8];

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

#if (ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the allocator functions conveniently.
 */

struct allocator_control_t allocator_ctrl = {
	allocator_control_configration_init,

	allocator_control_configration_destroy,

	allocator_control_configration_expection,

	allocator_control_allocate,

	allocator_control_deallocate,
};

#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

/**
 * @brief This struct will control all the allocator debug functions conveniently.
 */

struct allocator_debug_control_t allocator_dbg_ctrl = {
	allocator_control_memory_detect_memory_free_status
};

DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE g_allocator_dbg_link_index = 0;

#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

#endif // (ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

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

void allocator_control_configration_init(ALLOCATOR_TYPEDEF_PPTR allocator,
										 void (*lack_of_memory)(void))
{
	assert(allocator);

	struct allocator_t
		*allocator_alloced = (struct allocator_t *)calloc(1, sizeof(struct allocator_t));			/* Malloc #1 */

	if (NULL == allocator_alloced) {
		return;
	}

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_init(&allocator_alloced->capture_stack_back_trace, 100);
	debug_capture_stack_back_trace_link_init(&allocator_alloced->capture_stack_back_trace_link, 256);

	#endif

	allocator_alloced->info.size = 0u;			                                                    /* Assign the allocator struct */
	allocator_alloced->exception.lack_of_memory = lack_of_memory;

	(*allocator) = allocator_alloced;
}

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return NONE
 */

void allocator_control_configration_destroy(ALLOCATOR_TYPEDEF_PPTR allocator)
{
	assert(allocator);

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	printf("allocator.destroy:memory free status : %d \r\n", (*allocator)->info.size);

	if (0 < (*allocator)->info.size) {
		//debug_capture_stack_back_trace_to_symbol((*allocator)->capture_stack_back_trace);
	}

	debug_capture_stack_back_trace_destroy(&(*allocator)->capture_stack_back_trace);
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

void allocator_control_configration_expection(ALLOCATOR_TYPEDEF_PTR allocator,
											  void (*lack_of_memory)(void))
{
	assert(allocator);

	// TODO Statement ...																	/* TODO	*/
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

void *allocator_control_allocate(ALLOCATOR_TYPEDEF_PTR allocator,
								 ALLOCATOR_SIZE_TYPEDEF count, ALLOCATOR_SIZE_TYPEDEF size)
{
	assert(allocator);

	void
		*block_alloced = calloc(count, size);                           /* Malloc #2 : allocates the storage to block_alloced */

	if (NULL == block_alloced) {
		allocator->exception.lack_of_memory();

		return NULL;
	}

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	g_allocator_dbg_link_index = debug_capture_stack_back_trace_link_mark(allocator->capture_stack_back_trace_link,
																		  allocator->capture_stack_back_trace, 1);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

	allocator->info.size += count;

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

void allocator_control_deallocate(ALLOCATOR_TYPEDEF_PTR allocator,
								  void *block, ALLOCATOR_SIZE_TYPEDEF count)
{
	assert(allocator);

	allocator->info.size -= count;

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	back_trace_hash_t hash = debug_capture_stack_back_trace_link_link(allocator->capture_stack_back_trace_link, g_allocator_dbg_link_index, 1);

	if (0 != hash) {
		debug_capture_stack_back_trace_reduce_count(allocator->capture_stack_back_trace, hash);
	} else {
		while (true) {
		}
	}

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

	free(block);																	            /* Free #1 */
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

void allocator_control_memory_alloc(ALLOCATOR_TYPEDEF_PTR allocator,
									void *block, ALLOCATOR_SIZE_TYPEDEF size)
{
	assert(allocator);

	allocator->info.size++;

	free(block);																	            /* Free #1 */
}

/**
 * @brief This function will detect memory free status of the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return the memory free status of the allocator struct
 */

ALLOCATOR_SIZE_TYPEDEF allocator_control_memory_detect_memory_free_status(ALLOCATOR_TYPEDEF_PTR allocator)
{
	assert(allocator);

	return allocator->info.size;
}