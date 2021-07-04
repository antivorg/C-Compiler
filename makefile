CC = gcc
CFLAGS=-I.

_DEPS = main.h fileHandling.h lexing.h
_OBJ = main.o fileHandling.o lexing.o 

IDIR = headers
ODIR = oFiles

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ccc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJ)

cleanExe:
	rm ccc.exe