CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11
TARGET = inventory
SRCS = src/prog.c src/func.c 
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c src/func.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS) prog.o inventory.dat

.PHONY: clean
