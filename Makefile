GCC = gcc
#GCC = C:\MinGW\bin\gcc.exe -IC:\MinGW\include

SRC = src/*.c src/utilities/*.c src/core/*.c src/functions/*.c
INCLUDE = -Iinclude -Iinclude/functions -Iinclude/structures -Iinclude/core -Iinclude/utilities

LINK = -lMemTrack

OUT = rca.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = b.asm a.asm -o out.txt -B
#COMMAND_ARGS = a.asm b.asm 

ERROR = -Wall -Werror -Wpedantic -fanalyzer

BIG_ERROR = -Wall -Werror -Wpedantic -Wextra -fanalyzer

default: build run

d: build debug


build:
	@${GCC} -g -DTRACK_ALLOCATIONS ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}

run:
	@${OUT} ${COMMAND_ARGS}

debug:
	@gdb ${OUT}
