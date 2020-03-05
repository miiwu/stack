/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_DEFINATION_H
#define __CONTAINER_DEFINATION_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

#include "container_cfg.h"

/*
*********************************************************************************************************
*												DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*									         DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This typedef is the container size type
 */

typedef CONTAINER_GLOBAL_CFG_SIZE_TYPE container_size_t;

/**
 * @brief This enum is the container's category enums
 */

enum container_category_e {
	SEQUENCE_CONTAINERS = 0x10,

	ASSOCIATIVE_CONTAINERS = 0x20,

	UNORDERED_ASSOCIATIVE_CONTAINERS = 0x30,

	CONTAINERS_ADAPTORS = 0x40,

	SPAN = 0x50,
};

/**
 * @brief This enum is the container's type enums
 */

enum container_type_e {
	ARRAY = SEQUENCE_CONTAINERS,
	VECTOR,
	DEQUE,
	FORWARD_LIST,
	LIST,

	SET = ASSOCIATIVE_CONTAINERS,
	MAP,

	UNORDERED_SET = UNORDERED_ASSOCIATIVE_CONTAINERS,

	STACK = CONTAINERS_ADAPTORS,
	QUEUE,
	PRIORITY_QUEUE,
};

/**
 * @brief This struct is the container's common information
 */

struct container_common_information_s {
	/* @brief This variables will record the size that each element will take up.						*/
	container_size_t mem_size;

	/* @brief This variables will record the maximum number of elements.								*/
	container_size_t max_size;

	/* @brief This variables will record the number of elements that
			  the container has currently allocated space for.											*/
	container_size_t size;
};

/**
 * @brief This type is the assign method typedef of the generic type element.
 */

typedef errno_t(*generic_type_element_assign_t)(void *gnc, void *src);

/**
 * @brief This type is the free method typedef of the generic type element.
 */

typedef errno_t(*generic_type_element_free_t)(void *gnc);

/**
 * @brief This struct is the container's generic element handler
 */

struct container_generic_type_element_handler_s {
	/* @brief This variables will point to the address of the vector element assign handler.			*/
	generic_type_element_assign_t assign;

	/* @brief This variables will point to the address of the vector element free handler.				*/
	generic_type_element_free_t free;
};

/**
 * @brief This struct is the container's common exception
 */

struct container_common_exception_s {
	/* @brief This variables will point to the address of the list empty exception handler.				*/
	void (*empty)(void);

	/* @brief This variables will point to the address of the list full exception handler.				*/
	void (*full)(void);
};

/**
 * @brief This struct is the init return package of _configration_init().
 */

struct container_control_configuration_allocate_return_s {
	errno_t error;

	/* @brief This variables will point to the allocator_ptr control.										*/
	struct allocator_control_s *allocator_control_ptr;

	/* @brief This variables will point to the allocator_ptr.												*/
	void *allocator_ptr;

	/* @brief This variables will be a external addon, validity only depends on memory allocation.		*/
	char addon[0];
};

/**
 * @brief This struct is the adapt return package of configuration_adapt().
 */

struct container_allocte_package_s {
	enum allocator_type_e allocator_type;
	container_size_t container_mem_size;
	void *arg_list;
};

/**
 * @brief This struct is the container's common control
 */

struct container_control_s {
	struct {
		/* @brief This function will initialize the container struct and the specified container.		*/
		errno_t(*init)(void **container,
					   container_size_t element_size,
					   generic_type_element_assign_t assign,
					   generic_type_element_free_t free);

		/* @brief This function will destroy the container struct. */
		errno_t(*destroy)(void **container);
	}configuration;

	struct {
		/* @brief This function will returns a reference to the element
					at specified location position, with bounds checking.								*/
		void *(*at)(void *container, container_size_t position);
	}element_access;

	struct {
		/* @brief This function will check if the underlying container has no elements.					*/
		bool(*empty)(void *container);

		/* @brief This function will returns the number of elements in the container.					*/
		size_t(*size)(void *container);

		/* @brief This function will returns the maximum number of elements
					the container is able to hold due to system or library implementation limitations.	*/
		size_t(*max_size)(void *container);
	}capacity;

	struct {
		/* @brief This function will inserts elements at the specified location in the container.		*/
		void (*insert)(void *container,
					   container_size_t position,
					   container_size_t amount, void **source);

		/* @brief This function will erases the specified elements from the container.                  */
		void (*earse)(void *container,
					  container_size_t position);

	   /* @brief This function will exchange the contents of the container adaptor with those of other. */
		void (*swap)(void **container,
					 void **other);

		/* @brief This function will erase the specified elements from the container.					*/
		void (*copy)(void **destination,
					 void *source);
	}modifiers;

	struct {
		/* @brief This function will sorts the elements of the container in ascending order.			*/
		void (*sort)(void *container,
					 compare_t *comp);
	}list_operations;
};

/*
*********************************************************************************************************
*								        FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the container.
 *
 * @param void
 *
 * @return void
 */

struct container_control_configuration_allocate_return_s
	container_control_configuration_allocate(void **container,
											 struct container_allocte_package_s package);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__CONTAINER_DEFINATION_H