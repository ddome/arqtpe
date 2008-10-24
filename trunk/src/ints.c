#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/ints.h"
#include "../include/defs.h"

/* Variable global de la posicion en pantalla */
int screen_pos = 0;
char * video = (char *) 0xb8000;

/* Buffer de prueba en reemplazo del buffer del teclado */
extern test_buffer[];
extern gl;
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

int int_80r(FileDesc fd, char * buff, int size)
{
	int i;


	switch (fd)
	{
		case KEYBOARD: break;
		default: break;
	}

	if( gl < 0 )
		return EMPTY;

	_Cli();

	for(i = 0; i < size; i++) {
		/* deja de almacenar en caso de no haber mas caracteres */
		if( gl<0 )
		  break;
		buff[i] =  test_buffer[gl--];
  }
	_Sti();

	return READ;

}
