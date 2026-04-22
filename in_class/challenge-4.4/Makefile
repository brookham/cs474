CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGETS = a2po po2a

all: $(TARGETS)

a2po: a2po.c
	$(CC) $(CFLAGS) -o $@ $<

po2a: po2a.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	./a2po 5
	./po2a 5

clean:
	rm -f $(TARGETS)

.PHONY: all run clean