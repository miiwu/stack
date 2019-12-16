#ifndef __STACK_H
#define __STACK_H

#include "stdio.h"
#include "stdbool.h"
#include "malloc.h"

#define STACK_MAXSIZE       100

#define STACK_DATA_TYPE         char
#define CHAIN_STACK_DATA_TYPE   char

typedef struct Stack_Info
{
    size_t stack_top;
    size_t stack_depth;
    bool stack_malloc;
}STACK_INFO_TYPEDEF;

typedef struct Stack_Expection
{
    void (*full_stack)(void);
    void (*null_stack)(void);
    void (*null_heap)(void);
}STACK_EXPECTION_TYPEDEF;

typedef struct Stack
{
    STACK_INFO_TYPEDEF __info;
    char* data;
    
    bool (*push)(struct Stack* stack, char atom);
    bool (*pop)(struct Stack* stack, char* atom);
    bool (*multi_pop)(struct Stack* stack, char* array, size_t depth);

    STACK_EXPECTION_TYPEDEF expection;
}STACK_TYPEDEF,*STACK_TYPEDEF_PTR;

typedef struct Chain_Stack_Info
{
    size_t stack_crt_depth;
    size_t stack_max_depth;
    bool stack_malloc;
}CHAIN_STACK_INFO_TYPEDEF;

typedef struct Chain_Stack_Node
{
    struct Chain_Stack_Node* next;
    CHAIN_STACK_DATA_TYPE data;
}CHAIN_STACK_NODE_TYPEDEF,* CHAIN_STACK_NODE_TYPEDEF_PTR;

typedef struct Chain_Stack_Expection
{
    void (*full_stack)(void);
    void (*null_stack)(void);
    void (*null_heap)(void);
}CHAIN_STACK_EXPECTION_TYPEDEF;

typedef struct Chain_Stack
{
    CHAIN_STACK_INFO_TYPEDEF __info;
    CHAIN_STACK_NODE_TYPEDEF_PTR top;                           // 已知头节点

    bool (*push)(struct Chain_Stack* stack, CHAIN_STACK_DATA_TYPE atom);
    bool (*pop)(struct Chain_Stack* stack, CHAIN_STACK_DATA_TYPE* atom);
    bool (*multi_pop)(struct Chain_Stack* stack, CHAIN_STACK_DATA_TYPE* array, size_t depth);

    CHAIN_STACK_EXPECTION_TYPEDEF expection;
}CHAIN_STACK_TYPEDEF, * CHAIN_STACK_TYPEDEF_PTR;

typedef struct Stack_Control
{

    bool (*init)(STACK_TYPEDEF_PTR stack, size_t depth);
    bool (*free)(STACK_TYPEDEF_PTR stack);

    struct
    {
        bool (*init)(CHAIN_STACK_TYPEDEF_PTR stack, size_t depth);
        bool (*free)(CHAIN_STACK_TYPEDEF_PTR stack);
    }chain_stack;

}STACK_CONTROL_TYPEDEF;

STACK_CONTROL_TYPEDEF stack_ctrl;

#endif // __STACK_H