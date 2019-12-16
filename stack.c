#include "stack.h"

bool stack_control_init(STACK_TYPEDEF_PTR stack, int depth);
bool stack_control_free(STACK_TYPEDEF_PTR stack);

bool stack_push(STACK_TYPEDEF_PTR stack, STACK_DATA_TYPE atom);
bool stack_pop(STACK_TYPEDEF_PTR stack, STACK_DATA_TYPE* atom);
bool stack_multi_pop(STACK_TYPEDEF_PTR stack, STACK_DATA_TYPE* array, int size);

void stack_default_full_stacl_expection(void);
void stack_default_null_stacl_expection(void);
void stack_default_null_heap_expection(void);

bool stack_control_chain_stack_init(CHAIN_STACK_TYPEDEF_PTR stack, int depth);
bool stack_control_chain_stack_free(CHAIN_STACK_TYPEDEF_PTR stack);

bool chain_stack_push(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
bool chain_stack_pop(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE* atom);
bool chain_stack_multi_pop(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE* array, int size);

void chain_stack_default_full_stacl_expection(void);
void chain_stack_default_null_stacl_expection(void);
void chain_stack_default_null_heap_expection(void);

STACK_CONTROL_TYPEDEF stack_ctrl =
{
    stack_control_init,
    stack_control_free,
    {
        stack_control_chain_stack_init,
        stack_control_chain_stack_free
    }
};

bool stack_control_init(STACK_TYPEDEF_PTR stack,int depth)
{
    if ((stack->data = (char*)malloc(sizeof(char) * depth)) == NULL)
        return false;

    stack->__info.stack_malloc = true;
    stack->__info.stack_depth = depth;
    stack->__info.stack_top = 0;

    stack->push = stack_push;
    stack->pop = stack_pop;
    stack->multi_pop = stack_multi_pop;

    stack->expection.full_stack = stack_default_full_stacl_expection;
    stack->expection.null_stack = stack_default_null_stacl_expection;
    stack->expection.null_heap = stack_default_null_heap_expection;

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

bool stack_push(STACK_TYPEDEF_PTR stack, STACK_DATA_TYPE atom)
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

bool stack_pop(STACK_TYPEDEF_PTR stack, STACK_DATA_TYPE* atom)
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

void stack_default_null_heap_expection(void)
{
    printf("heap_null_expectopn. \r\n");
}

bool stack_multi_pop(STACK_TYPEDEF_PTR stack, STACK_DATA_TYPE* array,int size)
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

bool stack_control_chain_stack_init(CHAIN_STACK_TYPEDEF_PTR chain_stack, int max_depth)
{
    if ((chain_stack->top = (CHAIN_STACK_NODE_TYPEDEF_PTR)malloc(sizeof(CHAIN_STACK_NODE_TYPEDEF))) == NULL)
    {
        chain_stack->expection.null_heap();

        return false;
    }

    chain_stack->__info.stack_crt_depth = 0;
    chain_stack->__info.stack_max_depth = max_depth;

    chain_stack->push = chain_stack_push;
    chain_stack->pop = chain_stack_pop;
//    chain_stack->multi_pop = chain_stack_multi_pop;

    chain_stack->expection.full_stack = chain_stack_default_full_stacl_expection;
    chain_stack->expection.null_stack = chain_stack_default_null_stacl_expection;
    chain_stack->expection.null_heap = chain_stack_default_null_heap_expection;

    return true;
}

bool stack_control_chain_stack_free(CHAIN_STACK_TYPEDEF_PTR chain_stack)
{
    if (chain_stack->__info.stack_malloc == true)
    {
        free(chain_stack->top);

        chain_stack->__info.stack_malloc = false;
        chain_stack->top = NULL;
    }

    return true;
}

bool chain_stack_push(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom)
{
    CHAIN_STACK_NODE_TYPEDEF_PTR 
        stack_node_temp = (CHAIN_STACK_NODE_TYPEDEF_PTR)calloc(1,sizeof(CHAIN_STACK_NODE_TYPEDEF));

 //   char* stack_node_data_temp = (char*)calloc(2, sizeof(char));

    if (stack_node_temp == NULL)
    {
        chain_stack->expection.null_heap();

        return false;
    }
    if(chain_stack->__info.stack_max_depth <= chain_stack->__info.stack_crt_depth)
    {
        chain_stack->expection.full_stack();

        return false;
    }

    stack_node_temp->data = atom;
    stack_node_temp->next = chain_stack->top->next;

    chain_stack->top->next = stack_node_temp;
    
    chain_stack->__info.stack_crt_depth++;

    return true;
}

bool chain_stack_pop(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE* atom)
{
    CHAIN_STACK_NODE_TYPEDEF_PTR
        stack_node_temp = NULL;

    if (chain_stack->__info.stack_crt_depth == 0)
    {
        chain_stack->expection.null_stack();

        return false;
    }
    
    stack_node_temp = chain_stack->top->next;

    chain_stack->top->next = stack_node_temp->next;

    *atom = stack_node_temp->data;

    chain_stack->__info.stack_crt_depth--;

    free(stack_node_temp);    /* 释放存储空间 */

    return true;
}

void chain_stack_default_full_stacl_expection(void)
{
    printf("stack_full_expectopn. \r\n");
}

void chain_stack_default_null_stacl_expection(void)
{
    printf("stack_null_expectopn. \r\n");
}

void chain_stack_default_null_heap_expection(void)
{
    printf("heap_null_expectopn. \r\n");
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
  //  char atom = 0;
  //  char array[100] = { 0 };
  //  STACK_TYPEDEF stack;

  //  stack_ctrl.init(&stack,100);

  //  for (size_t i = 0; i < 10; i++)
  //  {
  //      stack.push(&stack, i + '0');
  //  }
  //  stack.multi_pop(&stack, array,10);

  //stack_pop(&stack, &atom);

  //printf("pop: %d ", atom);

  //  for (size_t i = 0; i < 10; i++)
  //  {
  //      printf("pop: %c ", array[i]);
  //  }

  //  stack_ctrl.free(&stack);

  //  printf("\r\n");

    char atom = 0;
    char array[100] = { 0 };
    CHAIN_STACK_TYPEDEF chain_stack;

    stack_ctrl.chain_stack.init(&chain_stack, 10);

    for (size_t i = 0; i < 10; i++)
    {
        chain_stack.push(&chain_stack, i + '0');
    }

    for (size_t i = 0; i < 10; i++)
    {
        chain_stack.pop(&chain_stack, &array[i]);

     
    }

    stack_ctrl.free(&chain_stack);

    printf("\r\nend\r\n");

    //int
    //    array[10] = { 0,1,3,0,5,6,7,0,9,1 },
    //    rule[10] = { 1,2,3,4,5,6,7,8,9,1 };

    //int size = 10;

    //data_verify_percent(array,rule,size);

    //printf("*:%f \r\n", data_verify_percent(array, rule, size));
    //printf("_:%f \r\n", _data_verify_percent(array, rule, size));

    return;
}
