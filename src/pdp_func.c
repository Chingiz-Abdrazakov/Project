#include "pdp_func.h"
#include "pdp_mem.h"
#include "pdp_run.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


word reg[8]; //registers from R0 to R7

// pc definition
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
	printf(
		"Registers info: \
		\nR[0] = %06o R[1] = %06o R[2] = %06o\
		\nR[3] = %06o R[4] = %06o R[5] = %06o\
		\nR[6] = %06o R[7] = %06o\n",
		reg[0], reg[1], reg[2], reg[3],
		reg[4], reg[5], reg[6], reg[7]
	);
}








	