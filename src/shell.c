#include "../include/shell.h"
#include "../include/video.h"
#include "../include/defs.h"



/* Indica la posicion actual del cursor */
extern screen_pos;

void
shell()
{
	/* Buffer de almacenamiento de caracteres */
	char in_buffer[MAX_CHARS];
	int last = EMPTY;

	clear_screen();
	welcome();

	while(1) {

		getline(in_buffer,&last);

		// proceso el comando almacenado en in_buffer

		last = EMPTY;
		prompt();
	}


	return;
}
