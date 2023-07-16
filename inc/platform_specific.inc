%ifndef PLATFORM_SPECIFIC_INC
%define PLATFORM_SPECIFIC_INC


%ifdef LINUX
       %define WRITE_SYSCALL_CODE 1
       %define READ_SYSCALL_CODE 0
       %define GET_ERRNO __errno_location
       %define ERANGE_ERROR_CODE 34
       %define EINVAL_ERROR_CODE 22

%elifdef MACOS
       %define WRITE_SYSCALL_CODE 0x2000004
       %define READ_SYSCALL_CODE 0x2000003
       %define GET_ERRNO ___error ; check on mac in school!
       %define ERANGE_ERROR_CODE 34 ; check on mac in school!
       %define EINVAL_ERROR_CODE 22 ; check on mac in school!

%else
       %error "No operating system specified\n" \
              "Usage: nasm -dLINUX=1 or nasm -dMACOS=1"
%endif

; clang prefixes its compiled functions with an underscore,
; but gcc doesn't. So in order to interface with both we
; let the makefile determine what compiler is being used
; and change the function names accordingly
%ifdef COMPILER
       %ifidni COMPILER, gcc
              %define FT_WRITE ft_write
              %define FT_READ ft_read
              %define FT_STRCMP ft_strcmp
              %define FT_STRCPY ft_strcpy
              %define FT_STRDUP ft_strdup
              %define FT_STRLEN ft_strlen
              %define FT_ATOI_BASE ft_atoi_base
              %define FT_LIST_PUSH_FRONT ft_list_push_front
              %define FT_LIST_REMOVE_IF ft_list_remove_if
              %define FT_LIST_SIZE ft_list_size
              %define FT_LIST_SORT ft_list_sort

              %define MALLOC malloc
              %define FREE free

       %elifidni COMPILER, clang
              %define FT_WRITE _ft_write
              %define FT_READ _ft_read
              %define FT_STRCMP _ft_strcmp
              %define FT_STRCPY _ft_strcpy
              %define FT_STRDUP _ft_strdup
              %define FT_STRLEN _ft_strlen
              %define FT_ATOI_BASE _ft_atoi_base
              %define FT_LIST_PUSH_FRONT _ft_list_push_front
              %define FT_LIST_REMOVE_IF _ft_list_remove_if
              %define FT_LIST_SIZE _ft_list_size
              %define FT_LIST_SORT _ft_list_sort

              %define MALLOC _malloc
              %define FREE _free

       %endif ; COMPILER == gcc || COMPILER == clang

%else
       %error "No compiler specified\n" \
              "Usage: nasm -dCOMPILER=gcc or nasm -dCOMPILER=clang"

%endif ; COMPILER

%define INT32_MAX 2147483647
%define INT32_MIN -2147483648

%endif ; PLATFORM_SPECIFIC_INC