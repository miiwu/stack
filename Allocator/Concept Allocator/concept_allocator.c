/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "concept_allocator.h"

#include "allocator_pte_def.h"

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

/**
 * @brief This const variable is the concept allocator control structure.
 */

const struct concept_allocator_control_s
concept_allocator_control = {
	.configuration.init = concept_allocator_control_configuration_init,
	.configuration.destroy = concept_allocator_control_configuration_destroy,
	.configuration.exception = allocator_control_configuration_exception,

	.allocate = concept_allocator_control_allocate,
	.deallocate = concept_allocator_control_deallocate,
};

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/**
 * @brief This table variable is the concept allocator function address table.
 */

void *concept_allocator_function_address_table[] =
{
	(void *)&concept_allocator_control_configuration_init,						/* No.0 : initialize	*/

	(void *)&concept_allocator_control_configuration_destroy,					/* No.1 : destroy		*/

	(void *)&allocator_control_configuration_exception,					        /* No.2 : exception		*/

	(void *)&concept_allocator_control_allocate,								/* No.3 : allocate		*/

	(void *)&concept_allocator_control_deallocate								/* No.4 : deallocate	*/
};

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

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
 * @param allocator the pointer of allocator address
 *
 * @return the error code
 */

errno_t concept_allocator_control_configuration_init(concept_allocator_stpp allocator)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);

	if (NULL == ((*allocator) = calloc(1, sizeof(struct allocator_s)))) {					/* Allocate the allocator structure */
		return -1;
	}

	(*allocator)->allocator_type_id = CONCEPT_ALLOCATOR;                                    /* Assign the allocator structure */
	(*allocator)->info.match = 0u;

	static struct allocator_exception_s exception = { NULL };

	allocator_control_configuration_exception((*allocator),
											  exception);

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_link_init(&allocator_alloced->capture_stack_back_trace_link, 256);

	#endif

	return 0;
}

/**
 * @brief This function will destroy the allocator struct.
 *
 * @param allocator the pointer of allocator address
 *
 * @return the error code
 */

errno_t concept_allocator_control_configuration_destroy(concept_allocator_stpp allocator)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(*allocator);

	return allocator_control_configuration_destroy(allocator);
}

/**
 * @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
 *			malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).
 *
 * @param allocator the pointer of allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return return the pointer point to the uninitialized storage which allocated
 */

void *concept_allocator_control_allocate(concept_allocator_stp allocator,
										 size_t count, size_t size)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(count, > , size_t, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(size, > , size_t, 0);

	static void *block_alloced;

	if (NULL == (block_alloced = calloc(count, size))) {                                    /* Allocate the block needed */
		allocator->exception.lack_of_memory(allocator);                                     /* Enter exception */

		return NULL;
	}

	allocator->info.match += 1;

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_link_mark(allocator->capture_stack_back_trace_link, 1);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

	return block_alloced;
}

/**
 * @brief This function will deallocates the storage referenced by the pointer block,
 *			which must be a pointer obtained by an earlier call to allocate().
 *
 * @param allocator the pointer of allocator
 * @param block the pointer of block
 *
 * @return NONE
 */

errno_t concept_allocator_control_deallocate(concept_allocator_stp allocator,
											 void *block)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(block);

	allocator->info.match -= 1;

	free(block);																	        /* Deallocate the block */

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	debug_capture_stack_back_trace_link_link(allocator->capture_stack_back_trace_link, 1);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

	return 0;
}