#pragma once


typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Address; //16 bit

#define pc reg[7]

void trace(const char* format, ...);

void debug(const char * format, ...);

void run();

typedef struct {
	word mask;
	word opcode;
	char * name;
	void (do_func)(void);
} Command;