/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_adaptor_def.h"

#include "container_adatpor_pte_def.h"

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
 * @brief This function will let container adaptor adapt the container
 *			that introduced or initialized by parameters.
 *
 * @param void
 *
 * @return void
 */

errno_t
container_adaptor_control_configuration_adapt(struct container_adaptor_s *adaptor,
											  struct container_adaptor_adapt_package_s package);

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
 * @brief This function will initialize the container adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t container_adapotr_control_configuration_init(struct container_adaptor_s **adaptor,
													 enum container_type_e adaptor_type,
													 struct container_allocte_package_s allocate_package,
													 struct container_adaptor_adapt_package_s adapt_package,
													 void *addon,
													 size_t addon_size)
{
	assert(adaptor);
	assert(adaptor_type);
	assert(allocate_package.allocator_type &&
		   allocate_package.container_mem_size);
	assert(adapt_package.container
		   || (adapt_package.container_type
			   && adapt_package.element_size));

	struct container_control_configuration_allocate_return_s allocate_return = { 0 };

	if ((allocate_return
		 = container_control_configuration_allocate(adaptor, allocate_package))		/* Allocate the adaptor structure */
		.error) {
		return allocate_return.error;
	}

	if (allocate_return.error
		= container_adaptor_control_configuration_adapt(*adaptor, adapt_package)) {	/* Adapt the container structure */
		return allocate_return.error;
	}

	(*adaptor)->container_type_id = adaptor_type;									/* Assign priority_queue structure */

	(*adaptor)->allocator_control_ptr = allocate_return.allocator_control_ptr;
	(*adaptor)->allocator_ptr = allocate_return.allocator_ptr;

	memcpy((*adaptor)->addon, addon, addon_size);									/* Assign the addon memory space */

	return 0;
}

/**
 * @brief This function will let container adaptor adapt the container
 *			that introduced or initialized by parameters.
 *
 * @param void
 *
 * @return void
 */

errno_t
container_adaptor_control_configuration_adapt(struct container_adaptor_s *adaptor,
											  struct container_adaptor_adapt_package_s package)
{
	assert(adaptor);
	assert(package.container
		   || (package.container_type
			   && package.element_size));

	const static errno_t err_code[] 														/* Appoint the error code of every return point */
		= { 4,5 };

	if (!package.container_type) {
		package.container_type = *(enum container_type_e *)package.container;				/* Get the container type from the id of the container */
	}

	if (NULL
		== (adaptor->container_control_ptr													/* Get the universal function address table of container_ptr */
			= container_adaptor_control_get_container_func_addr_table(package.container_type))) {
		return err_code[0];
	}

	if (NULL == (adaptor->container_ptr = package.container)) {
		if (adaptor->container_control_ptr->configuration
			.init(&adaptor																	/* Initialize the specified container_ptr struct */
				  ->container_ptr, package.element_size, package.assign, package.free)) {
			return err_code[1];
		}
	}

	return 0;
}

/**
 * @brief This function will convert and return the function address table
 *			that is related to the specified container type.
 *
 * @param void
 *
 * @return void
 */

extern inline void
*container_adaptor_control_get_container_func_addr_table(enum container_type_e type)
{
	void
		*func_addr_table = NULL;

	switch (type) {
		#if (CONTAINER_FAMILY_LEVEL_CFG_BINARY_TREE_EN)

		#endif // (CONTAINER_FAMILY_LEVEL_CFG_BINARY_TREE_EN)

		#if (CONTAINER_FAMILY_LEVEL_CFG_RED_BLACK_TREE_EN)

		#endif // (CONTAINER_FAMILY_LEVEL_CFG_RED_BLACK_TREE_EN)

		#if (CONTAINER_FAMILY_LEVEL_CFG_B_TREE_EN)

		#endif // (CONTAINER_FAMILY_LEVEL_CFG_B_TREE_EN)

		#if (CONTAINER_FAMILY_LEVEL_CFG_ARRAY_EN)

		case ARRAY:
			func_addr_table = &array_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_ARRAY_EN)

			#if (CONTAINER_FAMILY_LEVEL_CFG_VECTOR_EN)

		case VECTOR:
			func_addr_table = &vector_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_VECTOR_EN)

			#if (CONTAINER_FAMILY_LEVEL_CFG_FORWARD_LIST_EN)

		case FORWARD_LIST:
			func_addr_table = &forward_list_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_FORWARD_LIST_EN)

			#if (CONTAINER_FAMILY_LEVEL_CFG_LIST_EN)

		case LIST:
			func_addr_table = &list_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_LIST_EN)
			break;
		default:
			break;
	}

	return func_addr_table;
}