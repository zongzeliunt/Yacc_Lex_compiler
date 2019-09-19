compiler 	: lex.c y.tab.c main.cpp
		g++ y.tab.c lex.c main.cpp -o compiler 

yacc.y		: gram.tok gram.prod
		cat gram.tok gram.prod > yacc.y

lex.c		: lex.l
		lex lex.l
		mv lex.yy.c lex.c


y.tab.c y.tab.h	: yacc.y
		yacc -d yacc.y


clean		:
		rm compiler yacc.y y.tab.c y.tab.h lex.c 
