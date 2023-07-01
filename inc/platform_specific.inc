%ifndef PLATFORM_SPECIFIC_INC
%define PLATFORM_SPECIFIC_INC


%ifdef LINUX
       %define WRITE_SYSCALL_CODE 1
       %define READ_SYSCALL_CODE 0
       %define GET_ERRNO __errno_location
       %define ERANGE_ERROR_CODE 34
       %define EINVAL_ERROR_CODE 22
       %define MALLOC malloc
       %define FREE free

%elifdef MACOS
       %define WRITE_SYSCALL_CODE 0x2000004
       %define READ_SYSCALL_CODE 0x2000003
       %define GET_ERRNO ___error ; check on mac in school!
       %define ERANGE_ERROR_CODE 34 ; check on mac in school!
       %define EINVAL_ERROR_CODE 22 ; check on mac in school!
       %define MALLOC _malloc
       %define FREE _free

%else
       %error "No operating system specified\n" \
              "Usage: nasm -dLINUX=1 or nasm -dMACOS=1"
%endif

%endif ; PLATFORM_SPECIFIC_INC