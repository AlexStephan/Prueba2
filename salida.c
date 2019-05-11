#include <stdio.h>
#include "salida.h"

void bienvenida(void){ //Da la bienvenida al usuario...

	printf("\nBienvenido al Juego de la Vida.\n");
	printf("\nEn este programa, usted puede ingresar la configuración inicial del mundo.\n");
	printf("\nEl mundo cuenta con %d filas y %d columnas.\n\n",FILAS,COLUMNAS);

	help(); //... y le informa las opciones disponibles

}

void help(void){ //Informa las opciones disponibles
	printf("Opciones:\n");
	printf("I + ENTER	[Inicialización]: Ingresa la configuración inicial del mundo\n");
	printf("ENTER (sólo)	[Siguiente]: Avanza a la próxima generación\n");
	printf("Q + ENTER	[Quit]: Sale del programa\n");
	printf("H + ENTER	[Help]: Vuelve a mostrar las opciones\n");
	printf("B + ENTER	[Bunny]: Muestra un conejito\n\n");
}

void display(int Matriz[FILAS+2][COLUMNAS+2], unsigned int time){ //Imprime en pantalla la configuracion actual del mundo
	int i; //Fila actual
	int j; //Columna actual

	printf("Generación %u\n",time); //Informa el nùmero de generación actual
	for (i=1;i<=FILAS;i++){ //Por cada fila...
		for (j=1;j<=COLUMNAS;j++){ //Por cada columna...
			if (Matriz[i][j]==VIVA){ //..si encuentra una celula viva...
				printf("|O"); //...coloca una "O" (un círculo que simboliza la celula)
			} else {	//De lo contrario...
				printf("| "); //...oloca un espacio vacío
			}
		}
		printf("|\n"); // (borde derecho de la matriz)
	}
	return;

}
