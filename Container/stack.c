/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "stack.h"

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
 * @brief This struct is the stack structure module
 */

struct stack_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e	container_type_id;

	/* @brief This variables will record if the stack attach to other container instead of initialize.	*/
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

#if (STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This type will contain all the stack control functions.
 */

struct stack_control_s stack_ctrl =
{
	stack_control_configuration_init,

	stack_control_configuration_attach,

	stack_control_configuration_destroy,

	stack_control_element_access_top,

	stack_control_capacity_empty,

	stack_control_capacity_size,

	stack_control_capacity_max_size,

	stack_control_modifiers_push,

	stack_control_modifiers_emplace,

	stack_control_modifiers_pop,

	stack_control_modifiers_swap,

	stack_control_modifiers_copy
};

#endif // (STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN)

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
 * @brief This function will initialize the stack struct and the specified container.
 *
 * @param stack the pointer to container adapter struct pointer
 * @param type the type of the container
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void stack_control_configuration_init(stack_stpp stack,
									  enum container_type_e type,
									  container_size_t element_size,
									  generic_type_element_assign_t assign,
									  generic_type_element_free_t free)
{
	assert(stack);
	assert(element_size);

	enum container_type_e
		adapt_container_type = STACK_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	void
		*allocator = NULL;																		/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON);	/* Variables pointer to	the function address table of
																									specified allocator type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct stack_s
		*stack_alloced = (struct stack_s *)allocator_ctrl->allocate(allocator,					/* Allocate #1 */
																	1, sizeof(struct stack_s));
																								/* Variables pointer to	the stack struct which
																									will be allocate and assign to the stack 	*/

	struct container_control_s
		*container_ctrl = NULL;

	void
		*container = NULL;																		/* Variables pointer to	the specified container struct */

	void
		*func_addr_table = container_adaptor_control_get_container_func_addr_table(adapt_container_type);
																								/* Variables pointer to	the function address table of
																									specified container type		*/

	container_ctrl = func_addr_table;

	if (NULL == stack ||																		/* Check if stack point to NULL			*/
		NULL == stack_alloced) {																/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	container_ctrl->configuration.init(&container, element_size, assign, free);					/* Initialize the specified container struct */

	stack_alloced->container_type_id = STACK;													/* Assign stack structure					*/
	stack_alloced->attach = false;
	stack_alloced->container = container;
	stack_alloced->container_control = container_ctrl;
	stack_alloced->allocator = allocator;
	stack_alloced->allocator_ctrl = allocator_ctrl;

	*stack = stack_alloced;

	#if (STACK_CFG_DEBUG_EN)

	printf("init.stack allocator : %p \r\n", allocator);										/* Debug only								*/
	printf("init.stack block : %p \r\n", stack_alloced);

	#endif // (STACK_CFG_DEBUG_EN)
}

/**
 * @brief This function will initialize the stack struct and attach to the specified container.
 *
 * @param stack the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

void stack_control_configuration_attach(stack_stpp stack,
										enum container_type_e type, void *container)
{
	assert(stack);
	assert(container);
	assert(type);

	enum container_type_e
		adapt_container_type = STACK_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	void
		*allocator = NULL;																		/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_COMMON);	/* Variables pointer to	the function address table of
																									specified allocator type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct stack_s
		*stack_alloced = (struct stack_s *)allocator_ctrl->allocate(allocator,					/* Allocate #1 */
																	1, sizeof(struct stack_s));
																								/* Variables pointer to	the stack struct which
																									will be allocate and assign to the stack 	*/

	void
		*func_addr_table = container_adaptor_control_get_container_func_addr_table(adapt_container_type);
																								/* Variables pointer to	the function address table of
																									specified container type		*/
	if (NULL == stack ||																	/* Check if stack point to NULL			*/
		NULL == func_addr_table ||															/* Check if stack point to NULL			*/
		NULL == stack_alloced) {															/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	stack_alloced->container_type_id = STACK;												/* Assign stack structure					*/
	stack_alloced->attach = true;
	stack_alloced->container = container;
	stack_alloced->container_control = func_addr_table;
	stack_alloced->allocator = allocator;
	stack_alloced->allocator_ctrl = allocator_ctrl;

	*stack = stack_alloced;

	#if (STACK_CFG_DEBUG_EN)

	printf("init.stack block : %p \r\n", stack_alloced);									/* Debug only								*/

	#endif // (STACK_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the stack struct.
 *
 * @param stack the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void stack_control_configuration_destroy(stack_stpp stack)
{
	assert(stack);

	#if (STACK_CFG_DEBUG_EN)

	printf("destroy.stack container : %p \r\n", (*stack)->container);
	printf("destroy.stack allocator : %p \r\n", (*stack)->allocator);
	printf("destroy.stack block : %p \r\n", (*stack));

	#endif // (STACK_CFG_DEBUG_EN)

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void
		*allocator = (*stack)->allocator;;																	/* Variables pointer to	the allocator struct */

	struct allocator_control_s
		*allocator_ctrl = (*stack)->allocator_ctrl;

	(*stack)->container_control->configuration.destroy(&(*stack)->container);				/* Destroy the container */

	allocator_ctrl->deallocate(allocator, (*stack), 1);										/* Deallocate #2 */

	(*stack)->container_type_id = 0u;
	(*stack)->attach = false;
	(*stack)->container = NULL;
	(*stack)->container_control = NULL;
	(*stack)->allocator = NULL;

	allocator_ctrl->configuration.destroy(&allocator);

	*stack = NULL;
}

/**
 * @brief This function will return reference to the top element in the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void *stack_control_element_access_top(stack_stp stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return stack->container_control->element_access.at(stack->container,
													   stack->container_control->capacity.size(stack->container) - 1);
																							/* Get the top element of the container */
}

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

bool stack_control_capacity_empty(stack_stp stack)
{
	assert(stack);

	if (((container_size_t)stack_control_capacity_size(stack)) <=
		((container_size_t)stack_control_capacity_max_size(stack))) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_size(stack_stp stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	#if (STACK_CFG_DEBUG_EN)

	printf("stack.size : %d \r\n", stack->container_control->capacity.size(stack->container));

	#endif // (STACK_CFG_DEBUG_EN)

	return stack->container_control->capacity.size(stack->container);						/* Get the number of elements in the container */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container is able to hold due to system or library implementation limitations.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_max_size(stack_stp stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return stack->container_control->capacity.max_size(stack->container);					/* Get the maximum number of elements the container
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the top of the stack.
 *
 * @param stack the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

void stack_control_modifiers_push(stack_stp stack, void *source)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	stack->container_control->modifiers.insert(stack->container,
											   stack->container_control->capacity.size(stack->container), 1, &source);
																							/* push the given element source to the top of the stack */
}

/**
 * @brief This function will push a new element on top of the stack. The element is constructed in-place.
 *
 * @param stack the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void stack_control_modifiers_emplace(stack_stp stack, void *destination)
{
	assert(stack);
}

/**
 * @brief This function will remove the top element from the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_pop(stack_stp stack)
{
	assert(stack);

	stack->container_control->modifiers.earse(stack->container,
											  stack_control_capacity_size(stack) - 1); /* push the given element source to the top of the stack */
}

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param stack the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_swap(stack_stpp stack, stack_stpp other)
{
	assert(stack);

	(*stack)->container_control->modifiers.swap(&(*stack)->container, &(*other)->container);/* exchange the contents of the container adaptor with those of other */
}

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_copy(stack_stpp destination, stack_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control->modifiers.copy(&(*destination)->container, source->container);		/* copy the contents of the container adaptor to those of other */
}