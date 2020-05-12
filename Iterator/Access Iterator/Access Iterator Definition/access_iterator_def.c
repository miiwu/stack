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
	.iterator_operations.front = access_iterator_control_iterator_operations_front,
	.iterator_operations.back = access_iterator_control_iterator_operations_back,

	.range_access.empty = access_iterator_control_range_access_empty,
	.range_access.size = access_iterator_control_range_access_size,
	.range_access.data = access_iterator_control_range_access_data,
	.range_access.max_size = access_iterator_control_range_access_max_size,
};

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will check if the index of the iterator operations is valid.
 *
 * @param
 *
 * @return
 */

bool
access_iterator_control_iterator_operations_valid_index(struct access_iterator_s *access_iterator,
														size_t index);

/**
 * @brief This function will check if the object unit for the iterator operations is valid.
 *
 * @param
 *
 * @return
 */

bool
access_iterator_control_iterator_operations_valid_object_unit(struct access_iterator_s *access_iterator);

/**
 * @brief This function will check if the object units are same.
 *
 * @param
 *
 * @return
 */

bool
access_iterator_control_iterator_operations_distance_same_object_unit(struct access_iterator_s *lhs,
																	  struct access_iterator_s *rhs);

/**
 * @brief This function will check if the object unit for the range access is valid.
 *
 * @param
 *
 * @return
 */

bool
access_iterator_control_range_access_valid_object_unit(struct access_iterator_s *access_iterator);

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
														  struct access_iterator_advance_unit_s advance_unit,
														  int step)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(void *, 2, 1, 2);

	if (NULL != advance_unit.valid_step_ptr) {
		if (!advance_unit.valid_step_ptr(step)) {
			DEBUG_ERROR_CONTROL_RETURN_VAL = NULL;
			DEBUG_ERROR_CONTROL_JUDGE(1, "valid_step(): invalid step");
		}
	}

	size_t index = ((int)access_iterator->info.position + step);

	if (0 < index) {
		index = 0;
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL
		= access_iterator_control_iterator_operations_at(access_iterator,
														 advance_unit.access_unit,
														 index);

	DEBUG_ERROR_CONTROL_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

int access_iterator_control_iterator_operations_distance(struct access_iterator_s *lhs,
														 struct access_iterator_s *rhs)
{
	DEBUG_ASSERT_CONTROL_POINTER(lhs);
	DEBUG_ASSERT_CONTROL_POINTER(rhs);

	DBG_ERR(SINGLE_ERROR,
			int,
			1,
			access_iterator_control_iterator_operations_distance_same_object_unit(lhs, rhs),
			"_same_object_unit(): fail");

	DEBUG_ERROR_CONTROL_RETURN_VAL = lhs->info.position - rhs->info.position;
	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_next(struct access_iterator_s *access_iterator,
													   struct access_iterator_access_unit_s access_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	size_t index = ((int)access_iterator->info.position + 1);

	DBG_ERR(SINGLE_ERROR,
			void *,
			1,
			DEBUG_ERROR_CONTROL_RETURN_VAL
			= access_iterator_control_iterator_operations_at(access_iterator,
															 access_unit,
															 index),
			"_iterator_operations_at(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_prev(struct access_iterator_s *access_iterator,
													   struct access_iterator_access_unit_s access_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	size_t index = ((int)access_iterator->info.position - 1);

	DBG_ERR(SINGLE_ERROR,
			void *,
			1,
			DEBUG_ERROR_CONTROL_RETURN_VAL
			= access_iterator_control_iterator_operations_at(access_iterator,
															 access_unit,
															 index),
			"_iterator_operations_at(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_at(struct access_iterator_s *access_iterator,
													 struct access_iterator_access_unit_s access_unit,
													 size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(void *, 3, 1, 2, 3);

	if (!access_iterator_control_iterator_operations_valid_index(access_iterator,
																 index)) {
		DEBUG_ERROR_CONTROL_JUDGE(1, "_valid_index(): index is not valid or the object is empty");
	}

	if (!access_iterator_control_iterator_operations_valid_object_unit(access_iterator)) {
		DEBUG_ERROR_CONTROL_JUDGE(2, "_valid_object_unit(): object unit is not valid");
	}

	access_iterator->info.position = index;

	if (NULL != access_unit.extension_ptr) {
		DEBUG_ERROR_CONTROL_RETURN_VAL = access_unit
			.extension_ptr(access_iterator,
						   access_iterator->info.position);
	} else {
		DEBUG_ERROR_CONTROL_RETURN_VAL = access_iterator->object_unit.control_ptr->element_access
			.at(access_iterator->object_unit.object_ptr,
				access_iterator->info.position);
	}
	DEBUG_ERROR_CONTROL_JUDGE(3, "access the element address fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_front(struct access_iterator_s *access_iterator,
														struct access_iterator_access_unit_s access_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DBG_ERR(SINGLE_ERROR,
			void *,
			1,
			DEBUG_ERROR_CONTROL_RETURN_VAL
			= access_iterator_control_iterator_operations_at(access_iterator,
															 access_unit,
															 0),
			"_iterator_operations_at(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

void *access_iterator_control_iterator_operations_back(struct access_iterator_s *access_iterator,
													   struct access_iterator_access_unit_s access_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	size_t index = access_iterator->object_unit.control_ptr->capacity
		.max_size(access_iterator->object_unit.object_ptr) - 1;

	DBG_ERR(SINGLE_ERROR,
			void *,
			1,
			DEBUG_ERROR_CONTROL_RETURN_VAL
			= access_iterator_control_iterator_operations_at(access_iterator,
															 access_unit,
															 index),
			"_iterator_operations_at(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
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

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(size_t, 2, 1, 2);

	if (!access_iterator_control_range_access_valid_object_unit(access_iterator)) {
		DEBUG_ERROR_CONTROL_JUMP(1, "_valid_object_unit(): invalid object unit");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = access_iterator->object_unit.control_ptr->capacity
		.size(access_iterator->object_unit.object_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(2, "object_unit.control_ptr->capacity.size(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

size_t access_iterator_control_range_access_max_size(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(size_t, 2, 1, 2);

	if (!access_iterator_control_range_access_valid_object_unit(access_iterator)) {
		DEBUG_ERROR_CONTROL_JUMP(1, "_valid_object_unit(): invalid object unit");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = access_iterator->object_unit.control_ptr->capacity
		.max_size(access_iterator->object_unit.object_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(2, "object_unit.control_ptr->capacity.max_size(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
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

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(bool, 2, 1, 2);

	if (!access_iterator_control_range_access_valid_object_unit(access_iterator)) {
		DEBUG_ERROR_CONTROL_JUMP(1, "_valid_object_unit(): invalid object unit");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = access_iterator->object_unit.control_ptr->capacity
		.empty(access_iterator->object_unit.object_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(2, "object_unit.control_ptr->capacity.empty(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
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

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(void *, 2, 1, 2);

	if (!access_iterator_control_range_access_valid_object_unit(access_iterator)) {
		DEBUG_ERROR_CONTROL_JUMP(1, "_valid_object_unit(): invalid object unit");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = access_iterator->object_unit.control_ptr->element_access
		.data(access_iterator->object_unit.object_ptr);
	DEBUG_ERROR_CONTROL_JUDGE(2, "object_unit.control_ptr->element_access.data(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will check if the index of the iterator operations is valid.
 *
 * @param
 *
 * @return
 */

static inline bool
access_iterator_control_iterator_operations_valid_index(struct access_iterator_s *access_iterator,
														size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(bool, 2, 1, 2);

	if (access_iterator->object_unit.control_ptr->capacity
		.empty(access_iterator->object_unit.object_ptr)) {                                  /* Check if empty() */
		DEBUG_ERROR_CONTROL_JUMP(1, "object_unit.control_ptr.capacity.empty(): object is empty");
	}

	if ((int)access_iterator->object_unit.control_ptr->capacity
		.max_size(access_iterator->object_unit.object_ptr) - 1 < (int)index                 /* Check if max_size() is less than index */
		|| (int)0 > (int)index) {                                                           /* Check if 0 is greater than index */
		DEBUG_ERROR_CONTROL_JUMP(2, "object_unit.control_ptr.capacity.max_size(): index is greater than max size");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = true;
	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will check if the object unit for the iterator operations is valid.
 *
 * @param
 *
 * @return
 */

static inline bool
access_iterator_control_iterator_operations_valid_object_unit(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(bool, 2, 1, 2);

	if (NULL == access_iterator->object_unit.control_ptr->element_access.at) {
		DEBUG_ERROR_CONTROL_JUMP(1, "object_unit.control_ptr.element_access.at(): not found");
	}

	if (NULL == access_iterator->object_unit.control_ptr->element_access.data) {
		DEBUG_ERROR_CONTROL_JUMP(2, "object_unit.control_ptr.element_access.data(): not found");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = true;
	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will check if the object units are same.
 *
 * @param
 *
 * @return
 */

static inline bool
access_iterator_control_iterator_operations_distance_same_object_unit(struct access_iterator_s *lhs,
																	  struct access_iterator_s *rhs)
{
	DEBUG_ASSERT_CONTROL_POINTER(lhs);
	DEBUG_ASSERT_CONTROL_POINTER(rhs);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(bool, 1, 1);

	void
		**lhs_ptr = (void *)&lhs->object_unit,
		**rhs_ptr = (void *)&rhs->object_unit;

	size_t
		offset = 0,
		object_unit_size = sizeof(struct access_iterator_object_control_s) + sizeof(void *);

	do {
		if (*lhs_ptr != *rhs_ptr) {
			DEBUG_ERROR_CONTROL_JUMP(1, "not the same object unit");
		}

		lhs_ptr++;
		rhs_ptr++;
	} while (object_unit_size > (offset += sizeof(void *)));

	DEBUG_ERROR_CONTROL_RETURN_VAL = true;
	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will check if the object unit for the range access is valid.
 *
 * @param
 *
 * @return
 */

static inline bool
access_iterator_control_range_access_valid_object_unit(struct access_iterator_s *access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(bool, 4, 1, 2, 3, 4);

	if (NULL == access_iterator->object_unit.control_ptr->capacity.size) {
		DEBUG_ERROR_CONTROL_JUMP(1, "object_unit.control_ptr.capacity.size(): not found");
	}

	if (NULL == access_iterator->object_unit.control_ptr->capacity.empty) {
		DEBUG_ERROR_CONTROL_JUMP(2, "object_unit.control_ptr.capacity.empty(): not found");
	}

	if (NULL == access_iterator->object_unit.control_ptr->capacity.max_size) {
		DEBUG_ERROR_CONTROL_JUMP(3, "object_unit.control_ptr.capacity.max_size(): not found");
	}

	if (NULL == access_iterator->object_unit.control_ptr->element_access.at) {
		DEBUG_ERROR_CONTROL_JUMP(4, "object_unit.control_ptr.element_access.at(): not found");
	}

	DEBUG_ERROR_CONTROL_RETURN_VAL = true;
	DEBUG_ERROR_CONTROL_LOG_EXIT();
}