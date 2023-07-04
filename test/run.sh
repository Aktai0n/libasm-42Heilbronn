#!/bin/bash

CC="cc"
CFLAGS="-Wall -Wextra -Wpedantic -Wconversion" #-Werror

LIB=../libasm.a

cp ${LIB} .

compile () {
    # 1=sources 2=bouns_flag
    eval "$CC $CFLAGS "
}

case $1

esac