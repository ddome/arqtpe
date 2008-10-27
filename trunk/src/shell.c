#include "../include/shell.h"
#include "../include/video.h"
#include "../include/defs.h"


enum { NOTFOUND, VOID };


int
command(char *line )
{
	if( line[0] == '\0' )
		return VOID;


	return NOTFOUND;
}

void
bash(char *line  )
{
	int fnumber;

	fnumber = command(line);

	switch(fnumber) {
	case VOID: 	break;


	default: 	printf("bash: ");
				printf(line);
				printf(": command not found\n");
	}


}

void
shell()
{
	/* Buffer de almacenamiento de caracteres */
	char in_buffer[MAX_CHARS];

	clear_screen();
	welcome();

	while(1) {
		prompt();
		getline(in_buffer,MAX_CHARS);
		// proceso el comando almacenado en in_buffer
		bash(in_buffer);
	}


	return;
}
