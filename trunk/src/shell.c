#include "../include/shell.h"
#include "../include/video.h"
#include "../include/defs.h"



/* Indica la posicion actual del cursor */
extern screen_pos;

int
command(char *line )
{
	return 10;

}


void
printline(char *line)
{
	while( *line != '\n' ) {
		putchar(*line);
		line++;
	}
}


void
bash(char *line  )
{
	int fnumber;

	fnumber = command(line);

	switch(fnumber) {
	default: printf("bash: ");
			 printline(line);
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

		getline(in_buffer);
		bash(in_buffer);

		// proceso el comando almacenado en in_buffer

		prompt();
	}


	return;
}
