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

#include "container_def.h"

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
#define QUEUE_CFG_INTERGRATED_STRUCTURE_MODE_EN			        1u

/* Configure    if enable queue debug.																    */
#define QUEUE_CFG_DEBUG_EN										0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* ------------------------------------------- VECTOR TYPE -------------------------------------------- */
/* Configure    vector ptr type.                                                                        */
typedef struct queue_t *QUEUE_TYPEDEF_PTR;

/* Configure    vector pptr type.                                                                       */
typedef struct queue_t **QUEUE_TYPEDEF_PPTR;

struct queue_control_t {
    struct {
        /* @brief This function will initialize the queue struct and the specified container.           */
        void (*init)(QUEUE_TYPEDEF_PPTR queue,
                     enum container_type_e type,
                     CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
                     void (*assign)(void *dst, void *src), void (*free)(void *dst));

        /* @brief This function will initialize the queue struct and attach to the specified container. */
        void (*attach)(QUEUE_TYPEDEF_PPTR queue,
                       enum container_type_e type, void *container);

        /* @brief This function will destroy the queue struct.                                          */
        void (*destroy)(QUEUE_TYPEDEF_PPTR queue);
    }configuration;

    struct {
        /* @brief This function will return reference to the top element in the queue.                  */
        void *(*front)(QUEUE_TYPEDEF_PTR queue);

		/* @brief This function will return reference to the last element in the queue.                 */
		void *(*back)(QUEUE_TYPEDEF_PTR queue);
    }element_access;

    struct {
        /* @brief This function will check if the underlying container has no elements.                 */
        bool(*empty)(QUEUE_TYPEDEF_PTR queue);

        /* @brief This function will returns the number of elements in the container.                   */
        size_t(*size)(QUEUE_TYPEDEF_PTR queue);

        /* @brief This function will returns the maximum number of elements
                    the container is able to hold due to system or library implementation limitations.  */
        size_t(*max_size)(QUEUE_TYPEDEF_PTR queue);
    }capacity;

    struct {
        /* @brief This function will push the given element source to the top of the queue.             */
        void (*push)(QUEUE_TYPEDEF_PTR queue,
                     void *source);

        /* @brief This function will push a new element on top of the queue. 
                    The element is constructed in-place.                                                */
        void (*emplace)(QUEUE_TYPEDEF_PTR queue,
                        void *destination);

        /* @brief This function will remove the top element from the queue. */
        void (*pop)(QUEUE_TYPEDEF_PTR queue);

        /* @brief This function will exchange the contents of the container adaptor with those of other.*/
        void (*swap)(QUEUE_TYPEDEF_PPTR queue,
                     QUEUE_TYPEDEF_PPTR other);

        /* @brief This function will erase the specified elements from the container. */
        void (*copy)(QUEUE_TYPEDEF_PPTR destination,
                     QUEUE_TYPEDEF_PTR source);
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

void queue_control_configration_init(QUEUE_TYPEDEF_PPTR queue,
                                     enum container_type_e type,
                                     CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
                                     void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will initialize the queue struct and attach to the specified container.
 *
 * @param queue the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

void queue_control_configration_attach(QUEUE_TYPEDEF_PPTR queue,
                                       enum container_type_e type, void *container);

/**
 * @brief This function will destroy the queue struct
 *
 * @param queue the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void queue_control_configration_destroy(QUEUE_TYPEDEF_PPTR queue);

/**
 * @brief This function will return reference to the first element in the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_front(QUEUE_TYPEDEF_PTR queue);

/**
 * @brief This function will return reference to the last element in the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void *queue_control_element_access_back(QUEUE_TYPEDEF_PTR queue);

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

CONTAINER_GLOBAL_CFG_SIZE_TYPE queue_control_capacity_size(QUEUE_TYPEDEF_PTR queue);

/**
 * @brief This function will push the given element source to the top of the queue.
 *
 * @param queue the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

bool queue_control_capacity_empty(QUEUE_TYPEDEF_PTR queue);

/**
 * @brief This function will return the number of elements in the underlying container.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE queue_control_capacity_max_size(QUEUE_TYPEDEF_PTR queue);

void queue_control_modifiers_push(QUEUE_TYPEDEF_PTR queue, void *source);

/**
 * @brief This function will push a new element on top of the queue. The element is constructed in-place.
 *
 * @param queue the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void queue_control_modifiers_emplace(QUEUE_TYPEDEF_PTR queue, void *destination);

/**
 * @brief This function will remove the top element from the queue.
 *
 * @param queue the pointer to container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_pop(QUEUE_TYPEDEF_PTR queue);

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param queue the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_swap(QUEUE_TYPEDEF_PPTR queue, QUEUE_TYPEDEF_PPTR other);

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void queue_control_modifiers_copy(QUEUE_TYPEDEF_PPTR destination, QUEUE_TYPEDEF_PTR source);

/*
*********************************************************************************************************
*                                    EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

extern struct queue_control_t queue_ctrl;

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__QUEUE_H