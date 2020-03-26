/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ITERATOR_H
#define __ITERATOR_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "iterator_def.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the iterator typedef.
 */

typedef struct iterator_s
*iterator_stp,
**iterator_stpp;

/**
 * @brief This type is the iterator control structure.
 */

struct iterator_control_s {
	struct {
		errno_t(*init)(iterator_stpp iterator,
					   struct iterator_object_unit_s object_unit);

		errno_t (*destroy)(iterator_stpp iterator);
	}configuration;

	struct {
		void *(*advance)(iterator_stp iterator);

		size_t (*distance)(iterator_stp iterator);

		void *(*next)(iterator_stp iterator);

		void *(*prev)(iterator_stp iterator);
	}iterator_operations;

	struct {
		void *(*begin)(iterator_stp iterator);

		void *(*end)(iterator_stp iterator);

		size_t (*size)(iterator_stp iterator);

		bool (*empty)(iterator_stp iterator);

		void *(*data)(iterator_stp iterator);
	}range_access;
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
* @brief This function will initialize the iterator.
*
* @param
*
* @return
*/

errno_t iterator_control_configuration_init(iterator_stpp iterator,
											struct iterator_object_unit_s object_unit);

/**
* @brief This function will destroy the iterator.
*
* @param
*
* @return
*/

errno_t iterator_control_configuration_destroy(iterator_stpp iterator);

/**
* @brief This function will.
*
* @param
*
* @return
*/

void *iterator_control_iterator_operations_next(iterator_stp iterator);

/**
* @brief This function will.
*
* @param
*
* @return
*/

void *iterator_control_iterator_operations_prev(iterator_stp iterator);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This type is the iterator control structure.
 */

extern struct iterator_control_s iterator_control;

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ITERATOR_H