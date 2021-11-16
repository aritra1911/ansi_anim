CC ?= cc

INC = -Iinc -Ilib/inc
LIB =

CFLAGS = $(INC) -Wall -Wextra -pedantic -std=c99
CPPFLAGS =
LDFLAGS =

SRCS = lib/src/graphics/common.c \
       lib/src/graphics/shapes.c \
       lib/src/ansi/cursor.c \
       src/main.c

OBJS = obj/graphics/common.o \
       obj/graphics/shapes.o \
       obj/ansi/cursor.o \
       obj/main.o

.PHONY: all clean

all: bin/anim

bin/anim: $(OBJS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) -o $@ $^

obj/graphics/%.o: lib/src/graphics/%.c
	@mkdir -p obj/graphics
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/ansi/%.o: lib/src/ansi/%.c
	@mkdir -p obj/ansi
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf obj bin
