#include "pdp_mem.h"
#include "pdp_run.h"
#include "pdp_func.h"
#include "pdp_do.h"
#include <stdio.h>
#include <stdlib.h>

// Commands

Command cmd[] = {
	{ 0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov },
	{ 0170000, 0060000, "add", HAS_DD | HAS_SS, do_add },
	{ 0177000, 0077000, "sob", HAS_N, do_sob },
	{ 0177777, 0000000, "halt", NO_PARAMS, do_halt },
	{ 0000000, 0000000, "unknown", NO_PARAMS, do_nothing }
};


int compare(word w, word mask, word opcode) {
	return (w & mask) == opcode;
}

int check_is_byte(word w) {
	return ((w >> 15) & 1);
}


void mode0(int r, Argument *res) {
	res->adr = r;
	res->val = reg[r];

	trace("R%o ", r);
}

void mode1(int r, Argument *res) {
	res->adr = reg[r];
	if(check_is_byte(reg[r])) {
		// Check whether it is a byte
		res->val = b_read(res->adr);
	}
	else {
		// Whether it is a word
		res->val = w_read(res->adr);
	}

	trace("R%o ", r);
}

void mode2(int r, Argument *res) {

	res->adr = reg[r];
	if(check_is_byte(reg[r]) && r < 6) {
		// Check whether it is a byte
		res->val = b_read(res->adr); 
		reg[r] += 1;
	}
	else {
		// Check whether it is a word
		res->val = w_read(res->adr);
		reg[r] += 2;
	}
	
	if(r == 7) {
		trace("#%o ", res->val);
	}
	else {
		trace("(R%o)+ ", r);
	}
}

void mode3(int r, Argument * res) {
	res->adr = w_read(reg[r]);
	res->val = w_read(res->adr);
	reg[r] += 2;

	trace("@#%o ", res->adr);
}

void mode4(int r, Argument * res) {
	if(r == 7 && pc == 8) {
		trace(" -- Out of register range, program crashed\n");
		exit(1);
	}

	if(check_is_byte(reg[r]) && r < 6) {
		reg[r] -= 1;
		res->adr = reg[r];
		res->val = b_read(res->adr);
	}
	else {
		reg[r] -= 2;
		res->adr = reg[r];
		res->val = w_read(res->adr);		
	}

	if(r == 7) {
		trace("-(pc) ", res->val);
	}
	else {
		trace("-(R%o) ", r);
	}
}

Argument get_modereg(word w) {
	Argument res;
	int r = w & 7; //Register number
	int mode = (w >> 3) & 7; //Mode number

	switch(mode) {
		case 0:			// Rn
			mode0(r, &res);
			break;
		case 1: 		// (Rn)
			mode1(r, &res);
			break;
		case 2: 		// 	(Rn)+
			mode2(r, &res);
			break;
		case 3:			// 
			mode3(r, &res);
			break;
		case 4:
			mode4(r, &res);
			break;
		default:
			fprintf(stderr, "Mode %o is not implemented yet.\n", mode);
			exit(1);
	}


	return res;

}




Operand get_params(word w, char parameters) {
	Operand result;

	if((parameters & HAS_SS) == HAS_SS) {
		result.ss = get_modereg(w >> 6);
	}

	if((parameters & HAS_DD) == HAS_DD) {
		result.dd = get_modereg(w);
	}

	if((parameters & HAS_N) == HAS_N) {
		result.nn = w & 077;
		trace("%06o ", (pc - 2 * result.nn));
	}

	result.is_byte = (w >> 15) & 1;

	return result;
}



void run() {
	pc = 01000;

	while(1) {
		word w = w_read(pc);
		trace("%06o %06o: ", pc, w);
		pc += 2;

		int i = 0;
		while(1) {
			if((w & cmd[i].mask) == (cmd[i]).opcode) {
				trace("%s ", (cmd[i]).name);
				op = get_params(w, (cmd[i]).params);
				(cmd[i]).do_func(op);

				trace("%s", cmd[i].name);
				break;
			}
			
			i++;
		}
	}
}



