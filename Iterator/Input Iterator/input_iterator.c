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

	.iterator_operations.advance = iterator_control_iterator_operations_advance,
	.iterator_operations.next = iterator_control_iterator_operations_next,

	.range_access.empty = iterator_control_range_access_empty,
	.range_access.size = iterator_control_range_access_size,
	.range_access.data = iterator_control_range_access_data,
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

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool input_iterator_control_feature_package_advance(int step);

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
												  struct iterator_object_unit_s object_unit)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, errno_t, 1);
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(object_unit.object_ptr, errno_t, 2);
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(object_unit.control_ptr, errno_t, 3);

	if (iterator_control_configuration_init(iterator,
											object_unit,
											sizeof(struct iterator_feature_package_s))) {
		return 4;
	}

	static struct iterator_feature_package_s *feature_package;

    feature_package = (struct iterator_feature_package_s *)(*iterator)->addon;

	feature_package->advance = input_iterator_control_feature_package_advance;

	return 0;
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

static inline bool input_iterator_control_feature_package_advance(int step)
{
	if (0 > step) {
		return false;
	}

	return true;
}