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
  
  struct generic_type_demo_t {
  	char symbol;
  
  	char *string;
  
  	int number;
  }generic_demo;
  
  
  void generic_type_demo_assign_method(void *gnc, void *src)					
      /* function may preform like copy the pointer src to the pointer gnc */
  {
  	assert(gnc);
  	assert(src);
  
  	struct generic_type_t
  		*generic_type_gnc = gnc,
  		*generic_type_src = src;
  
  	generic_type_gnc->string = calloc(1, sizeof("stack"));							/* those are pointer,so malloc it as count*sizeof("stack"),the sizeof("stack") 			will be the memory size of the type the pointer point to */
  
  	if (NULL == generic_type_gnc->string) {
  		return;
  	}
  
  	generic_type_gnc->symbol = generic_type_src->symbol;							/* both below are the not-pointer type handle method */
  	memcpy(&generic_type_gnc->number, &generic_type_src->number, sizeof(int));
  
  	memcpy(generic_type_gnc->string, generic_type_src->string, sizeof("stack"));	/* memcpy the content of the pointer point to */
  }
  
  void generic_type_demo_free_method(void *gnc)
      /* function may preform like free the pointer gnc */
  {
  	struct generic_type_t
  		*generic_type_gnc = gnc;
  
  	memset(generic_type_gnc->string, '0', sizeof("stack"));
  
  	free(generic_type_gnc->string);													/* free the memory space the calloc on the assign function */
  }
  ```

- **Poly-Instantiation**

  I can only make sure it can `initialize multiple instance`, but `can't guarantee thread safety`, because i even have no experience at that place.

- **Impact By Cppreference**

  Count in? I means it may be some where is familiar with the CPP? May just the name, but learn from it  is endless.

## Include

- Container
  - Container Adaptor
    - Stack
    - Queue
    - ...
  - Sequence Container
    - Array Family
      - Array
      - Vector
    - List Family
      - Forward_list
      - List
    - ...
  - Tree
    - Binary Search Tree
    - Red Black Tree
    - B Tree
    - ...

- Algorithm

  - Sort
    - Bubble Sort
    - ...
  - Compare
    - Greater
    - Lesser
    - ...

- Allocator

  - Allocator common

    It is simple add a shell for the malloc() and free().

  - ...

- Debug Component

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

## Reference

[cppreference.com](<http://en.cppreference.com/w/>)

## Thanks

All the people who have helped and inspired me.

## License

[Apache-2.0](https://github.com/Miao-Mico/stack/blob/master/LICENSE)