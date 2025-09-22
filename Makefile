GCC = gcc
SRC = src/*.c
INCLUDE = -Iinclude
FLAGS = -Wall -Werror -Wpedantic -g
OUT = out.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = a.asm b.asm -o c.txt -B


default: build run

d: build debug_run


build:
	@${GCC} ${FLAGS} -o ${OUT} ${SRC} ${INCLUDE}

run:
	@${OUT} ${COMMAND_ARGS}

debug:
	@gdb ${OUT}