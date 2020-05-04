/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_def.h"

#include "iterator_pte_def.h"

#include "iterator.h"

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

/**
 * @brief This function will check if the at iterator operations can perform.
 *
 * @param
 *
 * @return
 */

bool iterator_control_iterator_operations_at_check(struct iterator_s *iterator,
												   size_t index);

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
 * @brief This function will inquire for the allocator unit of the iterator.
 *
 * @param iterator the pointer to the iterator
 *
 * @return the allocator unit of the iterator
 */

struct allocator_unit_s iterator_control_inquire_allocator_unit(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	return iterator->allocator_unit;
}

/**
 * @brief This function will initialize the iterator.
 *
 * @param
 *
 * @return
 */

errno_t iterator_control_configuration_init(struct iterator_s **iterator,
											enum iterator_type_e iterator_type,
											enum allocator_type_e allocator_type,
											struct iterator_object_unit_s object_unit,
											size_t addon_size)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);
	DEBUG_ASSERT_CONTROL_VARIABLE(iterator_type, > , int, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE(allocator_type, > , int, 0);
	DEBUG_ASSERT_CONTROL_POINTER(object_unit.object_ptr);
	DEBUG_ASSERT_CONTROL_POINTER(object_unit.control_ptr);
	DEBUG_ASSERT_CONTROL_VARIABLE(addon_size, >= , int, 0);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(1, 1);

	struct allocator_unit_s allocator_unit
		= unify_struct_control_construct(iterator,                    /* Construct the iterator */
										 allocator_type,
										 sizeof(struct iterator_s) + addon_size);
	DEBUG_ERROR_CONTROL_JUDGE(1);

	(*iterator)->type_id = iterator_type;
	(*iterator)->info.position = (size_t)-1;
	(*iterator)->info.featured = (addon_size) ? true : false;
	(*iterator)->allocator_unit = allocator_unit;
	(*iterator)->object_unit = object_unit;

	DEBUG_ERROR_CONTROL_EXIT();
}

/**
 * @brief This function will destroy the iterator.
 *
 * @param
 *
 * @return
 */

errno_t iterator_control_configuration_destroy(struct iterator_s **iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);
	DEBUG_ASSERT_CONTROL_POINTER((*iterator));

	DEBUG_ERROR_CONTROL_ERRNO_INIT(1, 1);

	if (unify_struct_control_destruct(iterator,                                          /* Destruct the iterator */
									  (*iterator)->allocator_unit,
									  true)) {
		DEBUG_ERROR_CONTROL_JUMP(1);
	}

	DEBUG_ERROR_CONTROL_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_advance(struct iterator_s *iterator,
												   int step)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	if (iterator->info.featured) {                                                          /* Check if is featured */
		static struct iterator_feature_package_s *feature_package;

		if (!(feature_package = (struct iterator_feature_package_s *)iterator->addon)
			->advance(step)) {
			return NULL;
		}
	}

	return iterator_control_iterator_operations_at(iterator,
												   (size_t)((int)iterator->info.position + step));
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_next(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	return iterator_control_iterator_operations_at(iterator,
												   (size_t)((int)iterator->info.position + 1));
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_prev(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	return iterator_control_iterator_operations_at(iterator,
												   (size_t)((int)iterator->info.position - 1));
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *iterator_control_iterator_operations_at(struct iterator_s *iterator,
											  size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

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

void *iterator_control_range_access_begin(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

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

void *iterator_control_range_access_end(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	return iterator->object_unit.control_ptr->element_access
		.at(iterator->object_unit.object_ptr,
			iterator->object_unit.control_ptr->capacity
			.max_size(iterator->object_unit.object_ptr) - 1);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t iterator_control_range_access_size(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

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

bool iterator_control_range_access_empty(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

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

void *iterator_control_range_access_data(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	return iterator->object_unit.control_ptr->element_access
		.data(iterator->object_unit.object_ptr);
}

/**
 * @brief This function will check if the at iterator operations can perform.
 *
 * @param
 *
 * @return
 */

static inline bool
iterator_control_iterator_operations_at_check(struct iterator_s *iterator,
											  size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	if (iterator->object_unit.control_ptr->capacity
		.empty(iterator->object_unit.object_ptr)) {                                         /* Check if empty() */
		return false;
	}

	if ((int)iterator->object_unit.control_ptr->capacity
		.max_size(iterator->object_unit.object_ptr) - 1 < (int)index                        /* Check if max_size() is less than index */
		|| (int)0 > (int)index) {                                                           /* Check if 0 is greater than index */
		return false;
	}

	return true;
}