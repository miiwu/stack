/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "queue.h"

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
 * @brief This struct is the queue structure module
 */

struct queue_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e	container_type_id;

	/* @brief This variables will record if the queue attach to other container instead of initialize.	*/
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

/**
 * @brief This type will contain all the queue control functions.
 */

struct queue_control_t queue_ctrl =
{
	queue_control_configuration_init,

	queue_control_configuration_attach,

	queue_control_configuration_destroy,

	queue_control_element_access_front,

	queue_control_element_access_back,

	queue_control_capacity_empty,

	queue_control_capacity_size,

	queue_control_capacity_max_size,

	queue_control_modifiers_push,

	queue_control_modifiers_emplace,

	queue_control_modifiers_pop,

	queue_control_modifiers_swap,

	queue_control_modifiers_copy
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
 * @brief This function will initialize the queue struct and the specified container.
 *
 * @param queue the pointer to container adapter struct pointer
 * @param type the type of the container
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void queue_control_configuration_init(queue_stpp queue,
									  enum container_type_e type,
									  container_size_t element_size,
									  generic_type_element_assign_t assign,
									  generic_type_element_free_t free)
{
	assert(queue);
	assert(element_size);

	enum container_type_e
		adapt_container_type = QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	void
		*allocator = NULL;																		/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON);	/* Variables pointer to	the function address table of
																									specified allocator type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct queue_s
		*queue_alloced = (struct queue_s *)allocator_ctrl->allocate(allocator,					/* Allocate #1 */
																	1, sizeof(struct queue_s));
																								/* Variables pointer to	the queue struct which
																									will be allocate and assign to the queue 	*/

	struct container_control_s
		*container_ctrl = NULL;

	void
		*container = NULL;																		/* Variables pointer to	the specified container struct */

	void
		*func_addr_table = container_adaptor_control_get_container_func_addr_table(adapt_container_type);
																								/* Variables pointer to	the function address table of
																									specified container type		*/

	container_ctrl = func_addr_table;

	if (NULL == queue ||																		/* Check if queue point to NULL			*/
		NULL == queue_alloced) {																/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	container_ctrl->configuration.init(&container, element_size, assign, free);					/* Initialize the specified container struct */

	queue_alloced->container_type_id = QUEUE;													/* Assign queue structure					*/
	queue_alloced->attach = false;
	queue_alloced->container = container;
	queue_alloced->container_control = container_ctrl;
	queue_alloced->allocator = allocator;
	queue_alloced->allocator_ctrl = allocator_ctrl;

	*queue = queue_alloced;

	#if (QUEUE_CFG_DEBUG_EN)

	printf("init.queue allocator : %p \r\n", allocator);										/* Debug only								*/
	printf("init.queue block : %p \r\n", queue_alloced);

	#endif // (QUEUE_CFG_DEBUG_EN)
}

/**
 * @brief This function will initialize the queue struct and attach to the specified container.
 *
 * @param queue the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

void queue_control_configuration_attach(queue_stpp queue,
										enum container_type_e type, void *container)
{
	assert(queue);
	assert(container);
	assert(type);

	enum container_type_e
		adapt_container_type = QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	void
		*allocator = NULL;																		/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON);	/* Variables pointer to	the function address table of
																									specified allocator type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct queue_s
		*queue_alloced = (struct queue_s *)allocator_ctrl->allocate(allocator,					/* Allocate #1 */
																	1, sizeof(struct queue_s));
																								/* Variables pointer to	the queue struct which
																									will be allocate and assign to the queue 	*/

	void
		*func_addr_table = container_adaptor_control_get_container_func_addr_table(adapt_container_type);
																								/* Variables pointer to	the function address table of
																									specified container type		*/
	if (NULL == queue ||																	/* Check if queue point to NULL			*/
		NULL == func_addr_table ||															/* Check if queue point to NULL			*/
		NULL == queue_alloced) {															/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	queue_alloced->container_type_id = QUEUE;												/* Assign queue structure					*/
	queue_alloced->attach = true;
	queue_alloced->container = container;
	queue_alloced->container_control = func_addr_table;
	queue_alloced->allocator = allocator;
	queue_alloced->allocator_ctrl = allocator_ctrl;

	*queue = queue_alloced;

	#if (QUEUE_CFG_DEBUG_EN)

	printf("init.queue block : %p \r\n", queue_alloced);									/* Debug only								*/

	#endif // (QUEUE_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the queue struct.
 *
 * @param queue the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void queue_control_configuration_destroy(queue_stpp queue)
{
	assert(queue);

	#if (QUEUE_CFG_DEBUG_EN)

	printf("destroy.queue container : %p \r\n", (*queue)->container);
	printf("destroy.queue allocator : %p \r\n", (*queue)->allocator);
	printf("destroy.queue block : %p \r\n", (*queue));

	#endif // (QUEUE_CFG_DEBUG_EN)

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void
		*allocator = (*queue)->allocator;;																	/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = (*queue)->allocator_ctrl;

	(*queue)->container_control->configuration.destroy(&(*queue)->container);				/* Destroy the container */

	allocator_ctrl->deallocate(allocator, (*queue), 1);										/* Deallocate #2 */

	(*queue)->container_type_id = 0u;
	(*queue)->attach = false;
	(*queue)->container = NULL;
	(*queue)->container_control = NULL;
	(*queue)->allocator = NULL;

	allocator_ctrl->configuration.destroy(&allocator);

	*queue = NULL;
}

/**
 * @brief This function will return reference to the first element in the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_front(queue_stp queue)
{
	assert(queue);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return queue->container_control->element_access.at(queue->container,
													   0);
																							/* Get the top element of the container */
}

/**
 * @brief This function will return reference to the last element in the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_back(queue_stp queue)
{
	assert(queue);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return queue->container_control->element_access.at(queue->container,
													   queue->container_control->capacity.size(queue->container) - 1);
																							/* Get the top element of the container */
}

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param queue the pointer to container adapter struct
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
 * @brief This function will returns the number of elements in the container.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t queue_control_capacity_size(queue_stp queue)
{
	assert(queue);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	#if (QUEUE_CFG_DEBUG_EN)

	printf("queue.size : %d \r\n", queue->container_control->capacity.size(queue->container));

	#endif // (QUEUE_CFG_DEBUG_EN)

	return queue->container_control->capacity.size(queue->container);						/* Get the number of elements in the container */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container is able to hold due to system or library implementation limitations.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t queue_control_capacity_max_size(queue_stp queue)
{
	assert(queue);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return queue->container_control->capacity.max_size(queue->container);					/* Get the maximum number of elements the container
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the bottom of the queue.
 *
 * @param queue the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

void queue_control_modifiers_push(queue_stp queue, void *source)
{
	assert(queue);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	queue->container_control->modifiers.insert(queue->container,
											   queue->container_control->capacity.size(queue->container), 1, &source);
																							/* push the given element source to the top of the queue */
}

/**
 * @brief This function will push a new element on bottom of the queue. The element is constructed in-place.
 *
 * @param queue the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void queue_control_modifiers_emplace(queue_stp queue, void *destination)
{
	assert(queue);
}

/**
 * @brief This function will remove the top element from the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_pop(queue_stp queue)
{
	assert(queue);

	queue->container_control->modifiers.earse(queue->container,
											  0);											/* pop the top element */
}

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param queue the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_swap(queue_stpp queue, queue_stpp other)
{
	assert(queue);

	(*queue)->container_control->modifiers.swap(&(*queue)->container, &(*other)->container);/* exchange the contents of the container adaptor with those of other */
}

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_copy(queue_stpp destination, queue_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control->modifiers.copy(&(*destination)->container, source->container);		/* copy the contents of the container adaptor to those of other */
}