#!/bin/bash

CC="cc"
CFLAGS="-Wall -Wextra -Wpedantic -Wconversion" #-Werror

compile () {
    # 1=sources 2=bouns_flag
    eval "$CC $CFLAGS "
}