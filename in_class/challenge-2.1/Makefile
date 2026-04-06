CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = test_and_set
SRC = test_and_set.c

all: $(TARGET)

$(TARGET): $(SRC)
		$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
		./$(TARGET) 5

clean:
		rm -f $(TARGET)

.PHONY: all run clean