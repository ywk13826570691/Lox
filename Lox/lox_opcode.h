#ifndef LOX_OPCODE_H
#define LOX_OPCODE_H
#include "lox_config.h"

/*
 *
 * cmd:
nop
move 1,2
push 1,2,3,4,5,6
pop 1,2,3,4,5,6

add 1, 2, 3
sub 1, 2, 3
mul 1, 2, 3
div 1, 2, 3
mod 1, 2, 3
not 1, 2 qu fang
xor 1, 2, 3
or wei huo 1, 2, 3
and wei yu 1, 2, 3
shl 1,2,3
shr 1,2,3
cmp 1 , 2 she zhi Z

jmp r1

cprs
0 1 2 3 4 5
N Z V

N:
Z:运算结果为0时为1，其他都为1
V:除0
 */

enum lox_opcode
{
    LOX_NOP,
    LOX_MOVE,       //move r1,r2
    LOX_MOVEEQ,       //move r1,r2
    LOX_MOVENEQ,       //move r1,r2

    LOX_ADD ,       //add r1,r2,r3  :r1 = r2+r3
    LOX_SUB,        // sub r1,r2,r3 :r1 = r2 - r3
    LOX_MUL,        //mul r1,r2,r3  :r1 = r2*r3
    LOX_DIV,        //div r1,r2,r3  :r1 = r2/r3
    LOX_MOD,        //mod r1,r2,r3  :r1 = r2%r3
    LOX_NOT,        //not r1,r2     :r1 = !r2
    LOX_XOR,        //xor r1,r2,r3  :r1 = r2^r3
    LOX_AND,        //and r1,r2,r3  :r1 = r2&r3
    LOX_OR,         //or r1,r2,r3   :r1 = r2|r3
    LOX_SL,         //sl r1,r2,r3   :r1 = r2 << r3
    LOX_SR,         //sr r1,r2,r3   :r1 = r2 >> r3
    LOX_CMP,        //cmp r1,r2,r3  :r1 = r2 == r3

    LOX_PUSH,       // push a var
    LOX_JMP,        //jmp r1        :pc to r1
    LOX_JMPNEQ,        //jmp r1        :pc to r1
    LOX_JMPEQ,        //jmp r1        :pc to r1
    LOX_JMP_LABEL,  //jmp r1        :pc to r1
    LOX_JMPNEQ_LABEL,  //jmp r1        :pc to r1
    LOX_JMPEQ_LABEL,  //jmp r1        :pc to r1
    LOX_RETURN,
    LOX_END_FUNCTION, // end an function
    LOX_FUNCTION_PARAM_END, // param end


    LOX_GET_VAR,
    LOX_NULL,
};

enum lox_push_type
{
    PUSH_NUMBER,
    PUSH_ARG,
    PUSH_NUMBER_VAR,
    PUSH_STRING_VAR,
    PUSH_VAR,
    PUSH_TEMP_VAR,
    PUSH_ARRARY,
};

struct lox_cmd_push
{
    int  p_type;
    long f_number;
    float f_f;
    char *f_str;
    char *f_var_name;
    int  f_label_index;
};

struct lox_cmd_jmp
{
    unsigned int args_cnt;
    long args[100];
};

struct lox_cmd
{
    int  cmd_opcode;
    char cmd_jmp_label[LOX_VAR_MAX_NAME_LEN];
    long cmd_args[LOX_REGISTER_CNT*20];

    struct lox_cmd_push cmd_push;
    struct lox_cmd_jmp cmd_jmp;

    //for get var
    char *cmd_var_name;


    int  cmd_label_index;
};

//int lox_opcode_push_number(long n);
//int lox_opcode_push_arg(char *argname, int reg);

int lox_opcode_push_number_var(float f, int label);
int lox_opcode_push_string_var(char *str, int label);
int lox_opcode_push_var(char *var_name, int label);
int lox_opcode_push_temp_var(int label);
int lox_opcode_push_array_var(int label, long *labels, long label_cnt);


//int lox_opcode_get_var(char *var_name, int label);


int lox_opcode_add(long r1, long r2, int label);
int lox_opcode_sub(long r1, long r2, int label);
int lox_opcode_mul(long r1, long r2, int label);
int lox_opcode_div(long r1, long r2, int label);


int lox_opcode_move(long r1, long r2);

int lox_opcode_jmp(long r1, int reg);

int lox_opcode_return(long r1, int has_ret_expr);

int lox_opcode_function_end(void);
int lox_opcode_function_param_end(void);


#endif // T_H
