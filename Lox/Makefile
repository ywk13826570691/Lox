
source := lex.yy.c  lox.c  lox_opcode.c  lox_register.c  lox_stack.c  main.c  y.tab.c lox_function.c lox_handle.c lox_object.c lox_keywords.c lox_array.c
all: yacc lex
	gcc -g $(source) -ll -ly

yacc:
	yacc -d  vkang.y
lex:
	lex vkang.l

clean:
	rm y.tab.c lex.yy.c a.out *.o y.tab.h
