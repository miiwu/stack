/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This VECTOR definition header file is protected from multiple pre-processor inclusion
*               through use of the AT definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __VECTOR_H
#define __VECTOR_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdbool.h"
#include "assert.h"
#include "malloc.h"

/*
*********************************************************************************************************
*									    VECTOR CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    if enable integrated structure.                                                         */
#define VECTOR_CFG_INTERGRATED_STRUCTURE_MODE_EN			    1u

/* Configure    the default max size of vector.                                                         */
#define VECTOR_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define VECTOR_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		102400u

/* Configure    the type of size.                                                                       */
#define VECTOR_CFG_SIZE_TYPE                                    size_t

#pragma warning( disable : 4996)

/*
*********************************************************************************************************
*									        VECTOR DATA TYPES
*********************************************************************************************************
*/

/* ----------------------------------------- VECTOR SIZE TYPE ----------------------------------------- */
/* Configure    vector size type.                                                                       */
typedef VECTOR_CFG_SIZE_TYPE VECTOR_SIZE_TYPEDEF;

/* Configure    vector size ptr type.                                                                   */
typedef VECTOR_CFG_SIZE_TYPE *VECTOR_SIZE_TYPEDEF_PTR;

/* Configure    vector size pptr type.                                                                  */
typedef VECTOR_CFG_SIZE_TYPE **VECTOR_SIZE_TYPEDEF_PPTR;

/* ------------------------------------------- VECTOR TYPE -------------------------------------------- */
/* Configure    vector type.                                                                            */
typedef struct vector_t	VECTOR_TYPEDEF;

/* Configure    vector ptr type.                                                                        */
typedef struct vector_t *VECTOR_TYPEDEF_PTR;

/* Configure    vector pptr type.                                                                       */
typedef struct vector_t **VECTOR_TYPEDEF_PPTR;

#if (VECTOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

struct vector_control_t {
	struct {
		/* @brief This function will initialize the vector struct.                                      */
		void (*init)(VECTOR_TYPEDEF_PPTR vector,
					 VECTOR_SIZE_TYPEDEF dst_size, bool string_type,
					 void (*assign_func)(void *dst, void *src), void (*free_func)(void *dst));

		/* @brief This function will destroy the vector struct and free the space.                      */
		void (*destroy)(VECTOR_TYPEDEF_PPTR vector);

		/* @brief This function will configure the vector element handler.                              */
		void (*element_handler)(VECTOR_TYPEDEF_PTR vector,
								void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will configure the vector exception callback.                           */
		void (*callback)(VECTOR_TYPEDEF_PTR vector,
						 void (*empty)(void), void (*full)(void), void (*null_heap)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the vector struct.                                      */
		void (*begin)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will initialize the vector struct.                                      */
		void (*end)(VECTOR_TYPEDEF_PTR vector);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the element
				  at specified location position, with bounds checking.                                 */
		void *(*at)(VECTOR_TYPEDEF_PTR vector,
					VECTOR_SIZE_TYPEDEF position);

		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will returns reference to the last element in the container.            */
		void *(*back)(VECTOR_TYPEDEF_PTR vector);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will returns the number of elements in the container.                   */
		VECTOR_SIZE_TYPEDEF(*size)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		VECTOR_SIZE_TYPEDEF(*max_size)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will returns the number of elements
				  that the container has currently allocated space for.                                 */
		VECTOR_SIZE_TYPEDEF(*capacity)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will increase the capacity of the vector to a size
				  that's greater or equal to new_cap. */
		void (*reserve)(VECTOR_TYPEDEF_PPTR vector,
						VECTOR_SIZE_TYPEDEF size);

		/* @brief This function will requests the removal of unused capacity.                           */
		void (*shrink_to_fit)(VECTOR_TYPEDEF_PPTR vector);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(VECTOR_TYPEDEF_PTR vector);

		/* @brief This function will inserts elements at the specified location in the container.       */
		void *(*insert)(VECTOR_TYPEDEF_PTR vector,
						VECTOR_SIZE_TYPEDEF position, VECTOR_SIZE_TYPEDEF amount, void **source);

		/* @brief This function will erases the specified elements from the container.                  */
		void (*erase)(VECTOR_TYPEDEF_PTR vector,
					  VECTOR_SIZE_TYPEDEF position, void *data);

		/* @brief This function will appends the given element source to the end of the container.      */
		void (*push_back)(VECTOR_TYPEDEF_PTR vector,
						  void *source);

		/* @brief This function will removes the last element of the container.                         */
		void (*pop_back)(VECTOR_TYPEDEF_PTR vector,
						 void *destination);

		/* @brief This function will resizes the container to contain count elements.                   */
		void (*resize)(VECTOR_TYPEDEF_PPTR vector,
					   VECTOR_SIZE_TYPEDEF size);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(VECTOR_TYPEDEF_PPTR destination,
					 VECTOR_TYPEDEF_PTR source);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(VECTOR_TYPEDEF_PPTR vector,
					 VECTOR_TYPEDEF_PPTR other);
	}modifiers;
};

#endif // (VECTOR_CONTROL_INTERGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*								    VECTOR CONROL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the vector struct.
 *
 * @param vector container struct
 * @param element_size the size of element
 * @param string_type if the element is the string type
 * @param assign_func pointer to the assign function of element
 * @param free_func pointer to the free function of element
 *
 * @return NONE
 */

void vector_control_configuration_init(VECTOR_TYPEDEF_PPTR vector,
									   VECTOR_SIZE_TYPEDEF element_size, bool string_type,
									   void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will destroy the vector struct and free the space.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_configuration_destroy(VECTOR_TYPEDEF_PPTR vector);

/**
 * @brief This function will configure the vector element handler.
 *
 * @param vector container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

void vector_control_configuration_element_handler(VECTOR_TYPEDEF_PTR vector,
												  void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will configure the vector exception callback.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_configuration_callback(VECTOR_TYPEDEF_PTR vector,
										   void (*empty)(void), void (*full)(void), void (*null_heap)(void));

/**
 * @brief This function will
 *
 * @param vector container struct
 * @param empty pointer to the address of element callback that container has no elements when delete element
 * @param full pointer to the address of element callback that container has no elements when add element
 * @param null_heap pointer to the address of element callback that malloc is valid
 *
 * @return NONE
 */

void vector_control_iterators_front(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_iterators_back(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param vector container struct
 * @param position the position of element
 *
 * @return NONE
 */

void *vector_control_element_access_at(VECTOR_TYPEDEF_PTR vector,
									   VECTOR_SIZE_TYPEDEF position);

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void *vector_control_element_access_front(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void *vector_control_element_access_back(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param vector container struct
 *
 * @return
 *  if the container has no elements
 */

bool vector_control_capacity_empty(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param vector container struct
 *
 * @return
 *  the number of elements in the container
 */

VECTOR_SIZE_TYPEDEF vector_control_capacity_size(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param vector container struct
 *
 * @return
 *  the maximum number of elements the container
 */

VECTOR_SIZE_TYPEDEF vector_control_capacity_max_size(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will returns the number of elements that the container has currently allocated space for.
 *
 * @param vector container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

VECTOR_SIZE_TYPEDEF vector_control_capacity_capacity(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will increase the capacity of the vector to a size that's greater or equal to new_cap.
 *
 * @param vector container struct
 * @param position the position of element
 * @param size the size of elements
 *
 * @return NONE
 */

void vector_control_capacity_reserve(VECTOR_TYPEDEF_PPTR vector,
									 VECTOR_SIZE_TYPEDEF size);

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_capacity_shrink_to_fit(VECTOR_TYPEDEF_PPTR vector);

/**
 * @brief This function will erases all elements from the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_modifiers_clear(VECTOR_TYPEDEF_PTR vector);

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

void *vector_control_modifiers_insert(VECTOR_TYPEDEF_PTR vector,
									  VECTOR_SIZE_TYPEDEF position, VECTOR_SIZE_TYPEDEF amount, void **source);

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param vector container struct
 * @param position the position of element
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_erase(VECTOR_TYPEDEF_PTR vector,
									VECTOR_SIZE_TYPEDEF position, void *destination);

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param vector container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void vector_control_modifiers_push_back(VECTOR_TYPEDEF_PTR vector,
										void *source);

/**
 * @brief This function will removes the last element of the container.
 *
 * @param vector container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void vector_control_modifiers_pop_back(VECTOR_TYPEDEF_PTR vector,
									   void *destination);

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param vector container struct
 * @param count the count of elements
 *
 * @return NONE
 */

void vector_control_modifiers_resize(VECTOR_TYPEDEF_PPTR vector,
									 VECTOR_SIZE_TYPEDEF count);

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

void vector_control_modifiers_copy(VECTOR_TYPEDEF_PPTR destination,
								   VECTOR_TYPEDEF_PTR source);

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param vector container struct
 * @param other container struct
 *
 * @return NONE
 */

void vector_control_modifiers_swap(VECTOR_TYPEDEF_PPTR vector,
								   VECTOR_TYPEDEF_PPTR other);

/*
*********************************************************************************************************
*                                   VECTOR EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

extern struct vector_control_t vector_ctrl;

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // __VECTOR_H