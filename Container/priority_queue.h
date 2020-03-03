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

/*
*********************************************************************************************************
*									     CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    if enable integrated structure.                                                         */
#define PRIORITY_QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE						VECTOR

/* Configure    the type of allocator.                                                                  */
#define PRIORITY_QUEUE_CFG_ALLOCATOR_TYPE									ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define PRIORITY_QUEUE_CFG_INTEGRATED_STRUCTURE_MODE_EN			        1u

/* Configure    if enable priority_queue debug.															*/
#define PRIORITY_QUEUE_CFG_DEBUG_EN											0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    vector ptr type.                                                                        */
typedef struct priority_queue_s 
*priority_queue_stp,
**priority_queue_stpp;

struct priority_queue_control_s {
	struct {
		/* @brief This function will initialize the priority_queue struct and the specified container.           */
		void (*init)(priority_queue_stpp priority_queue,
					 enum container_type_e type,
					 container_size_t element_size,
					 void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will initialize the priority_queue struct and attach to the specified container. */
		void (*attach)(priority_queue_stpp priority_queue,
					   enum container_type_e type, void *container);

		/* @brief This function will destroy the priority_queue struct.                                          */
		void (*destroy)(priority_queue_stpp priority_queue);
	}configuration;

	struct {
		/* @brief This function will return reference to the top element in the priority_queue.                  */
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
		/* @brief This function will push the given element source to the top of the priority_queue.             */
		void (*push)(priority_queue_stp priority_queue,
					 void *source);

		/* @brief This function will push a new element on top of the priority_queue.
					The element is constructed in-place.                                                */
		void (*emplace)(priority_queue_stp priority_queue,
						void *destination);

		/* @brief This function will remove the top element from the priority_queue. */
		void (*pop)(priority_queue_stp priority_queue);

		/* @brief This function will exchange the contents of the container adaptor with those of other.*/
		void (*swap)(priority_queue_stpp priority_queue,
					 priority_queue_stpp other);

		/* @brief This function will erase the specified elements from the container. */
		void (*copy)(priority_queue_stpp destination,
					 priority_queue_stp source);
	}modifiers;
};

/*
*********************************************************************************************************
*								        CONROL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

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