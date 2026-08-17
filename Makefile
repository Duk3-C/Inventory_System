CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11
TARGET = Inventory_System

$(TARGET): inventory.o
	$(CC) -o $@ $^

inventory.o: main.c 
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf $(TARGET) inventory.o

.PHONY: clean
