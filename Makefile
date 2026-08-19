CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11
TARGET = Inventory_System

$(TARGET): inventory.o
	$(CC) -o $@ $^

inventory.o: inventory.c 
	$(CC) $(CFLAGS) -c inventory.c

clean:
	rm -rf $(TARGET) inventory.o inventory.dat

.PHONY: clean
