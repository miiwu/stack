/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "output_iterator.h"

#include "iterator_pte_def.h"
#include "iterator_adaptor_pte_def.h"

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
	.configuration.readapt = iterator_adaptor_control_configuration_readapt,
	.configuration.adapt_exist = iterator_adaptor_control_configuration_adapt_exist,
	.configuration.destroy = iterator_adaptor_control_configuration_destroy,

	.iterator_operations.advance = iterator_adaptor_control_iterator_operations_advance,

	.range_access.empty = iterator_adaptor_control_range_access_empty,
	.range_access.size = iterator_adaptor_control_range_access_size,
	.range_access.data = iterator_adaptor_control_range_access_data,

	.modify = output_iterator_control_modify,
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
output_iterator_control_configuration_init(output_iterator_stpp output_iterator,
										   enum iterator_type_e iterator_type,
										   struct iterator_object_unit_s object_unit)
{
	DBG_ERR(SINGLE_ERROR,
			errno_t,
			1,
			iterator_adaptor_control_configuration_init(output_iterator,
														OUTPUT_ITERATOR,
														iterator_type,
														OUTPUT_ITERATOR_CFG_ALLOCATOR_TYPE,
														object_unit),
			"iterator_adaptor_control_configuration_init(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

void *output_iterator_control_modify(output_iterator_stp output_iterator,
									 size_t index,
									 void *source)
{
	DBG_ERR(SINGLE_ERROR,
			void *,
			1,
			DEBUG_ERROR_CONTROL_RETURN_VAL
			= iterator_control_modifiers_modify(output_iterator->iterator_unit.iterator_ptr,
												index,
												source),
			"iterator_control_modifiers_modify(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}