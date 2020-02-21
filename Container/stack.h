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

#include "container_def.h"

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
#define STACK_CFG_INTERGRATED_STRUCTURE_MODE_EN			        1u

/* Configure    if enable stack debug.																    */
#define STACK_CFG_DEBUG_EN										0u

/*
*********************************************************************************************************
*									        DATA TYPES
*********************************************************************************************************
*/

/* Configure    vector ptr type.                                                                        */
typedef struct stack_s *STACK_TYPEDEF_PTR;

/* Configure    vector pptr type.                                                                       */
typedef struct stack_s **STACK_TYPEDEF_PPTR;

struct stack_control_s {
	struct {
		/* @brief This function will initialize the stack struct and the specified container. */
		void (*init)(STACK_TYPEDEF_PPTR stack,
					 enum container_type_e type,
					 container_size_t element_size,
					 void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will initialize the stack struct and attach to the specified container. */
		void (*attach)(STACK_TYPEDEF_PPTR stack,
					   enum container_type_e type, void *container);

		/* @brief This function will destroy the stack struct. */
		void (*destroy)(STACK_TYPEDEF_PPTR stack);
	}configuration;

	struct {
		/* @brief This function will return reference to the top element in the stack. */
		void *(*top)(STACK_TYPEDEF_PTR stack);
	}element_access;

	struct {
		/* @brief This function will check if the underlying container has no elements. */
		bool(*empty)(STACK_TYPEDEF_PTR stack);

		/* @brief This function will returns the number of elements in the container. */
		size_t(*size)(STACK_TYPEDEF_PTR stack);

		/* @brief This function will returns the maximum number of elements
					the container is able to hold due to system or library implementation limitations. */
		size_t(*max_size)(STACK_TYPEDEF_PTR stack);
	}capacity;

	struct {
		/* @brief This function will push the given element source to the top of the stack. */
		void (*push)(STACK_TYPEDEF_PTR stack,
					 void *source);

		/* @brief This function will push a new element on top of the stack. The element is constructed in-place. */
		void (*emplace)(STACK_TYPEDEF_PTR stack,
						void *destination);

		/* @brief This function will remove the top element from the stack. */
		void (*pop)(STACK_TYPEDEF_PTR stack);

		/* @brief This function will exchange the contents of the container adaptor with those of other. */
		void (*swap)(STACK_TYPEDEF_PPTR stack,
					 STACK_TYPEDEF_PPTR other);

		/* @brief This function will erase the specified elements from the container. */
		void (*copy)(STACK_TYPEDEF_PPTR destination,
					 STACK_TYPEDEF_PTR source);
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

void stack_control_configration_init(STACK_TYPEDEF_PPTR stack,
									 enum container_type_e type,
									 container_size_t element_size,
									 void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will initialize the stack struct and attach to the specified container.
 *
 * @param stack the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

void stack_control_configration_attach(STACK_TYPEDEF_PPTR stack,
									   enum container_type_e type, void *container);

/**
 * @brief This function will destroy the stack struct
 *
 * @param stack the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void stack_control_configration_destroy(STACK_TYPEDEF_PPTR stack);

/**
 * @brief This function will return reference to the top element in the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void *stack_control_element_access_top(STACK_TYPEDEF_PTR stack);

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

container_size_t stack_control_capacity_size(STACK_TYPEDEF_PTR stack);

/**
 * @brief This function will push the given element source to the top of the stack.
 *
 * @param stack the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

bool stack_control_capacity_empty(STACK_TYPEDEF_PTR stack);

/**
 * @brief This function will return the number of elements in the underlying container.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t stack_control_capacity_max_size(STACK_TYPEDEF_PTR stack);

void stack_control_modifiers_push(STACK_TYPEDEF_PTR stack, void *source);

/**
 * @brief This function will push a new element on top of the stack. The element is constructed in-place.
 *
 * @param stack the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void stack_control_modifiers_emplace(STACK_TYPEDEF_PTR stack, void *destination);

/**
 * @brief This function will remove the top element from the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_pop(STACK_TYPEDEF_PTR stack);

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param stack the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_swap(STACK_TYPEDEF_PPTR stack, STACK_TYPEDEF_PPTR other);

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_copy(STACK_TYPEDEF_PPTR destination, STACK_TYPEDEF_PTR source);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

extern struct stack_control_s stack_ctrl;

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__STACK_H