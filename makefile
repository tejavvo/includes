CC      = gcc
CFLAGS  = -std=c17 -Wall -Wextra -O2 -I.
AR      = ar
ARFLAGS = rcs

SRC = utils.c stack/stack.c
OBJ = $(SRC:.c=.o)
LIB = libutils.a

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean

