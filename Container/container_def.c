/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

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
 * @brief This function will initialize the container.
 *
 * @param void
 *
 * @return void
 */

struct container_control_configuration_allocate_return_s
	container_control_configuration_allocate(void **container,
											 struct container_allocte_package_s package)
{
	assert(container);
	assert(package.allocator_type &&
		   package.container_mem_size);

	const static errno_t err_code[] 														/* Appoint the error code of every return point */
		= { 1,2,3 };

	struct container_control_configuration_allocate_return_s
		init_return = { 0 };

	if (NULL
		== (init_return.allocator_control_ptr
			= allocator_control_convert_type_to_func_addr_table(package.allocator_type))) {
		return (struct container_control_configuration_allocate_return_s) { err_code[0] };
	}

	if (init_return.allocator_control_ptr->configuration
		.init(&init_return.allocator_ptr, package.arg_list_ptr)) {							/* Initialize the allocator_ptr struct */
		return (struct container_control_configuration_allocate_return_s) { err_code[1] };
	}

	if (NULL == ((*container) = init_return.allocator_control_ptr							/* Allocate the container_ptr struct */
				 ->allocate(init_return.allocator_ptr, 1, package.container_mem_size))) {
		return (struct container_control_configuration_allocate_return_s) { err_code[2] };
	}

	return init_return;
}