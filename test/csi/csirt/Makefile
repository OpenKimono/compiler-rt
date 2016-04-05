include ../common.mk
CC=clang

default: csirt.o

csirt.o: csirt.c
	$(CC) $(CFLAGS) -c -g -O3 $< -o $@

clean:
	rm -f csirt.o
