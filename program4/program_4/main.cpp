 #include <stdio.h>
 #include <string.h>
 #include <iostream>
using namespace std;

extern int yyparse();
extern void print_head();
extern void print_tail();

int main(void) {
 
print_head();	
yyparse();
print_tail();


 return 0;
}
