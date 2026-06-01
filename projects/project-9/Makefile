CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = testfs
LIB = libvvsfs.a
OBJS = testfs.o image.o block.o free.o inode.o dir.o ls.o
LIB_OBJS = image.o block.o free.o pack.o inode.o dir.o ls.o

all: $(LIB) $(TARGET)

$(TARGET): testfs.o $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET) testfs.o $(LIB)

$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

testfs.o: testfs.c image.h block.h free.h inode.h dir.h
	$(CC) $(CFLAGS) -c testfs.c

image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c

block.o: block.c block.h
	$(CC) $(CFLAGS) -c block.c

free.o: free.c free.h
	$(CC) $(CFLAGS) -c free.c

inode.o: inode.c inode.h pack.h
	$(CC) $(CFLAGS) -c inode.c

pack.o: pack.c pack.h
	$(CC) $(CFLAGS) -c pack.c

dir.o: dir.c dir.h
	$(CC) $(CFLAGS) -c dir.c

ls.o: ls.c
	$(CC) $(CFLAGS) -c ls.c


test: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o

pristine: clean
	rm -f $(TARGET) *.a

.PHONY: all clean pristine test