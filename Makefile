CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11
TARGET = inventory

$(TARGET): inventory.o
	$(CC) -o $@ $^

inventory.o: src/inventory.c 
	$(CC) $(CFLAGS) -c src/inventory.c

clean:
	rm -rf $(TARGET) inventory.o inventory.dat

.PHONY: clean
