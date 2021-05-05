#include "pdp_do.h"
#include "pdp_func.h"
#include <stdlib.h>
#include "pdp_mem.h"
#include "pdp_run.h"

void do_halt(Operand op) {
	trace(" -- do halt is in work\n");

	register_info();
	exit(0);
}

void do_mov(Operand op) {
	trace(" -- do mov is in work\n");


	if(op.is_byte) {
		b_write(op.dd.adr, op.ss.val);
	}
	else {
		w_write(op.dd.adr, op.ss.val);
	}


	// NZVC **0-
	set_n(op.ss.val, op.is_byte);
	set_z(op.ss.val);
}

void do_add(Operand op) {
	trace(" -- do add is in work\n");

	word w = w_read(op.dd.adr);
	w += op.ss.val;

	w_write(op.dd.adr, w);

	// NZVC ****
	set_n(w, op.is_byte);
	set_z(w);
	set_c(w, op.is_byte);
}

void do_sob(Operand op) {
	trace(" -- do sob is in work\n");


	return;
}

void do_nothing() {
	return;
}

