/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "access_iterator_def.h"

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

/**
 * @brief This type is the iterator control structure.
 */

struct access_iterator_control_s access_iterator_control = {
	.iterator_operations.advance = access_iterator_control_iterator_operations_advance,
	.iterator_operations.distance = access_iterator_control_iterator_operations_distance,

	.range_access.empty = access_iterator_control_range_access_empty,
	.range_access.size = access_iterator_control_range_access_size,
	.range_access.data = access_iterator_control_range_access_data,
};

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

bool access_iterator_control_inquire_feature_function_package_null_function(void *input);

struct access_iterator_feature_function_package_s
	access_iterator_control_inquire_feature_function_package(struct access_iterator_s *access_iterator);

/**
 * @brief This function will check if the at iterator operations can perform.
 *
 * @param
 *
 * @return
 */

bool access_iterator_control_iterator_operations_at_check(struct access_iterator_s *iterator,
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
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_advance(struct access_iterator_s *access_iterator,
														  int step)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(void *, 2, 1, 2);

	if (access_iterator->feature_unit.enabled.advance) {
		if (!access_iterator_control_inquire_feature_function_package(access_iterator)
			.advance(step)) {
			DEBUG_ERROR_CONTROL_RETURN_VAL = NULL;
			DEBUG_ERROR_CONTROL_JUDGE(1, "_inquire_feature_function_package():fail");
		}
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL
		= access_iterator_control_iterator_operations_at(access_iterator,
														 (size_t)((int)access_iterator->info.position + step));

	DEBUG_ERROR_CONTROL_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_iterator_operations_distance(struct access_iterator_s *access_iterator)
{
	return 0;
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_next(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator_control_iterator_operations_at(access_iterator,
														  (size_t)((int)access_iterator->info.position + 1));
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_prev(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator_control_iterator_operations_at(access_iterator,
														  (size_t)((int)access_iterator->info.position - 1));
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_at(struct access_iterator_s *access_iterator,
													 size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(void *, 1, 1);

	if (!access_iterator_control_iterator_operations_at_check(access_iterator,
															  index)) {
		DEBUG_ERROR_CONTROL_JUDGE(1, "_iterator_operations_at_check(): index is not valid or the object is empty");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = access_iterator->object_unit.control_ptr->element_access
		.at(access_iterator->object_unit.object_ptr,
			access_iterator->info.position = index);

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_begin(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator->object_unit.control_ptr->element_access
		.at(access_iterator->object_unit.object_ptr,
			0);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_end(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator->object_unit.control_ptr->element_access
		.at(access_iterator->object_unit.object_ptr,
			access_iterator->object_unit.control_ptr->capacity
			.max_size(access_iterator->object_unit.object_ptr) - 1);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_range_access_size(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator->object_unit.control_ptr->capacity
		.size(access_iterator->object_unit.object_ptr);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool access_iterator_control_range_access_empty(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator->object_unit.control_ptr->capacity
		.empty(access_iterator->object_unit.object_ptr);
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_range_access_data(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	return access_iterator->object_unit.control_ptr->element_access
		.data(access_iterator->object_unit.object_ptr);
}

/**
 * @brief This function will check if the at access_iterator operations can perform.
 *
 * @param
 *
 * @return
 */

static inline bool
access_iterator_control_iterator_operations_at_check(struct access_iterator_s *access_iterator,
													 size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(bool, 2, 1, 2);

	if (access_iterator->object_unit.control_ptr->capacity
		.empty(access_iterator->object_unit.object_ptr)) {                                  /* Check if empty() */
		DEBUG_ERROR_CONTROL_JUMP(1, "object_unit.control.capacity.empty(): object is empty");
	}

	if ((int)access_iterator->object_unit.control_ptr->capacity
		.max_size(access_iterator->object_unit.object_ptr) - 1 < (int)index                 /* Check if max_size() is less than index */
		|| (int)0 > (int)index) {                                                           /* Check if 0 is greater than index */
		DEBUG_ERROR_CONTROL_JUMP(2, "object_unit.control.capacity.max_size(): index is greater than max size");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = true;
	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

struct access_iterator_feature_function_package_s
	access_iterator_control_inquire_feature_function_package(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct access_iterator_feature_function_package_s, 1, 1);

	struct access_iterator_feature_function_package_s function_package = { NULL };

	bool *enable_ptr = &access_iterator->feature_unit.enabled;
	size_t
		*function_ptr = &access_iterator->feature_unit.function,
		*function_ptr_function_package = &function_package;
	size_t addr_offset = 0;

	do {
		if (true == *enable_ptr) {
			if (NULL == function_ptr) {
				DEBUG_ERROR_CONTROL_JUMP(1, "the feature is Enabled, but the related function pointer is NULL");
				*function_ptr_function_package = (void *(*)(void*))access_iterator_control_inquire_feature_function_package_null_function;
			} else {
				memcpy(function_ptr_function_package, function_ptr, sizeof(bool));
			}
		}

		enable_ptr++;
		function_ptr++;
		function_ptr_function_package++;
	} while (sizeof(struct access_iterator_feature_enabled_package_s) > (addr_offset += sizeof(bool)));

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

bool access_iterator_control_inquire_feature_function_package_null_function(void *input)
{
	return false;
}