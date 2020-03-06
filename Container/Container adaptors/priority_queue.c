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
 * @brief This struct is the priority queue addon structure
 */

struct priority_queue_addon_s {
	/* @brief This variables will point to the compare_ptr function.									*/
	compare_t compare_ptr;
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

/**
 * @brief This struct is the priority queue control structure
 */

struct priority_queue_control_s priority_queue_ctrl =
{
	.configuration.init = priority_queue_control_configuration_init,
	.configuration.adapt = priority_queue_control_configuration_adapt,
	.configuration.destroy = priority_queue_control_configuration_destroy,

	.element_access.top = priority_queue_control_element_access_top,

	.capacity.empty = priority_queue_control_capacity_empty,
	.capacity.size = priority_queue_control_capacity_size,
	.capacity.max_size = priority_queue_control_capacity_max_size,

	.modifiers.push = priority_queue_control_modifiers_push,
	.modifiers.emplace = priority_queue_control_modifiers_emplace,
	.modifiers.pop = priority_queue_control_modifiers_pop,
	.modifiers.swap = priority_queue_control_modifiers_swap,
	.modifiers.copy = priority_queue_control_modifiers_copy
};

/**
 * @brief This struct is the priority queue allocate package
 */

struct container_allocte_package_s
	priority_queue_contro_allocate_package = {
	.allocator_type = PRIORITY_QUEUE_CFG_ALLOCATOR_TYPE ,
	.container_mem_size = sizeof(struct container_adaptor_s) + sizeof(struct priority_queue_addon_s)
};

/**
 * @brief This struct is the priority queue adapt package
 */

struct container_adaptor_adapt_package_s
	priority_queue_control_adapt_package = { 0 };

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
 * @brief This function will initialize the priority_queue struct and the specified container.
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

	if (container_type) {
		container_type = PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;
	}

	priority_queue_contro_allocate_package.arg_list_ptr = NULL;								/* Set the allocate package */

	priority_queue_control_adapt_package.container_ptr = NULL;								/* Set the adapt package */
	priority_queue_control_adapt_package.container_type = container_type;
	priority_queue_control_adapt_package.element_size = element_size;
	priority_queue_control_adapt_package.assign_ptr = assign;
	priority_queue_control_adapt_package.free_ptr = free;

	if (container_adaptor_control_configuration_init(priority_queue,						/* Initialize the container adaptor */
													 PRIORITY_QUEUE,
													 priority_queue_contro_allocate_package,
													 priority_queue_control_adapt_package)) {
		return 1;
	}

	if (priority_queue_control_configuration_change_compare(*priority_queue,				/* Set the addon */
															compare)) {
		return 2;
	}

	return 0;
}

/**
 * @brief This function will initialize the priority_queue struct and attach to the specified container.
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

	priority_queue_contro_allocate_package.arg_list_ptr = NULL;								/* Set the allocate package */

	priority_queue_control_adapt_package.container_ptr = container;							/* Set the adapt package */

	if (container_adaptor_control_configuration_init(priority_queue,						/* Initialize the container adaptor */
													 PRIORITY_QUEUE,
													 priority_queue_contro_allocate_package,
													 priority_queue_control_adapt_package)) {
		return 1;
	}

	if (priority_queue_control_configuration_change_compare(*priority_queue,				/* Set the addon */
															compare)) {
		return 2;
	}

	return 0;
}

/**
 * @brief This function will initialize the priority_queue struct and attach to the specified container.
 *
 * @param void
 *
 * @return void
 */

errno_t priority_queue_control_configuration_change_compare(priority_queue_stp priority_queue,
															compare_t compare)
{
	assert(priority_queue);

	if (NULL == compare) {
		struct priority_queue_addon_s *priority_queue_addon = (void *)priority_queue->addon;

		if (NULL != priority_queue_addon->compare_ptr) {
			goto EXIT;
		}

		compare = &compare_control_greater;
	}

	struct priority_queue_addon_s addon
		= { compare };

	if (NULL == memcpy(priority_queue->addon, &addon, sizeof(struct priority_queue_addon_s))) {
		return -1;
	}

EXIT:

	return 0;
}

/**
 * @brief This function will destroy the priority_queue struct.
 *
 * @param priority_queue the pointer to container_ptr adapter struct pointer
 *
 * @return NONE
 */

extern inline errno_t
priority_queue_control_configuration_destroy(priority_queue_stpp priority_queue)
{
	assert(priority_queue);
	assert(*priority_queue);

	return container_adaptor_control_configuration_destroy(priority_queue);
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
		*container_ptr = NULL;																/* Variables pointer to	the specified container_ptr struct */

	return priority_queue->container_control_ptr->element_access.							/* Get the back element of the container_ptr */
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

	return priority_queue->container_control_ptr->capacity
		.size(priority_queue->container_ptr);												/* Get the number of elements in the container_ptr */
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

	return priority_queue->container_control_ptr->capacity
		.max_size(priority_queue->container_ptr);											/* Get the maximum number of elements the container_ptr
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

errno_t priority_queue_control_modifiers_push(priority_queue_stp priority_queue, void *source)
{
	assert(priority_queue);

	struct priority_queue_addon_s *priority_queue_addon = (void *)priority_queue->addon;

	priority_queue->container_control_ptr->modifiers
		.insert(priority_queue->container_ptr,												/* Insert the given element source to the back of the container_ptr */
				priority_queue->container_control_ptr->capacity
				.size(priority_queue->container_ptr), 1, &source);

	if (NULL != priority_queue->container_control_ptr->list_operations.sort) {				/* If the container_ptr have sort prototype */
		priority_queue->container_control_ptr->list_operations
			.sort(priority_queue->container_ptr, priority_queue_addon->compare_ptr);
	} else {
		while (true) {
		// TODO ...,if enter here please wait further update, or you can fix it, thanks.
		}
	}

	return 0;
}

/**
 * @brief This function will push a new element on top of the priority_queue. The element is constructed in-place.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

errno_t priority_queue_control_modifiers_emplace(priority_queue_stp priority_queue, void *destination)
{
	assert(priority_queue);

	return 0;
}

/**
 * @brief This function will remove the top element from the priority_queue.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

errno_t priority_queue_control_modifiers_pop(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	priority_queue->container_control_ptr->modifiers
		.earse(priority_queue->container_ptr,												/* Earse back element of the container_ptr. */
			   priority_queue->container_control_ptr->capacity.
			   size(priority_queue->container_ptr) - 1);

	return 0;
}

/**
 * @brief This function will exchange the contents of the container_ptr adaptor with those of other.
 *
 * @param priority_queue the pointer to container_ptr adapter struct
 * @param other the pointer to other container_ptr adapter struct
 *
 * @return NONE
 */

errno_t priority_queue_control_modifiers_swap(priority_queue_stpp priority_queue, priority_queue_stpp other)
{
	assert(priority_queue);

	(*priority_queue)->container_control_ptr->modifiers
		.swap(&(*priority_queue)->container_ptr, &(*other)->container_ptr);					/* exchange the contents of the container_ptr adaptor with those of other */

	return 0;
}

/**
 * @brief This function will copy the contents of the container_ptr adaptor to those of other.
 *
 * @param destination the pointer to destination container_ptr adapter struct
 * @param source the pointer to source container_ptr adapter struct
 *
 * @return NONE
 */

errno_t priority_queue_control_modifiers_copy(priority_queue_stpp destination, priority_queue_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control_ptr->modifiers
		.copy(&(*destination)->container_ptr, source->container_ptr);						/* copy the contents of the container_ptr adaptor to those of other */

	return 0;
}