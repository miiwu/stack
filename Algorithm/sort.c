/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "sort.h"

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
 * @brief This function will get the value of object.
 *
 * @param sort_package the package of the sort information
 * @param pos the position of the value
 * @param value_lhs the pointer to the left side value
 * @param value_rhs the pointer to the right side value
 *
 * @return if get the value of object successful
 *	- true	yes
 *	- false	no
 */

static inline bool sort_algorithm_control_get_value(struct sort_package_s sort_package,
													size_t pos,
													void **value_lhs,
													void **value_rhs);

/**
 * @brief This function will sort the object by the comp.
 *
 * @param data the pointer to the data list will give
 *
 * @return if the data match the rule
 *	- true	yes
 *	- false	no
 */

void sort_algorithm_control_quick_sort(struct sort_package_s sort_package,
									   compare_t *compare);

/**
 * @brief This function will sort the object by the comp.
 *
 * @param data the pointer to the data list will give
 *
 * @return if the data match the rule
 *	- true	yes
 *	- false	no
 */

void sort_algorithm_control_bubble_sort(struct sort_package_s sort_package,
										compare_t *compare);

/*
*********************************************************************************************************
*                                            FUNCTIONS
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

void sort_algorithm_control(void *sort_algorithm_addr,
							struct sort_package_s sort_package, compare_t *comp)
{
	void (*sort_algorithm)(struct sort_package_s, compare_t * comp) = sort_algorithm_addr;

	sort_algorithm(sort_package, comp);
}

/**
 * @brief This function will return the specified sort algorithm's function address.
 *
 * @param data the pointer to the data list will give
 *
 * @return the specified sort algorithm's function address
 */

void *sort_algorithm_control_convert_type_to_func_addr(enum sort_algorithm_type type)
{
	void *func_addr_table = NULL;

	switch (type) {
		case QUICK_SORT:
			func_addr_table = sort_algorithm_control_quick_sort;
			break;
		case BUBBLE_SORT:
			func_addr_table = sort_algorithm_control_bubble_sort;
			break;
		default:
			break;
	}

	return func_addr_table;
}

/**
 * @brief This function will get the value of object.
 *
 * @param sort_package the package of the sort information
 * @param pos the position of the value
 * @param value_lhs the pointer to the left side value
 * @param value_rhs the pointer to the right side value
 *
 * @return if get the value of object successful
 *	- true	yes
 *	- false	no
 */

static inline bool sort_algorithm_control_get_value(struct sort_package_s sort_package,
													size_t pos,
													void **value_lhs,
													void **value_rhs)
{
	if (NULL == sort_package.get_value_method) {								/* Get the value */
		*value_lhs = (void *)((size_t)sort_package.object + pos * sort_package.mem_len);
		*value_rhs = (void *)((size_t)sort_package.object + (pos + 1) * sort_package.mem_len);
	} else {
		*value_lhs = sort_package.get_value_method(sort_package.object, pos);
		*value_rhs = sort_package.get_value_method(sort_package.object, pos + 1);
	}

	if (NULL == *value_lhs &&
		NULL == *value_rhs) {
		return false;
	}

	return true;
}

/**
 * @brief This function will sort the object by the compare().
 *
 * @param sort_package the information package of the sort
 * @param compare the compare() function
 *
 * @return void
 */

void sort_algorithm_control_quick_sort(struct sort_package_s sort_package,
									   compare_t *compare)
{
}

/**
 * @brief This function will sort the object by the compare().
 *
 * @param sort_package the information package of the sort
 * @param compare the compare() function
 *
 * @return void
 */

void sort_algorithm_control_bubble_sort(struct sort_package_s sort_package,
										compare_t *compare)
{
	char
		*value_lhs = NULL,
		*value_rhs = NULL;

	for (size_t cnt = 0; cnt < sort_package.len - 1; cnt++) {
		for (size_t ct = 0; ct < sort_package.len - cnt - 1; ct++) {
			if (!sort_algorithm_control_get_value(sort_package, ct, &value_lhs, &value_rhs)) {	/* Get the value */
				return;
			}

			if (compare(value_lhs, value_rhs, sort_package.mem_len)) {						    /* Compare the value */
				#if (SORT_ALGORITHM_CFG_DEBUG_EN)

				printf("sort_algorithm.bubble_sort.no.%d-%d: %d \"%s\" swap %d \"%s\" \r\n",
					   cnt, ct, ct, value_lhs, ct + 1, value_rhs);

				#endif // (SORT_ALGORITHM_CFG_DEBUG_EN)

				sort_package.swap_method(sort_package.object, ct, ct + 1);
			}
		}
	}
}