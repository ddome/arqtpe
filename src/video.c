#include "../include/video.h"
#include "../include/defs.h"
#include "../include/ints.h"
#include "../include/kasm.h"

extern int screen_pos;



/* Buffer de prueba en reemplazo del buffer del teclado */
/* el buffer del teclado original tiene que ser una cola
 * ya que con este buffer se imprime ar revez.
 */
char test_buffer[10];
int gl=EMPTY;
/* */



int writeWrapper(const void * buff, int size)
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

int
getNLChar()
{
	char c;
	read(SCREENNL, &c, 1);
	return c;
}

/* Funcion que chequea una entrada del teclado,
 * imprime en pantalla y la guarda en un buffer.
 */

/* funcion que simula una entrada del teclado */
void
test_keys()
{
	test_buffer[++gl] = 'i';
	test_buffer[++gl] = 'u';
	test_buffer[++gl] = 'q';
	test_buffer[++gl] = 'r';
	test_buffer[++gl] = 'a';
}/* funcion que simula una entrada del teclado */

void
getline(char *buffer)
{
    char c[1];
    int timer=0;
    int last = EMPTY;

    do {
        /* cada 10000 iteraciones se ingresa una palabra */
        timer++;
        if( timer%100000 == 0 ) {
            test_keys();
        }
        /* aca le da enter */
        if( timer%1000000 == 0 ) {
            test_buffer[++gl] = '\n';
            timer = 0;
        }

        /* gl indica si hay caracteres entrantes */
        if( gl >= 0 ) {
        /* chequea y lee en caso de haber una entrada pendiente */
            read(KEYBOARD,&(c[0]),1);

            buffer[++last] = c[0];
            putchar(buffer[last]);
        }
    } while( c[0] != '\n' );

    buffer[++last] = '\0';

}

void
welcome()
{
	printf("========================================================================\n");
    printf("                      	Minikernel v0.1                                 \n");
    printf("                Anda como el culo, pero anda...                         \n");
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
	printf("bombau@minikernel: ");
}



