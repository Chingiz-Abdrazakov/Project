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

void do_cln() {
	trace(" -- do cln is in work\n");
	b_write(psw.n, 0);
}

void do_clc() {
	trace(" -- do clc is in work\n");
	b_write(psw.c, 0);
}

void do_clz() {
	trace(" -- do clz is in work\n");
	b_write(psw.z, 0);
}

void do_clv() {
	trace(" -- do clv is in work\n");
	b_write(psw.v, 0);
}

void do_ccc() {
	trace(" -- do ccc is in work\n");

	b_write(psw.n, 0);
	b_write(psw.z, 0);
	b_write(psw.v, 0);
	b_write(psw.c, 0);
}

void do_clr(Operand op) {
	trace(" -- do clr is in work\n");
	w_write(op.dd.adr, 0);
}

void do_movb() {
	trace(" -- do movb is in work\n");
}

void do_sob(Operand op) {
	trace(" -- do sob is in work\n");

	reg[op.r] -= 1;
	if(reg[op.r] != 0) {
		pc -= 2 * op.nn;
	}

	// NZVC ----
}

void do_nop(Operand op) {
	trace(" -- do nob is in work\n");
	return;
}

void do_nothing() {
	trace(" -- unknown command\n");
	return;
}

