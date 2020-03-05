/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __PRIORITY_PRIORITY_QUEUE_H
#define __PRIORITY_PRIORITY_QUEUE_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"
#include "container_adaptor_def.h"

/*
*********************************************************************************************************
*									     CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    if enable integrated structure.                                                         */
#define PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE						FORWARD_LIST

/* Configure    the type of allocator.                                                                  */
#define PRIORITY_QUEUE_CFG_ALLOCATOR_TYPE									ALLOCATOR_COMMON

/* Configure    the type of sort algorithm.                                                             */
#define PRIORITY_QUEUE_CFG_SORT_ALGORITHM_TYPE								BUBBLE_SORT

/* Configure    the type of sort algorithm.                                                             */
#define PRIORITY_QUEUE_CFG_COMPARE_ALGORITHM_TYPE							compare_control_greater

/* Configure    if enable integrated structure.                                                         */
#define PRIORITY_QUEUE_CFG_INTEGRATED_STRUCTURE_MODE_EN						1u

/* Configure    if enable priority_queue debug.															*/
#define PRIORITY_QUEUE_CFG_DEBUG_EN											0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    priority queue type.																	*/
typedef struct container_adaptor_s
*priority_queue_stp,
**priority_queue_stpp;

struct priority_queue_control_s {
	struct {
		/* @brief This function will initialize the priority_queue struct and the specified container.	*/
		errno_t(*init)(priority_queue_stpp priority_queue,
					   enum container_type_e type,
					   container_size_t element_size,
					   compare_t compare,
					   generic_type_element_assign_t assign,
					   generic_type_element_free_t free);

		  /* @brief This function will initialize the priority_queue struct and
					  attach to the specified container.													*/
		errno_t(*adapt)(priority_queue_stpp priority_queue,
						void *container,
						compare_t compare);

	   /* @brief This function will destroy the priority_queue struct.									*/
		errno_t(*destroy)(priority_queue_stpp priority_queue);
	}configuration;

	struct {
		/* @brief This function will return reference to the top element in the priority_queue.			*/
		void *(*top)(priority_queue_stp priority_queue);
	}element_access;

	struct {
		/* @brief This function will check if the underlying container has no elements.                 */
		bool(*empty)(priority_queue_stp priority_queue);

		/* @brief This function will returns the number of elements in the container.                   */
		size_t(*size)(priority_queue_stp priority_queue);

		/* @brief This function will returns the maximum number of elements
					the container is able to hold due to system or library implementation limitations.  */
		size_t(*max_size)(priority_queue_stp priority_queue);
	}capacity;

	struct {
		/* @brief This function will push the given element source to the top of the priority_queue.	*/
		void (*push)(priority_queue_stp priority_queue,
					 void *source);

		/* @brief This function will push a new element on top of the priority_queue.
					The element is constructed in-place.                                                */
		void (*emplace)(priority_queue_stp priority_queue,
						void *destination);

		/* @brief This function will remove the top element from the priority_queue.					*/
		void (*pop)(priority_queue_stp priority_queue);

		/* @brief This function will exchange the contents of the container adaptor with those of other.*/
		void (*swap)(priority_queue_stpp priority_queue,
					 priority_queue_stpp other);

		/* @brief This function will erase the specified elements from the container.					*/
		void (*copy)(priority_queue_stpp destination,
					 priority_queue_stp source);
	}modifiers;
};

/*
*********************************************************************************************************
*								        CONROL FUNCTION PROTOTYPES
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

errno_t priority_queue_control_configuration_init(priority_queue_stpp priority_queue,
												  enum container_type_e type,
												  container_size_t element_size,
												  compare_t compare,
												  generic_type_element_assign_t assign,
												  generic_type_element_free_t free);

/**
 * @brief This function will initialize the priority_queue struct and attach to the specified container.
 *
 * @param priority_queue the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

errno_t priority_queue_control_configuration_adapt(priority_queue_stpp priority_queue,
												   void *container,
												   compare_t compare);

/**
 * @brief This function will destroy the priority_queue struct.
 *
 * @param priority_queue the pointer to container adapter struct pointer
 *
 * @return NONE
 */

errno_t priority_queue_control_configuration_destroy(priority_queue_stpp priority_queue);

/**
 * @brief This function will return reference to the top element in the priority_queue.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *priority_queue_control_element_access_top(priority_queue_stp priority_queue);

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

bool priority_queue_control_capacity_empty(priority_queue_stp priority_queue);

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t priority_queue_control_capacity_size(priority_queue_stp priority_queue);

/**
 * @brief This function will returns the maximum number of elements
 *			the container is able to hold due to system or library implementation limitations.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t priority_queue_control_capacity_max_size(priority_queue_stp priority_queue);

/**
 * @brief This function will push the given element source to the top of the priority_queue.
 *
 * @param priority_queue the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

void priority_queue_control_modifiers_push(priority_queue_stp priority_queue, void *source);

/**
 * @brief This function will push a new element on top of the priority_queue. The element is constructed in-place.
 *
 * @param priority_queue the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void priority_queue_control_modifiers_emplace(priority_queue_stp priority_queue, void *destination);

/**
 * @brief This function will remove the top element from the priority_queue.
 *
 * @param priority_queue the pointer to container adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_pop(priority_queue_stp priority_queue);

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param priority_queue the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_swap(priority_queue_stpp priority_queue, priority_queue_stpp other);

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void priority_queue_control_modifiers_copy(priority_queue_stpp destination, priority_queue_stp source);

/*
*********************************************************************************************************
*                                    EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

extern struct priority_queue_control_s priority_queue_ctrl;

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__PRIORITY_PRIORITY_QUEUE_H