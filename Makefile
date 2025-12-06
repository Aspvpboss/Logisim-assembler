
GCC = gcc

SRC = ${wildcard src/*.c src/utilities/*.c src/core/*.c src/functions/*.c}
INCLUDE = -Iinclude -Iinclude/functions -Iinclude/structures -Iinclude/core -Iinclude/utilities -IC:/msys64/mingw64/include

LINK = -lMemTrack
LIBS = -LC:/msys64/mingw64/lib

OUT = rca.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = b.asm a.asm c.asm d.asm -o out.txt -B
#COMMAND_ARGS = a.asm b.asm 

ERROR = -Wall -Werror -Wpedantic 

OPTIMIZATIONS = -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -s



default: json_build build run

debug: json_build build debug_run

test: json_build test_run

opt: json_build optimize_build run


json_build:
	@compiledb -n -- make build
	@compiledb -n -- make test_build


optimize_build:
	@${GCC} ${OPTIMIZATIONS} ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}

build:
	@${GCC} -g -DTRACK_ALLOCATIONS ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}


run:
	${OUT} ${COMMAND_ARGS}

test_build: 		
	@${GCC} test_validation/test.c -o ./test.exe -IC:/msys64/mingw64/include


test_run:

	@./test.exe
	

debug_run:
	@gdb ${OUT}


