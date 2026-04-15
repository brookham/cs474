CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = split
SRC = split.c

all: $(TARGET)

$(TARGET): $(SRC)
		$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
		./$(TARGET) 5

clean:
		rm -f $(TARGET)

.PHONY: all run clean