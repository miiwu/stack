/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "concept_allocator.h"

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
	.configuration.destroy = allocator_control_configuration_destroy,
	.configuration.exception = allocator_control_configuration_exception,

	.allocate = allocator_control_allocate,
	.deallocate = allocator_control_deallocate,
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

void *concept_allocator_control_function_address_table[] =
{
	(void *)&concept_allocator_control_configuration_init,						/* No.0 : initialize	*/

	(void *)&allocator_control_configuration_destroy,					        /* No.1 : destroy		*/

	(void *)&allocator_control_configuration_exception,					        /* No.2 : exception		*/

	(void *)&allocator_control_allocate,								        /* No.3 : allocate		*/

	(void *)&allocator_control_deallocate								        /* No.4 : deallocate	*/
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

/**
 * @brief This function will allocate the specified memory block.
 *
 * @param allocator the pointer of allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return the address of the memory block
 */

void *concept_allocator_control_memory_manage_allocate(void *memory_manage,
													   allocator_size_t count,
													   allocator_size_t size);

/**
 * @brief This function will allocate the memory block.
 *
 * @param allocator the pointer of allocator
 * @param block the pointer of block
 *
 * @return the error code
 */

errno_t concept_allocator_control_memory_manage_deallocate(void *memory_manage,
														   void *block);

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/**
 * @brief This variable is the concept allocator memory manage package.
 */

struct allocator_memory_manage_init_package_s
	concept_allocator_control_memory_manage_package = {
	.control.allocate = concept_allocator_control_memory_manage_allocate,
	.control.deallocate = concept_allocator_control_memory_manage_deallocate,

	.memory_manage_length = 0,
	.memory_manage_ptr = NULL,
};

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

	return allocator_control_configuration_init(allocator,
												CONCEPT_ALLOCATOR,
												concept_allocator_control_memory_manage_package);
}

/**
 * @brief This function will allocate the specified memory block.
 *
 * @param allocator the pointer of allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return the error code
 */

void *concept_allocator_control_memory_manage_allocate(void *memory_manage,
													   allocator_size_t count,
													   allocator_size_t size)
{
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(count, > , int, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(size, > , int, 0);

	#if CONCEPT_ALLOCATOR_CFG_DEBUG_MODE_EN

	static void *block;

	printf("concept_allocator.memory_manage.allocate.block:%p\r\n",
		   block = calloc(count, size));

	return block;

	#else

	return calloc(count, size);

	#endif // CONCEPT_ALLOCATOR_CFG_DEBUG_MODE_EN
}

/**
 * @brief This function will allocate the memory block.
 *
 * @param allocator the pointer of allocator
 * @param block the pointer of block
 *
 * @return the error code
 */

errno_t concept_allocator_control_memory_manage_deallocate(void *memory_manage,
														   void *block)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(block);

	#if CONCEPT_ALLOCATOR_CFG_DEBUG_MODE_EN

	printf("concept_allocator.memory_manage.deallocate.block:%p\r\n",
		   block);

	#endif // CONCEPT_ALLOCATOR_CFG_DEBUG_MODE_EN

	free(block);

	return 0;
}