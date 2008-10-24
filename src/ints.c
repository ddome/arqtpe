#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/ints.h"


/*esta variable es utilizada para chequear si hubo entradas del teclado */
/*se puede cambiar por una variable global manejada por el driver del teclado */
extern int entry;

/* Variable global de la posicion en pantalla */
int screen_pos = 0;
char * video = (char *) 0xb8000;

/* Buffer de prueba en reemplazo del buffer del teclado */
extern char test_buffer[];
extern int gl;
/* */

char format= WHITE_TXT;

void int_80w(FileDesc fd, const void * buff, int size)
{
	char * video;
	switch (fd)
	{
		case SCREEN: video = (char *) 0xb8000; break;
		default: video = (char *) 0xb8000; break;
	}

    int i;

    _Cli();
    for(i = 0; i < size; i++)
    {
        video[screen_pos++]= *((char*)buff+i);
        video[screen_pos++]= format;
    }
    _Sti();
}

void int_80r(FileDesc fd, char * buff, int size)
{
	int i;


	switch (fd)
	{
		case KEYBOARD: break;
		default: break;
	}

	_Cli();

	if( gl< 0 )
		entry = EMPTY;
	else
		entry = READ;

	i=0;
	while( gl >= 0 && i<= size ) {
		buff[i] = test_buffer[gl];
		i++;
		gl--;
	}

	_Sti();

}
