#include "pdp_do.h"
#include "pdp_func.h"
#include <stdlib.h>
#include "pdp_mem.h"
#include "pdp_run.h"

void do_halt(Operand op) {
	trace("\n        ---------halted-----------      \n");

	register_info();
	exit(0);
}

void do_mov(Operand op) {
	trace("      R%o = %06o.\n", op.dd.adr, op.ss.val);

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
	trace("      R%o = R%o + R%o.\n", op.dd.adr, op.dd.adr, op.ss.adr);

	word w = w_read(op.dd.adr);
	w += op.ss.val;

	w_write(op.dd.adr, w);

	// NZVC ****
	set_n(w, op.is_byte);
	set_z(w);
	set_c(w, op.is_byte);
}

void do_cln(Operand op) {
	trace(" -- do cln is in work\n");
	set_n(0, op.is_byte);
}

void do_clc(Operand op) {
	trace(" -- do clc is in work\n");
	set_c(0, op.is_byte);
}

void do_clz(Operand op) {
	trace(" -- do clz is in work\n");
	set_z(0);
}

void do_clv(Operand op) {
	trace(" -- do clv is in work\n");
	psw.v = 0;
}

void do_ccc(Operand op) {
	trace(" -- do ccc is in work\n");

	set_n(0, op.is_byte);
	set_z(0);
	set_c(0, op.is_byte);
	psw.v = 0;
}

void do_clr(Operand op) {
	trace("      mem[%o] = 0.\n", op.dd.adr);
	w_write(op.dd.adr, 0);

	// NZVC 0100
	set_n(0, op.is_byte);
	set_z(0);
	set_c(0, op.is_byte);
}	


void do_sob(Operand op) {
	trace("\n");
	reg[op.r] -= 1;
	if(reg[op.r] != 0) {
		pc -= 2 * op.nn;
	}

	// NZVC ----
}

void do_nop(Operand op) {
	return;
}

void do_nothing() {
	trace(" -- unknown command\n");
	return;
}

