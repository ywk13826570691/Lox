%{
	#include<ctype.h>
	#include<stdio.h>
    #include "lox_function.h"
    #include "lox_opcode.h"
    #include "lox_register.h"
    #include "lox_array.h"
    extern int lox_linenumber;
    extern unsigned int lox_var_label_index;
    extern int lox_function_parsing;
    
    char lox_var_name[50];
    char lox_var_name2[50];
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
%token  TRUE
%token  FALSE
%token  <vChar> STRING
%token  <vFloat> NUMBER
%token  <vChar> NAME
 

//%type <vInt> var exprlist exprlist1
//%type <vInt> expr  var retlist varlist1 val_list functionvalue functioncall
//%type <vInt> expr1 

//%type <pChar> parlist1

%type <vLong> expr var  varlist functionvalue  functioncall retlist

%left AND OR
%left EQ NE '>' '<' LE GE
%left CONC
%left '+' '-'
%left '*' '/'
%left NOT
%left '['
%left ']'

%nonassoc LEFT_BRACKETS
%nonassoc RIGHT_BRACKETS

%nonassoc UMINUS

%%
program : function_list
        ;
        
function_list : 
	  | function_list  stat sc
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


stat1 : IF expr THEN PrepJump block PrepJump elsepart END
	| WHILE  expr DO PrepJump block PrepJump END
	| REPEAT  block UNTIL expr PrepJump
    | var_create '=' varlist
            {
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
    | functioncall {
                       struct lox_function_calling *call_f = lox_get_cur_calling_function();
                       lox_opcode_jmp($1, -100, (long)call_f);
                       lox_func_clear((long)call_f);
                       lox_pop_cur_calling_function();
    				}
    | var_decalre
    | ret
	//| typeconstructor                
	//| LOCAL localdeclist decinit
	;
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
				 }
          | varlist1 '[' expr ']' { lox_set_is_array_element(); lox_array_element_index_push_label($3); }
	      ;

varlist  : expr { $$ = $1; }
          /*| val_list ',' expr*/
     | array {
                    extern long  lox_array_index;
                    extern long  lox_array_label[1000];
                    $$ = lox_var_label_index;
                    lox_opcode_push_array_var(lox_var_label_index, lox_array_label, lox_array_index);
                    lox_var_label_index++;
                    lox_array_parsing_end();
                }
		  ;
/*
exprlist  :
	  |	exprlist1
	  ;

	
exprlist1 :	expr
      |	exprlist1 ',' expr
	  ; 
*/

elsepart : /* empty */
	 | ELSE block
     | ELSEIF expr THEN PrepJump block PrepJump elsepart   
     ;
     
PrepJump : /* empty */
		 ;

expr : '(' expr ')' { $$ = $2; }
     |	expr EQ expr	
     |	expr '<' expr	
     |	expr '>' expr	
     |	expr NE  expr	
     |	expr LE  expr	
     |	expr GE  expr	
     |	expr '+' expr { $$ = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_add($1, $3, lox_var_label_index);lox_var_label_index++;}
     |	expr '-' expr { $$ = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_sub($1, $3, lox_var_label_index); lox_var_label_index++;}
     |	expr '*' expr { $$ = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_mul($1, $3, lox_var_label_index); lox_var_label_index++;}
     |	expr '/' expr { $$ = lox_var_label_index;lox_opcode_push_temp_var(lox_var_label_index);lox_opcode_div($1, $3, lox_var_label_index); lox_var_label_index++;}
     |	expr CONC expr 
     //	'+' expr %prec UMINUS
     //|	'-' expr %prec UMINUS
     //| typeconstructor
     //|  '@' '(' dimension ')'
     |	var { $$ = $1; }
     |	NUMBER { $$ = lox_var_label_index; lox_opcode_push_number_var($1, lox_var_label_index);lox_var_label_index++; }
     |	STRING { $$ = lox_var_label_index; lox_opcode_push_string_var($1, lox_var_label_index);lox_var_label_index++; }
     |	NIL
     |	functioncall {
                       struct lox_function_calling *call_f = lox_get_cur_calling_function();
                       struct lox_symbol *sym = (struct lox_symbol *)call_f->func;
     				   $$ = lox_var_label_index;
     				   lox_opcode_push_temp_var(lox_var_label_index);
                       lox_opcode_jmp($1, lox_var_label_index, (long)call_f);
                       lox_func_clear(call_f);
                       lox_pop_cur_calling_function();
                       lox_var_label_index++;
                       lox_info("---------------------function call end2:%s\n", sym->sym_name);
                     }
     //|	NOT expr %prec UMINUS
     |	expr AND PrepJump expr
     |	expr OR PrepJump expr	
     ;
    /*
dimension    :
	     | expr
	     ;
         */

array: '[' arraylist ']'
        ;

arraylist:
        | arraylist1
        ;

//
arraylist1: expr {   lox_array_push_label($1); }
          | arraylist1  ','  expr { lox_array_push_label($3);}
          ;
	     
functioncall : functionvalue  '(' function_parlistlist ')' { 
									$$ = $1; 
                                    struct lox_function_calling *call_f = lox_get_cur_calling_function();
                                    struct lox_symbol *sym = (struct lox_symbol *)call_f->func;
                                    lox_func_check_args((long)call_f);
								}
            ;

function_parlistlist  : /* empty */
          |	function_parlistlist1
          ;

function_parlistlist1 :	expr { lox_func_push_arg_label($1); }
          |	function_parlistlist1 ',' expr { lox_func_push_arg_label($3); }
          ;

functionvalue : NAME {
            $$ = lox_find_function($1);
            lox_info("calling function:%s\n", $1);
            lox_push_cur_calling_function($$);
            if ($$ < 0)
            {
                lox_info("Call invalid function at line:%d %s\n", lox_linenumber, $1);
                exit(0);
            }
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
				int ret = lox_find_local_symbol(lox_var_name2);
				
				if (ret <= 0)
				{
					lox_error("Using an invalid var:%s %d\n", lox_var_name2, lox_cur_line_number());
					exit(0);
				}
				
				if (lox_get_is_array_element())
				{
					extern long lox_array_ele_index;
					extern long lox_arrary_ele_labels[50];
					$$ = lox_var_label_index;
					lox_opcode_push_temp_var(lox_var_label_index);
					lox_opcode_get_array_object(ret, lox_var_label_index, lox_arrary_ele_labels, lox_array_ele_index);
					lox_var_label_index++;
					lox_array_element_end();
                    memset(lox_var_name2, 0, 50);
				}
				else
				{
					$$ = ret;
				}
			}
	;

varlist2  :	NAME { 
					strcpy(lox_var_name2, $1);
				 }
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
    printf("%s %d error!\n",s, yyget_lineno());
}
