/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "iterator.h"
#include "iterator_pte_def.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/* Define			iterator control common prepare block.												*/
#define ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(pointer,error_type,error_code)							\
	do {																								\
		assert(NULL != (pointer));									/* Assert first,DEBUG will work */	\
		if (NULL == (pointer)) {									/* If second,RELEASE will work	*/	\
			return (error_type)(error_code);															\
		}																								\
	} while (false)

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

struct iterator_control_s iterator_control = {
	.configuration.init = iterator_control_configuration_init,
	.configuration.destroy = iterator_control_configuration_destroy,

	.iterator_operations.next = iterator_control_iterator_operations_next,
	.iterator_operations.prev = iterator_control_iterator_operations_prev,
};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
* @brief This function will check if the next iterator operations can perform.
*
* @param
*
* @return
*/

static inline bool
iterator_control_iterator_operations_next_check(iterator_stp iterator);

/**
* @brief This function will check if the previous iterator operations can perform.
*
* @param
*
* @return
*/

static inline bool
iterator_control_iterator_operations_prev_check(iterator_stp iterator);

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

errno_t iterator_control_configuration_init(iterator_stpp iterator,
											struct iterator_object_unit_s object_unit)
{
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(iterator, errno_t, 1);

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

errno_t iterator_control_configuration_destroy(iterator_stpp iterator)
{
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(iterator, errno_t, 1);
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK((*iterator), errno_t, 1);

	return 0;
}

/**
* @brief This function will.
*
* @param
*
* @return
*/

void *iterator_control_iterator_operations_next(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(iterator, void *, 1);

	if (!iterator_control_iterator_operations_next_check(iterator)) {
		return NULL;
	}

	return iterator->object_unit.control_ptr->element_access
		.at(iterator->object_unit.object_ptr
			,iterator->info.position++);
}

/**
* @brief This function will.
*
* @param
*
* @return
*/

void *iterator_control_iterator_operations_prev(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(iterator, void *, 1);

	if (!iterator_control_iterator_operations_prev_check(iterator)) {
		return NULL;
	}

	return iterator->object_unit.control_ptr->element_access
		.at(iterator->object_unit.object_ptr
			,iterator->info.position--);
}

/**
* @brief This function will check if the next iterator operations can perform.
*
* @param
*
* @return
*/

static inline bool
iterator_control_iterator_operations_next_check(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(iterator, bool, false);

	if (iterator->info.position + 1 > iterator->object_unit.control_ptr->capacity
		.max_size(iterator->object_unit.object_ptr)) {
		return false;
	}

	return true;
}

/**
* @brief This function will check if the previous iterator operations can perform.
*
* @param
*
* @return
*/

static inline bool
iterator_control_iterator_operations_prev_check(iterator_stp iterator)
{
	ITERATOR_CONTROL_COMMON_PREPARE_BLOCK(iterator, bool, false);

	if ((int)0 > (int)iterator->info.position - 1) {
		return false;
	}

	return true;
}