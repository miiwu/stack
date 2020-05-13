/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "input_iterator.h"

#include "iterator_pte_def.h"

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
 * @brief This type is the input iterator control structure.
 */

struct input_iterator_control_s input_iterator_control = {
	.configuration.init = input_iterator_control_configuration_init,
	.configuration.destroy = iterator_control_configuration_destroy,

	.iterator_operations.begin = iterator_control_iterator_operation_begin,
	.iterator_operations.end = iterator_control_iterator_operation_end,
	.iterator_operations.dereferance = iterator_control_iterator_operation_dereference,

	.access = iterator_control_access,
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
 * @brief This function will initialize the iterator.
 *
 * @param
 *
 * @return
 */

errno_t input_iterator_control_configuration_init(input_iterator_stpp iterator,
												  struct access_iterator_object_unit_s object_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);
	DEBUG_ASSERT_CONTROL_POINTER(object_unit.object_ptr);
	DEBUG_ASSERT_CONTROL_POINTER(object_unit.control_ptr);

	DBG_ERR(SINGLE_ERROR,
			errno_t,
			1,
			iterator_control_configuration_init(iterator,
												INPUT_ITERATOR,
												INPUT_ITERATOR_CFG_ALLOCATOR_TYPE,
												object_unit,
												0),
			"iterator_control_configuration_init(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}