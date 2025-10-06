GCC = gcc
SRC = src/*.c
INCLUDE = -Iinclude -Iinclude/functions -Iinclude/structures
LINK = -lMemTrack

OUT = out.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = a.asm -o out.txt -B
#COMMAND_ARGS = a.asm b.asm 

ERROR = -Wall -Werror -Wpedantic -Wextra -fanalyzer

BIG_ERROR = -Wall -Wextra -Wpedantic -Werror \
    -Wconversion -Wsign-conversion -Wshadow -Wpointer-arith -Wstrict-prototypes \
    -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition \
    -Wcast-align=strict -Wwrite-strings -Wcast-qual -Wundef \
    -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wnonnull \
    -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wswitch-enum \
    -Wuninitialized -Winit-self -Wstrict-overflow=5 \
    -fanalyzer -fsanitize=undefined,address -fstack-protector-strong \
    -fno-common -fstrict-aliasing -Werror=vla \

default: build run

d: build debug_run


build:
	@${GCC} -g -DTRACK_ALLOCATIONS ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}

run:
	@${OUT} ${COMMAND_ARGS}

debug:
	@gdb ${OUT}