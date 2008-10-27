#include "../include/video.h"
#include "../include/defs.h"
#include "../include/ints.h"
#include "../include/kasm.h"
#include "../include/buffer.h"

extern int screen_pos;

int
writeWrapper(const void * buff, int size)
{
	//FileDesc fd;
	char auxc = ' ';
	int i;
	int c;

	if (screen_pos >= (CANT_COLS * CANT_ROWS)*2)
	{
		for (screen_pos = 0; screen_pos < CANT_COLS *(CANT_ROWS -1)*2;)
		{
			c = getNLChar(SCREENNL);
			write (SCREEN, &c, 1);
		}
		for(i = 0; i < CANT_COLS; i++)
			write (SCREEN, &auxc, 1); // cambie esto porque estaba escribiendo mierda cuando borrabas
		screen_pos = CANT_COLS *(CANT_ROWS -1)*2;
	}
	for (i = 0; i < size; i++)
	{
		if (((char*)buff)[i] == '\n')
		{
			screen_pos += (CANT_COLS*2) - (screen_pos % (CANT_COLS *2));
		}
		else if (((char*)buff)[i] == '\t')
		{
			screen_pos += 4;
		}
		else if (((char*)buff)[i] == '\b')
		{
			screen_pos -= 2;
			write (SCREEN,&auxc,1);
			screen_pos -= 2;
		}
		else
		{
			write (SCREEN,buff+i,1);
		}
	}

    return size;
}

void
clear_screen()
{
	char c = ' ';
	unsigned int i=0;

	while(i < (80*25)){
		i++;
		putchar(c);
	};
	screen_pos = 0;
}

void
putchar(char c)
{
	writeWrapper(&c,1);
}

int
getNLChar()
{
	char c;
	read(SCREENNL, &c, 1);
	return c;
}

void
getline(char *buffer)
{
    char c[1];
    int timer=0;
    int last = EMPTY;

    do {
    	/* CAMBIAR, no se puede acceder al teclado directamente */
		if( !BufferIsEmpty() ) {
		/* chequea y lee en caso de haber una entrada pendiente */
			read(KEYBOARD,&(c[0]),1);

			/* Chequeo que al recibir un backspace no borre mas alla
			 * del prompt y no borre del buffer de salida al caracter
			 * borrado
			 */
			if( c[0] == '\b' && last != EMPTY ) {
				buffer[last] = ' ';
				last--;
				putchar(c[0]);
			}
			if( c[0] != '\b' ) {
					buffer[++last] = c[0];
					putchar(c[0]);
			}
        }
    } while( c[0] != '\n' );

	/* Completo el string */
	buffer[++last] = '\0';
}

void
printLine(char *line)
{
	while( *line != '\n' ) {
		putchar(*line);
		line++;
	}
}

void
welcome()
{
	printf("========================================================================\n");
    printf("                      	Minikernel v0.1                                 \n");
    printf("                   BOMBAU ARREGLA EL TECLADO!!!                         \n");
	printf("========================================================================\n");
	printf("\n");
	prompt();
}

void
printf(char *string)
{
	while( *string != '\0' ) {
		putchar(*string);
		string++;
	}
}

void
prompt()
{
	printf(">: ");
}



