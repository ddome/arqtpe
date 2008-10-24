#ifndef VIDEO_H
#define VIDEO_H

/* Atributo de video. Letras blancas, fondo negro */
#define WHITE_TXT 0x07

/* Tiempo de espera */
void wait(int time);

/* Funcion general para escribir en pantalla */
int writeWrapper(const void * buff, int size);

/* Limpia la pantalla */
void clear_screen();

/* Funcion simple que escribe un caracter */
void putchar(char c);

/* Imprime un mensaje de bienvenida */
void welcome();

#endif
