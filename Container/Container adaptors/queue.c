/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "queue.h"

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

/**
 * @brief This type will contain all the queue control functions.
 */

struct queue_control_t queue_ctrl =
{
	.configuration.init = queue_control_configuration_init,
	.configuration.adapt = queue_control_configuration_adapt,
	.configuration.destroy = queue_control_configuration_destroy,

	.element_access.front = queue_control_element_access_front, 
	.element_access.back = queue_control_element_access_back,

	.capacity.empty = queue_control_capacity_empty,
	.capacity.size = queue_control_capacity_size,
	.capacity.max_size = queue_control_capacity_max_size,

	.modifiers.push = queue_control_modifiers_push,
	.modifiers.emplace = queue_control_modifiers_emplace,
	.modifiers.pop = queue_control_modifiers_pop,
	.modifiers.swap = queue_control_modifiers_swap,
	.modifiers.copy = queue_control_modifiers_copy,

	.get_container = container_adaptor_control_get_container,
};

/**
 * @brief This struct is the queue allocate package
 */

struct container_allocte_package_s
	queue_control_allocate_package = {
.allocator_type = QUEUE_CFG_ALLOCATOR_TYPE ,
.container_mem_size = sizeof(struct container_adaptor_s)
};

/**
 * @brief This struct is the queue adapt package
 */

struct container_adaptor_adapt_package_s
	queue_control_adapt_package = { 0 };

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
 * @brief This function will initialize the queue struct and the specified container_ptr.
 *
 * @param queue the pointer to container_ptr adapter struct pointer
 * @param type the type of the container_ptr
 * @param element_size the pointer to container_ptr
 * @param string_type the pointer to container_ptr
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t queue_control_configuration_init(queue_stpp queue,
										 enum container_type_e container_type,
										 container_size_t element_size,
										 generic_type_element_assign_t assign,
										 generic_type_element_free_t free)
{
	assert(queue);
	assert(element_size);

	if (container_type) {
		container_type = PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;
	}

	queue_control_allocate_package.arg_list_ptr = NULL;										/* Set the allocate package */

	queue_control_adapt_package.container_ptr = NULL;										/* Set the adapt package */
	queue_control_adapt_package.container_type = container_type;
	queue_control_adapt_package.element_size = element_size;
	queue_control_adapt_package.assign_ptr = assign;
	queue_control_adapt_package.free_ptr = free;

	if (container_adaptor_control_configuration_init(queue,									/* Initialize the container_ptr adaptor */
													 QUEUE,
													 queue_control_allocate_package,
													 queue_control_adapt_package)) {
		return 1;
	}

	return 0;
}

/**
 * @brief This function will initialize the queue struct and attach to the specified container_ptr.
 *
 * @param queue the pointer to container_ptr adapter struct pointer
 * @param container_ptr the pointer to container_ptr pointer
 * @param func_addr_table the pointer to the function address table of the specified container_ptr
 *
 * @return NONE
 */

errno_t queue_control_configuration_adapt(queue_stpp queue,
										  void *container_ptr)
{
	assert(queue);
	assert(container_ptr);

	queue_control_allocate_package.arg_list_ptr = NULL;										/* Set the allocate package */

	queue_control_adapt_package.container_ptr = container_ptr;								/* Set the adapt package */

	if (container_adaptor_control_configuration_init(queue,									/* Initialize the container_ptr adaptor */
													 QUEUE,
													 queue_control_allocate_package,
													 queue_control_adapt_package)) {
		return 1;
	}

	return 0;
}

/**
 * @brief This function will destroy the queue struct.
 *
 * @param queue the pointer to container_ptr adapter struct pointer
 *
 * @return NONE
 */

errno_t queue_control_configuration_destroy(queue_stpp queue)
{
	assert(queue);
	assert(*queue);

	return container_adaptor_control_configuration_destroy(queue);						    /* Destroy the container_ptr adaptor */
}

/**
 * @brief This function will return reference to the first element in the queue.
 *
 * @param queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_front(queue_stp queue)
{
	assert(queue);

	void
		*container_ptr = NULL;																/* Variables pointer to	the specified container_ptr struct */

	return queue->container_control_ptr->element_access
		.at(queue->container_ptr, 0);														/* Get the top element of the container_ptr */
}

/**
 * @brief This function will return reference to the last element in the queue.
 *
 * @param queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_back(queue_stp queue)
{
	assert(queue);

	void
		*container_ptr = NULL;																/* Variables pointer to	the specified container_ptr struct */

	return queue->container_control_ptr->element_access
		.at(queue->container_ptr, queue->container_control_ptr->capacity					/* Get the top element of the container_ptr */
			.size(queue->container_ptr) - 1);
}

/**
 * @brief This function will check if the underlying container_ptr has no elements.
 *
 * @param queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

bool queue_control_capacity_empty(queue_stp queue)
{
	assert(queue);

	if (((container_size_t)queue_control_capacity_size(queue)) <=
		((container_size_t)queue_control_capacity_max_size(queue))) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container_ptr.
 *
 * @param queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

container_size_t queue_control_capacity_size(queue_stp queue)
{
	assert(queue);

	#if (QUEUE_CFG_DEBUG_EN)

	printf("queue.size : %d \r\n", queue->container_control_ptr->capacity.size(queue->container_ptr));

	#endif // (QUEUE_CFG_DEBUG_EN)

	return queue->container_control_ptr->capacity.size(queue->container_ptr);				/* Get the number of elements in the container_ptr */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container_ptr is able to hold due to system or library implementation limitations.
 *
 * @param queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

container_size_t queue_control_capacity_max_size(queue_stp queue)
{
	assert(queue);

	return queue->container_control_ptr->capacity.max_size(queue->container_ptr);			/* Get the maximum number of elements the container_ptr
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the bottom of the queue.
 *
 * @param queue the pointer to container_ptr adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

errno_t queue_control_modifiers_push(queue_stp queue, void *source)
{
	assert(queue);

	queue->container_control_ptr->modifiers
		.insert(queue->container_ptr, queue->container_control_ptr->capacity				/* Insert the given element source to the back of the container_ptr */
				.size(queue->container_ptr), 1, &source);

	return 0;
}

/**
 * @brief This function will push a new element on bottom of the queue. The element is constructed in-place.
 *
 * @param queue the pointer to container_ptr adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

errno_t queue_control_modifiers_emplace(queue_stp queue, void *destination)
{
	assert(queue);

	return 0;
}

/**
 * @brief This function will remove the top element from the queue.
 *
 * @param queue the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

errno_t queue_control_modifiers_pop(queue_stp queue)
{
	assert(queue);

	queue->container_control_ptr->modifiers
		.earse(queue->container_ptr, 0);													/* Earse the front element of the container_ptr */

	return 0;
}

/**
 * @brief This function will exchange the contents of the container_ptr adaptor with those of other.
 *
 * @param queue the pointer to container_ptr adapter struct
 * @param other the pointer to other container_ptr adapter struct
 *
 * @return NONE
 */

errno_t queue_control_modifiers_swap(queue_stpp queue, queue_stpp other)
{
	assert(queue);

	(*queue)->container_control_ptr->modifiers
		.swap(&(*queue)->container_ptr, &(*other)->container_ptr);							/* Swap the contents of the container_ptr adaptor with those of other */

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

errno_t queue_control_modifiers_copy(queue_stpp destination, queue_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control_ptr->modifiers
		.copy(&(*destination)->container_ptr, source->container_ptr);						/* Copy the contents of the container_ptr adaptor to those of other */

	return 0;
}