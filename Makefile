CC=gcc
CFLAGS=-I.
DEPS = pdp_mem.h pdp_func.h pdp_run.h pdp_do.h
OBJ = Main.o pdp_mem.o pdp_func.o pdp_run.o pdp_do.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


Output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)