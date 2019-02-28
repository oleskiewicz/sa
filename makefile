include config.mk

BIN = sample
SRC = sample.c util.c
OBJ = $(SRC:.c=.o)

all: sample

clean:
	rm -f $(OBJ) $(BIN)

include dep.mk

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.o:
	$(LD) $(LDFLAGS) -o $@ $(OBJ)
