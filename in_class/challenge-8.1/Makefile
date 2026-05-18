CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = animal
SRCS = animal.c pack.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET) 5

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean