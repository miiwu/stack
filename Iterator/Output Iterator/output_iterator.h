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

#include "iterator_adaptor_def.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configure    the type of output iterator.                                                            */
#define OUTPUT_ITERATOR_CFG_ALLOCATOR_TYPE                                                              \
    CONCEPT_ALLOCATOR

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the output iterator structure typedef.
 */

typedef struct iterator_adaptor_s
*output_iterator_stp,
**output_iterator_stpp;

/**
 * @brief This type is the output iterator control structure.
 */

struct output_iterator_control_s {
	struct {
		errno_t(*init)(output_iterator_stpp output_iterator,
					   enum iterator_type_e iterator_type,
					   struct iterator_object_unit_s object_unit);

		errno_t(*destroy)(output_iterator_stpp iterator_adaptor);

		errno_t(*readapt)(output_iterator_stpp iterator_adaptor,
						  enum iterator_type_e iterator_type,
						  struct iterator_object_unit_s object_unit);

		errno_t(*adapt_exist)(output_iterator_stpp iterator_adaptor,
							  struct iterator_s *iterator);
	}configuration;

	struct {
		void *(*advance)(output_iterator_stp output_iterator,
						 int step);

		size_t(*distance)(output_iterator_stp output_iterator);
	}iterator_operations;

	struct {
		size_t(*size)(output_iterator_stp output_iterator);

		bool (*empty)(output_iterator_stp output_iterator);

		void *(*data)(output_iterator_stp output_iterator);
	}range_access;

	void *(*modify)(output_iterator_stp output_iterator,
					size_t index,
					void *source);
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

errno_t output_iterator_control_configuration_init(output_iterator_stpp output_iterator,
												   enum iterator_type_e iterator_type,
												   struct iterator_object_unit_s object_unit);

void *output_iterator_control_modify(output_iterator_stp output_iterator,
									 size_t index,
									 void *source);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This type is the output iterator control structure.
 */

extern struct output_iterator_control_s output_iterator_control;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__OUTPUT_ITERATOR_H