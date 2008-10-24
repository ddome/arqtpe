#include "../include/video.h"
#include "../include/defs.h"

extern screen_pos;
extern video; /*ESTA DIRECCION NO DEBERIA LEERSE FUERA DE LA INT80H*/


int writeWrapper(const void * buff, int size)
{
	//FileDesc fd;
	char auxc = ' ';
	int i;

	if (screen_pos >= (CANT_COLS * CANT_ROWS)*2)
	{
		for (screen_pos = 0; screen_pos < CANT_COLS *(CANT_ROWS -1)*2;)
		{
			write (SCREEN, video + screen_pos + CANT_COLS *2, 1);
		}
		for(i = 0; i < CANT_COLS; i++)
			write (SCREEN, &auxc, 1);
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
			write (SCREEN,0,1);
			screen_pos -= 2;
		}
		else
		{
			write (SCREEN,buff+i,1);
		}
	}

    return size;
}

void clear_screen()
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

/* Funcion que chequea una entrada del teclado,
 * imprime en pantalla y la guarda en un buffer.
 */

void
refresh_in(char *buffer,int *last)
{
	char c[1];

	if( read(KEYBOARD,&(c[0]),1) != EMPTY ) {
		putchar(c[0]);
		buffer[++(*last)];
	}


}

void
welcome()
{
	putchar('B');
	putchar('i');
	putchar('e');
	putchar('n');
	putchar('v');
	putchar('e');
	putchar('n');
	putchar('i');
	putchar('d');
	putchar('o');
	putchar('\n');
}
