/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __SORT_H
#define __SORT_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "algorithm_def.h"

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
* @brief This struct will contain the necessary information that sort needed.
*/

struct sort_pack_t {
	void *object;

	size_t len;
	size_t mem_len;

	void (*swap_method)(void *, size_t, size_t);

	void *(*get_value_method)(void *, size_t);
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
* @brief This function will return the specified sort algorithm's function address.
*
* @param data the pointer to the data list will give
*
* @return the specified sort algorithm's function address
*/

void *sort_algorithm_control_convert_type_to_func_addr(enum sort_algorithm_type type);

/**
* @brief This function will sort the object by the comp and the sort algorithm is distinguished by
*		   the sort_algorithm_addr that will get by xxx_convert_type_to_func_addr_table().
*
* @param data the pointer to the data list will give
*
* @return void
*/

void sort_algorithm_control(void *sort_algorithm_addr,
							struct sort_pack_t sort_package, bool (*comp)(void *, void *, size_t));

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

#endif // !__SORT_H