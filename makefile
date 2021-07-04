CC = gcc
CFLAGS=-I -Wall

_DEPS = main.h fileHandling.h lexing.h
_OBJ = main.o fileHandling.o lexing.o 

IDIR = headers
ODIR = oFiles
EDIR = bin

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/ccc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJ)

cleanExe:
	rm $(ODIR)/ccc.exe