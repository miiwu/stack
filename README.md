# Stack - 有些算法和数据结构

## 目录

* [版本](#版本)
* [关于](#关于)
* [状态](#状态)
* [特性](#特性)
* [包含](#包含)
* [应用](#应用)
* [引用](#引用)
* [致谢](#致谢)
* [许可](#许可)

<small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc / 由 markdown-toc 项目生成</a></i></small>

## 版本

[English Version](https://github.com/Miao-Mico/stack/blob/_multi_projects_solution/.doc/.README/README.en.md)

## 关于

这个项目包含一些数据结构、算法实现以及对 C++ 某些概念的拙劣模仿。

恶魔喵喵咩咩嘛，也不能叫模仿吧，毕竟我也没有用过 C++ 写过啥东西，也不太了解，只是在看到一些他的概念之后，想用用。

## 状态

![建设暂时搁置ing](<https://github.com/Miao-Mico/stack/blob/master/constructing.png>)

**暂时搁置中。如果有更新也是在其他分支。**

## 特性

- **泛型数据存储**

  原则上，你可以往数据结构里存入任何类型数据（最终都会被降格成 void 指针指向的内存区域，所以内存长度必须是一定的），而且你可以选择性的指定 `the assign method` 用于复制和 `the free method` 和销毁 ，默认 `the assign method`  使用 `memcpy()` ，默认 `the free method` 什么也不干 。

  下面是一个展示想法的小示例，他或者我的想法一起都可能不完善，但是这就需要大家提点建议啥的啦，哈哈哈。

  ```c
  
  struct generic_type_demo_s {
  	char symbol;
  
  	char *string;
  
  	int number;
  };
  
  /* 复制，根据类型合理复制副本 */
  errno_t generic_type_element_assign(void *gnc, void *src)
  {
  	assert(gnc);
  	assert(src);
  
  	/* 类型成员，如果做不到长度一定，在这里动态分配内存，在 free() 里面自行解分配。 */
  
  	struct generic_type_demo_s
  		*generic_type_gnc = gnc,
  		*generic_type_src = src;
  
  	/* 这里是 char* ，所以分配内存，字符串的最大长度定为 sizeof("stack") */
  	if (NULL == (generic_type_gnc->string = calloc(1, sizeof("stack")))) {
  		return -1;
  	}
  
  	/* 复制字符串到副本 */
  	if (NULL == memcpy(generic_type_gnc->string, generic_type_src->string,
  					   sizeof("stack"))) {
  		return 1;
  	}
  
  	/* 复制非指针类型 */
  	generic_type_gnc->symbol = generic_type_src->symbol;
  	generic_type_gnc->number = generic_type_src->number;
  
  	return 0;
  }
  
  /* 分配，解分配 assign() 中分配的内存 */
  errno_t generic_type_element_free(void *gnc)
  {
  	assert(gnc);
  
  	free(((struct generic_type_demo_s *)gnc)->string);
  
  	return 0;
  }
  
  ```

- **多实例化**

  这个只能确定一种数据结构能被多实例化，被多次初始化，因为他们的信息块是分开的。

  但是不知道多线程那块怎么样，就是不知道，没接触过，相关的问题在这里也不讨论了。

- **集成结构体控制**

  你可以使用 `xxx_ctrl/xxx_control` 这样的结构体来访问所有可用的函数，个人以为在有智能提示的 IDE 或编辑器里面可能更优雅点，：）。

  ~~如果你不喜欢，你可以在各自的头文件禁用 `xxx_CFG_INTEGRATED_STRUCTURE_MODE_EN` 这个宏来关闭它。（大多数时候是没必要的吧，不关不用，也占用不了几个字节，主要是我没有在引用的地方不使用这种方法，以后再改过去）~~。

  下面是从 stack.h 引用的示例：

  ```c
  
  struct stack_control_s {
  	struct {
  		errno_t (*init)(...);
          ...
  	}configuration;
  	...
  };
  
  errno_t any_function(void *arg_list)
  {
      assert(arg_list);
      
  	/* 这两种访问函数方式都是正确的 */
      stack_ctrl.configuration.init(...);
      stack_control_configration_init(...);
  }
  
  ```
  
  
  
- **模块可分割独立**

  举个栗子，如果只想要 list 而不想用其他的，只需要跟着文件递归关系包含相关的就可以了。

- **受 C++ 影响**

  这个？能算吗？哈哈，就是上头说的啦，相关概念或者命名啥的。

## 包含

> 注意: 所有数据结构的 `emplace()` 都没有实现。

- Container / 容器
  - Container Adaptor / 容器适配器
    - [x] Stack / 堆栈

    - [x] Queue / 队列

    - [ ] Priority Queue / 优先级队列

      排序方法有待重写。

    - [ ] ...
  - Sequence Container / 序列容器
    - Array Family / 数组家族
      - [x] Array / 数组
      - [x] Vector / 向量
    - List Family / 链表家族
      - [x] Forward_list / 前向链表
      
      - [ ] List / 链表
      
        push_back() 和 pop_back() 未完成。
    - ...
  - Tree / 树
    - [x] Binary Search Tree / 二叉搜索树
    - [x] Red Black Tree / 红黑树
    - [ ] AVL Tree / 平衡二叉树
    - [x] B Tree / B 树
    - [ ] B+ Tree / B+ 树
    - [ ] ...

- Algorithm / 算法

  - Sort / 排序
    - [x] Bubble Sort / 冒泡排序
    - [ ] ...
  - Compare / 比较
    - [x] Greater / 大于
    - [x] Lesser / 小于
    - [x] Equal / 等于
    - [ ] ...
  - Substring Search / 子串字符匹配
    - [x] Brute Force algorithm / 暴力匹配
    - [x] Sunday algorithm
    - [ ] ...

- Allocator / 分配器

  - [x] Allocator common / 普通分配器

    就是给语言的 calloc() 和 free() 套个壳而已。

  - [ ] ...

- Iterator / 迭代器

  - [ ] ...
  
- Self-Define Library

  - Platform / 平台

    包含平台相关的头文件。

  - Micro / 宏

    一些预处理器宏。

  - Log / 日志、记录

    可以为 Assert 和 Error  提供接口。

    默认输出接口为 `printf()`，你可以通过 `LOG_CFG_LOGGER`，改成你想要的。

    ```c
    
    LOG("i will log something");
    LOG_DIAGNOSE("i will log something, with the head of __FUNCTION__");
    
    ```
    
  - Assert / 断言

    尝试着用来断言函数入口参数。

    ```c

    void main_assert(char *pointer, size_t variable)
    {
        ASSERT(true == true);
        ASSERT_POINTER(pointer);
        ASSERT_VARIABLE(variable, >= , int, 0);
        
        // ...
    }
    
    ```
    
  - Error / 错误处理

    尝试处理函数内错误发生到返回期间的事情。

    如果  `_TRAP()` 或 `_JUDGE()` 检测到错误发生，他会沿着错误序号往上执行用户定义的处理方法，最后返回。

    用例:

    ```c
    
    errno_t main_error(void)
    {
        ERROR_CONTROL_ERRNO_INIT(2, 1, 2);
        /* ERROR_CONTROL_INIT(errno_t, 2, 0, 1, 2); */
    
        ERROR_CONTROL_JUDGE(1, "test:succeed_index_1",
                            printf("i'm the 2st one to be printed!\r\n"));
    
        int fail = 1;
        ERROR_CONTROL_TRAP(fail,
                           2, "test:succeed_index_2",
                           printf("i'm the 1st one to be printed!\r\n"));
        
        ERROR_CONTROL_RETURN = 1;
        /* error_control_return = 1; */
        
        ERROR_CONTROL_EXIT(printf("error\r\n    "
                                  ".code: %d\r\n    "
                                  ".string: %s\r\n",
                                  ERROR_CONTROL_CODE(),
                                  ERROR_CONTROL_STRING()));
    }
    
    ```

  - ...

- Debug Component / 调试组件

  - Stack back trace / 堆栈追踪

    主要是想确定 `malloc()` 和 `free()` 可以配对，防止内存泄漏。

    现阶段只写了 Windows 平台的，基于 `the WIN32 Api`，你可以去 微软文档看到使用此 API 使用方法， [戳这里](https://docs.microsoft.com/en-us/windows/win32/debug/capturestackbacktrace)，`CaptureStackBackTrace()`;
  
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
    
  - ...

## 应用

[AT Instruction Set Suite](<https://github.com/Miao-Mico/at>): 俺的另一个项目，祸由她起。

## 引用

- [cppreference.com](<http://en.cppreference.com/w/>)/[zh.cppreference]([https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5](https://zh.cppreference.com/w/首页)): 

  A website can provide programmers with a complete online reference for the C and C++ languages and standard libraries.

  You can `change language` to your mother language `at the bottom of the website`.

  简而言之，可以去这里看到一些 C/C++ 的介绍啥的，可以在网页底部切换语言。

- [visualized data structures and algorithms](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html): 

  A website have visualizations for much of the data structures and algorithms.
  
  可视化数据结构和算法的网站。

## 致谢

谢所有帮助、支持、鼓励的大佬们。

## 许可

[Apache-2.0](https://github.com/Miao-Mico/stack/blob/master/LICENSE)