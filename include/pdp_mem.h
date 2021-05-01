#pragma once

typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Address; //16 bit

#define MEMSIZE (64 * 1024)

void b_write(Address adr, byte b);
byte b_read(Address adr);

void w_write(Address adr, word w);
word w_read(Address adr);

void load_file();
void mem_dump(Address start, word n);