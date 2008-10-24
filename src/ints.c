#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/ints.h"

/* Variable global de la posicion en pantalla */
int screen_pos = 0;
char * video = (char *) 0xb8000;

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

void int_80r(FileDesc fd, void * buff, int size)
{
	int i;

	
	switch (fd)
	{
		case KEYBOARD: break;
		default: break;
	}
		
	
	_Cli();
	    for(i = 0; i < size; i++)
	    {
//	        ((char*)buff)[i] =  ascbuff[gl+i];	/* ascbuff arreglo GLOBAL con los ascii y gl la posicion*/
	    }
	_Sti();
	
}
