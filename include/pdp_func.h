#pragma once
#include <stddef.h>
#include "pdp.h"

extern word reg[8];
#define pc reg[7]


// Functions definition
void trace(int command_flag, const char* format, ...);

void debug(const char * format, ...);

void register_info(int command_flag);

void flags_info(int command_flag);

void all_info(int command_flag);
// Flags
void set_n(size_t val, word w);

void set_z(size_t val);

void set_c(size_t val, word w);

// Program usage directives
void instruction_print();

void get_console_arguments(int argc, char * argv[]);