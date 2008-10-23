#include "../include/kc.h"
#include "../include/kasm.h"

extern char * video;
extern int screen_pos;


/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]='7';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

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
