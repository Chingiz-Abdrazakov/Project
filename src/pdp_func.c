#include "pdp_func.h"
#include "pdp_mem.h"
#include "pdp_run.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


word reg[8]; //registers from R0 to R7

// pc definition
Operand op;

PSW psw;

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
	printf(
		"Registers info: \
		\nR[0] = %06o R[1] = %06o R[2] = %06o\
		\nR[3] = %06o R[4] = %06o R[5] = %06o\
		\nR[6] = %06o R[7] = %06o\n",
		reg[0], reg[1], reg[2], reg[3],
		reg[4], reg[5], reg[6], reg[7]
	);
	printf("PSW N = %d, Z = %d, V = %d, C = %d\n", psw.n, psw.z, psw.v, psw.c);
}

void set_n(size_t val, word w) {
	if(check_is_byte(w)) {
		psw.n = (val >> 7) & 1;
	}
	else {
		psw.n = (val >> 15) & 1;
	}
}

void set_z(size_t val) {
	psw.z = (val == 0);
}

void set_c(size_t val, word w) {
	if(check_is_byte(w)) {
		psw.c = (val >> 8) & 1;
	}
	else {
		psw.c = (val >> 16) & 1; 
	}
}


