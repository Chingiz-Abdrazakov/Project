#include "pdp_mem.h"
#include <stdarg.h>


byte mem[MEMSIZE];
//byte write
void b_write(Address adr, byte b){
	mem[adr] = b;
}

//byte read
byte b_read(Address adr) {
	return mem[adr];
}

//word read
word w_read(Address adr) {
	word w = ((word)mem[adr + 1]) << 8;
	//printf("w = %x\n", w);
	w = w | mem[adr];
	return w;
}


//word write
void w_write(Address adr, word w) {
	mem[adr] = w;
	mem[adr + 1] = (w >> 8);

}


void load_file() {
	while(1 == 1){
		Address a;
		word n;	
		int y = scanf("%hx %hx", &a, &n);

		if(y != 2){
			break;
		}
		for(int i = 0; i < (int)n; ++i){
			byte b;
			scanf("%hhx", &b);
			b_write(a + (Address)i, b);	
		}
	}
}

void mem_dump(Address start, word n){
	for(int i = 0; i < (int)n; i += 2){
		printf("%06o : %06o\n", (start + i), w_read(start + i));
	}
}

