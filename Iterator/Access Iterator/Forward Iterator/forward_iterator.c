/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "forward_iterator.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                           LOCAL CONSTANTS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                          LOCAL DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            LOCAL TABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

bool forward_iterator_control_iterator_operations_advance_valid_step(int step);

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/**
 * @brief This variable is the forward iterator structure.
 */

struct forward_iterator_s forward_iterator = {
	.advance.access_unit.function_ptr = access_iterator_control_iterator_operations_advance,
	.advance.valid_step_ptr = forward_iterator_control_iterator_operations_advance_valid_step,

	.distance.function_ptr = access_iterator_control_iterator_operations_distance,

	.next.function_ptr = access_iterator_control_iterator_operations_next,

	.front.function_ptr = access_iterator_control_iterator_operations_front,

	.back.function_ptr = access_iterator_control_iterator_operations_back,
};

/*
 *********************************************************************************************************
 *                                            FUNCTIONS
 *********************************************************************************************************
 */

/**
 * @brief This function will.
 *
 * @param
 *
 * @return
 */

static inline bool
forward_iterator_control_iterator_operations_advance_valid_step(int step)
{
	if (0 > step) {
		return false;
	}

	return true;
}