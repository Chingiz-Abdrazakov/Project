#pragma once

typedef unsigned char byte; //8 bit
typedef unsigned short int word; //16 bit
typedef word Address; //16 bit




//All the "do" functions

void do_halt();

void do_mov();

void do_movb();

void do_add();

void do_sob();

void do_nop();

void do_cln();

void do_clz();

void do_clc();

void do_ccc();

void do_clr();

void do_nothing();