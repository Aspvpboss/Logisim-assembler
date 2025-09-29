GCC = gcc
SRC = src/*.c
INCLUDE = -Iinclude -Iinclude/functions -Iinclude/structures -IMemTrack/include
LIBS = -LMemTrack/lib
LINK = -lMemTrack
ERROR = -Wall -Werror -Wpedantic -g
OUT = out.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = a.asm -o c.txt -B
#COMMAND_ARGS = a.asm b.asm 


default: build run

d: build debug_run


build:
	${GCC} ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}

run:
	@${OUT} ${COMMAND_ARGS}

debug:
	@gdb ${OUT}