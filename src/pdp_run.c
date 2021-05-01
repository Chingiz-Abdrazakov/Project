#include "pdp_mem.h"
#include "pdp_run.h"
#include "pdp_func.h"


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
		while((w & cmd[i].mask) != (cmd[i]).opcode) {
			trace("%s", cmd[i].name);
			i++;
		}

		//op = get_params(w, (cmd[i]).params);
	}
}


