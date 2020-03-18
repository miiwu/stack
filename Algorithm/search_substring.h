/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __SEARCH_SUBSTRING_H
#define __SEARCH_SUBSTRING_H

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

/* Configure        if enable string matching debug.													*/
#define SEARCH_SUBSTRING_CFG_DEBUG_EN										1u

/* Configure        if enable max match rate.															*/
#define SEARCH_SUBSTRING_CFG_MAX_MATCH_RATE_EN								1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
* @brief This struct will contain the necessary information that sort needed.
*/

enum search_substring_type_e {
	DEFAULT_SEARCH_SUBSTRING_ALGORITHM,

	BRUTE_FORCE_ALGORITHM,

	SUNDAY_ALGORITHM,
};

/**
 * @brief This type is the substring search function prototype typedef
 */

typedef float (*search_substring_t)(const char *str, size_t len,
									const char *substr, size_t sublen);

/**
* @brief This struct will contain the necessary information that sort needed.
*/

struct string_unit_s {
	char *string;
	size_t length;
};

/**
* @brief This struct will contain the necessary information that sort needed.
*/

struct search_substring_package_s {
	struct string_unit_s str;

	struct string_unit_s substr;
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will sort the object by the comp and the sort algorithm is distinguished by
 *		   the sort_algorithm_addr that will get by xxx_convert_type_to_func_addr_table().
 *
 * @param data the pointer to the data list will give
 *
 * @return void
 */

float search_substring_control(enum search_substring_type_e algorithm,
							   struct search_substring_package_s package);

/**
* @brief This function will search the substring upon the string by the brute force algorithm.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param len the length of the substring.
*
* @return the max matching rate.
*/

float search_substring_control_brute_force_algorithm(const char *str, size_t len,
													 const char *substr, size_t sublen);

/**
* @brief This function will search the substring upon the string by the sunday algorithm.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param len the length of the substring.
*
* @return the max matching rate.
*/

float search_substring_control_sunday_algorithm(const char *str, size_t len,
												const char *substr, size_t sublen);

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

#endif // !__SEARCH_SUBSTRING_H