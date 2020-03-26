/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ITERATOR_DEFINITION_H
#define __ITERATOR_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

#include "allocator.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			iterator control common prepare block.												*/
#define ITERATOR_CONTROL_COMMON_POINTER_ASSERT(pointer,error_type,error_code)							\
	do {																								\
		assert(NULL != (pointer));									/* Assert first,DEBUG will work */	\
		if (NULL == (pointer)) {									/* If second,RELEASE will work	*/	\
			return (error_type)(error_code);															\
		}																								\
	} while (false)

#pragma warning( disable : 4996)
#pragma warning( disable : 26812)

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator type enum.
 */

enum iterator_type {
	ITORATER,
};

/**
 * @brief This type is the iterator object control structure.
 */

struct iterator_object_control_s {
    struct {
        /* @brief This function will returns a reference to the element
                    at specified location position, with bounds checking.								*/
        void *(*at)(void *object, size_t position);

        /* @brief This function will returns pointer to the underlying array
                  serving as element storage.                                                           */
        void *(*data)(void *object);
    }element_access;

    struct {
        /* @brief This function will check if the underlying object has no elements.					*/
        bool(*empty)(void *object);

        /* @brief This function will returns the number of elements in the object.					    */
        size_t(*size)(void *object);

        /* @brief This function will returns the maximum number of elements
                    the object is able to hold due to system or library implementation limitations.	    */
        size_t(*max_size)(void *object);
    }capacity;
};

/**
 * @brief This type is the iterator common information structure.
 */

struct iterator_common_information_s {
	size_t position;
};

/**
 * @brief This type is the iterator object unit structure.
 */

struct iterator_object_unit_s {
	/* @brief This variables will point to the object.						                            */
    void *object_ptr;

	/* @brief This variables will point to the control structure of the object_ptr.				        */
    struct iterator_object_control_s *control_ptr;
};

/**
 * @brief This type is the iterator allocator unit structure.
 */

struct iterator_allocator_unit_s {
    /* @brief This variables will point to the object.						                            */
    void *allocator_ptr;

    /* @brief This variables will point to the control structure of the object_ptr.				        */
    struct allocator_control_s *control_ptr;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will check if the at iterator operations can perform.
 *
 * @param
 *
 * @return
 */

bool iterator_control_iterator_operations_at_check(struct iterator_s *iterator,
                                                   size_t index);

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

#endif // !__ITERATOR_DEFINITION_H