GCC = gcc
#GCC = C:\MinGW\bin\gcc.exe -IC:\MinGW\include

SRC = src/*.c src/utilities/*.c src/core/*.c src/functions/*.c
INCLUDE = -Iinclude -Iinclude/functions -Iinclude/structures -Iinclude/core -Iinclude/utilities

LINK = -lMemTrack

OUT = rca.exe

DEBUG = -ex "break main" -ex "run"

COMMAND_ARGS = b.asm a.asm c.asm d.asm -o out.txt -B
#COMMAND_ARGS = a.asm b.asm 

ERROR = -Wall -Werror -Wpedantic 

OPTIMIZATIONS = -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -s

default: build run

debug: build debug_run

test: build test_run

opt: optimize_build run


optimize_build:
	@${GCC} ${OPTIMIZATIONS} ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}

build:
	@${GCC} -g -DTRACK_ALLOCATIONS ${ERROR} -o ${OUT} ${SRC} ${INCLUDE} ${LIBS} ${LINK}


run:
	@${OUT} ${COMMAND_ARGS}


test_run:
	@echo "-------No command args-------"
	-${OUT}
	@echo "-------No output file-------"
	-${OUT} test_validation/empty.asm
	@echo "-------Invalid command arg-------"
	-${OUT} test_validation/empty.asm -o
	@echo "-------No output type flag-------"
	-${OUT} test_validation/empty.asm -o out.txt
	@echo "-------Duplicate output type flags-------"
	-${OUT} test_validation/empty.asm -o out.txt -B -B
	@echo "-------Empty file-------"
	-${OUT} test_validation/empty.asm -o out.txt -B
	@echo "-------Failed to find input file-------"
	-${OUT} nothing.asm -o out.txt -B
	@echo "-------Invalid output file type-------"
	-${OUT} test_validation/empty.asm -o out.asm -B
	@echo "-------Inline macro error-------"
	-${OUT} test_validation/inline_macro.asm -o out.txt -B
	@echo "-------Multi macro error-------"
	-${OUT} test_validation/multi_macro.asm -o out.txt -B
	@echo "-------Cannot find .include file-------"
	-${OUT} test_validation/no_find_include.asm -o out.txt -B
	@echo "-------Double .include file-------"
	-${OUT} test_validation/multi_include.asm test_validation/a.asm -o out.txt -B

	

debug_run:
	@gdb ${OUT}
