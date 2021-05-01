#include "pdp_func.h"
#include "pdp_mem.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

word reg[8]; //registers from R0 to R7

Operand op;

void trace(const char * format, ...) {
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void debug(const char* format, ...) { // Пока что аналогично trace,
// может в процессе пойму разницу
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void register_info() {
	printf("Registers info: R[0] = %06hx\n R[1] = %06hx\n R[2] = %06hx\n R[3] = %06hx\n R[4] = %06hx\n R[5] = %06hx\n R[6] = %06hx\n R[7] = %06hx\n", reg[0], reg[1], reg[2], reg[3], reg[4], 
		reg[5], reg[6], reg[7]);
}

Command cmd[] = {
	{ 0170000, 0010000, "mov", HAS_DD | HAS_SS}, //, do_mov },
	{ 0170000, 0060000, "add", HAS_DD | HAS_SS}, //, do_add },
	{ 0177777, 0000000, "halt", NO_PARAMS}, //, do_halt },
	{ 0000000, 0000000, "unknown", NO_PARAMS}//, do_nothing }
};

int check_is_byte(word w) {
	return ((w >> 15) & 1);
}

Argument get_mode(word w) {
	Argument res;
	int r = w & 7; //Register number
	int mode = (w >> 3) & 7; //Mode number

	switch(mode) {
		case 0:			// R3
			res.adr = r;
			res.val = reg[r];

			trace("R%o ", r);
			break;
		case 1: 		// (R3)
			res.adr = reg[r];
			if(check_is_byte(reg[r])) {
				// Check whether it is a byte
				res.val = b_read(res.adr);
			}
			else {
				// Whether it is a word
				res.val = w_read(res.adr);
			}

			trace("R%o ", r);
			break;
		case 2:
			res.adr = reg[r];

			if(check_is_byte(reg[r]) && r < 6) {
				// Check whether it is a byte
				res.val = b_read(res.adr); 
				reg[r] += 1;
			}
			else { 
				// Check whether it is a word
				res.val = w_read(res.adr); 
				reg[r] += 2;
			}
			
			if(r == 7) {
				trace("#%o ", res.val);
			}
			else {
				trace("(R%o)+ ", r);
			}

		default:
			fprintf(stderr, "Mode %o is not implemented yet.\n", mode);
			exit(1);
	}


	return res;

}

#ifdef NOT_READY
Operand get_params(word w, char parameters) {
	Operand result;

	if((parameters & HAS_SS) == HAS_SS) {
		result.ss.val = (w >> 6);
	}
	if((parameters & HAS_DD) == HAS_DD) {
		result.dd = ;
	}
}
#endif






	