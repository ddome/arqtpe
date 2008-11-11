#include "../include/defs.h"
#include "../include/kasm.h"
#include "../include/ints.h"
#include "../include/buffer.h"

#define CANT_KEYS 104
#define ALTGR 0x38
#define IS_NUMPAD_KEY(c) ((c)>=0x47 && (c)<=0x53)
#define IS_VALID_ASCII(c) (c)!=0

extern screen_pos;

/* mapeo de los estados del teclado */
int numlock=0,caps=0,scrolllock=0,shift=0,altgr=0;

/* Contador del cursor */
int counter=0;

static void
parpadeo()
{
	counter++;
	if(counter == DELAY/2)
		_DelCursor();
	if(counter == DELAY) {
		_RestoreCursor();
		counter = 0;
	}
}

void
int_08()
{
	parpadeo();
}



int
int_09_US(unsigned char code)
{
	/*Veo que teclas estan oprimidas y modifico las variables
		 *globales, en caso de ser las teclas scrolllock,capslock
		 *o numlock */
	    char ascii;
	    if( code==LSHIFT || code==RSHIFT)
			shift=1;
		else if( code==(LSHIFT | MASK) || code==(RSHIFT | MASK) )
			shift=0;
		else if( code==CAPSLOCK )
			caps=!caps;
		else if( code==NUMLOCK )
			numlock=!numlock;
		else if( code==SCROLLLOCK )
			scrolllock=!scrolllock;
	        else if( IS_NUMPAD_KEY(code) && !numlock)
	            return 0;
		else
		{
			if( IS_MAKE_CODE(code) && code<=CANT_KEYS)
			{
			    ascii=ToAsciiUS(code);
			    if(IS_VALID_ASCII(ascii))
			        AddToBuffer(ascii);
			}
		}
		return 0;
}


int
int_09_LAT(unsigned char code)
{
	/*Veo que teclas estan oprimidas y modifico las variables
		 *globales, en caso de ser las teclas scrolllock,capslock
		 *o numlock */
	   char ascii;
	    if( code==LSHIFT || code==RSHIFT)
			shift=1;
		else if( code==(LSHIFT | MASK) || code==(RSHIFT | MASK) )
			shift=0;
		else if( code==CAPSLOCK )
			caps=!caps;
		else if( code==NUMLOCK )
			numlock=!numlock;
		else if( code==SCROLLLOCK )
			scrolllock=!scrolllock;
	        else if( IS_NUMPAD_KEY(code) && !numlock)
	            return 0;
		else
		{
			if( IS_MAKE_CODE(code) && code<=CANT_KEYS)
			{
			    ascii=ToAsciiLAT(code);
			    if(IS_VALID_ASCII(ascii))
			        AddToBuffer(ascii);
			}
		}
		return 0;
}

void
int_80w(FileDesc fd, const void * buff, int size)
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
        video[screen_pos++]= WHITE_TXT;
    }
    _Sti();
}

void
int_80r(FileDesc fd, char * buff, int size)
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







