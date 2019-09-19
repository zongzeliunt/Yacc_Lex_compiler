#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct symbol_table_element
{
	char *s;
	int offset;
};

typedef struct symbol_table_element *SymbolTableElement;

