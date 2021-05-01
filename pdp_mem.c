#include "pdp_mem.h"
#include <stdarg.h>
#include <errno.h> 
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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


void load_file(const char * filename) { 
	FILE * fin = fopen(filename, "r"); //Reading data from file

	if(fin == NULL) { //Whether there is an error
		char * error_message =
		 malloc(sizeof(char) * (strlen(filename) + 90));
		sprintf(error_message, "Cannot open the file: %s", filename);

		perror(error_message);
		free(error_message);
		exit(errno);
	}


	//If not
	Address a;
	word n;	
	byte b;
	while(1){ //Read from stream
		if(2 != scanf("%hx%hx", &a, &n)) {
			break;
		}
		for(int i = 0; i < (int)n; ++i){
			fscanf(fin, "%hhx", &b);

			b_write(a + (Address)i, b);
		}
	}

	fclose(fin); // Close the stream
}

void mem_dump(Address start, word n){
	for(int i = 0; i < (int)n; i += 2){
		printf("%06o : %06o\n", (start + i), w_read(start + i));
	}
	printf("\n");
}

	