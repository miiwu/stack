/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "continuous_iterator.h"

#include "access_iterator_pte_def.h"

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

void *access_iterator_control_iterator_operations_at_extension(struct access_iterator_s *access_iterator,
															   size_t index);

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/**
 * @brief This type is the continuous iterator structure.
 */

struct continuous_iterator_s continuous_iterator = {
	.advance.access_unit.function_ptr = (void *)access_iterator_control_element_access_advance,
	.advance.access_unit.extension_ptr = access_iterator_control_iterator_operations_at_extension,

	.distance.function_ptr = (void *)access_iterator_control_element_access_distance,

	.next.function_ptr = (void *)access_iterator_control_element_access_next,
	.next.extension_ptr = access_iterator_control_iterator_operations_at_extension,

	.prev.function_ptr = (void *)access_iterator_control_element_access_prev,
	.next.extension_ptr = access_iterator_control_iterator_operations_at_extension,

	.at.function_ptr = (void *)access_iterator_control_iterator_operations_at,
	.at.extension_ptr = access_iterator_control_iterator_operations_at_extension,

	.front.function_ptr = (void *)access_iterator_control_element_access_front,
	.front.extension_ptr = access_iterator_control_iterator_operations_at_extension,

	.back.function_ptr = (void *)access_iterator_control_element_access_back,
	.front.extension_ptr = access_iterator_control_iterator_operations_at_extension,
};

/*
 *********************************************************************************************************
 *                                            FUNCTIONS
 *********************************************************************************************************
 */

void *access_iterator_control_iterator_operations_at_extension(struct access_iterator_s *access_iterator,
															   size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(void *, 3, 1, 2, 3);

	if (NULL == access_iterator->object_unit_ptr->control_ptr->capacity.element_size) {
		DEBUG_ERROR_CONTROL_JUMP(1, "object_unit_ptr->control_ptr.capacity.element_size(): not found");
	}

	size_t element_size = access_iterator->object_unit_ptr->control_ptr->capacity
		.element_size(access_iterator->object_unit_ptr->object_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(2, "object_unit_ptr->control_ptr.capacity.element_size(): "
							  "fail to get the element size");

	void *data_ptr = access_iterator->object_unit_ptr->control_ptr->element_access
		.data(access_iterator->object_unit_ptr->object_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(3,
							  "object_unit_ptr->control_ptr->element_access.data(): "
							  "fail to get the data address");

	DEBUG_ERROR_CONTROL_RETURN_VAL = (void *)((size_t)data_ptr + (element_size * index));

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}