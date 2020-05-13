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
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

static struct access_iterator_s
*iterator_control_iterator_operation_referance(struct iterator_s *iterator,
											   size_t position);

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

void *iterator_control_virtual_access_iterator_box(struct access_iterator_s *access_iterator,
												   void *source,
												   struct access_iterator_access_unit_s access_unit,
												   void *arg[8]);

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

errno_t iterator_control_configuration_init(struct iterator_s **iterator,
											enum iterator_type_e iterator_type,
											enum allocator_type_e allocator_type,
											struct access_iterator_object_unit_s object_unit,
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
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

struct access_iterator_s
	*iterator_control_iterator_operation_begin(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct access_iterator_s *, 1, 1);

	DEBUG_ERROR_CONTROL_RETURN_VAL
		= iterator_control_iterator_operation_referance(iterator,
														0);
	DEBUG_ERROR_CONTROL_JUDGE(1, "_iterator_operation_referance(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

struct access_iterator_s
	*iterator_control_iterator_operation_end(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct access_iterator_s *, 1, 1);

	size_t position = iterator->object_unit.control_ptr->capacity
		.max_size(iterator->object_unit.object_ptr);

	DEBUG_ERROR_CONTROL_RETURN_VAL
		= iterator_control_iterator_operation_referance(iterator,
														position);
	DEBUG_ERROR_CONTROL_JUDGE(1, "_iterator_operation_referance(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

errno_t
iterator_control_iterator_operation_dereference(struct iterator_s *iterator,
												struct access_iterator_s **access_iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);
	DEBUG_ASSERT_CONTROL_POINTER(*access_iterator);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(1, 1);

	iterator->allocator_unit.control_ptr
		->deallocate(iterator->allocator_unit.allocator_ptr, *access_iterator);
	DEBUG_ERROR_CONTROL_JUDGE(1, "iterator.allocator_unit.control_ptr.deallocate(): fail");

	access_iterator = NULL;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

void *iterator_control_access(struct access_iterator_s *access_iterator,
							  struct access_iterator_access_unit_s access_unit,
							  ...)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	va_list va_ptr;
	void *arg_list[8] = { NULL };

	va_start(va_ptr, access_unit);

	size_t i = 0;
	do {
		arg_list[i] = va_arg(va_ptr, void *);
	} while (8 > ++i);

	va_end(va_ptr);

	return iterator_control_virtual_access_iterator_box(access_iterator,
														NULL,
														access_unit,
														arg_list);
}

/**
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

void *iterator_control_modify(struct access_iterator_s *access_iterator,
							  void *source,
							  struct access_iterator_access_unit_s access_unit,
							  ...)
{
	DEBUG_ASSERT_CONTROL_POINTER(access_iterator);

	va_list va_ptr;
	void *arg_list[8] = { NULL };

	va_start(va_ptr, access_unit);

	size_t i = 0;
	do {
		arg_list[i] = va_arg(va_ptr, void *);
	} while (8 > ++i);

	va_end(va_ptr);

	return iterator_control_virtual_access_iterator_box(access_iterator,
														source,
														access_unit,
														arg_list);
}

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
 * @brief This function will .
 *
 * @param
 *
 * @return
 */

static struct access_iterator_s
*iterator_control_iterator_operation_referance(struct iterator_s *iterator,
											   size_t position)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);
	DEBUG_ASSERT_CONTROL_VARIABLE(position, >= , int, 0);

	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct access_iterator_s *, 1, 1);

	DEBUG_ERROR_CONTROL_RETURN_VAL = iterator->allocator_unit.control_ptr
		->allocate(iterator->allocator_unit.allocator_ptr,
				   1,
				   sizeof(struct access_iterator_s));
	DEBUG_ERROR_CONTROL_JUDGE(1, "iterator.allocator_unit.control_ptr.allocate(): fail");

	DEBUG_ERROR_CONTROL_RETURN_VAL->privite.position = position;
	DEBUG_ERROR_CONTROL_RETURN_VAL->object_unit_ptr = &iterator->object_unit;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

void
*iterator_control_virtual_access_iterator_box(struct access_iterator_s *access_iterator,
											  void *source,
											  struct access_iterator_access_unit_s access_unit,
											  void *arg[8])
{
	void *address = access_unit.function_ptr(access_iterator,
											 access_unit,
											 arg[0], arg[1], arg[2], arg[3],
											 arg[4], arg[5], arg[6], arg[7]);

	if (NULL != source) {
		size_t element_size
			= access_iterator_control.range_access.element_size(access_iterator);

		memcpy(address, source, element_size);
	}

	return address;
}