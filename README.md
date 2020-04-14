# Stack - Some Data Structures Together

## About

This package contains some simple data structures together.

## Status

![Constructing](<https://github.com/Miao-Mico/stack/blob/master/constructing.png>)

## Feature

- **Generic Type Element**

  In principle, you can store `any type data` into all these data structure, by means of appointing `the assign method` and `the free method` manually.

  This is a demo show my thought, it may have some problem and may not be very good, but we will make it look greater, won't we?

  ```c
  /* Generic type element Assign and Free function prototypes typedef.        */
  typedef errno_t(*genric_type_element_assign_t)(void *gnc, void *src);
  typedef errno_t(*genric_type_element_free_t)(void *gnc);
  
  /* Generic type element demo.                                               */
  struct generic_type_demo_s {
      char symbol;
      
      char *string;
      
      int number;
  };
  
  /* Generic type element Assign function,
      function may perform like copy the pointer src to the pointer gnc,
      it may allocate memory space for the pointer in the generic structure   */
  errno_t generic_type_element_assign(void *gnc, void *src)
  {
      assert(gnc);
      assert(src);
      
      /* The length of these data type below must be absolutely CERTAIN,
          because it may use the memcpy(), for safety,
          Or you need to allocate the memory for the type in advance,
          then Store the address of the memory to the container,
          when this element is useless, deallocate it yourself.               */
      
      struct generic_type_demo_s
          *generic_type_gnc = gnc,
          *generic_type_src = src;
      
      /* This are pointer,i want to store many "*tack",
          so malloc it as count * sizeof("stack").                            */
      if (NULL == (generic_type_gnc->string = calloc(1, sizeof("stack")))) {
          return -1;
      }
      
      /* Memcpy the content of the pointer point to.                          */
      if (NULL == memcpy(generic_type_gnc->string, generic_type_src->string,
                         sizeof("stack"))) {
          return 1;
      }
      
      /* Copy the value of src to the gnc.                                    */
      generic_type_gnc->symbol = generic_type_src->symbol;
      generic_type_gnc->number = generic_type_src->number;
      
      return 0;
  }
  
  /* Generic type element Free function,
      function may perform like free the memory space the assign() allocated. */
  errno_t generic_type_element_free(void *gnc)
  {
      assert(gnc);
      
      /* Free the memory space allocated at the assign().                     */
      free(((struct generic_type_demo_s *)gnc)->string);
      
      return 0;
  }
  ```

- **Poly-Instantiation**

  I can only make sure it can `initialize multiple instances`, but `can't guarantee thread safety`, because i even have no experience at that place.

- **Integrated  Control Structure**

  You can use this `xxx_ctrl` to code more convenient in the IDE or Editor with `intelligense`.

  If you don't like it, you can `Disable it` by `xxx_CFG_INTEGRATED_STRUCTURE_MODE_EN` at it's .h file.

  Here is the template referenced From stack.h:

  ```c
  /**
   * @brief This type will contain all the stack control functions.
   */
  
  struct stack_control_s {
      struct {
          /* @brief This function will initialize the stack struct and the specified container. */
          errno_t (*init)(...);
          
          /* @brief This function will destroy the stack struct.                                */
          errno_t (*destroy)(...);
          
          ...
      }configuration;
      
      struct {
          /* @brief This function will return reference to the top element in the stack.        */
          void *(*top)(...);
          
          ...
      }element_access;
      
      ...
  };
  
  errno_t any_function(void *arg_list)
  {
      assert(arg_list);
      
      /* Both two methods call the init function of the stack are correct.                      */
      stack_ctrl.configuration.init(...);
      stack_control_configration_init(...);
  }
  ```
  
  

- **Divisible-To-Independent-Module**

  If you want to use List, you need to include all those files.

  If it is a member of any family, include the file of that family.

  Common family files include:

  1. x.c and x.h
  2. x_cfg.h
  3. x_def.h

- **Influenced By Cppreference**

  Count in? I means it may be some where is familiar with the CPP? May just the name, but learn from it  is endless.

## Include

> Note: The `emplace()` of all these containers is not completed and it is ignored on this include list.

- Container
  - Container Adaptor
    - [x] Stack

    - [x] Queue

    - [ ] Priority Queue

      Only the sort part of list-family container is completed.

    - [ ] ...
  - Sequence Container
    - Array Family
      - [x] Array
      - [x] Vector
    - List Family
      - [x] Forward_list
      
      - [ ] List
      
        The  push_back() and pop_back() is not completed.
    - ...
  - Tree
    - [x] Binary Search Tree
    - [x] Red Black Tree
    - [ ] AVL Tree
    - [x] B Tree
    - [ ] B+ Tree
    - [ ] ...

- Algorithm

  - Sort
    - [x] Bubble Sort
    - [ ] ...
  - Compare
    - [x] Greater
    - [x] Lesser
    - [ ] ...
  - Substring Search
    - [x] Brute Force algorithm
    - [x] Sunday algorithm
    - [ ] ...

- Allocator

  - [x] Allocator common

    It is simple add a shell for the malloc() and free().

  - [ ] ...

- Iterator

  - [x] Input iterator
- [ ] Forward iterator
  
  - [ ] Bidirectional iterator
- [x] Random access iterator
  - [ ] Output iterator
  - [x] _modify
  
- Debug Component

  - Assert

    A try on function entry check definition file.

    ```c
  void debug_assert(char *pointer, size_t variable)
    {
      DEBUG_ASSERT_CONTROL_POINTER_PRINTF(pointer);
        DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(variable, >= , int, 0);
      DEBUG_ASSERT_CONTROL_EXPRESSION_PRINTF(true == true);
        
        // ...
    }
    ```
  
  - Error
  
    A try on function  error return.
  
    The using sample is here:
  
    ```c
  struct debug_error_structure_s {
        errno_t err;    /* This is the must */
  
        char *string;
    };
    
    errno_t debug_error_errno(void)
    {
        DEBUG_ERROR_CONTROL_ERRNO_INIT(1, 1);
        /* DEBUG_ERROR_CONTROL_INIT(errno_t, 2, 0, 1); */
    
        if (true) {
            DEBUG_ERROR_CONTROL_JUMP(1);
        }
    
        DEBUG_ERROR_CONTROL_EXIT(printf("error:%d\r\n",
                                        DEBUG_ERROR_CONTROL_ERROR_VAL),
                                 printf("error:%d\r\n",
                                        DEBUG_ERROR_CONTROL_RETURN_VAL));
    }
    
    struct debug_error_structure_s debug_error_structure(void)
    {
        DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct debug_error_structure_s, 1, 1);
        /* DEBUG_ERROR_CONTROL_INIT(struct debug_error_structure_s, 2, 0, 1); */
    
        DEBUG_ERROR_CONTROL_RETURN_VAL.string = "debug_error_structure";
    
        if (true) {
            DEBUG_ERROR_CONTROL_JUMP(1);
        }
    
        DEBUG_ERROR_CONTROL_EXIT(printf("error:%d\r\n",
                                        DEBUG_ERROR_CONTROL_ERROR_VAL),
                                 printf("string:\"%s\"\r\n",
                                        DEBUG_ERROR_CONTROL_RETURN_VAL.string));
    }
    ```
    
  - Stack back trace
  
    I think of it because i want to make sure the malloc() and the free() can match themselves.
  
    It can get much information from the stack trace, of course, it depends on `the WIN32 Api`, you can watch more from the MS's doc, [click here](https://docs.microsoft.com/en-us/windows/win32/debug/capturestackbacktrace).
  
    Now, it only support the windows platform.
  
    The API is `CaptureStackBackTrace()`;
  
    ```c
    #include <DbgHelp.h>
    
    #pragma comment(lib, "Dbghelp.lib")
    
    /* The Lib environment should be upward. */
    
    USHORT WINAPI CaptureStackBackTrace(
      _In_      ULONG  FramesToSkip,
      _In_      ULONG  FramesToCapture,
      _Out_     PVOID  *BackTrace,
      _Out_opt_ PULONG BackTraceHash
    );
    ```

All these `...` mean they may be ready to add.

## Application

[AT Instruction Set Suite](<https://github.com/Miao-Mico/at>): another repo of mine.

## Reference

- [cppreference.com](<http://en.cppreference.com/w/>)/[zh.cppreference]([https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5](https://zh.cppreference.com/w/首页)): 

  A website can provide programmers with a complete online reference for the C and C++ languages and standard libraries.

  You can `change language` to your mother language `at the bottom of the website`.

- [visualized data structures and algorithms](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html): 

  A website have visualizations for much of the data structures and algorithms.

## Thanks

All the people who have helped and inspired me.

## License

[Apache-2.0](https://github.com/Miao-Mico/stack/blob/master/LICENSE)