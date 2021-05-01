IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)
BIN=pdp11.exe


SDIR=src
ODIR=obj


LIBS=-lm


_DEPS = pdp_mem.h pdp_func.h pdp_run.h pdp_do.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = Main.o pdp_mem.o pdp_func.o pdp_run.o pdp_do.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: $(BIN)


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean


clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ $(INCDIR)/*~