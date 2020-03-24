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

/**
 * @brief This type is the sort algorithm category enum.
 */

void *sort_control_algorithm_address_table[] = {
	sort_control_bubble_sort,
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

static inline bool
sort_control_get_value(struct sort_package_s sort_package,
					   size_t pos,
					   void **value_lhs,
					   void **value_rhs);

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

extern inline errno_t
sort_control(enum sort_algorithm_type type,
			 struct sort_package_s package)
{
	sort_t sort = sort_control_algorithm_address_table[type];

	return sort(package);
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

static inline bool
sort_control_get_value(struct sort_package_s sort_package,
					   size_t pos,
					   void **value_lhs,
					   void **value_rhs)
{
	if (NULL == sort_package.object_operator.get_value_ptr) {								/* Get the value */
		*value_lhs = *(void **)((size_t)sort_package
							  .object_ptr + pos * sort_package.mem_len);
		*value_rhs = *(void **)((size_t)sort_package
							  .object_ptr + (pos + 1) * sort_package.mem_len);
	} else {
		*value_lhs = sort_package.object_operator
			.get_value_ptr(sort_package.object_ptr, pos);
		*value_rhs = sort_package.object_operator
			.get_value_ptr(sort_package.object_ptr, pos + 1);
	}

	if (NULL == *value_lhs &&
		NULL == *value_rhs) {
		return false;
	}

	return true;
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

static inline bool
sort_control_get_address(struct sort_package_s sort_package,
						 size_t pos,
						 void **address_lhs,
						 void **address_rhs)
{
	if (NULL == sort_package.object_operator.get_address_ptr) {								/* Get the address */
		*address_lhs = (void *)((size_t)sort_package
								.object_ptr + pos * sort_package.mem_len);
		*address_rhs = (void *)((size_t)sort_package
								.object_ptr + (pos + 1) * sort_package.mem_len);
	} else {
		*address_lhs = sort_package.object_operator
			.get_address_ptr(sort_package.object_ptr, pos);
		*address_rhs = sort_package.object_operator
			.get_address_ptr(sort_package.object_ptr, pos + 1);
	}

	if (NULL == *address_lhs &&
		NULL == *address_rhs) {
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

errno_t sort_control_bubble_sort(struct sort_package_s package)
{
	assert(package.count);
	assert(package.mem_len);
	assert(package.object_ptr);

	static char
		*value_lhs,
		*value_rhs;
	static void
		*address_lhs,
		*address_rhs;

	if (0u == package.mem_len_key) {
		package.mem_len_key = package.mem_len;												/* Default the memory length of the object's compare key */
	}

	if (NULL == package.compare_ptr) {														/* Default the compare function */
		package.compare_ptr = SORT_CFG_DEFAULT_COMPARE_ADDRESS;
	}

	if (NULL == package.swap_ptr) {															/* Default the swap function */
		package.swap_ptr = SORT_CFG_DEFAULT_SWAP_ADDRESS;
	}

	for (size_t cnt = 0; cnt < package.count - 1; cnt++) {
		for (size_t ct = 0; ct < package.count - cnt - 1; ct++) {
			if (!sort_control_get_value(package, ct, &value_lhs, &value_rhs)) {				/* Get the value */
				return 1;
			}

			if (package.compare_ptr(value_lhs, value_rhs, package.mem_len_key)) {			/* Compare the value */
				#if (SORT_CFG_DEBUG_EN)

				printf("sort_algorithm.bubble_sort.no.%d-%d: %d \"%s\" swap %d \"%s\" \r\n",
					   cnt, ct, ct, value_lhs, ct + 1, value_rhs);

				#endif // (SORT_CFG_DEBUG_EN)

				if (!sort_control_get_address(package, ct, &address_lhs, &address_rhs)) {
					return 2;
				}

				package.swap_ptr(address_lhs, address_rhs, package.mem_len);
			}
		}
	}

	return 0;
}