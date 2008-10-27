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

/* Funcion simple que lee el caracter de la siguiente fila de la pantalla */
int getNLChar();

/* Imprime un mensaje de bienvenida */
void welcome();

/* Imprime un string */
void printf(char *string);

/* Levanta una linea a buffer desde el teclado */
void getline(char *buffer);

void prompt(void);

/* Imprime un string hasta llegar a un \n */
void printLine(char *line);

#endif
