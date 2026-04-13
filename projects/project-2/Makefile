CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGETS = ticketlock rwspinlock
SRCS = ticketlock.c rwspinlock.c


all: $(TARGETS)
$(TARGETS): %: %.c
		$(CC) $(CFLAGS) -o $@ $<

clean:
		rm -f $(TARGETS)
		
.PHONY: all clean

