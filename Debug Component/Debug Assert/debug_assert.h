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

/* Define			debug assert control expression.										            */
#define DEBUG_ASSERT_CONTROL_EXPRESSION(expression, ...)                                                \
	do {																								\
		assert((expression));	                                                                        \
        if (!(expression)) {                                                                            \
            __VA_ARGS__;                                                                                \
            while (1) {                                                                                 \
            }                                                                                           \
        }                                                                                               \
	} while (0)

/* Define			debug assert control variable.										                */
#define DEBUG_ASSERT_CONTROL_VARIABLE(variable, comp, value_type, value, ...)                           \
	DEBUG_ASSERT_CONTROL_EXPRESSION((((value_type)(variable)) comp ((value_type)(value))),              \
                                    __VA_ARGS__)

/* Define			debug assert control pointer.										                */
#define DEBUG_ASSERT_CONTROL_POINTER(pointer, ...)							                            \
	DEBUG_ASSERT_CONTROL_VARIABLE(pointer, !=, void*, NULL,                                             \
                                  __VA_ARGS__)

/* Define			debug assert control expression with printf output.								    */
#define DEBUG_ASSERT_CONTROL_EXPRESSION_PRINTF(expression)                                              \
   DEBUG_ASSERT_CONTROL_EXPRESSION(expression,                                                          \
                                   printf("Assert Failed: \"%s\"\r\n    "                               \
                                          "func:\"%s\"\r\n    "                                         \
                                          "file:\"%s\" line:%ld\r\n",                                   \
                                          #expression,                                                  \
                                          __FUNCTION__,                                                 \
                                          __FILE__, (size_t)__LINE__))

/* Define			debug assert control variable with printf output.								    */
#define DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(variable, comp, value_type, value)                         \
	DEBUG_ASSERT_CONTROL_EXPRESSION_PRINTF((((value_type)(variable)) comp ((value_type)(value))))

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