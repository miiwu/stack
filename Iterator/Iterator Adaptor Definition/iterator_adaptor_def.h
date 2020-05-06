/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ITERATOR_ADAPTOR_DEFINITION_H
#define __ITERATOR_ADAPTOR_DEFINITION_H

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

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will initialize the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_init(struct iterator_adaptor_s **iterator_adaptor,
													enum iterator_adaptor_type_e iterator_adaptor_type,
													enum iterator_type_e iterator_type,
													enum allocator_type_e allocator_type,
													struct iterator_object_unit_s object_unit);

/**
 * @brief This function will readapt the iterator of the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_readapt(struct iterator_adaptor_s **iterator_adaptor,
													   enum iterator_type_e iterator_type,
													   struct iterator_object_unit_s object_unit);

/**
 * @brief This function will adapt the exist iterator to the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_adapt_exist(struct iterator_adaptor_s **iterator_adaptor,
														   struct iterator_s *iterator);

/**
 * @brief This function will destroy the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

errno_t iterator_adaptor_control_configuration_destroy(struct iterator_adaptor_s **iterator_adaptor);

/**
 * @brief This function will advance base iterator of the iterator adaptor.
 *
 * @param void
 *
 * @return void
 */

void *iterator_adaptor_control_iterator_operations_advance(struct iterator_adaptor_s *iterator_adaptor,
														   int step);

/**
 * @brief This function will access the size of base iterator of the iterator adaptor.
 *
 * @param
 *
 * @return
 */

size_t iterator_adaptor_control_range_access_size(struct iterator_adaptor_s *iterator_adaptor);

/**
 * @brief This function will access if base iterator of the iterator adaptor is empty.
 *
 * @param
 *
 * @return
 */

bool iterator_adaptor_control_range_access_empty(struct iterator_adaptor_s *iterator_adaptor);

/**
 * @brief This function will access the data pointer that base iterator of the iterator adaptor pointed.
 *
 * @param
 *
 * @return
 */

void *iterator_adaptor_control_range_access_data(struct iterator_adaptor_s *iterator_adaptor);

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

#endif // !__ITERATOR_ADAPTOR_DEFINITION_H