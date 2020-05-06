/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_adaptor_def.h"

#include "iterator_pte_def.h"

#include "iterator_adaptor_pte_def.h"

#include "iterator.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

void *iterator_control_function_address_table_set[] = {
	#ifdef __RANDOM_ACCESS_ITERATOR_H
	(void *)&random_access_iterator_control_function_address_table,
	#else
	NULL,
	#endif // __RANDOM_ACCESS_ITERATOR_H
	#ifdef __INPUT_ITERATOR_H
	(void *)&input_iterator_control_function_address_table,
	#else
	NULL,
	#endif // __INPUT_ITERATOR_H
	#ifdef __RANDOM_ACCESS_ITERATOR_H
	(void *)&random_access_iterator_control_function_address_table,
	#else
	NULL,
	#endif // __RANDOM_ACCESS_ITERATOR_H
};

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
 * @brief This function is the _readapt() core.
 *
 * @param void
 *
 * @return void
 */

void iterator_adaptor_control_configuration_readapt_core(enum iterator_type_e iterator_type,
														 struct iterator_object_unit_s object_unit);

/**
 * @brief This function will get the type enum id of the iterator.
 *
 * @param void
 *
 * @return void
 */

enum iterator_type_e iterator_adaptor_control_get_iterator_type(struct iterator_s *iterator);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

struct unify_adaptor_package_s iterator_adaptor_control_unify_adaptor_package = {
	.adaptor.adaptor_size
		= sizeof(struct iterator_adaptor_s),
	.adaptor.adaptee_unit_size
		= sizeof(struct iterator_unit_s),
	.adaptor.adaptee_unit_offset
		= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct iterator_adaptor_s, iterator_unit),
	.adaptor.allocator_unit_offest
		= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct iterator_adaptor_s, allocator_unit),
	.adaptor.get_adaptee_type
		= iterator_adaptor_control_get_iterator_type,

	.adaptee.allocator_unit_offest
		= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct iterator_s, allocator_unit),
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t
iterator_adaptor_control_configuration_init(struct iterator_adaptor_s **iterator_adaptor,
											enum iterator_adaptor_type_e iterator_adaptor_type,
											enum iterator_type_e iterator_type,
											enum allocator_type_e allocator_type,
											struct iterator_object_unit_s object_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);
	DEBUG_ASSERT_CONTROL_VARIABLE(iterator_type, >= , int, 0);

	iterator_adaptor_control_unify_adaptor_package.adaptor.allocator_type
		= allocator_type;
	iterator_adaptor_control_unify_adaptor_package.adaptor.adaptor_size
		= sizeof(struct iterator_adaptor_s);

	iterator_adaptor_control_configuration_readapt_core(iterator_type,
														object_unit);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(errno_t,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = unify_adaptor_control_construct(iterator_adaptor,
																	 iterator_adaptor_control_unify_adaptor_package),
									 "unify_adaptor_control_construct():fail");

	(*iterator_adaptor)->iterator_type_id = iterator_adaptor_type;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will readapt the iterator of the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t
iterator_adaptor_control_configuration_readapt(struct iterator_adaptor_s **iterator_adaptor,
											   enum iterator_type_e iterator_type,
											   struct iterator_object_unit_s object_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);
	DEBUG_ASSERT_CONTROL_POINTER(*iterator_adaptor);

	iterator_adaptor_control_configuration_readapt_core(iterator_type,
														object_unit);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(errno_t,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = unify_adaptor_control_readapt(iterator_adaptor,
																   iterator_adaptor_control_unify_adaptor_package),
									 "unify_adaptor_control_readapt():fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will adapt the exist iterator to the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t
iterator_adaptor_control_configuration_adapt_exist(struct iterator_adaptor_s **iterator_adaptor,
												   struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);
	DEBUG_ASSERT_CONTROL_POINTER(*iterator_adaptor);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(errno_t,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = unify_adaptor_control_adapt_exist(iterator_adaptor,
																	   iterator,
																	   iterator_adaptor_control_unify_adaptor_package),
									 "unify_adaptor_control_adapt_exist():fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will destroy the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_destroy(struct iterator_adaptor_s **iterator_adaptor)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);
	DEBUG_ASSERT_CONTROL_POINTER(*iterator_adaptor);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(errno_t,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = unify_adaptor_control_destruct(iterator_adaptor,
																	iterator_adaptor_control_unify_adaptor_package),
									 "unify_adaptor_control_destruct(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will advance base iterator of the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

extern inline void
*iterator_adaptor_control_iterator_operations_advance(struct iterator_adaptor_s *iterator_adaptor,
													  int step)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(void *,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL 
									 = iterator_adaptor->iterator_unit.control_ptr->iterator_operations
									 .advance(iterator_adaptor->iterator_unit.iterator_ptr,
											  step),
									 ".iterator_unit.iterator_control.iterator_operations.advance(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will advance base iterator of the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

extern inline size_t
iterator_adaptor_control_iterator_operations_distance(struct iterator_adaptor_s *iterator_adaptor,
													  int step)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);

	return 0;
}

/**
 * @brief This function will access the size of base iterator of the iterator adaptor.
 *
 * @param
 *
 * @return
 */

extern inline size_t
iterator_adaptor_control_range_access_size(struct iterator_adaptor_s *iterator_adaptor)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(size_t,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = iterator_adaptor->iterator_unit.control_ptr->range_access
									 .size(iterator_adaptor->iterator_unit.iterator_ptr),
									 ".iterator_unit.iterator_control.range_access.size(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will access if base iterator of the iterator adaptor is empty.
 *
 * @param
 *
 * @return
 */

extern inline bool
iterator_adaptor_control_range_access_empty(struct iterator_adaptor_s *iterator_adaptor)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(size_t,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = iterator_adaptor->iterator_unit.control_ptr->range_access
									 .empty(iterator_adaptor->iterator_unit.iterator_ptr),
									 ".iterator_unit.iterator_control.range_access.empty(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will access the data pointer that base iterator of the iterator adaptor pointed.
 *
 * @param
 *
 * @return
 */

extern inline void
*iterator_adaptor_control_range_access_data(struct iterator_adaptor_s *iterator_adaptor)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);

	DEBUG_ERROR_CONTROL_SINGLE_ERROR(void *,
									 1,
									 DEBUG_ERROR_CONTROL_RETURN_VAL
									 = iterator_adaptor->iterator_unit.control_ptr->range_access
									 .data(iterator_adaptor->iterator_unit.iterator_ptr),
									 ".iterator_unit.iterator_control.range_access.data(): fail");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will get the iterator unit of the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

extern inline struct iterator_unit_s
iterator_adaptor_control_get_iterator_unit(struct iterator_adaptor_s *iterator_adaptor)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);

	return iterator_adaptor->iterator_unit;
}

/**
 * @brief This function is the _readapt() core.
 *
 * @param void
 *
 * @return void
 */

static inline void
iterator_adaptor_control_configuration_readapt_core(enum iterator_type_e iterator_type,
													struct iterator_object_unit_s object_unit)
{
	iterator_adaptor_control_unify_adaptor_package.adaptor.adaptee_type
		= iterator_type;
	iterator_adaptor_control_unify_adaptor_package.adaptee.function_address_table_set_ptr
		= iterator_control_function_address_table_set;
	iterator_adaptor_control_unify_adaptor_package.adaptee.init_arg_ptr[0]
		= &object_unit;
}

/**
 * @brief This function will get the type enum id of the iterator.
 *
 * @param void
 *
 * @return void
 */

static inline enum iterator_type_e
iterator_adaptor_control_get_iterator_type(struct iterator_s *iterator)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator);

	return *(enum iterator_type_e *)iterator;
}