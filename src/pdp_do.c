#include <pdp_do.h>
#include <pdp_func.h>
#include <stdlib.h>
#include "pdp_mem.h"


void do_halt(Operand op) {
	trace("H  A  L  T!!!\n");
	register_info();
	exit(0);
}

void do_mov(Operand op) {
	trace("M  O  V!!!\n");

	w_write(op.dd.adr, op.ss.val);
	
}

void do_add() {
	return;
}

void do_nothing() {
	return;
}

