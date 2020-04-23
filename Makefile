CC      = cc
CFLAGS  = -std=c99 -O2 -march=native -Wall -lgsl
PREFIX  = /usr/local

SRC     = $(shell find . -type f -name '*.c')
BIN     = $(SRC:.c=)
SCRIPTS = \
	sa-rescale \
	sa-plot

all: $(BIN)

install: all
	for f in $(BIN) $(SCRIPTS); do install -m 0755 $$f $(PREFIX)/bin; done

clean:
	rm -f $(BIN)
