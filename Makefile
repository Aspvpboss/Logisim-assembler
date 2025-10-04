GCC = gcc
SRC = src/*.c
INCLUDE = -Iinclude -Iinclude/functions -Iinclude/structures
LINK = -lMemTrack
ERROR = -Wall -Werror -Wpedantic -g
OUT = out.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = a.asm -o out.txt -B
#COMMAND_ARGS = a.asm b.asm 


default: build run

d: build debug_run


build:
	@${GCC} -DTRACK_ALLOCATIONS ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}

run:
	@${OUT} ${COMMAND_ARGS}

debug:
	@gdb ${OUT}