include config.mk

SRC = $(shell find . -type f -name '*.c')
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
BIN = $(SRC:.c=)
SCRIPTS = \
	sa-rescale \
	sa-plot

all: dep $(BIN)

install: all
	for f in $(BIN) $(SCRIPTS); do install -m 0755 $$f $(PREFIX)/bin; done

dep: $(DEP)

clean:
	rm -f $(BIN) $(DEP) $(OBJ)

-include $(SRC:.c=.d)

.SUFFIXES: .c .d .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.c.d:
	$(CC) $(CFLAGS) $(LDFLAGS) -MMD $< > $@
	rm -f a.out
