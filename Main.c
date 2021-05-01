#include <stdio.h>
#include <assert.h>
#include "pdp_func.h"
#include "pdp_mem.h"
#include "pdp_run.h"
#include "pdp_do.h"

typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Address; //16 bit

#define MEMSIZE (64 * 1024)

byte mem[MEMSIZE];

/*void b_write(Address adr, byte b);
byte b_read(Address adr);

void w_write(Address adr, word w);
word w_read(Address adr);

void load_file();
void mem_dump(Address start, word n);
*/

void test_mem() {
	byte b0 = 0x0a;
	//write a byte, read a byte
	b_write(2, b0);
	byte bres = b_read(2);

	printf("%02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);


	//write 2 bytes, read a word
	Address a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a + 1, b1);
	word ww = 0x0d0c;
	w_write(a, ww);
	word wres = w_read(a);

	//printf("word_write function's work's result is %04hx\n", ww);

	printf("ww/br \t %04hx = %02hhx%02hhx\n", wres, b1, b0);
	//assert(wres == w);

}

int main(int argc, char * argv) {
	load_file();


	return 0;
}

	