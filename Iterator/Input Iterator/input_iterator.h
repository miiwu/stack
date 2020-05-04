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

/* Configure    the type of input iterator.                                                                  */
#define INPUT_ITERATOR_CFG_ALLOCATOR_TYPE                                 CONCEPT_ALLOCATOR

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
	struct {
		errno_t(*init)(input_iterator_stpp iterator,
					   struct iterator_object_unit_s object_unit);

		errno_t(*destroy)(input_iterator_stpp iterator);
	}configuration;

	struct {
		void *(*advance)(input_iterator_stp iterator,
						 int step);

		size_t(*distance)(input_iterator_stp iterator);

		void *(*next)(input_iterator_stp iterator);
	}iterator_operations;

	struct {
		size_t(*size)(input_iterator_stp iterator);

		bool (*empty)(input_iterator_stp iterator);

		void *(*data)(input_iterator_stp iterator);
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

errno_t input_iterator_control_configuration_init(input_iterator_stpp iterator,
												  struct iterator_object_unit_s object_unit);

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