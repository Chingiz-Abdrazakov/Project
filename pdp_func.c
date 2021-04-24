#include "pdp_func.h"
#include <stdlib.h>
#include <stdio.h>

word reg[8]; //registers from R0 to R7

void trace(const char * format, ...) {
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void do_halt() {
	trace("THE END!!!\n");
	exit(0);
}

void do_mov() {
	trace("\n");
	
}

void do_add() {

}

void do_nothing() {

}


Command cmd[] = {
	{ 0170000, 0010000, "mov", do_mov },
	{ 0170000, 0060000, "add", do_add },
	{ 0177777, 0000000, "halt", do_halt },
	{ 0000000, 0000000, "unknown", do_nothing }
};

int compare(word w, word mask, word opcode) {
	return (w & mask) == opcode;
}

void run() {
	pc = 01000;
	while(1) {
		word w = w_read(pc);
		trace("%06o %06o: ", pc, w);
		pc += 2;

		int i = 0;
		while(compare(w, cmd[i].mask, cmd[i].opcode) != 1) {
			i++;
		}
	}
}




