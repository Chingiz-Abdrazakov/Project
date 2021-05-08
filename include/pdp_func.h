#pragma once
#include <stddef.h>
#include "pdp.h"

extern word reg[8];
#define pc reg[7]


// Functions definition
void trace(const char* format, ...);

void debug(const char * format, ...);

void register_info();

void flags_info();

void all_info();
// Flags
void set_n(size_t val, word w);

void set_z(size_t val);

void set_c(size_t val, word w);

void get_console_arguments(int argc, char * argv[]);