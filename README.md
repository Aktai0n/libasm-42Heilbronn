# libasm-42Heilbronn
The goal of libasm is yo get familiar with X86_64 assembly by working with strings, numbers, functions, function pointers, and structures (linked lists) in nasm.

1. [Usage](#usage)
2. [Sneek-Peek into assembly](#sneek-peek-into-assembly)
3. [Overview](#overview)
4. [Resources](#resources)
# note to self: change .asm to .s before submitting!


## Usage:

First, make sure you have `nasm`, `make` and either `gcc` or `clang` installed.

Clone the repository:
```bash
git clone https://github.com/Aktai0n/libasm-42Heilbronn.git libasm && cd libasm
```

Build the project with:
```bash
make test
```
this will build an archive named `libasm.a` and an executeable named `tester`

To run all tests at once use
```bash
./tester
```
Or use
```bash
./tester [function_name]
```
with the specific function you want to test (e.g. `strdup`, `atoi_base`, ...) to test only a specific function<br>
You can also provide multiple function names as arguments

If you want a more detailed output on what is being tested with you can rebuild the project with
```bash
make re VERBOSE=1
```
to enable verbose test output (only recommended for testing individual functions)


## Overview:

The available functions are:
```C
size_t ft_strlen(const char* str);
char* ft_strcpy(char* dest, const char* src);
int ft_strcmp(const char* s1, const char* s2);
char* ft_strdup(const char* s);
ssize_t ft_write(int fd, const void* buf, size_t count);
ssize_t ft_read(int fd, void* buf, size_t count);
int ft_atoi_base(char* str, char* base);
void ft_list_push_front(t_list** begin_list, void* data);
int ft_list_size(t_list* begin_list);
void ft_list_sort(t_list** begin_list, int (*cmp)());
void ft_list_remove_if(t_list** begin_list, void* data_ref, int (*cmp)(), void (*free_fct)(void*));
```

`t_list` is a struct defined as follows:
```C
typedef struct s_list {
    void* data;
    struct s_list* next;
} t_list;
```

More information about each function can be found at [inc/libasm.h](./inc/libasm.h)

## Assembly quick reference:

A reference with the most commonly used x86_64 instructions and paradigms can be found [here][1]

[1]: <https://treeniks.github.io/x86-64-simplified/prefix.html> "x86_64 simplified"

#### Registers:

In assembly you work with `registers`. Those are (in x64) 64-bit wide memory spaces where values can be stored.<br>

There are 16 Registers:

```asm

rax, rbx, rcx, rdx, rdi, rsi, rbp, rsp, r8 - r15

```

According to the calling convention they can be divided into volitaile and non-volitile registers.<br>

Volitile registers are:

```asm

rax, rcx, rdx, r8 - r11

```

And non-volitile registers:

```asm

rbx, rdi, rsi, rbp, rsp, r12 - r15

```

Some of the registers are used for specific purposes:

- `rsp` Holds the value of the stack pointer

- `rax` Holds the return value of a function call

- `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` Used to pass the 1st to 6th parameter to functions - in this exact order. Further function arguments are passed on the stack.

- `rbp` is often used to save the value of `rsp` upon function start. That's why it's often referred to as base pointer.

 

### Program structure:

Every instruction is divided into an instruction and the registers or memory regions that are affected by it. E.g.:

 

```s

mov     rax, 0

```

^^^^^^ <br>

instruction

 

### Branching:

There are neither conditional statements like `if`, `else if` and `else` nor classic loops like `for` or `while` in assembly.

Instead those are replaced by `jumps`

## Resources:
https://en.wikipedia.org/wiki/X86-64#
https://en.wikipedia.org/wiki/X86_calling_conventions#
https://gist.github.com/yellowbyte/d91da3c3b0bc3ee6d1d1ac5327b1b4b2
https://web.stanford.edu/class/cs107/resources/x86-64-reference.pdf
https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html
https://www.nasm.us/doc/nasmdoc0.html
https://image.slidesharecdn.com/assemblylanguageprogrammingunit4-111106021136-phpapp02/95/assembly-language-programmingunit-4-28-728.jpg?cb=1320545565
https://man7.org/linux/man-pages/man2/syscall.2.html
https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
https://www.youtube.com/watch?v=GV10eIuPs9k&t=403s
https://blog.packagecloud.io/the-definitive-guide-to-linux-system-calls/