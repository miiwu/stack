/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "priority_queue.h"

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

struct priority_queue_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e	container_type_id;

	/* @brief This variables will record if the priority_queue attach to other container
				instead of initialize.																	*/
	bool attach;

	/* @brief This variables will point to the container.												*/
	void *container;

	/* @brief This variables will point to the function address table of front container type.			*/
	struct container_control_s *container_control;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_ctrl;
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

	priority_queue_control_configuration_attach,

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
 * @param priority_queue the pointer to container adapter struct pointer
 * @param type the type of the container
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void priority_queue_control_configuration_init(priority_queue_stpp priority_queue,
											   enum container_type_e type,
											   container_size_t element_size,
											   generic_type_element_assign_t assign,
											   generic_type_element_free_t free)
{
	assert(priority_queue);
	assert(element_size);

	enum container_type_e
		adapt_container_type = PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	void
		*allocator = NULL;																		/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON);	/* Variables pointer to	the function address table of
																									specified allocator type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct priority_queue_s
		*priority_queue_alloced =
		(struct priority_queue_s *)allocator_ctrl->allocate(allocator,							/* Allocate #1 */
															1, sizeof(struct priority_queue_s));
																								/* Variables pointer to	the priority_queue struct which
																									will be allocate and assign to the priority_queue 	*/

	struct container_control_s
		*container_ctrl = NULL;

	void
		*container = NULL;																		/* Variables pointer to	the specified container struct */

	void
		*func_addr_table = container_control_convert_type_to_func_addr_table(adapt_container_type);
																								/* Variables pointer to	the function address table of
																									specified container type		*/

	container_ctrl = func_addr_table;

	if (NULL == priority_queue ||																/* Check if priority_queue point to NULL			*/
		NULL == priority_queue_alloced) {														/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	container_ctrl->configuration.init(&container, element_size, assign, free);					/* Initialize the specified container struct */

	priority_queue_alloced->container_type_id = STACK;											/* Assign priority_queue structure					*/
	priority_queue_alloced->attach = false;
	priority_queue_alloced->container = container;
	priority_queue_alloced->container_control = container_ctrl;
	priority_queue_alloced->allocator = allocator;
	priority_queue_alloced->allocator_ctrl = allocator_ctrl;

	*priority_queue = priority_queue_alloced;

	#if (STACK_CFG_DEBUG_EN)

	printf("init.priority_queue allocator : %p \r\n", allocator);								/* Debug only								*/
	printf("init.priority_queue block : %p \r\n", priority_queue_alloced);

	#endif // (STACK_CFG_DEBUG_EN)
}

/**
 * @brief This function will initialize the priority_queue struct and attach to the specified container.
 *
 * @param priority_queue the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

void priority_queue_control_configuration_attach(priority_queue_stpp priority_queue,
												 enum container_type_e type, void *container)
{
	assert(priority_queue);
	assert(container);
	assert(type);

	enum container_type_e
		adapt_container_type = PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	void
		*allocator = NULL;																		/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON);	/* Variables pointer to	the function address table of
																									specified allocator type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct priority_queue_s
		*priority_queue_alloced = (struct priority_queue_s *)
		allocator_ctrl->allocate(allocator,														/* Allocate #1 */
								 1, sizeof(struct priority_queue_s));
																								 /* Variables pointer to	the priority_queue struct which
																									 will be allocate and assign to the priority_queue 	*/

	void
		*func_addr_table = container_control_convert_type_to_func_addr_table(adapt_container_type);
																								/* Variables pointer to	the function address table of
																									specified container type		*/
	if (NULL == priority_queue ||																/* Check if priority_queue point to NULL			*/
		NULL == func_addr_table ||																/* Check if priority_queue point to NULL			*/
		NULL == priority_queue_alloced) {														/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	priority_queue_alloced->container_type_id = STACK;											/* Assign priority_queue structure					*/
	priority_queue_alloced->attach = true;
	priority_queue_alloced->container = container;
	priority_queue_alloced->container_control = func_addr_table;
	priority_queue_alloced->allocator = allocator;
	priority_queue_alloced->allocator_ctrl = allocator_ctrl;

	*priority_queue = priority_queue_alloced;

	#if (STACK_CFG_DEBUG_EN)

	printf("init.priority_queue block : %p \r\n", priority_queue_alloced);						/* Debug only								*/

	#endif // (STACK_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the priority_queue struct.
 *
 * @param priority_queue the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void priority_queue_control_configuration_destroy(priority_queue_stpp priority_queue)
{
	assert(priority_queue);

	#if (STACK_CFG_DEBUG_EN)

	printf("destroy.priority_queue container : %p \r\n", (*priority_queue)->container);
	printf("destroy.priority_queue allocator : %p \r\n", (*priority_queue)->allocator);
	printf("destroy.priority_queue block : %p \r\n", (*priority_queue));

	#endif // (STACK_CFG_DEBUG_EN)

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void
		*allocator = (*priority_queue)->allocator;;											/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = (*priority_queue)->allocator_ctrl;

	(*priority_queue)->container_control->configuration.
		destroy(&(*priority_queue)->container);												/* Destroy the container */

	allocator_ctrl->deallocate(allocator, (*priority_queue), 1);							/* Deallocate #2 */

	(*priority_queue)->container_type_id = 0u;
	(*priority_queue)->attach = false;
	(*priority_queue)->container = NULL;
	(*priority_queue)->container_control = NULL;
	(*priority_queue)->allocator = NULL;

	allocator_ctrl->configuration.destroy(&allocator);

	*priority_queue = NULL;
}

/**
 * @brief This function will return reference to the top element in the priority_queue.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *priority_queue_control_element_access_top(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return priority_queue->container_control->element_access.								/* Get the back element of the container */
		at(priority_queue->container,
		   priority_queue->container_control->capacity.
		   size(priority_queue->container) - 1);
}

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param priority_queue the pointer to container adapter struct
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
 * @brief This function will returns the number of elements in the container.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t priority_queue_control_capacity_size(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	#if (STACK_CFG_DEBUG_EN)

	printf("priority_queue.size : %d \r\n", priority_queue->container_control->capacity.size(priority_queue->container));

	#endif // (STACK_CFG_DEBUG_EN)

	return priority_queue->container_control->capacity.size(priority_queue->container);		/* Get the number of elements in the container */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container is able to hold due to system or library implementation limitations.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t priority_queue_control_capacity_max_size(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	return priority_queue->container_control->capacity.max_size(priority_queue->container);	/* Get the maximum number of elements the container
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the top of the priority_queue.
 *
 * @param priority_queue the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

void priority_queue_control_modifiers_push(priority_queue_stp priority_queue, void *source)
{
	assert(priority_queue);

	priority_queue->container_control->modifiers.insert(priority_queue->container,			/* Insert the given element source to the back of the container */
														priority_queue->container_control->capacity.size(priority_queue->container), 1, &source);

	if (NULL != priority_queue->container_control->list_operations.sort) {					/* If the container have sort prototype */
		priority_queue->container_control->list_operations.sort(priority_queue->container,
																compare_control_greater);
	} else {
		while (true) {
		// TODO ...,if enter here please wait further update, or you can fix it, thanks.
		}
	}
}

/**
 * @brief This function will push a new element on top of the priority_queue. The element is constructed in-place.
 *
 * @param priority_queue the pointer to container adapter struct
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
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_pop(priority_queue_stp priority_queue)
{
	assert(priority_queue);

	priority_queue->container_control->modifiers.earse(priority_queue->container,			/* Earse back element of the container. */
													   priority_queue->container_control->capacity.
													   size(priority_queue->container) - 1);
}

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param priority_queue the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_swap(priority_queue_stpp priority_queue, priority_queue_stpp other)
{
	assert(priority_queue);

	(*priority_queue)->container_control->modifiers.swap(&(*priority_queue)->container, &(*other)->container);/* exchange the contents of the container adaptor with those of other */
}

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_copy(priority_queue_stpp destination, priority_queue_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control->modifiers.copy(&(*destination)->container, source->container);		/* copy the contents of the container adaptor to those of other */
}