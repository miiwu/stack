#include "stack.h"

bool stack_control_init(STACK_TYPEDEF_PTR stack, int depth);
bool stack_control_free(STACK_TYPEDEF_PTR stack);

bool stack_push(STACK_TYPEDEF_PTR stack, int atom);
bool stack_pop(STACK_TYPEDEF_PTR stack, int* atom);
bool stack_multi_pop(STACK_TYPEDEF_PTR stack, int* array, int size);

void stack_default_full_stacl_expection(void);
void stack_default_null_stacl_expection(void);

STACK_CONTROL_TYPEDEF stack_ctrl =
{
    stack_control_init,
    stack_control_free
};

bool stack_control_init(STACK_TYPEDEF_PTR stack,int depth)
{
    if ((stack->data = (int*)malloc(sizeof(int) * depth)) == NULL)
        return false;

    stack->__info.stack_malloc = true;
    stack->__info.stack_depth = depth;
    stack->__info.stack_top = 0;

    stack->push = stack_push;
    stack->pop = stack_pop;
    stack->multi_pop = stack_multi_pop;

    stack->expection.full_stack = stack_default_full_stacl_expection;
    stack->expection.null_stack = stack_default_null_stacl_expection;

    return true;
}

bool stack_control_free(STACK_TYPEDEF_PTR stack)
{
    if (stack->__info.stack_malloc == true)
    {
        free(stack->data);

        stack->__info.stack_malloc = false;
        stack->data = NULL;
        
    }

    return true;
}

bool stack_push(STACK_TYPEDEF_PTR stack,int atom)
{
    if(stack->__info.stack_top < stack->__info.stack_depth)    // 如果没有满栈
    {
        stack->data[++stack->__info.stack_top] = atom;

        return true;
    }
    else
    {
        stack->expection.full_stack();                           // stack_exception

        return false;
    }
}

bool stack_pop(STACK_TYPEDEF_PTR stack,int* atom)
{
    if(stack->__info.stack_top > 0)                            // 如果没有空栈
    {
        *atom = stack->data[stack->__info.stack_top];
        stack->__info.stack_top --;

        return true;
    }
        else
    {
        stack->expection.null_stack();                           // stack_exception

        return false;
    }
}

void stack_default_full_stacl_expection(void)
{
    printf("stack_full_expectopn. \r\n");
}

void stack_default_null_stacl_expection(void)
{
    printf("stack_null_expectopn. \r\n");
}

bool stack_multi_pop(STACK_TYPEDEF_PTR stack, int* array,int size)
{
    if (stack->__info.stack_top >= size)                            // 如果没有空栈
    {
        for (size_t cnt = size; cnt > 0; cnt--)
        {
            *(array + cnt - 1) = stack->data[stack->__info.stack_top--];
        }
        
        return true;
    }
    else
    {
        stack->expection.null_stack();                           // stack_exception

        return false;
    }
}

int stack_get_top(STACK_TYPEDEF_PTR stack)
{
    int temp = 0;

    if(stack_pop(stack,&temp) == false)
        return false;

    return temp;
}

float _data_verify_percent(int* input, int* rule,int sizeof_rule)     // 数据正确率
{
    float perc = 0;
    int 
        correct_num = 0,
        order_correct_num = 0;

    for (size_t cnt = 0; cnt < sizeof_rule; cnt++)
    {
        if (input[cnt] == rule[cnt])
        {
            correct_num++;
        }
    }

    perc = correct_num / (float)sizeof_rule;

    return perc;
}

float data_verify_percent(int* input, int* rule, int sizeof_rule)     // 数据正确率
{
    float perc = 0;

    int record_num[11] = {0};
    int
        record_part_num = 0,
        record_part[10] = { 0 },
        record_part_param[10][10] = { 0 };

    int correct_num = 0;

    for (size_t cnt = 0; cnt < sizeof_rule; cnt++)
    {
        for (size_t i = record_num[cnt]; i < sizeof_rule; i++)
        {
            if (input[cnt] == rule[i])
            {
                record_num[cnt+1] = i+1;
                
                record_part_param[record_part_num][record_part[record_part_num]] = rule[i];
                record_part[record_part_num]++;

                break;
            }
            else if (record_num[cnt] != 0 && cnt != 0)
            {
                record_num[cnt + 1] = cnt + 1;

                record_part_num++;

                break;
            }
        }
    }

    for (size_t cnt = 0; cnt <= record_part_num; cnt++)
    {
        correct_num += record_part[cnt];
    }

    perc = correct_num / (float)sizeof_rule;

    return perc;
}

void main()
{
    int atom = 0;
    int array[100] = { 0 };
    STACK_TYPEDEF stack;

    stack_ctrl.init(&stack,100);

    for (size_t i = 0; i < 10; i++)
    {
        stack.push(&stack, i);
    }
    stack.multi_pop(&stack, array,10);

//  stack_pop(&stack, &atom);

//  printf("pop: %d ", atom);

    for (size_t i = 0; i < 10; i++)
    {
        printf("pop: %d ", array[i]);
    }

    stack_ctrl.free(&stack);

    printf("\r\n");

    //int
    //    array[10] = { 1,1,3,0,5,6,7,0,9,1 },
    //    rule[10] = { 1,2,3,4,5,6,7,8,9,1 };

    //int size = 10;

    //data_verify_percent(array,rule,size);

    //printf("*:%f \r\n", data_verify_percent(array, rule, size));
    //printf("_:%f \r\n", _data_verify_percent(array, rule, size));

    return;
}
