target = lox
lox_src := lex.yy.c  lox.c  lox_opcode.c  lox_register.c  lox_stack.c  main.c  y.tab.c lox_function.c lox_handle.c 
lox_src += lox_object.c lox_keywords.c lox_array.c lox_lib.c lox_if.c lox_foreach.c
lox_src += lox_while.c lox_repeat.c lox_loop.c
all: yacc lex
	gcc -g $(lox_src) -ll -ly -lm -o $(target)

yacc:
	yacc -d -v vkang.y -Wconflicts-sr
lex:
	lex vkang.l

clean:
	rm y.tab.c lex.yy.c   y.tab.h $(target)
