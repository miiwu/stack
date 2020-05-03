/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "unify_structure.h"

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

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will construct the structure and initialize the allocator unit.
 *
 * @param structure the pointer to structure
 * @param package the package of the unify structure allocate
 *
 * @return the construct package
 */

struct unify_structure_construct_package_s
	unify_structure_control_construct(void **structure,
									  enum allocator_type_e allocator_type,
									  size_t structure_mem_size)
{
	DEBUG_ASSERT_CONTROL_POINTER(structure);
	DEBUG_ASSERT_CONTROL_VARIABLE(allocator_type, > , int, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE(structure_mem_size, > , int, 0);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct unify_structure_construct_package_s, 3, 1, 2, 3);
	DEBUG_ERROR_CONTROL_STRING_HEADER("unify_structure.construct.error.");

	if (NULL == (DEBUG_ERROR_CONTROL_RETURN_VAL.allocator_unit.control_ptr
				 = allocator_control_get_function_address_table(allocator_type))) {
		DEBUG_ERROR_CONTROL_JUMP(1, "allocator_..._get_function_address_table():fail");
    }

	DEBUG_ERROR_CONTROL_RETURN_VAL.allocator_unit.control_ptr->configuration
		.init(&DEBUG_ERROR_CONTROL_RETURN_VAL.allocator_unit.allocator_ptr);                /* Initialize the structure pointer */
	DEBUG_ERROR_CONTROL_JUDGE(2, "allocator.configuration.init():fail");

	*structure = DEBUG_ERROR_CONTROL_RETURN_VAL.allocator_unit.control_ptr
		->allocate(DEBUG_ERROR_CONTROL_RETURN_VAL.allocator_unit.allocator_ptr,             /* Allocate the structure pointer */
				   1, structure_mem_size);
	DEBUG_ERROR_CONTROL_JUDGE(3, "allocator.allocator():fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will destruct the structure and destroy the allocator unit.
 *
 * @param structure the pointer to structure
 * @param allocator_unit the package of the unify structure allocator unit
 *
 * @return the error code
 */

errno_t
unify_structure_control_destruct(void **structure,
								 struct allocator_unit_s allocator_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(structure);
	DEBUG_ASSERT_CONTROL_POINTER(allocator_unit.allocator_ptr);
	DEBUG_ASSERT_CONTROL_POINTER(allocator_unit.control_ptr);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3, 1, 2, 3);
	DEBUG_ERROR_CONTROL_STRING_HEADER("unify_structure.construct.error");

	allocator_unit.control_ptr
		->deallocate(allocator_unit.allocator_ptr, *structure);
	DEBUG_ERROR_CONTROL_JUDGE(1, "allocator.deallocate():fail");

	allocator_unit.control_ptr->configuration
		.destroy(&allocator_unit.allocator_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(1, "allocator.destroy():fail");

	allocator_unit.allocator_ptr = NULL;
	allocator_unit.control_ptr = NULL;
	*structure = NULL;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}