Digit	[0-9]
Letter	[a-zA-Z]
IntLit	{Digit}+
Blank	" "


%{
#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void yyerror(char *);
#include "y.tab.h"
void process_id();
%}
%%
[ \t\n]+	{/*delete*/}

begin		{return (START);}
end		{return (END);}
output		{return (OUTPUT);}

"int"		{
		process_id();
		return DEC_TYPE;
		}
"true"		{
		yylval.num = 1;
		return INTEGER;
		}
"false"		{
		yylval.num = 0;
		return INTEGER;
		}

"char"		{
		process_id();
		return DEC_TYPE;
		}
"boolean"		{
		process_id();
		return DEC_TYPE;
		}
"bool"		{
		process_id();
		return DEC_TYPE;
		}
"unsigned"	{
		process_id();
		return DEC_TYPE;
		}
"do"		{
		return DO;
		}
"if"		{
		return IF;
		}
"else"		{
		return ELSE;
		}
"void"		{
		process_id();
		return DEC_TYPE;
		}
"return"		{
		return RETURN;
		}
"continue"	{
		return DO_END;
		}

"and"		{
		return AND;
		}

"or"		{
		return OR;
		}

".lt."		{
		process_id();
		return JUDGE_OPT;
		}

".gt."		{
		process_id();
		return JUDGE_OPT;
		}
".ge."		{
		process_id();
		return JUDGE_OPT;
		}
".le."		{
		process_id();
		return JUDGE_OPT;
		}
".eq."		{
		process_id();
		return JUDGE_OPT;
		}
".neq."		{
		process_id();
		return JUDGE_OPT;
		}

{Letter}({Letter}|{Digit}|_)*		{
		process_id();
		return (ID);
		}
\"({Letter}|{Digit}|{Blank}|:|_|-|=|\[|\]|!|@|#|$|\%|\^|\&|\*|\(|\)|\{|\}|\[|\]|\<|\>|\+|\*|\/|\;|\\|\,)*\"		{
		process_id();
		return (STRING);
		}

{IntLit} {
		yylval.num = atoi(yytext);
		return INTEGER;
		}
"="		{return (ASG); }

"**"		return EXP;
"+"		return '+';
"\""		return '"';
"-"		return '-';
"*"		return '*';
"/"		return '/';
";"		return ';';
"("		return '(';
")"		return ')';
"["		return '[';
"]"		return ']';
","		return ',';
":"		return ':';
"&"		return '&';
"|"		return '|';
"~"		return '~';
"^"		return '^';
"%"		return '%';
"<"		return '<';
">"		return '>';


%%

void process_id()
{
	
	SymbolTableElement symbol_table_node;

//###############################################	
	symbol_table_node = (SymbolTableElement)
		malloc(sizeof(struct symbol_table_element));
	symbol_table_node->s = (char *) malloc(strlen(yytext) + 1);
	strcpy(symbol_table_node->s,yytext);
	
//	printf("ID : %s\n",symbol_table_node->s ) ;
//###############################################	
	yylval.symbol = symbol_table_node;
}
	
int yywrap(void) {
 return 1;
}
