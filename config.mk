CC      = cc
CFLAGS  = -std=c99 -O3 -DNDEBUG -Wall -Wextra -Wpedantic -Wshadow `pkg-config --cflags gsl`
LD      = $(CC)
LDFLAGS = `pkg-config --libs gsl`
PREFIX  = /usr/local
