# Filename: Makefile
# IFJ 2022/2023 project
# TRP variant
#
# Makefile for project compilation
#
# Author: <xsklen14> - David Sklenář
# Author: <xproch0o> - Marek Procházka
# Author: <xzavad20> - Lukáš Zavadil
# Author: <xsvetl07> - Adam Světlík

CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
MODULES=error.o parser.o scanner.o stack.o symtable.o dynamic_string.o expr.o


all: main


# generating executable file

main: main.o $(MODULES)
	$(CC) $(CFLAGS) $^ -o $@


# generating .o files

error.o: src/error.c
	$(CC) $(CFLAGS) $< -c -o $@

main.o: src/main.c
	$(CC) $(CFLAGS) $< -c -o $@

parser.o: src/parser.c
	$(CC) $(CFLAGS) $< -c -o $@

scanner.o: src/scanner.c
	$(CC) $(CFLAGS) $< -c -o $@

stack.o: src/stack.c
	$(CC) $(CFLAGS) $< -c -o $@

symtable.o: src/symtable.c
	$(CC) $(CFLAGS) $< -c -o $@

dynamic_string.o: src/dynamic_string.c
	$(CC) $(CFLAGS) $< -c -o $@

expr.o: src/expr.c
	$(CC) $(CFLAGS) $< -c -o $@

# Formatting
lint:
	clang-format -i src/*.c & clang-format -i src/*.h

# Cleaning
clean:
	rm *.o

win-clean:
	del *.o

win-delete:
	del main.exe

delete:
	rm main

win-compile :
	make & make win-clean

compile :
	make && make clean

# Execution
win-compile-and-run :
	make lint & make & make win-clean & main.exe

win-compile-and-run-clion :
	make lint & make & make win-clean

# tests
MODULES_TEST=error.o parser.o scanner.o stack.o symtable.o dynamic_string.o expr.o
tests.o: src/__tests__/tests.c
	$(CC) $(CFLAGS) $< -c -o $@


tests: tests.o $(MODULES_TEST)
	$(CC) $(CFLAGS) $^ -o $@

run-tests-win:
	make lint && make tests && make win-clean && tests.exe

run-tests:
	make tests && make clean && ./tests