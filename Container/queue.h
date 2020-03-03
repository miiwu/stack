/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __QUEUE_H
#define __QUEUE_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "container_adaptor_family.h"

/*
*********************************************************************************************************
*									     CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    if enable integrated structure.                                                         */
#define QUEUE_CFG_DEFAULT_ADAPT_CONTAINER_TYPE			        VECTOR

/* Configure    the type of allocator.                                                                  */
#define QUEUE_CFG_ALLOCATOR_TYPE                                ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define QUEUE_CFG_INTEGRATED_STRUCTURE_MODE_EN			        1u

/* Configure    if enable queue debug.																    */
#define QUEUE_CFG_DEBUG_EN										0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    vector ptr type.                                                                        */
typedef struct queue_s 
*queue_stp,
**queue_stpp;

/**
 * @brief This type will contain all the queue control functions.
 */

struct queue_control_t {
	struct {
		/* @brief This function will initialize the queue struct and the specified container.           */
		void (*init)(queue_stpp queue,
					 enum container_type_e type,
					 container_size_t element_size,
					 generic_type_element_assign_t assign,
					 generic_type_element_free_t free);

		/* @brief This function will initialize the queue struct and attach to the specified container. */
		void (*attach)(queue_stpp queue,
					   enum container_type_e type, void *container);

		/* @brief This function will destroy the queue struct.                                          */
		void (*destroy)(queue_stpp queue);
	}configuration;

	struct {
		/* @brief This function will return reference to the top element in the queue.                  */
		void *(*front)(queue_stp queue);

		/* @brief This function will return reference to the last element in the queue.                 */
		void *(*back)(queue_stp queue);
	}element_access;

	struct {
		/* @brief This function will check if the underlying container has no elements.                 */
		bool(*empty)(queue_stp queue);

		/* @brief This function will returns the number of elements in the container.                   */
		size_t(*size)(queue_stp queue);

		/* @brief This function will returns the maximum number of elements
					the container is able to hold due to system or library implementation limitations.  */
		size_t(*max_size)(queue_stp queue);
	}capacity;

	struct {
		/* @brief This function will push the given element source to the top of the queue.             */
		void (*push)(queue_stp queue,
					 void *source);

		/* @brief This function will push a new element on top of the queue.
					The element is constructed in-place.                                                */
		void (*emplace)(queue_stp queue,
						void *destination);

		/* @brief This function will remove the top element from the queue. */
		void (*pop)(queue_stp queue);

		/* @brief This function will exchange the contents of the container adaptor with those of other.*/
		void (*swap)(queue_stpp queue,
					 queue_stpp other);

		/* @brief This function will erase the specified elements from the container. */
		void (*copy)(queue_stpp destination,
					 queue_stp source);
	}modifiers;
};

/*
*********************************************************************************************************
*								        CONROL FUNCTION PROTOTYPES
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
									  generic_type_element_free_t free);

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
										enum container_type_e type, void *container);

/**
 * @brief This function will destroy the queue struct
 *
 * @param queue the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void queue_control_configuration_destroy(queue_stpp queue);

/**
 * @brief This function will return reference to the first element in the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_front(queue_stp queue);

/**
 * @brief This function will return reference to the last element in the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_back(queue_stp queue);

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t queue_control_capacity_size(queue_stp queue);

/**
 * @brief This function will push the given element source to the top of the queue.
 *
 * @param queue the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

bool queue_control_capacity_empty(queue_stp queue);

/**
 * @brief This function will return the number of elements in the underlying container.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

container_size_t queue_control_capacity_max_size(queue_stp queue);

void queue_control_modifiers_push(queue_stp queue, void *source);

/**
 * @brief This function will push a new element on top of the queue. The element is constructed in-place.
 *
 * @param queue the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void queue_control_modifiers_emplace(queue_stp queue, void *destination);

/**
 * @brief This function will remove the top element from the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_pop(queue_stp queue);

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param queue the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_swap(queue_stpp queue, queue_stpp other);

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_copy(queue_stpp destination, queue_stp source);

/*
*********************************************************************************************************
*                                    EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (QUEUE_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This type will contain all the queue control functions.
 */

extern struct queue_control_t queue_ctrl;

#endif // (QUEUE_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__QUEUE_H