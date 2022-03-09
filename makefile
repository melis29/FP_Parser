# This Makefile is set up for CS201 A1
# copy to your MCECS account with:
# cp ~markem/public_html/CS201/homework/Makefile .
# NOTE: All indented lines are indented with a tab character.
#       This is required.

CC=gcc
# flag all warnings. default optimization level.
CFLAGS=-Wall -Og 
# set up for use in gdb
DFLAGS=-g
# For additional libraries, e.g. -lm
LDFLAGS=-lm
PROGS=fp_parse

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f $(PROGS) *.o ~*

