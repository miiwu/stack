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

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3);

	iterator_adaptor_control_unify_adaptor_package.adaptor.allocator_type
		= allocator_type;
	iterator_adaptor_control_unify_adaptor_package.adaptor.adaptor_size
		= sizeof(struct iterator_adaptor_s);

	iterator_adaptor_control_configuration_readapt_core(iterator_type,
														object_unit);

	unify_adaptor_control_construct(iterator_adaptor,
									iterator_adaptor_control_unify_adaptor_package);
	DEBUG_ERROR_CONTROL_JUDGE(1, "unify_adaptor_control_construct():fail");

	(*iterator_adaptor)->iterator_type_id = iterator_adaptor_type;
	//(*iterator_adaptor)->iterator_unit.control_ptr = iterator_control_ptr;

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

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3);

	iterator_adaptor_control_configuration_readapt_core(iterator_type,
														object_unit);

	unify_adaptor_control_readapt(iterator_adaptor,
								  iterator_adaptor_control_unify_adaptor_package);
	DEBUG_ERROR_CONTROL_JUDGE(1, "unify_adaptor_control_readapt():fail");

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

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3);

	unify_adaptor_control_adapt_exist(iterator_adaptor,
									  iterator,
									  iterator_adaptor_control_unify_adaptor_package);
	DEBUG_ERROR_CONTROL_JUDGE(1, "unify_adaptor_control_readapt():fail");

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

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3);

	unify_adaptor_control_destruct(iterator_adaptor,
								   iterator_adaptor_control_unify_adaptor_package);
	DEBUG_ERROR_CONTROL_JUDGE(1, "unify_adaptor_control_destruct():fail");

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