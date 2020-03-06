/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "stack.h"

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

#if (STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This type will contain all the stack control functions.
 */

struct stack_control_s stack_ctrl =
{
	.configuration.init = stack_control_configuration_init,
	.configuration.adapt = stack_control_configuration_adapt,
	.configuration.destroy = stack_control_configuration_destroy,

	.element_access.top = stack_control_element_access_top,

	.capacity.empty = stack_control_capacity_empty,
	.capacity.size = stack_control_capacity_size,
	.capacity.max_size = stack_control_capacity_max_size,

	.modifiers.push = stack_control_modifiers_push,
	.modifiers.emplace = stack_control_modifiers_emplace,
	.modifiers.pop = stack_control_modifiers_pop,
	.modifiers.swap = stack_control_modifiers_swap,
	.modifiers.copy = stack_control_modifiers_copy
};

#endif // (STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct is the stack allocate package
 */

struct container_allocte_package_s
	stack_control_allocate_package = {
.allocator_type = STACK_CFG_ALLOCATOR_TYPE ,
.container_mem_size = sizeof(struct container_adaptor_s)
};

/**
 * @brief This struct is the stack adapt package
 */

struct container_adaptor_adapt_package_s
	stack_control_adapt_package = { 0 };

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
 * @brief This function will initialize the stack struct and the specified container_ptr.
 *
 * @param stack the pointer to container_ptr adapter struct pointer
 * @param type the type of the container_ptr
 * @param element_size the pointer to container_ptr
 * @param string_type the pointer to container_ptr
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t stack_control_configuration_init(stack_stpp stack,
										 enum container_type_e container_type,
										 container_size_t element_size,
										 generic_type_element_assign_t assign,
										 generic_type_element_free_t free)
{
	assert(stack);
	assert(element_size);

	if (container_type) {
		container_type = PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;
	}

	stack_control_allocate_package.arg_list_ptr = NULL;										/* Set the allocate package */

	stack_control_adapt_package.container_ptr = NULL;										/* Set the adapt package */
	stack_control_adapt_package.container_type = container_type;
	stack_control_adapt_package.element_size = element_size;
	stack_control_adapt_package.assign_ptr = assign;
	stack_control_adapt_package.free_ptr = free;

	if (container_adaptor_control_configuration_init(stack,									/* Initialize the container adaptor */
													 STACK,
													 stack_control_allocate_package,
													 stack_control_adapt_package)) {
		return 1;
	}

	return 0;
}

/**
 * @brief This function will initialize the stack struct and attach to the specified container_ptr.
 *
 * @param stack the pointer to container_ptr adapter struct pointer
 * @param container_ptr the pointer to container_ptr pointer
 * @param func_addr_table the pointer to the function address table of the specified container_ptr
 *
 * @return NONE
 */

errno_t stack_control_configuration_adapt(stack_stpp stack,
										  void *container)
{
	assert(stack);
	assert(container);

	stack_control_allocate_package.arg_list_ptr = NULL;										/* Set the allocate package */

	stack_control_adapt_package.container_ptr = container;									/* Set the adapt package */

	if (container_adaptor_control_configuration_init(stack,									/* Initialize the container adaptor */
													 STACK,
													 stack_control_allocate_package,
													 stack_control_adapt_package)) {
		return 1;
	}

	return 0;
}

/**
 * @brief This function will destroy the stack struct.
 *
 * @param stack the pointer to container_ptr adapter struct pointer
 *
 * @return NONE
 */

extern inline errno_t
stack_control_configuration_destroy(stack_stpp stack)
{
	assert(stack);
	assert(*stack);

	return container_adaptor_control_configuration_destroy(stack);						    /* Destroy the container adaptor */
}

/**
 * @brief This function will return reference to the top element in the stack.
 *
 * @param stack the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

void *stack_control_element_access_top(stack_stp stack)
{
	assert(stack);

	return stack->container_control_ptr->element_access
		.at(stack->container_ptr,															/* Access the specified element of the stack */
			stack->container_control_ptr->capacity.size(stack->container_ptr) - 1);
}

/**
 * @brief This function will check if the underlying container_ptr has no elements.
 *
 * @param stack the pointer to container_ptr adapter struct
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
 * @brief This function will returns the number of elements in the container_ptr.
 *
 * @param stack the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_size(stack_stp stack)
{
	assert(stack);

	#if (STACK_CFG_DEBUG_EN)

	printf("stack.size : %d \r\n", stack->container_control_ptr->capacity.size(stack->container_ptr));

	#endif // (STACK_CFG_DEBUG_EN)

	return stack->container_control_ptr->capacity.size(stack->container_ptr);				/* Get the number of elements in the container_ptr */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container_ptr is able to hold due to system or library implementation limitations.
 *
 * @param stack the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_max_size(stack_stp stack)
{
	assert(stack);

	return stack->container_control_ptr->capacity.max_size(stack->container_ptr);			/* Get the maximum number of elements the container_ptr
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the top of the stack.
 *
 * @param stack the pointer to container_ptr adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

errno_t stack_control_modifiers_push(stack_stp stack, void *source)
{
	assert(stack);

	stack->container_control_ptr->modifiers
		.insert(stack->container_ptr,														/* Insert the given element source to the top of the stack */
				stack->container_control_ptr->capacity.size(stack->container_ptr), 1, &source);

	return 0;
}

/**
 * @brief This function will push a new element on top of the stack. The element is constructed in-place.
 *
 * @param stack the pointer to container_ptr adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

errno_t stack_control_modifiers_emplace(stack_stp stack, void *destination)
{
	assert(stack);

	return 0;
}

/**
 * @brief This function will remove the top element from the stack.
 *
 * @param stack the pointer to container_ptr adapter struct
 *
 * @return NONE
 */

errno_t stack_control_modifiers_pop(stack_stp stack)
{
	assert(stack);

	stack->container_control_ptr->modifiers
		.earse(stack->container_ptr,
			   stack_control_capacity_size(stack) - 1);										/* Earse the top element of the stack */

	return 0;
}

/**
 * @brief This function will exchange the contents of the container_ptr adaptor with those of other.
 *
 * @param stack the pointer to container_ptr adapter struct
 * @param other the pointer to other container_ptr adapter struct
 *
 * @return NONE
 */

errno_t stack_control_modifiers_swap(stack_stpp stack, stack_stpp other)
{
	assert(stack);

	(*stack)->container_control_ptr->modifiers
		.swap(&(*stack)->container_ptr, &(*other)->container_ptr);							/* exchange the contents of the container_ptr adaptor with those of other */

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

errno_t stack_control_modifiers_copy(stack_stpp destination, stack_stp source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control_ptr->modifiers
		.copy(&(*destination)->container_ptr, source->container_ptr);						/* copy the contents of the container_ptr adaptor to those of other */

	return 0;
}