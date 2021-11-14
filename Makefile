CFLAGS = -Wall -Wextra -pedantic -std=c99

SRCS = main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: anim

anim: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) anim
