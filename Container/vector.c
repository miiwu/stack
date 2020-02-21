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

#if (VECTOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

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

		vector_control_capacity_reserve,

		vector_control_capacity_shrink_to_fit,
	},
	{
		array_family_control_modifiers_clear,

		array_family_control_modifiers_insert,

		array_family_control_modifiers_erase,

		array_family_control_modifiers_push_back,

		array_family_control_modifiers_pop_back,

		vector_control_modifiers_resize,

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

void vector_control_configuration_init(VECTOR_TYPEDEF_PPTR vector,
									   container_size_t element_size,
									   void (*assign)(void *dst, void *src), void (*free)(void *dst))
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

/**
 * @brief This function will increase the capacity of the vector to a size that's greater or equal to new_cap.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param size the size of elements
 *
 * @return NONE
 */

void vector_control_capacity_reserve(VECTOR_TYPEDEF_PPTR vector,
									 container_size_t size)
{
	assert(vector);
	assert(0 <= size);

	// TODO...
}

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

void vector_control_capacity_shrink_to_fit(VECTOR_TYPEDEF_PPTR vector)
{
	assert(vector);

	// TODO...
}

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param vector the pointer to the container struct
 * @param count the count of elements
 *
 * @return NONE
 */

void vector_control_modifiers_resize(VECTOR_TYPEDEF_PPTR vector,
									 container_size_t count)
{
	assert(vector);
	assert(0 <= count);

	if ((*vector)->info.max_size >= count) {
		return;
	}

	(*vector)->allocator_ctrl->deallocate((*vector)->allocator, (*vector)->data, 1);									/* Deallocate #2.1 */

	void
		*data_pack_alloced = (*vector)->allocator_ctrl->allocate((*vector)->allocator,
																 count,
																 (*vector)->info.mem_size);								/* Malloc	vector malloc #2.1 */

	if (NULL == data_pack_alloced) {
		return;
	}

	(*vector)->info.max_size = count;
	(*vector)->data = data_pack_alloced;
}