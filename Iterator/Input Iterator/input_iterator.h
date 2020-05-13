/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __INPUT_ITERATOR_H
#define __INPUT_ITERATOR_H

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

/* Configure    the allocator type of the input iterator.                                               */
#define INPUT_ITERATOR_CFG_ALLOCATOR_TYPE                                                               \
    CONCEPT_ALLOCATOR

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the input iterator typedef.
 */

typedef struct iterator_s
*input_iterator_stp,
**input_iterator_stpp;

/**
 * @brief This type is the input iterator control structure.
 */

struct input_iterator_control_s {
	struct iterator_control_s;

	void *(*access)(struct access_iterator_s *access_iterator,
					struct access_iterator_access_unit_s access_unit,
					...);
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

errno_t input_iterator_control_configuration_init(input_iterator_stpp iterator,
												  struct access_iterator_object_unit_s object_unit);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This type is the input iterator control structure.
 */

extern struct input_iterator_control_s input_iterator_control;

/**
 * @brief This variable is the iterator control function address table.
 */

extern const void *input_iterator_control_function_address_table[];

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__INPUT_ITERATOR_H