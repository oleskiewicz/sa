include config.mk

SRC = $(shell find . -type f -name '*.c')
BIN = $(SRC:.c=)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: dep $(BIN)

dep: $(DEP)

clean:
	rm -f a.out $(BIN) $(DEP) $(OBJ)

include $(SRC:.c=.d)

.SUFFIXES: .c .d .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.c.d:
	$(CC) $(CFLAGS) $(LDFLAGS) -MMD $<
	rm a.out
