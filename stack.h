#ifndef __STACK_H
#define __STACK_H

#include "stdio.h"
#include "stdbool.h"
#include "malloc.h"

#define STACK_MAXSIZE       100

typedef struct LIFO_Stack_Info
{
    int stack_top;
    int stack_depth;
    bool stack_malloc;
}STACK_INFO_TYPEDEF;

typedef struct LIDO_Stack_Expection
{
    void (*full_stack)(void);
    void (*null_stack)(void);
}STACK_EXPECTION_TYPEDEF;

typedef struct Stack
{
    STACK_INFO_TYPEDEF __info;
    int* data;
    
    bool (*push)(struct Stack* stack, int atom);
    bool (*pop)(struct Stack* stack, int* atom);
    bool (*multi_pop)(struct Stack* stack, int* array, int depth);

    STACK_EXPECTION_TYPEDEF expection;
}STACK_TYPEDEF,*STACK_TYPEDEF_PTR;

typedef struct Stack_Control
{
 /*   struct
    {
        int* stack_addr[100];
    }__info;*/

    bool (*init)(STACK_TYPEDEF_PTR stack, int depth);
    bool (*free)(STACK_TYPEDEF_PTR stack);
}STACK_CONTROL_TYPEDEF;

STACK_CONTROL_TYPEDEF stack_ctrl;

#endif // __STACK_H