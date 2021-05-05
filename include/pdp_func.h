#pragma once
#include <stddef.h>

// types definition
typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Address; //16 bit

extern word reg[8];
#define pc reg[7]


// Functions definition
void trace(const char* format, ...);

void debug(const char * format, ...);

void register_info();


// Flags
void set_n(size_t val, word w);

void set_z(size_t val);

void set_c(size_t val, word w);

