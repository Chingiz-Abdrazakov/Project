#pragma once
#include "pdp.h"

#define MEMSIZE (64 * 1024)

void b_write(Address adr, byte b);
byte b_read(Address adr);

void w_write(Address adr, word w);
word w_read(Address adr);

void load_file(const char * filename);
void mem_dump(Address start, word n);