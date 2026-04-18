CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGETS = myalloc rwspinlock
SRCS = myalloc.c rwspinlock.c


all: $(TARGETS)
$(TARGETS): %: %.c
		$(CC) $(CFLAGS) -o $@ $<

clean:
		rm -f $(TARGETS)
		
.PHONY: all clean

