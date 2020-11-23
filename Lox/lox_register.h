#ifndef LOX_REGISTER_H
#define LOX_REGISTER_H
extern long lox_register[];

#define R0 lox_register[0]
#define R1 lox_register[1]
#define R2 lox_register[2]
#define R3 lox_register[3]
#define R4 lox_register[4]
#define R5 lox_register[5]
#define R6 lox_register[6]
#define R7 lox_register[7]
#define R8 lox_register[8]
#define R9 lox_register[9]


#define R10 lox_register[10]
#define R11 lox_register[11]
#define R12 lox_register[12]
#define R13 lox_register[13]
#define R14 lox_register[14]

#define FP lox_register[10]
#define SP lox_register[11]
#define LR lox_register[12]
#define PC lox_register[13]
/*
bit 0: zero , 1 is zero ,0 not zero
*/
#define SPR lox_register[14]


#define LOX_R(x) lox_register[x]

int lox_register_init();

#endif // REGISTER_H
