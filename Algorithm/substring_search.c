/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "substring_search.h"

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

/**
* @brief This struct will contain the necessary information that sort needed.
*/

substring_search_t substring_search_control_algorithm_address_table[] = {
	&substring_search_control_sunday_algorithm,
	&substring_search_control_brute_force_algorithm,
	&substring_search_control_sunday_algorithm
};

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
* @brief This function will match the substring by forward search.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param sublen the length of the substring.
*
* @return the location of not match.
*/

static inline size_t
substring_search_control_match_forward_search(const char *str,
											  const char *substr,
											  size_t sublen);

/**
* @brief This function will match the substring by backward search.
*
* @param str the pointer to the string.
* @param substr the pointer to the substring.
* @param sublen the length of the substring.
*
* @return the location of not match.
*/

static inline size_t
substring_search_control_match_backward_search(const char *str,
											   const char *substr,
											   size_t sublen);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will substring search the package by the specified algorithm.
 *
 * @param algorithm the enum name of the algorithm
 * @param package the package contains the necessary information
 *
 * @return void
 */

float substring_search_control(enum substring_search_type_e algorithm,
							   struct substring_search_package_s package)
{
	assert(NULL != package.str.string
		   && NULL != package.substr.string
		   && package.str.length
		   && package.substr.length);

	substring_search_t
		substring_search_algorithm
		= substring_search_control_algorithm_address_table[algorithm];

	return substring_search_algorithm(package.str.string,
									  package.str.length,
									  package.substr.string,
									  package.substr.length);
}

/**
 * @brief This function will search the substring upon the string by the brute force algorithm.
 *
 * @param str the pointer to the string.
 * @param substr the pointer to the substring.
 * @param len the length of the substring.
 *
 * @return the max matching rate.
 */

float substring_search_control_brute_force_algorithm(const char *str, size_t len,
													 const char *substr, size_t sublen)
{
	assert(str);
	assert(len);
	assert(substr);
	assert(sublen);

	static const size_t step = 1;

	static size_t
		loc, subloc;

	static char
		symbol_substr;

	static float
		max_matching_rate;

	loc = 0;																				/* Set zero */
	max_matching_rate = 0.0;

	do {
		subloc = substring_search_control_match_forward_search((str + loc),
															   substr,
															   sublen);

		if (sublen == subloc) {
			return 1.0;
		} else {
		}

		#if (SUBSTRING_SEARCH_CFG_MAX_MATCH_RATE_EN)

		if (subloc && max_matching_rate < subloc / (float)sublen) {
			max_matching_rate = subloc / (float)sublen;
		}

		#endif // (SUBSTRING_SEARCH_CFG_MAX_MATCH_RATE_EN)
	} while ((loc += step) < len);

	return max_matching_rate;
}

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
	} while (sublen > subloc++);

	do {
		subloc = substring_search_control_match_backward_search(str + loc,
																substr,
																sublen);

		if (sublen == subloc) {
			return 1.0;
		} else {
			if (*(substr + subloc) != *(str + loc + subloc)) {
				#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

				printf("substring_search.sunday_algorithm.not match:str \'%c\' - substr \'%c\' the point is \'%c\' \r\n",
					   *(substr + subloc), *(str + loc + subloc), *(str + loc + sublen));

				#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

				symbol_substr = *(str + loc + sublen);

				if (true == symbol[symbol_substr].exist) {
					#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

					printf("substring_search.sunday_algorithm.not match.point is exist \r\n");

					#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

					step = symbol[symbol_substr].location + 1;
				} else {
					#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

					printf("substring_search.sunday_algorithm.not match.point is not exist \r\n");

					#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

					step = sublen + 1;
				}
			}

			#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			printf("substring_search.sunday_algorithm.step:%d \r\n"
				   , step);

			#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)
		}

		#if (SUBSTRING_SEARCH_CFG_MAX_MATCH_RATE_EN)

		if (subloc && max_matching_rate < subloc / (float)sublen) {
			max_matching_rate = subloc / (float)sublen;
		}

		#endif // (SUBSTRING_SEARCH_CFG_MAX_MATCH_RATE_EN)
	} while (len > (loc += step));

	return max_matching_rate;
}

/**
 * @brief This function will match the substring by forward search.
 *
 * @param str the pointer to the string.
 * @param substr the pointer to the substring.
 * @param sublen the length of the substring.
 *
 * @return the location of not match.
 */

static inline size_t
substring_search_control_match_forward_search(const char *str,
											  const char *substr,
											  size_t sublen)
{
	assert(str);
	assert(substr);
	assert(sublen);

	static size_t
		subloc;

	subloc = sublen - 1;

	do {
		if (*(substr + subloc) != *(str + subloc)) {
			#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			printf("substring_search.match.forward_search.not match:str \'%c\' - substr \'%c\' \r\n",
				   *(substr + subloc), *(str + subloc));

			#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			break;
		} else if (0 == subloc) {															/* If the last symbol match */
			#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			printf("substring_search.match.forward_search.all matched \r\n");

			#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			return sublen;
		}
	} while (0 < subloc--);

	return subloc;
}

/**
 * @brief This function will match the substring by backward search.
 *
 * @param str the pointer to the string.
 * @param substr the pointer to the substring.
 * @param sublen the length of the substring.
 *
 * @return the location of not match.
 */

static inline size_t
substring_search_control_match_backward_search(const char *str,
											   const char *substr,
											   size_t sublen)
{
	assert(str);
	assert(substr);
	assert(sublen);

	static size_t
		subloc;

	subloc = 0;

	do {
		if (*(substr + subloc) != *(str + subloc)) {
			#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			printf("substring_search.match.backward_search.not match:str \'%c\' - substr \'%c\' \r\n",
				   *(substr + subloc), *(str + subloc));

			#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			break;
		} else if (sublen - 1 == subloc) {													/* If the last symbol match */
			#if (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			printf("substring_search.match.backward_search.all matched \r\n");

			#endif // (SUBSTRING_SEARCH_CFG_DEBUG_EN)

			return sublen;
		}
	} while (sublen > subloc++);

	return subloc;
}