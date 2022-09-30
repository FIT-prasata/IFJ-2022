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
MODULES=error.o parser.o scanner.o stack.o symtable.o


all: main


# generating executable file

main: main.o $(MODULES)
	$(CC) $(CFLAGS) $< -o $@


# generating .o files

error.o: error.c
	$(CC) $(CFLAGS) $< -c -o $@

main.o: main.c
	$(CC) $(CFLAGS) $< -c -o $@

parser.o: parser.c
	$(CC) $(CFLAGS) $< -c -o $@

scanner.o: scanner.c
	$(CC) $(CFLAGS) $< -c -o $@

stack.o: stack.c
	$(CC) $(CFLAGS) $< -c -o $@

symtable.o: symtable.c
	$(CC) $(CFLAGS) $< -c -o $@


# Cleaning

clean:
	rm *.o

win-clean:
	del *.o

win-delete:
	del main.exe

delete:
	rm main
