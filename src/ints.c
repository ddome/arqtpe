#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/ints.h"
#include "../include/keyboard.h"
#include "../include/buffer.h"


/* Variable global de la posicion en pantalla */
int screen_pos = 0;

/* mapeo de los estados del teclado */
int numlock=0,caps=0,scrolllock=0,shift=0;

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
	int i = 0;
	if (fd == KEYBOARD)
	{
		_Cli();


		while( !BufferIsEmpty() && i< size ) {

			buff[i] = GetFromBuffer() ;
			i++;
		}

		_Sti();
	}
	else if (fd == SCREENNL)
	{
		char * video;
		video = (char *) 0xb8000;
		_Cli();

		while( i< size ) {

			buff[i] = *(video + screen_pos + CANT_COLS *2);
			i++;

		}

		_Sti();
	}

}

int
int_09(unsigned char code)
{
	char lights=0;

	/*Veo que teclas estan oprimidas y modifico las variables
	 *globales. En caso de ser las teclas scrolllock,capslock
	 *o numlock envio el char lights, con informacion
	 *indicando que luces deben estar encendidas.
	*/


	if( code==LSHIFT || code==RSHIFT)
		shift=1;
	else if( code==(LSHIFT | MASK) || code==(RSHIFT | MASK) )
		shift=0;

	else if( code==CAPSLOCK )
	{
		caps=!caps;
		lights|=1;
		SetKBLights();
	}
	else if( code==NUMLOCK )
	{
		numlock==!numlock;
		lights|=2;
		SetKBLights();
	}
	else if( code==SCROLLLOCK )
	{
		scrolllock=!scrolllock;
		lights|=4;
		SetKBLights();
	}


	if( IS_MAKE_CODE(code) )
		AddToBuffer(code);

	return 0;
}





