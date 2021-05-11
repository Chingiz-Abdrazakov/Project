#include "pdp_mem.h"
#include "pdp_run.h"
#include "pdp_func.h"
#include "pdp_do.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
word __is_byte;



Command cmd[] = {
	{ 0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov },
	{ 0170000, 0110000, "movb", HAS_DD | HAS_SS, do_movb },
	{ 0170000, 0060000, "add", HAS_DD | HAS_SS, do_add },
	{ 0177000, 0077000, "sob", HAS_R | HAS_N, do_sob },
	{ 0170000, 0020000, "cmp", HAS_DD | HAS_SS, do_cmp },
	{ 0170000, 0120000, "cmpb", HAS_DD | HAS_SS, do_cmpb },
	

	{ 0177700, 0005000, "clr", HAS_DD, do_clr},
	{ 0177700, 0005700, "tst", HAS_DD, do_tst},
	{ 0177700, 0105700, "tstb", HAS_DD, do_tstb},

	{ 0177400, 0000400, "br", HAS_XX, do_br},
	{ 0177400, 0001400, "beq", HAS_XX, do_beq},
	{ 0177400, 0001000, "bne", HAS_XX, do_bne},
	{ 0177400, 0100400, "bmi", HAS_XX, do_bmi},
	{ 0177400, 0100000, "bpl", HAS_XX, do_bpl},
	{ 0177400, 0103000, "bhis", HAS_XX, do_bhis},
	{ 0177400, 0103400, "blo", HAS_XX, do_blo},

	{ 0177777, 000257, "ccc", NO_PARAMS, do_ccc},
	{ 0177777, 000250, "cln", NO_PARAMS, do_cln},
	{ 0177777, 000244, "clz", NO_PARAMS, do_clz},
	{ 0177777, 000241, "clc", NO_PARAMS, do_clc},

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
	if(__is_byte) {
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
	if(__is_byte && r < 6) {
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
		trace("#%06o ", res->val);
	}
	else {
		trace("(R%o)+ ", r);
	}
}

void mode3(int r, Argument * res) {
	res->adr = w_read(reg[r]);
	res->val = w_read(res->adr);
	reg[r] += 2;

	if(r == 7) {
		trace("@#%o ", res->adr);
	}
	else {
		trace("@(R%o)+ ", res->adr);
	}
}

void mode4(int r, Argument * res) {
	if(r == 7 && pc == 8) {
		trace(" -- Out of register range, program crashed\n");
		exit(1);
	}

	if(__is_byte && r < 6) {
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
		//trace("%06o ", result.ss);
	}

	if((parameters & HAS_DD) == HAS_DD) {
		result.dd = get_modereg(w);
		// trace("%06o ", result.dd);
	}

	if((parameters & HAS_N) == HAS_N) {
		result.nn = w & 077;
		// trace("%06o ", (pc - 2 * result.nn));
	}

	if((parameters & HAS_R) == HAS_R) {
		result.r = (w >> 6) & 1;
		// trace("%06o, ", result.r);
	}

	if((parameters & HAS_XX) == HAS_XX) {
		result.xx = w & 0777;
		// trace("%06o ", result.xx);
	}

	result.is_byte = (w >> 15) & 1;

	return result;
}



void run() {
	trace("      ----------running---------    \n");

	pc = 01000;

	word cur_capacity = 100;
	char * str = malloc((cur_capacity + 1) * sizeof(char));
	word cur_used_capacity = 0;

	while(1) {
		word w = w_read(pc);
		trace("%06o: ", pc);
		//trace("%06o, %06o: ", pc, w);
		

		__is_byte = check_is_byte(w);
		pc += 2;

		int i = 0;
		while(1) {
			if((w & cmd[i].mask) == (cmd[i]).opcode) {
				trace("%s ", (cmd[i]).name);

				op = get_params(w, (cmd[i]).params);

				if(cmd[i].name == "halt") {
					printf("%s\n", str);
					free(str);
				}


				if(cmd[i].name == "movb" && ((w >> 3) & 7) == 3) {
					// add (char)op.ss.val;
					// strcat(str, l);
					if (cur_used_capacity < cur_capacity) {
						str[cur_used_capacity++] = (char)op.ss.val;

					} else {
						str = realloc(str, cur_capacity * sizeof(char));
					}
				}
				(cmd[i]).do_func(op);




				break;
			}
			
			i++;
		}
	}



}