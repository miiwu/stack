/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This STACK definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __STACK_H
#define __STACK_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "container_adaptor_def.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    if enable integrated structure.                                                         */
#define STACK_CFG_DEFAULT_ADAPT_CONTAINER_TYPE			        VECTOR

/* Configure    the type of allocator.                                                                  */
#define STACK_CFG_ALLOCATOR_TYPE                                ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN			        1u

/* Configure    if enable stack debug.																    */
#define STACK_CFG_DEBUG_EN										0u

/*
*********************************************************************************************************
*									        DATA TYPES
*********************************************************************************************************
*/

/* Configure    stack type.                                                                             */
typedef struct stack_s
*stack_stp,
**stack_stpp;

/**
 * @brief This type will contain all the stack control functions.
 */

struct stack_control_s {
	struct {
		/* @brief This function will initialize the stack struct and the specified container.           */
		void (*init)(stack_stpp stack,
					 enum container_type_e type,
					 container_size_t element_size,
					 generic_type_element_assign_t assign,
					 generic_type_element_free_t free);

		/* @brief This function will initialize the stack struct and attach to the specified container. */
		void (*attach)(stack_stpp stack,
					   enum container_type_e type, void *container);

		/* @brief This function will destroy the stack struct.                                          */
		void (*destroy)(stack_stpp stack);
	}configuration;

	struct {
		/* @brief This function will return reference to the top element in the stack.                  */
		void *(*top)(stack_stp stack);
	}element_access;

	struct {
		/* @brief This function will check if the underlying container has no elements.                 */
		bool(*empty)(stack_stp stack);

		/* @brief This function will returns the number of elements in the container.                   */
		size_t(*size)(stack_stp stack);

		/* @brief This function will returns the maximum number of elements
					the container is able to hold due to system or library implementation limitations.  */
		size_t(*max_size)(stack_stp stack);
	}capacity;

	struct {
		/* @brief This function will push the given element source to the top of the stack.             */
		void (*push)(stack_stp stack,
					 void *source);

		/* @brief This function will push a new element on top of the stack.
					The element is constructed in-place.                                                */
		void (*emplace)(stack_stp stack,
						void *destination);

		/* @brief This function will remove the top element from the stack.                             */
		void (*pop)(stack_stp stack);

		/* @brief This function will exchange the contents of the container adaptor with those of other.*/
		void (*swap)(stack_stpp stack,
					 stack_stpp other);

		/* @brief This function will erase the specified elements from the container.                   */
		void (*copy)(stack_stpp destination,
					 stack_stp source);
	}modifiers;
};

/*
*********************************************************************************************************
*								        FUNCTION PROTOTYPES
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
									  generic_type_element_free_t free);

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
										enum container_type_e type, void *container);

 /**
  * @brief This function will destroy the stack struct
  *
  * @param stack the pointer to container adapter struct pointer
  *
  * @return NONE
  */

void stack_control_configuration_destroy(stack_stpp stack);

/**
 * @brief This function will return reference to the top element in the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void *stack_control_element_access_top(stack_stp stack);

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_size(stack_stp stack);

/**
 * @brief This function will push the given element source to the top of the stack.
 *
 * @param stack the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

bool stack_control_capacity_empty(stack_stp stack);

/**
 * @brief This function will return the number of elements in the underlying container.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_max_size(stack_stp stack);

void stack_control_modifiers_push(stack_stp stack, void *source);

/**
 * @brief This function will push a new element on top of the stack. The element is constructed in-place.
 *
 * @param stack the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void stack_control_modifiers_emplace(stack_stp stack, void *destination);

/**
 * @brief This function will remove the top element from the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_pop(stack_stp stack);

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param stack the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_swap(stack_stpp stack, stack_stpp other);

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_copy(stack_stpp destination, stack_stp source);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This type will contain all the stack control functions.
 */

extern struct stack_control_s stack_ctrl;

#endif // (STACK_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__STACK_H