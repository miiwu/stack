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
	.configuration.destroy = random_access_iterator_control_configuration_destroy,

	.iterator_operations.advance = random_access_iterator_control_iterator_operations_advance,
	.iterator_operations.next = random_access_iterator_control_iterator_operations_next,
	.iterator_operations.prev = random_access_iterator_control_iterator_operations_prev,
	.iterator_operations.at = random_access_iterator_control_iterator_operations_at,

    .range_access.begin = random_access_iterator_control_range_access_begin,
    .range_access.end = random_access_iterator_control_range_access_end,
    .range_access.empty = random_access_iterator_control_range_access_empty,
    .range_access.size = random_access_iterator_control_range_access_size,
    .range_access.data = random_access_iterator_control_range_access_data,
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

errno_t random_access_iterator_control_configuration_init(iterator_stpp iterator,
														  struct iterator_object_unit_s object_unit)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, errno_t, 1);

	struct iterator_allocator_unit_s
		allocator_unit = { 0 };

	if (NULL == (allocator_unit
				 .control_ptr = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON))) {
		return 2;
	}

	if (allocator_unit.control_ptr->configuration
		.init(&allocator_unit.allocator_ptr, NULL)) {
		return 3;
	}

	if (NULL == ((*iterator)
				 = allocator_unit.control_ptr->allocate(allocator_unit.allocator_ptr,
														1, sizeof(struct iterator_s)))) {
		return 4;
	}

	(*iterator)->allocator_unit = allocator_unit;
	(*iterator)->object_unit = object_unit;

	return 0;
}

/**
 * @brief This function will destroy the iterator.
 *
 * @param
 *
 * @return
 */

errno_t random_access_iterator_control_configuration_destroy(iterator_stpp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, errno_t, 1);
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT((*iterator), errno_t, 1);

	return 0;
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_iterator_operations_advance(iterator_stp iterator,
																 int step)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	return random_access_iterator_control_iterator_operations_at(iterator,
																 (int)iterator->info.position + step);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_iterator_operations_next(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	return random_access_iterator_control_iterator_operations_at(iterator,
																 (int)iterator->info.position + 1);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_iterator_operations_prev(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	return random_access_iterator_control_iterator_operations_at(iterator,
																 (int)iterator->info.position - 1);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_iterator_operations_at(iterator_stp iterator,
															size_t index)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	if (!iterator_control_iterator_operations_at_check(iterator,
													   index)) {
		return NULL;
	}

	return iterator->object_unit.control_ptr->element_access
		.at(iterator->object_unit.object_ptr,
			iterator->info.position = index);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_range_access_begin(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	return iterator->object_unit.control_ptr->element_access
		.at(iterator->object_unit.object_ptr,
			0);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_range_access_end(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	return iterator->object_unit.control_ptr->element_access
		.at(iterator->object_unit.object_ptr,
			iterator->object_unit.control_ptr->capacity
			.max_size(iterator->object_unit.object_ptr));
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t random_access_iterator_control_range_access_size(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, size_t, 0);

	return iterator->object_unit.control_ptr->capacity
		.size(iterator->object_unit.object_ptr);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool random_access_iterator_control_range_access_empty(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, bool, false);

	return iterator->object_unit.control_ptr->capacity
		.empty(iterator->object_unit.object_ptr);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *random_access_iterator_control_range_access_data(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_POINTER_ASSERT(iterator, void *, NULL);

	return iterator->object_unit.control_ptr->element_access
		.data(iterator->object_unit.object_ptr);
}