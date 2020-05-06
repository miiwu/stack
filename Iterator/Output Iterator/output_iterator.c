/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "output_iterator.h"

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

	//.iterator_operations.advance = iterator_control_iterator_operations_advance,

	//.range_access.empty = iterator_control_range_access_empty,
	//.range_access.size = iterator_control_range_access_size,
	//.range_access.data = iterator_control_range_access_data,
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

errno_t output_iterator_control_configuration_init(output_iterator_stpp output_iterator,
												   enum iterator_type_e iterator_type,
												   struct iterator_object_unit_s object_unit)
{
	return iterator_adaptor_control_configuration_init(output_iterator,
													   OUTPUT_ITERATOR,
													   iterator_type,
													   OUTPUT_ITERATOR_CFG_ALLOCATOR_TYPE,
													   object_unit);
}

void output_iterator_control_modify()
{
}