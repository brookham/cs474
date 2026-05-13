CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = testfs
LIB = libvvsfs.a
OBJS = testfs.o image.o block.o
LIB_OBJS = image.o block.o

all: $(LIB) $(TARGET)

$(TARGET): testfs.o $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) testfs.o $(LIB)

$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

testfs.o: testfs.c image.h block.h
	$(CC) $(CFLAGS) -c testfs.c

image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c

block.o: block.c block.h
	$(CC) $(CFLAGS) -c block.c

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o

pristine: clean
	rm -f $(TARGET) *.a

.PHONY: all clean pristine test