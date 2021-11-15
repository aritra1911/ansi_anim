CC ?= cc

INC = -Iinc -Ilib/inc
LIB =

CFLAGS = $(INC) -Wall -Wextra -pedantic -std=c99
CPPFLAGS =
LDFLAGS =

SRCS = src/main.c
OBJS = $(SRCS:src/%.c=obj/%.o)

.PHONY: all clean

all: bin/anim

bin/anim: $(OBJS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf obj bin
