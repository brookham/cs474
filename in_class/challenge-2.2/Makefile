CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = compare_and_swap
SRC = compare_and_swap.c

all: $(TARGET)

$(TARGET): $(SRC)
		$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
		./$(TARGET) 5

clean:
		rm -f $(TARGET)

.PHONY: all run clean