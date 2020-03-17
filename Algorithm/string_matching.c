/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "string_matching.h"

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

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
* @brief This function will search the substring upon the string by the sunday algorithm.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param len the length of the substring.
*
* @return the max matching rate.
*/

float substring_search_control_sunday_algorithm(const char *str, size_t len,
												const char *substr, size_t sublen)
{
	assert(str);
	assert(len);
	assert(substr);
	assert(sublen);

	static size_t
		loc, step, subloc;

	static char
		symbol_substr;

	static float
		max_matching_rate;

	struct sunday_algorith_substring_infomation_s {
		bool exist;

		size_t location;
	}symbol[128] = { 0 };																	/* ASSIC have 128 symbol */

	loc = 0;																				/* Set zero */
	step = 0;
	subloc = 0;
	max_matching_rate = 0.0;

	do {																					/* Get the information of the substring,
																									whether the symbol exist and where it is */
		symbol_substr = *(substr + subloc);

		if (false == symbol[symbol_substr].exist) {
			symbol[symbol_substr].exist = true;
		}

		symbol[symbol_substr].location = sublen - subloc - 1;
	} while (subloc++ < sublen);

	do {
		subloc = 0;
		do {
			symbol_substr = *(str + loc + subloc);

			if (*(substr + subloc) != symbol_substr) {
				#if (STRING_MATCHING_CFG_DEBUG_EN)

				printf("substring_search.sunday_algorithm.not match:str \'%c\' - substr \'%c\' the point is \'%c\' \r\n",
					   *(substr + subloc), symbol_substr, *(str + loc + sublen));

				#endif // (STRING_MATCHING_CFG_DEBUG_EN)

				symbol_substr = *(str + loc + sublen);

				if (true == symbol[symbol_substr].exist) {
					#if (STRING_MATCHING_CFG_DEBUG_EN)

					printf("substring_search.sunday_algorithm.not match.point is exist \r\n");

					#endif // (STRING_MATCHING_CFG_DEBUG_EN)

					step = symbol[symbol_substr].location + 1;
				} else {
					#if (STRING_MATCHING_CFG_DEBUG_EN)

					printf("substring_search.sunday_algorithm.not match.point is not exist \r\n");

					#endif // (STRING_MATCHING_CFG_DEBUG_EN)

					step = sublen + 1;
				}

				#if (STRING_MATCHING_CFG_DEBUG_EN)

				printf("substring_search.sunday_algorithm.step:%d \r\n", step);

				#endif // (STRING_MATCHING_CFG_DEBUG_EN)

				if (subloc && max_matching_rate < subloc / (float)sublen) {
					max_matching_rate = subloc / (float)sublen;
				}

				break;
			} else if (sublen - 1 == subloc) {
				return 1.0;
			}
		} while (subloc++ < sublen);
	} while ((loc += step) < len);

	return max_matching_rate;
}