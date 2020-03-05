/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "priority_queue.h"

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

/**
 * @brief This struct is the priority_queue structure module
 */

struct priority_queue_addon_s {
	/* @brief This variables will point to the compare_ptr function.									*/
	compare_t *compare_ptr;
};

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

struct priority_queue_control_s priority_queue_ctrl =
{
	priority_queue_control_configuration_init,

	priority_queue_control_configuration_adapt,

	priority_queue_control_configuration_destroy,

	priority_queue_control_element_access_top,

	priority_queue_control_capacity_empty,

	priority_queue_control_capacity_size,

	priority_queue_control_capacity_max_size,

	priority_queue_control_modifiers_push,

	priority_queue_control_modifiers_emplace,

	priority_queue_control_modifiers_pop,

	priority_queue_control_modifiers_swap,

	priority_queue_control_modifiers_copy
};

struct container_allocte_package_s
	priprity_queue_control_configuration_init_allocate_package = { 0 };

struct container_adaptor_adapt_package_s
	priprity_queue_control_configuration_init_adapt_package = { 0 };

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the priority_queue struct and the specified container_ptr.
 *
 * @param priority_queue the pointer to container_ptr adapter struct pointer
 * @param type the type of the container_ptr
 * @param element_size the pointer to container_ptr
 * @param string_type the pointer to container_ptr
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t priority_queue_control_configuration_init(priority_queue_stpp priority_queue,
												  enum container_type_e container_type,
												  container_size_t element_size,
												  compare_t compare,
												  generic_type_element_assign_t assign,
												  generic_type_element_free_t free)
{
	assert(priority_queue);
	assert(element_size);

	errno_t err = 0;

	if (container_type) {
		container_type = PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;
	}

	if (NULL == compare) {
		compare = &compare_control_greater;
	}

	priprity_queue_control_configuration_init_allocate_package
		.allocator_type = PRIORITY_QUEUE_CFG_ALLOCATOR_TYPE;
	priprity_queue_control_configuration_init_allocate_package
		.container_mem_size
		= sizeof(struct container_adaptor_s) + sizeof(struct priority_queue_addon_s);
	priprity_queue_control_configuration_init_allocate_package
		.arg_list = NULL;

	priprity_queue_control_configuration_init_adapt_package.container = NULL;
	priprity_queue_control_configuration_init_adapt_package.container_type = container_type;
	priprity_queue_control_configuration_init_adapt_package.element_size = element_size;
	priprity_queue_control_configuration_init_adapt_package.assign = assign;
	priprity_queue_control_configuration_init_adapt_package.free = free;

	struct priority_queue_addon_s addon
		= { compare };

	if (err = container_adapotr_control_configuration_init(priority_queue,
														   PRIORITY_QUEUE,
														   priprity_queue_control_configuration_init_allocate_package,
														   priprity_queue_control_configuration_init_adapt_package,
														   &addon,
														   sizeof(struct priority_queue_addon_s))) {
		goto EXIT;
	}

EXIT:

	return err;
}

/**
 * @brief This function will initialize the priority_queue struct and attach to the specified container_ptr.
 *
 * @param priority_queue the pointer to container_ptr adapter struct pointer
 * @param container_ptr the pointer to container_ptr pointer
 * @param func_addr_table the pointer to the function address table of the specified container_ptr
 *
 * @return NONE
 */

errno_t priority_queue_control_configuration_adapt(priority_queue_stpp priority_queue,
												   void *container,
												   compare_t compare)
{
	assert(priority_queue);
	assert(container);

	errno_t err = 0;

	if (NULL == compare) {
		compare = &compare_control_greater;
	}

	priprity_queue_control_configuration_init_allocate_package
		.allocator_type = PRIORITY_QUEUE_CFG_ALLOCATOR_TYPE;
	priprity_queue_control_configuration_init_allocate_package
		.container_mem_size
		= sizeof(struct container_adaptor_s) + sizeof(struct priority_queue_addon_s);
	priprity_queue_control_configuration_init_allocate_package
		.arg_list = NULL;

	priprity_queue_control_configuration_init_adapt_package.container = container;
	priprity_queue_control_configuration_init_adapt_package.container_type = 0u;
	priprity_queue_control_configuration_init_adapt_package.element_size = 0u;
	priprity_queue_control_configuration_init_adapt_package.assign = NULL;
	priprity_queue_control_configuration_init_adapt_package.free = NULL;

	struct priority_queue_addon_s addon
		= { compare };

	if (err = container_adapotr_control_configuration_init(priority_queue,
														   PRIORITY_QUEUE,
														   priprity_queue_control_configuration_init_allocate_package,
														   priprity_queue_control_configuration_init_adapt_package,
														   &addon,
														   sizeof(struct priority_queue_addon_s))) {
		return err;
	}

	return 0;

	//if (NULL == compare) {
	//	compare = &PRIORITY_QUEUE_CFG_COMPARE_ALGORITHM_TYPE;
	//}

	//struct priority_queue_addon_s addon
	//	= { compare };

	//struct container_control_configuration_allocate_return_s init_return
	//	= container_control_configuration_allocate(priority_queue,
	//											   sizeof(struct container_adaptor_s)
	//											   + sizeof(struct priority_queue_addon_s),
	//											   NULL);

	//struct container_control_configuration_adapt_return_s adapt_return
	//	= container_adaptor_control_configuration_adapt(priority_queue,
	//													container,
	//													0,
	//													0,
	//													NULL,
	//													NULL);

	//if (init_return.error) {
	//	return init_return.error;
	//}

	//if (adapt_return.error) {
	//	return adapt_return.error;
	//}

	//(*priority_queue)->container_type_id = PRIORITY_QUEUE;									/* Assign priority_queue structure					*/

	//(*priority_queue)->allocator_control_ptr = init_return.allocator_control_ptr;
	//(*priority_queue)->allocator_ptr = init_return.allocator_ptr;
	//(*priority_queue)->container_control_ptr = adapt_return.container_control_ptr;
	//(*priority_queue)->container_ptr = adapt_return.container_ptr;

	//memcpy((*priority_queue)->addon, &addon, sizeof(struct priority_queue_addon_s));

	//return 0;
}

/**
 * @brief This function will destroy the priority_queue struct.
 *
 * @param priority_queue the pointer to container_ptr adapter struct pointer
 *
 * @return NONE
 */

errno_t priority_queue_control_configuration_destroy(priority_queue_stpp priority_queue)
{
	assert(priority_queue);

	#if (STACK_CFG_DEBUG_EN)

	printf("destroy.priority_queue container_ptr : %p \r\n", (*priority_queue)->container_ptr);
	printf("destroy.priority_queue allocator_ptr : %p \r\n", (*priority_queue)->allocator_ptr);
	printf("destroy.priority_queue block : %p \r\n", (*priority_queue));

	#endif // (STACK_CFG_DEBUG_EN)

	void
		*container_ptr = NULL;																	/* Variables pointer to	the specified container_ptr struct */

	void
		*allocator_ptr = (*priority_queue)->allocator_ptr;;											/* Variables pointer to	the allocator_ptr struct */

	struct allocator_control_s
		*allocator_control_ptr = (*priority_queue)->allocator_control_ptr;

	(*priority_queue)->container_control_ptr->configuration.
		destroy(&(*priority_queue)->container_ptr);												/* Destroy the container_ptr */

	allocator_control_ptr->deallocate(allocator_ptr, (*priority_queue), 1);							/* Deallocate #2 */

	allocator_control_ptr->configuration.destroy(&allocator_ptr);

	*priority_queue = NULL;

	return 0;
}

/**
 * @brief This function will return reference to the top element in the priority_queue.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

void *priority_queue_control_element_access_top(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	void
		*container_ptr = NULL;																	/* Variables pointer to	the specified container_ptr struct */

	return priority_queue->container_control_ptr->element_access.								/* Get the back element of the container_ptr */
		at(priority_queue->container_ptr,
		   priority_queue->container_control_ptr->capacity.
		   size(priority_queue->container_ptr) - 1);
}

/**
 * @brief This function will check if the underlying container_ptr has no elements.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

bool priority_queue_control_capacity_empty(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	if (((container_size_t)priority_queue_control_capacity_size(priority_queue)) <=
		((container_size_t)priority_queue_control_capacity_max_size(priority_queue))) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container_ptr.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

container_size_t priority_queue_control_capacity_size(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	#if (STACK_CFG_DEBUG_EN)

	printf("priority_queue.size : %d \r\n", priority_queue->container_control_ptr->capacity.size(priority_queue->container_ptr));

	#endif // (STACK_CFG_DEBUG_EN)

	return priority_queue->container_control_ptr->capacity.size(priority_queue->container_ptr);		/* Get the number of elements in the container_ptr */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container_ptr is able to hold due to system or library implementation limitations.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

container_size_t priority_queue_control_capacity_max_size(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	return priority_queue->container_control_ptr->capacity.max_size(priority_queue->container_ptr);	/* Get the maximum number of elements the container_ptr
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the top of the priority_queue.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

void priority_queue_control_modifiers_push(priority_queue_stp priority_queue, void *source)
{
	assert(priority_queue);

	struct priority_queue_addon_s *priority_queue_addon = (void *)priority_queue->addon;

	priority_queue->container_control_ptr->modifiers.insert(priority_queue->container_ptr,			/* Insert the given element source to the back of the container_ptr */
															priority_queue->container_control_ptr->capacity.size(priority_queue->container_ptr), 1, &source);

	if (NULL != priority_queue->container_control_ptr->list_operations.sort) {					/* If the container_ptr have sort prototype */
		priority_queue->container_control_ptr->list_operations.sort(priority_queue->container_ptr,
																	priority_queue_addon->compare_ptr);
	} else {
		while (true) {
		// TODO ...,if enter here please wait further update, or you can fix it, thanks.
		}
	}
}

/**
 * @brief This function will push a new element on top of the priority_queue. The element is constructed in-place.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void priority_queue_control_modifiers_emplace(priority_queue_stp priority_queue, void *destination)
{
	assert(priority_queue);
}

/**
 * @brief This function will remove the top element from the priority_queue.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_pop(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	priority_queue->container_control_ptr->modifiers.earse(priority_queue->container_ptr,			/* Earse back element of the container_ptr. */
														   priority_queue->container_control_ptr->capacity.
														   size(priority_queue->container_ptr) - 1);
}

/**
 * @brief This function will exchange the contents of the container_ptr adaptor with those of other.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 * @param other the pointer to other container_ptr adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_swap(priority_queue_stpp priority_queue, priority_queue_stpp other)
{
	assert(priority_queue);

	(*priority_queue)->container_control_ptr->modifiers.swap(&(*priority_queue)->container_ptr, &(*other)->container_ptr);/* exchange the contents of the container_ptr adaptor with those of other */
}

/**
 * @brief This function will copy the contents of the container_ptr adaptor to those of other.
 *
 * @param destination the pointer to destination container_ptr adapter struct
 * @param source the pointer to source container_ptr adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_copy(priority_queue_stpp destination, priority_queue_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control_ptr->modifiers.copy(&(*destination)->container_ptr, source->container_ptr);		/* copy the contents of the container_ptr adaptor to those of other */
}