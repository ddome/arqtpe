#include "../include/shell.h"
#include "../include/video.h"
#include "../include/defs.h"



/* Indica la posicion actual del cursor */
extern screen_pos;

/* Buffer de prueba en reemplazo del buffer del teclado */
/* el buffer del teclado original tiene que ser una cola
 * ya que con este buffer se imprime ar revez.
 */
char test_buffer[10];
int gl=EMPTY;
/* */



/* funcion que simula una entrada del teclado */
void
test_keys()
{
	test_buffer[++gl] = 'i';
	test_buffer[++gl] = 'u';
	test_buffer[++gl] = 'q';
	test_buffer[++gl] = 'r';
	test_buffer[++gl] = 'a';
}

void
shell()
{
	/* Buffer de almacenamiento de caracteres */
	char in_buffer[MAX_CHARS];
	int last = EMPTY;

	/* contador de prueba para simulacion de entrada */
	int timer;

	clear_screen();
	welcome();


	timer = 0;
	while(1) {

		/* cada 10000 iteraciones se ingresa una palabra */
		timer++;
		if( timer%100000 == 0 ) {
			test_keys();
		}

		/* Chequeo si se almaceno algo en el buffer del teclado */
		/* mas adelante hay que implementar un getchar() para leer del
		 * buffer creado */
		refresh_in(in_buffer,&last);

	}


	return;
}
