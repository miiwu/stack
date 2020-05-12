/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __BIDIRECTIONAL_ITERATOR_H
#define __BIDIRECTIONAL_ITERATOR_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "access_iterator_def.h"

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
 * @brief This type is the bidirectional iterator structure.
 */

struct bidirectional_iterator_s {
	struct access_iterator_advance_unit_s advance;

	struct access_iterator_access_unit_s distance;

	struct access_iterator_access_unit_s next;

	struct access_iterator_access_unit_s prev;

	struct access_iterator_access_unit_s front;

	struct access_iterator_access_unit_s back;
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

/**
 * @brief This type is the bidirectional iterator structure.
 */

extern struct bidirectional_iterator_s bidirectional_iterator;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__BIDIRECTIONAL_ITERATOR_H