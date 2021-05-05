#pragma once



// For functions
#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_N 4
#define HAS_R 8


// Struct definition
typedef struct {
	word adr;
	word val;
} Argument;

typedef struct {
	Argument ss;
	Argument dd;
	unsigned char r;
	unsigned char nn;
	word is_byte;
} Operand;

typedef struct {
	word mask;
	word opcode;
	char * name;
	char params;
	void (* do_func)(Operand op);
} Command; 


typedef struct {
	byte n;
	byte z;
	byte v;
	byte c;
} PSW;



// Extern variables

extern word reg[8];
extern Operand op;
extern Command cmd[];
extern PSW psw;


int compare(word w, word mask, word opcode);

int check_is_byte(word w);


// Modes
void mode0(int r, Argument * res);

void mode1(int r, Argument * res);

void mode2(int r, Argument * res); 

void mode3(int r, Argument * res);

void mode4(int r, Argument * res);

Argument get_modereg(word w);

Operand get_params(word source, char parameters);



void run();
