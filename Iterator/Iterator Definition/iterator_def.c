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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
											enum iterator_type_e type,
											struct iterator_object_unit_s object_unit,
											size_t addon_size)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(type, > , int, 0);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(object_unit.object_ptr);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(object_unit.control_ptr);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(addon_size, >= , int, 0);

	struct allocator_unit_s
		allocator_unit = { 0 };

	if (NULL == (allocator_unit
				 .control_ptr = allocator_control_get_function_address_table(type))) {
		return 4;
	}

	if (allocator_unit.control_ptr->configuration
		.init(&allocator_unit.allocator_ptr)) {
		return 5;
	}

	if (NULL == ((*iterator)
				 = allocator_unit.control_ptr->allocate(allocator_unit.allocator_ptr,
														1,
														sizeof(struct iterator_s) + addon_size))) {
		return 6;
	}

	(*iterator)->type_id = type;
	(*iterator)->info.position = (size_t)-1;
	(*iterator)->info.featured = (addon_size) ? true : false;
	(*iterator)->allocator_unit = allocator_unit;
	(*iterator)->object_unit = object_unit;

	return 0;
}

/**
 * @brief This function will allocate the iterator.
 *
 * @param
 *
 * @return
 */

struct iterator_allocate_return_package_s
	iterator_control_configuration_allocate(void **iterator,
											struct iterator_allocate_package_s package)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(package.type, > , int, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(package.mem_size, >= , int, 0);

    DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct iterator_allocate_return_package_s, 3, 1, 2, 3);

	if (NULL == (DEBUG_ERROR_CONTROL_RETURN_PTR->allocator_unit
				 .control_ptr = allocator_control_get_function_address_table(CONCEPT_ALLOCATOR))) {
		DEBUG_ERROR_CONTROL_JUMP(1);
	}

	if (DEBUG_ERROR_CONTROL_RETURN_PTR->allocator_unit.control_ptr->configuration
		.init(&DEBUG_ERROR_CONTROL_RETURN_PTR->allocator_unit.allocator_ptr)) {
		DEBUG_ERROR_CONTROL_JUMP(2);
	}

	if (NULL == ((*iterator)
				 = DEBUG_ERROR_CONTROL_RETURN_PTR->allocator_unit.control_ptr
				 ->allocate(DEBUG_ERROR_CONTROL_RETURN_PTR->allocator_unit.allocator_ptr,
							1, package.mem_size))) {
		DEBUG_ERROR_CONTROL_JUMP(3);
	}

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF((*iterator));

	static struct allocator_unit_s allocator_unit = { 0 };

	allocator_unit = (*iterator)->allocator_unit;                                           /* Store allocator unit structure */

	if (allocator_unit.control_ptr
		->deallocate(allocator_unit.allocator_ptr,
					 (*iterator))) {					                                    /* Deallocate the iterator */
		return 2;
	}

	if (allocator_unit.control_ptr
		->configuration.destroy(&allocator_unit.allocator_ptr)) {						    /* Destroy the allocator */
		return 3;
	}

	*iterator = NULL;

	return 0;
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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(iterator);

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