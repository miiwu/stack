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

struct unify_adaptor_package_s iterator_adaptor_control_unify_adaptor_package = {
	.adaptor.allocator_type = CONCEPT_ALLOCATOR,
	.adaptor.adaptee_offset
		= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct iterator_adaptor_s, iterator_unit),
	.adaptor.allocator_unit_offest
		= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct iterator_adaptor_s, allocator_unit),

	.adaptee.allocator_unit_offest
		= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct iterator_s, allocator_unit),
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
 * @brief This function will initialize the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_init(struct iterator_adaptor_s **iterator_adaptor,
													enum iterator_adaptor_type_e iterator_adaptor_type,
													enum iterator_type_e iterator_type,
													enum allocator_type_e allocator_type,
													struct iterator_object_unit_s object_unit)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);
	DEBUG_ASSERT_CONTROL_VARIABLE(iterator_type, >= , int, 0);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3);

	struct iterator_control_s *iterator_control_ptr
		= iterator_control_function_address_table_set[iterator_type];

	iterator_adaptor_control_unify_adaptor_package.adaptor.adaptor_memory_size
		= sizeof(struct iterator_adaptor_s);
	iterator_adaptor_control_unify_adaptor_package.adaptee.init_ptr
		= iterator_control_ptr->configuration.init;
	iterator_adaptor_control_unify_adaptor_package.adaptee.destroy_ptr
		= iterator_control_ptr->configuration.destroy;
	iterator_adaptor_control_unify_adaptor_package.adaptee.init_arg_ptr[0]
		= &object_unit;

	unify_adaptor_control_construct(iterator_adaptor,
									iterator_adaptor_control_unify_adaptor_package);
	DEBUG_ERROR_CONTROL_JUDGE(1, "unify_adaptor_control_construct():fail");

	(*iterator_adaptor)->iterator_type_id = iterator_adaptor_type;
	(*iterator_adaptor)->iterator_unit.control_ptr = iterator_control_ptr;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will let iterator adaptor adapt the iterator
 *			that introduced or initialized by parameters.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_readapt(struct iterator_adaptor_s **iterator_adaptor)
{
	DEBUG_ASSERT_CONTROL_POINTER(iterator_adaptor);
	DEBUG_ASSERT_CONTROL_POINTER(*iterator_adaptor);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3);

	unify_adaptor_control_readapt(iterator_adaptor,
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

///**
// * @brief This function will get and return the iterator of the adaptor.
// *
// * @param void
// *
// * @return void
// */
//
//extern inline struct iterator_unit_s
//iterator_adaptor_control_get_iterator(struct iterator_adaptor_s *adaptor)
//{
//	assert(adaptor);
//
//	struct iterator_unit_s iterator_unit = {
//		.iterator_control_ptr = adaptor->iterator_control_ptr,
//		.iterator_ptr = adaptor->iterator_ptr,
//	};
//
//	return iterator_unit;
//}