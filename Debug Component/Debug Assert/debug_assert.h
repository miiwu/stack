/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_ASSERT_H
#define __DEBUG_ASSERT_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			debug assert control variable.										                */
#define DEBUG_ASSERT_CONTROL_VARIABLE(variable, comp, value_type, value, print)                         \
	do {																								\
		assert((((value_type)(variable)) comp ((value_type)(value))));	                                \
        if (!(((value_type)(variable)) comp ((value_type)(value)))) {                                   \
            print;                                                                                      \
            while (1) {                                                                                 \
            }                                                                                           \
        }                                                                                               \
	} while (0)

/* Define			debug assert control pointer.										                */
#define DEBUG_ASSERT_CONTROL_POINTER(pointer, print)							                        \
	DEBUG_ASSERT_CONTROL_VARIABLE(pointer, !=, void*, NULL, print)

/* Define			debug assert control variable with printf output.								    */
#define DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(variable, comp, value_type, value)                         \
	do {																								\
		assert((((value_type)(variable)) comp ((value_type)(value))));	                                \
        if (!(((value_type)(variable)) comp ((value_type)(value)))) {                                   \
            printf("Assert Failed: \r\n\tfunc:\"%s\"                                                    \
                assert:\"%s %s %s\"\r\n\tfile:\"%s\" line:%ld\r\n",                                     \
                __FUNCTION__, #variable, #comp, #value,                                                 \
                __FILE__, (size_t)__LINE__);                                                            \
            while (1) {                                                                                 \
            }                                                                                           \
        }                                                                                               \
	} while (0)

/* Define			debug assert control pointer with printf output.								    */
#define DEBUG_ASSERT_CONTROL_POINTER_PRINTF(pointer)							                        \
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(pointer, !=, void*, NULL)

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

#endif // !__DEBUG_ASSERT_H