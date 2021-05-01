#pragma once

// types definition
typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Address; //16 bit

// pc definition
#define pc reg[7]

// for functions
#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2

//struct definition
typedef struct {
	word adr;
	word val;
} Argument;

typedef struct {
	Argument ss;
	Argument dd;
	word is_byte;
} Operand;

typedef struct {
	word mask;
	word opcode;
	char * name;
	char params;
	//void (*do_func)(void);
} Command;


// Extern variables definition
extern Command cmd[];
extern word reg[8];
extern Operand op;

// Functions definition
void trace(const char* format, ...);

void debug(const char * format, ...);

void register_info();

int check_is_byte(word w);

Operand get_params(word source, char parameters);

Argument get_modereg();
