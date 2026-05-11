CC = gcc
CFLAGS = -Wall -Wextra

TARGET = testfs
OBJS = testfs.o image.o block.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c adder.h block.h
	$(CC) $(CFLAGS) -c main.c

adder.o: adder.c adder.h
	$(CC) $(CFLAGS) -c adder.c

block.o: block.c block.h
	$(CC) $(CFLAGS) -c block.c

libvvsfs.a: main.o adder.o block.o 
	ar rcs $@ $^

clean:
	rm -f *.o

pristine: clean
	rm -f $(TARGET)

.PHONY: all clean pristine