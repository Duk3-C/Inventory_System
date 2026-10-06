CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11
TARGET = inventory

$(TARGET): prog.o
	$(CC) -o $@ $^

prog.o: prog.c 
	$(CC) $(CFLAGS) -c prog.c

clean:
	rm -rf $(TARGET) prog.o inventory.dat

.PHONY: clean
