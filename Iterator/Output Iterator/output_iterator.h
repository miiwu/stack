/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __OUTPUT_ITERATOR_H
#define __OUTPUT_ITERATOR_H

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

/**
 * @brief This type is the iterator typedef.
 */

typedef struct iterator_s
*output_iterator_stp,
**output_iterator_stpp;

/**
 * @brief This type is the iterator control structure.
 */

struct output_iterator_control_s
{
	struct
	{
		errno_t(*init)(output_iterator_stpp iterator,
					   struct iterator_object_unit_s object_unit);

		errno_t(*destroy)(output_iterator_stpp iterator);
	}configuration;

	struct
	{
		void *(*advance)(output_iterator_stp iterator,
						 int step);

		size_t(*distance)(output_iterator_stp iterator);

		void *(*next)(output_iterator_stp iterator);

		void *(*prev)(output_iterator_stp iterator);

		void *(*at)(output_iterator_stp iterator,
					size_t index);

        errno_t(*modify)(output_iterator_stp iterator,
                         void *source);
	}iterator_operations;

	struct
	{
		void *(*begin)(output_iterator_stp iterator);

		void *(*end)(output_iterator_stp iterator);

		size_t(*size)(output_iterator_stp iterator);

		bool (*empty)(output_iterator_stp iterator);

		void *(*data)(output_iterator_stp iterator);
	}range_access;
};

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will initialize the iterator.
 *
 * @param
 *
 * @return
 */

errno_t output_iterator_control_configuration_init(output_iterator_stpp iterator,
												   struct iterator_object_unit_s object_unit);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator control structure.
 */

extern struct output_iterator_control_s output_iterator_control;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__OUTPUT_ITERATOR_H