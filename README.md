# libasm
The goal of libasm is to get familiar with x86_64 assembly by working with strings, numbers, functions, function pointers, and structures (linked lists) in nasm.

1. [Usage](#usage)
2. [Overview](#overview)
3. [Assembly quick reference](#assembly-quick-reference)
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

*Note: This only applies to the [x86_64 System V calling convention][2] used in this project*

A reference with the most commonly used x86_64 instructions and paradigms can be found [here][1].<br><br>

### **Registers:**

In assembly you work with `registers`. Those are (since the introduction of x64) 64-bit wide memory spaces where values can be stored.<br>

There are 16 Registers:

```asm

rax, rbx, rcx, rdx, rdi, rsi, rbp, rsp, r8, r9 ... r15

```

These can be divided into [volatile][3] and [non-volatile][4] registers.<br>

Volatile registers are:

```asm

rax, rcx, rdx, r8 ... r11

```

The rest of them are non-volatile:

```asm

rbx, rdi, rsi, rbp, rsp, r12 ... r15

```

Furthermore, some of the registers are used for specific purposes:

- `rsp`: Holds the value of the stack pointer

- `rax`: Holds the return value of a function call

- `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`: Used to pass the 1st to 6th parameter to functions - in this exact order. Further function arguments are passed on the stack.

- `rbp`: Often used to save the value of `rsp` upon function entry and restore the value of `rsp` upon function exit. That's why it's often referred to as base pointer.
- `EFLAGS`: A special register that is rarely set directly. Instead it holds specific [flags][5] that will be set / reset by comparison operations and read by conditional instructions.

[1]: <https://treeniks.github.io/x86-64-simplified/prefix.html> "x86_64 simplified"
[2]: <https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI> "x86_64 System V calling convention"
[3]: <https://en.wikipedia.org/wiki/X86_calling_conventions#Caller-saved_(volatile)_registers>
[4]: <https://en.wikipedia.org/wiki/X86_calling_conventions#Callee-saved_(non-volatile)_registers>
[5]: <https://image.slidesharecdn.com/assemblylanguageprogrammingunit4-111106021136-phpapp02/95/assembly-language-programmingunit-4-28-728.jpg?cb=1320545565> "Layout of EFLAGS"

### **Program structure:**

Every line of code is divided into an instruction and the registers or memory regions that are affected by it. E.g.:
```s &nbsp;
    mov                rax, 0
    ^^^                ^^^^^^
instruction      affected register(s)
```
Pointers are dereferenced by putting the register the pointer is stored in between [] and specifying how many bytes should be read from the pointer:
```s
mov BYTE [rax], 0 ; move zero into the Byte that rax points to
```
is equivalent to the C code of:
```C
*(char*)str = '\0'; // assuming that str points to a valid memory address
```

### **Branching:**

Conditional statements and loops are represented through `jumps` in assembly.<br>
They work by jumping to a `label` that is somewhere else in the program:
```s
...
jmp .LABEL
mov rax, 0 ; <------- this line of code will never be executed
.LABEL:
...
```
`If` statements are achived by comparing registers and using conditional jumps:
```s
...
test rax, rax       ; test the value in rax
jz .LABEL           ; jump to LABEL if the value in rax is zero
mov rax, 0          ; set rax to zero if it wasn't before
.LABEL:
...
```
`Loops` are achived by comparing registers and using conditional jumps to jump back in the program flow:
```s
mov rdx, 10
mov rcx, 0
.LOOP:
add rcx, 1          ; add one to rcx
cmp rcx, rdx        ; compare the value in rcx to rdx
jl .LOOP            ; jump back to .LOOP while the value in rcx < rdx
```

## Resources:
- [hands down the best reference for this project][1]
- [wikipedia on x86_64](https://en.wikipedia.org/wiki/X86-64#)
- [wikipedia on x86_64 System V AMD64 ABI calling convention][2]
- [how to transform assembly code into an executable](https://gist.github.com/yellowbyte/d91da3c3b0bc3ee6d1d1ac5327b1b4b2)
- [nasm cheat sheet](https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html)
- [official nasm documentation](https://www.nasm.us/doc/nasmdoc0.html)
- [what are syscalls (long read but very informative)](https://blog.packagecloud.io/the-definitive-guide-to-linux-system-calls/)
- [system call table for x86_64](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)
- [all x86_64 instructions out there](https://www.felixcloutier.com/x86/)