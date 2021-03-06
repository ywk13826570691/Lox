%{
	#include<ctype.h>
	#include<stdio.h>
    #include "lox_function.h"
    #include "lox_opcode.h"
    #include "lox_register.h"
    #include "lox_array.h"
    #include "lox_if.h"
    #include "lox_foreach.h"
    #include "lox_while.h"
    #include "lox_repeat.h"
    #include "lox_loop.h"
    #include "lox_keywords.h"
    extern int lox_linenumber;
    extern unsigned int lox_var_label_index;
    extern int lox_function_parsing;
    
    char lox_var_name[50];
    char lox_var_name2[50];
    //int yydebug=1;
    

static long lox_eq(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_equal(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_neq(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_nequal(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_lt(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_lt(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_gt(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_gt(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_ge(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_ge(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_le(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_le(r1, r2, ret);
	return ret;
}


static long lox_add(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_add(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_sub(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_sub(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_mul(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_mul(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_div(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_div(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_mod(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_mod(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_plus(long r1)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_plus(r1, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_minus(long r1)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_minus(r1, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_number(float r1)
{
	long ret = lox_var_label_index;
	lox_opcode_push_number_var(r1, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_string(char *str)
{
	long ret = lox_var_label_index;
	lox_opcode_push_string_var(str, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_nil()
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_var_label_index++;
	return ret;
}

static long lox_not(long r1)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_not(r1, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_and(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_and(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_or(long r1, long r2)
{
	long ret = lox_var_label_index;
	lox_opcode_push_temp_var(ret);
	lox_opcode_or(r1, r2, ret);
	lox_var_label_index++;
	return ret;
}

static long lox_bool(int v)
{
	long ret = lox_var_label_index;
	lox_opcode_push_bool_var(ret, v);
	lox_var_label_index++;
	return ret;
}

%}

%union 
{
 long   vLong;
 float vFloat;
 char *vChar;
}

%start program

%token IF 
%token THEN 
%token ELSE 
%token ELSEIF 
%token WHILE 
%token DO 
%token REPEAT 
%token UNTIL 
%token FOREACH
%token BREAK
%token CONTINUE
%token LOX_IN
%token FUNCTION
%token END
%token RETURN
%token GLOBAL
%token LOCAL

%token  <vLong> NIL
%token  AND
%token  OR
%token  NOT
%token  EQ
%token  NE
%token  LE
%token  GE
%token  CONC
%token  <vLong> LOX_TRUE
%token  <vLong> LOX_FALSE
%token  <vChar> STRING
%token  <vFloat> NUMBER
%token  <vChar> NAME
 

%type <vLong> expr var  varlist functionvalue  functioncall  retlist forexpr forrange for_range_list

%type <vLong> functioncall_dep_call 

%left AND OR
%left EQ NE '>' '<' LE GE
%left CONC
%left '+' '-'
%left '*' '/'
%left NOT

%nonassoc UMINUS

%%
program : function_list
        ;
        
function_list : 
	  | function_list stat sc
	  | function_list function
	  ;

function : FUNCTION  NAME { lox_new_function($2); lox_function_parsing = 1;}   '(' parlist ')' { lox_opcode_function_param_end(); } block END { lox_opcode_function_end();lox_cur_parsing_function_end(); lox_function_parsing = 0;}
		 ;
		 
parlist  :	/* empty */
	  |	parlist1
	  ;

parlist1 :	NAME { 
					lox_func_add_arg_name($1); 
					int ret = lox_add_local_symbol($1, lox_var_label_index);
					if (ret > 0)
					{
						lox_error("Defined function find an same var same with param???:%s\n", $1);
						exit(0);
					}
					else
					{
						lox_opcode_push_var($1, lox_var_label_index);
						lox_var_label_index++;
					}
				}
      |	parlist1 ',' NAME {
      						lox_func_add_arg_name($3); 
      
      						int ret = lox_add_local_symbol($3, lox_var_label_index);
							if (ret > 0)
							{
								lox_error("Define function find an same var same with param:%s\n", $3);
								exit(0);
							}
							else
							{
								lox_opcode_push_var($3, lox_var_label_index);
								lox_var_label_index++;
							}
      					}
	  ;
/*
block : statlist  ret 
       ;
*/

block : statlist
       ;

statlist : /* empty */
	 | statlist stat sc
	 ;
	 
stat : stat1 
	 ;
	 		
sc	 : /* empty */ | ';' ;


stat1 : IF expr THEN {
                        int ret = lox_if_index_increase();
                        lox_if_index_push(ret);
                        lox_opcode_cmp($2);
                        lox_opcode_jmpeq_label(lox_else_label(), 0);
                    } 
            block  {
                        lox_opcode_jmp_label(lox_if_end_label(), 0);
                   }
            elsepart END {
            				lox_opcode_push_label(lox_else_label());
                            lox_opcode_push_label(lox_if_end_label());
                            lox_if_index_pop();
                         }
	| WHILE  
        {
            int ret = lox_while_index_increase();
            lox_while_index_push(ret);
            lox_opcode_push_label(lox_while_label());
            lox_push_loop_index();
            lox_push_loop_end_label(lox_while_end_label());
            lox_push_loop_start_label(lox_while_label());
        }
        expr DO 
        {
            lox_opcode_cmp($3);
            lox_opcode_jmpeq_label(lox_while_end_label(), 0);
        } block   
        {
            lox_opcode_jmp_label(lox_while_label(), 1);
            lox_opcode_push_label(lox_while_end_label());
            lox_while_index_pop();
        }
        END { lox_pop_loop_index(); lox_pop_loop_end_label();lox_pop_loop_start_label(); }
	| REPEAT  
    {
        int ret = lox_foreach_index_increase();
    	lox_repeat_index_push(ret);
        lox_opcode_push_label(lox_repeat_label());
        lox_push_loop_index();
        lox_push_loop_end_label(lox_repeat_end_label());
        lox_push_loop_start_label(lox_repeat_label());
    }     
    block UNTIL expr
    {
        lox_opcode_cmp($5);
        lox_opcode_jmpneq_label(lox_repeat_label(), 1);
        lox_opcode_push_label(lox_repeat_end_label());
        lox_repeat_index_pop();
        lox_pop_loop_index();
        lox_pop_loop_end_label();
        lox_pop_loop_start_label();
    }
    | FOREACH 
    		{  
    			int ret = lox_foreach_index_increase();
    			lox_foreach_index_push(ret);
                lox_push_loop_index();
                lox_push_loop_end_label(lox_foreach_end_label());
                lox_push_loop_start_label(lox_foreach_label());
    		}
    forexpr LOX_IN forrange {
        						lox_opcode_push_label(lox_foreach_label());
    							lox_opcode_cmp_inrange($5, $3);
    							lox_opcode_jmpeq_label(lox_foreach_end_label(), 0);
    						} block END {
    										lox_opcode_jmp_label(lox_foreach_label(), 1);
    										lox_opcode_push_label(lox_foreach_end_label());
    										lox_foreach_index_pop();
                                            lox_pop_loop_index();
                                            lox_pop_loop_end_label();
                                            lox_pop_loop_start_label();
    								 	}
        /*
        | functioncall   {
                           struct lox_function_calling *call_f = lox_get_cur_calling_function();
                           lox_opcode_jmp($1, -100, (long)call_f);
                           lox_func_clear((long)call_f);
                           lox_pop_cur_calling_function();
    				    }
        */
        
        | functioncall_dep_call '(' function_parlistlist ')' {
                                    struct lox_function_calling *call_f = lox_get_cur_calling_function();
                                    lox_opcode_jmp($1, -100, (long)call_f);
                                    lox_func_clear((long)call_f);
                                    lox_pop_cur_calling_function();
                                }

        | var_create '=' varlist
            {
            	if (lox_is_keyword(lox_var_name))
            	{
            		lox_error("var is keyword\n");
            		exit(0);
            	}
				if (lox_get_is_array_element())
				{
					int ret = lox_find_local_symbol(lox_var_name);
					if (ret < 0)
					{
						lox_error("Using an invalid array:%s\n", lox_var_name);
						exit(0);
					}
					else
					{
						lox_info("Using array elememt:%s\n", lox_var_name);
					}
					extern long lox_array_ele_index;
					extern long lox_arrary_ele_labels[50];
					lox_opcode_set_array_object(ret, $3, lox_arrary_ele_labels, lox_array_ele_index);
					lox_array_element_end();
                    memset(lox_var_name, 0, 50);
				}
				else
				{
					int ret = lox_add_local_symbol(lox_var_name, lox_var_label_index);
                    long label = 0;
					if (ret > 0)
					{
		                lox_info("find same var:%s\n", lox_var_name);
						label = ret;
					}
					else
					{
						lox_opcode_push_var(lox_var_name, lox_var_label_index);
						label = lox_var_label_index;
						lox_var_label_index++;
					}
                    lox_opcode_move(label, $3);
				}
			}

    | var_decalre
    | ret
    | BREAK { 
                if (lox_is_loop_parsing() <= 0)
                {
                    lox_error("!!!break must in while/foreach/repeat\n");
                    exit(0);
                }
                lox_opcode_jmp_label(lox_get_cur_loop_end_label(), 0);
            }
    | CONTINUE {
                    if (lox_is_loop_parsing() <= 0)
                    {
                        lox_error("!!!continue must in while/foreach/repeat\n");
                        exit(0);
                    }
                    lox_opcode_jmp_label(lox_get_cur_loop_start_label(), 1);
                }
	;

functioncall_dep_call:functioncall_dep  
                     {
                        long ret = lox_find_local_symbol(lox_var_name2);
				        long retf = lox_find_function(lox_var_name2);		
				
				        if (ret < 0 && retf < 0)
				        {
					        lox_error("call function Using an invalid var:%s %d\n", lox_var_name2, lox_cur_line_number());
					        exit(0);
				        }
				
				        // function object
				        if (ret < 0 && retf > 0)
				        {
					        $$ = lox_var_label_index;
					        lox_opcode_push_func_var(lox_var_label_index, retf);
					        lox_var_label_index++;
				        }
				
				        if (ret > 0)
				        {
					        if (lox_get_is_array_element())
					        {
						        extern long lox_array_ele_index;
						        extern long lox_arrary_ele_labels[50];
						        $$ = lox_var_label_index;
						        lox_opcode_push_temp_var(lox_var_label_index);
						        lox_opcode_get_array_object(ret, lox_var_label_index, lox_arrary_ele_labels, lox_array_ele_index);
						        lox_var_label_index++;
						        lox_array_element_end();
					        }
					        else
					        {
						        $$ = ret;
					        }
				        }
                        lox_push_cur_calling_function($$);
                        memset(lox_var_name2, 0, 50);
                    }                 
                   ;

functioncall_dep: NAME { strcpy(lox_var_name2, $1); }
                | functioncall_dep '[' expr ']' { lox_set_is_array_element(); lox_array_element_index_push_label($3); }
;
	
forexpr:NAME {
				int ret = lox_add_local_symbol($1, lox_var_label_index);
				if (ret > 0)
				{
					lox_info("find same var foreach:%s\n", $1);
					$$ = ret;
				}
				else
				{
					lox_opcode_push_var($1, lox_var_label_index);
					$$ = lox_var_label_index;
					lox_var_label_index++;
				}
			}
        ;
forrange: for_range_list {$$ = $1;}
         ;

for_range_list:'[' expr ',' expr ']' { 
								lox_opcode_push_range_var(lox_var_label_index, $2, $4);
								$$ = lox_var_label_index;
								lox_var_label_index++;
							}
                ;
elsepart : /* empty */
	 | ELSE { lox_opcode_push_label(lox_else_label()); } block
     | ELSEIF expr THEN 
     { 
     	lox_opcode_push_label(lox_else_label()); 
     	lox_opcode_cmp($2); 
     	lox_opcode_jmpeq_label(lox_else_label(), 0);
     } block { lox_opcode_jmp_label(lox_if_end_label(), 0); }  elsepart   
     ;
ret	: /* empty */
        /*| RETURN exprlist sc */
        | RETURN  retlist sc
        {
            if (!lox_function_parsing)
            {
                lox_info("return must in function\n");
                exit(0);
            }
        }
        ;

retlist: /* empty */ { lox_opcode_return(0, 0);}
    | expr { $$ = $1; lox_opcode_return($1, 1);}
       ;
var_decalre: NAME sc
		   ;
var_create: varlist1 
			;
varlist1  :	NAME { 
					strcpy(lox_var_name, $1);
					long ret = lox_find_function(lox_var_name);
					if (ret > 0)
					{
						lox_error("Can not move an value to function\n");
						exit(0);
					}
				 }
          | varlist1 '[' expr ']' { lox_set_is_array_element(); lox_array_element_index_push_label($3); }
	      ;


varlist  : expr { $$ = $1; }
     	 | array {
                    extern long  lox_array_index;
                    extern long  lox_array_label[1000];
                    $$ = lox_var_label_index;
                    lox_opcode_push_array_var(lox_var_label_index, lox_array_label, lox_array_index);
                    lox_var_label_index++;
                    lox_array_parsing_end();
             	}
		 ;

expr : '(' expr ')' 			{ $$ = $2; }
     |	expr EQ expr			{ $$ = lox_eq($1, $3); 	}
     |	expr '<' expr			{ $$ = lox_lt($1, $3); 	}
     |	expr '>' expr			{ $$ = lox_gt($1, $3); 	}
     |	expr NE  expr			{ $$ = lox_neq($1, $3);	}
     |	expr LE  expr			{ $$ = lox_le($1, $3); 	}
     |	expr GE  expr			{ $$ = lox_ge($1, $3); 	}
     |	expr '+' expr 			{ $$ = lox_add($1, $3);	}
     |	expr '-' expr 			{ $$ = lox_sub($1, $3);	}
     |	expr '*' expr 			{ $$ = lox_mul($1, $3);	}
     |	expr '/' expr 			{ $$ = lox_div($1, $3);	}
     |	expr '%' expr 			{ $$ = lox_mod($1, $3);	}
     |	'+' expr %prec UMINUS 	{ $$ = lox_plus($2);    }
     |	'-' expr %prec UMINUS 	{ $$ = lox_minus($2);	}
     |	var     				{ $$ = $1; 				}
     |	NUMBER  				{ $$ = lox_number($1); 	}
     |	STRING  				{ $$ = lox_string($1); 	}
     |	NIL     				{ $$ = lox_nil();       }
     |	functioncall {
                       struct lox_function_calling *call_f = lox_get_cur_calling_function();
     				   $$ = lox_var_label_index;
     				   lox_opcode_push_temp_var(lox_var_label_index);
                       lox_opcode_jmp($1, lox_var_label_index, (long)call_f);
                       lox_func_clear(call_f);
                       lox_pop_cur_calling_function();
                       lox_var_label_index++;
                     }
     |	NOT expr %prec UMINUS 	{ $$ = lox_not($2);		}
     |	expr AND  expr 			{ $$ = lox_and($1, $3);	}
     |	expr OR   expr 			{ $$ = lox_or($1, $3);}
     |  LOX_FALSE      			{ $$ = lox_bool(0);  	}
     |  LOX_TRUE       			{ $$ = lox_bool(1); 	}
     ;

array: '[' arraylist ']'
        ;

arraylist:
        | arraylist1
        ;

//
arraylist1: expr {   lox_array_push_label($1); }
          | arraylist1  ','  expr { lox_array_push_label($3);}
          ;
	     
functioncall : functionvalue  '(' function_parlistlist ')' { $$ = $1; }
             ;

function_parlistlist  : /* empty */
          |	function_parlistlist1
          ;

function_parlistlist1 :	expr { lox_func_push_arg_label($1);}
          |	function_parlistlist1 ',' expr { lox_func_push_arg_label($3); }
          ;


/*
functionvalue : NAME {
                        $$ = lox_find_function($1);
                        lox_info("calling function:%s %d\n", $1, $$);
                        if ($$ < 0)
                        {
                            lox_info("Call invalid function at line:%d %s\n", lox_linenumber, $1);
                            exit(0);
                        }
                        lox_push_cur_calling_function($$);
                    }
	         ;
*/


functionvalue : var {
                        $$ = $1;
                        //lox_info("calling function:%s %d\n", $1, $$);
                        //if ($$ < 0)
                        //{
                            //lox_info("Call invalid function at line:%d %s\n", lox_linenumber, $1);
                            //exit(0);
                        //}
                        lox_push_cur_calling_function($$);
                    }
	         ;

/*
var	  :	NAME  { 
				struct lox_symbol *sym = lox_get_cur_parsing_function();
				int ret = lox_find_local_symbol($1);
				
				if (ret <= 0)
				{
					lox_error("Using an invalid var:%s\n", $1);
					exit(0);
				}
				$$ = ret;
			  }
	  ;
*/

var: varlist2
			{
				long ret = lox_find_local_symbol(lox_var_name2);
				long retf = lox_find_function(lox_var_name2);		
				
				if (ret < 0 && retf < 0)
				{
					lox_error("Using an invalid var:%s %d\n", lox_var_name2, lox_cur_line_number());
					exit(0);
				}
				
				// function object
				if (ret < 0 && retf > 0)
				{
					$$ = lox_var_label_index;
					lox_opcode_push_func_var(lox_var_label_index, retf);
					lox_var_label_index++;
				}
				
				if (ret > 0)
				{
					if (lox_get_is_array_element())
					{
						extern long lox_array_ele_index;
						extern long lox_arrary_ele_labels[50];
						$$ = lox_var_label_index;
						lox_opcode_push_temp_var(lox_var_label_index);
						lox_opcode_get_array_object(ret, lox_var_label_index, lox_arrary_ele_labels, lox_array_ele_index);
						lox_var_label_index++;
						lox_array_element_end();
					}
					else
					{
						$$ = ret;
					}
				}
                memset(lox_var_name2, 0, 50);
			}
	;

varlist2  :	NAME { strcpy(lox_var_name2, $1); }
          | varlist2 '[' expr ']' { lox_set_is_array_element(); lox_array_element_index_push_label($3); }
	      ;

%%

#if 0
int  main()
{
	extern FILE *yyin;
	yyin=fopen("b.txt","r");
	yyparse();
	return 0;
}
#endif

int yywrap (void)
{
 	return 1;
}
int yyerror(char *s)
{
    printf("%s %d error ! line:%d\n",s, yyget_lineno(), lox_cur_line_number());
    exit(0);
}
