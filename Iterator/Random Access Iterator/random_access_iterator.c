/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "random_access_iterator.h"

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
 * @brief This type is the iterator control structure.
 */

struct random_access_iterator_control_s random_access_iterator_control = {
	.configuration.init = random_access_iterator_control_configuration_init,
	.configuration.destroy = iterator_control_configuration_destroy,

	.iterator_operations.advance = iterator_control_iterator_operations_advance,
	.iterator_operations.next = iterator_control_iterator_operations_next,
	.iterator_operations.prev = iterator_control_iterator_operations_prev,
	.iterator_operations.at = iterator_control_iterator_operations_at,
	.iterator_operations.modify = iterator_control_iterator_operations_modify,

	.range_access.begin = iterator_control_range_access_begin,
	.range_access.end = iterator_control_range_access_end,
	.range_access.empty = iterator_control_range_access_empty,
	.range_access.size = iterator_control_range_access_size,
	.range_access.data = iterator_control_range_access_data,
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

/**
 * @brief This function will initialize the iterator.
 *
 * @param
 *
 * @return
 */

errno_t random_access_iterator_control_configuration_init(random_access_iterator_stpp iterator,
														  struct iterator_object_unit_s object_unit)
{
	ITERATOR_CONTROL_ASSERT_POINTER(iterator);
	ITERATOR_CONTROL_ASSERT_POINTER(object_unit.object_ptr);
	ITERATOR_CONTROL_ASSERT_POINTER(object_unit.control_ptr);

	return iterator_control_configuration_init(iterator,
											   RANDOM_ACCESS_ITORATER,
											   object_unit,
											   0);
}