/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "output_iterator.h"

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
 * @brief This type is the output iterator control structure.
 */

struct output_iterator_control_s output_iterator_control = {
	.configuration.init = output_iterator_control_configuration_init,
	.configuration.destroy = iterator_control_configuration_destroy,

	.iterator_operations.begin = iterator_control_iterator_operation_begin,
	.iterator_operations.end = iterator_control_iterator_operation_end,
	.iterator_operations.dereferance = iterator_control_iterator_operation_dereference,

	.access = iterator_control_access,

	.modify = iterator_control_modify,
};

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

errno_t
output_iterator_control_configuration_init(output_iterator_stpp iterator,
										   struct access_iterator_object_unit_s object_unit)
{
	DBG_ERR(SINGLE_ERROR,
			errno_t,
			1,
			iterator_control_configuration_init(iterator,
												OUTPUT_ITERATOR,
												OUTPUT_ITERATOR_CFG_ALLOCATOR_TYPE,
												object_unit,
												0),
			"iterator_control_configuration_init(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}