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

/**
 * @brief This type is the iterator control structure.
 */

struct iterator_control_s {
    struct {
        errno_t(*init)(struct iterator_s **iterator,
                       struct iterator_object_unit_s object_unit);

        errno_t(*destroy)(struct iterator_s **iterator);
    }configuration;

    struct {
        void *(*advance)(struct iterator_s *iterator,
                         int step);

        size_t(*distance)(struct iterator_s *iterator);
    }iterator_operations;

    struct {
        size_t(*size)(struct iterator_s *iterator);

        bool (*empty)(struct iterator_s *iterator);

        void *(*data)(struct iterator_s *iterator);
    }range_access;
};

/**
 * @brief This type is the unit of the iterator.
 */

struct iterator_unit_s {
    struct iterator_control_s *control_ptr;

    void *iterator_ptr;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

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