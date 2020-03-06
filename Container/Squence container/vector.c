/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "vector.h"

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
 * @brief This array will contain all the universal vector functions address.
 */

void *vector_function_address_tables[] =
{
	(void *)&vector_control_configuration_init,						/* No.0 : initialize */

	(void *)&array_family_control_configuration_destroy,					/* No.1 : destroy */

	(void *)&array_family_control_element_access_at,						/* No.3 : at */

	(void *)&array_family_control_capacity_empty,							/* No.4 : empty */

	(void *)&array_family_control_capacity_size,							/* No.5 : size */

	(void *)&array_family_control_capacity_max_size,						/* No.6 : max_size */

	(void *)&array_family_control_modifiers_insert,							/* No.7 : insert */

	(void *)&array_family_control_modifiers_erase,							/* No.8 : erase */

	(void *)&array_family_control_modifiers_swap,							/* No.9 : swap */

	(void *)&array_family_control_modifiers_copy,							/* No.10 : copy */
};

#if (VECTOR_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */

struct vector_control_s vector_ctrl = {
	{
		vector_control_configuration_init,

		array_family_control_configuration_destroy,

		array_family_control_configuration_element_handler,

		array_family_control_configuration_exception,
	},
	{
		array_family_control_iterators_front,

		array_family_control_iterators_back,
	},
	{
		array_family_control_element_access_at,

		array_family_control_element_access_data,

		array_family_control_element_access_front,

		array_family_control_element_access_back,
	},
	{
		array_family_control_capacity_empty,

		array_family_control_capacity_size,

		array_family_control_capacity_max_size,

		array_family_control_capacity_capacity,

		array_family_control_capacity_reserve,

		array_family_control_capacity_shrink_to_fit,
	},
	{
		array_family_control_modifiers_clear,

		array_family_control_modifiers_insert,

		array_family_control_modifiers_erase,

		array_family_control_modifiers_push_back,

		array_family_control_modifiers_pop_back,

		array_family_control_modifiers_resize,

		array_family_control_modifiers_copy,

		array_family_control_modifiers_swap,
	}
};

#endif

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will switch the array-family control.
 *
 * @param void
 *
 * @return void
 */

void vector_control_switch_control(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list struct
 *
 * @param list the pointer to the list struct pointer
 * @param element_size the element memory size of the list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void vector_control_configuration_init(vector_stpp vector,
									   container_size_t element_size,
									   generic_type_element_assign_t assign,
									   generic_type_element_free_t free)
{
	assert(vector);

	array_family_control_configuration_init(vector, vector_control_switch_control,
											VECTOR_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will This function will switch the array-family control.
 *
 * @param void
 *
 * @return void
 */

void vector_control_switch_control(void)
{
	array_family_control_get_control(ARRAY_FAMILY_VECTOR);
}