CC = gcc
CFLAGS = -Wall -Wextra

TARGET = main
OBJS = main.o adder.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c adder.h
	$(CC) $(CFLAGS) -c main.c

adder.o: adder.c adder.h
	$(CC) $(CFLAGS) -c adder.c

clean:
	rm -f *.o

pristine: clean
	rm -f $(TARGET)

.PHONY: all clean pristine