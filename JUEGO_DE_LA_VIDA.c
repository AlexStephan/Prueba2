#include <stdio.h>
#include "general.h"
#include "entrada.h"


void clean (int Matriz[FILAS+2][COLUMNAS+2] ); //Limpia la matriz del mundo

void evolution(int Matriz[FILAS+2][COLUMNAS+2], int Next[FILAS+2][COLUMNAS+2]); //Evalua el estado de la siguiente generacion, colocando...
										//... el resultado en la matriz auxiliar Next
int vecinos (int y, int x, int Matriz[FILAS+2][COLUMNAS+2] ); //Cuenta la cantidad de celulas vivas que rodean a una determinada posicion
void replace (int Matriz[FILAS+2][COLUMNAS+2], int Next[FILAS+2][COLUMNAS+2]);//Reemplaza el contenido del mundo por el de la matriz Next


/* ACLARACION:
	La matriz del mundo tiene como tamaño (columnas+2)*(filas+2).
Las 2 filas y columnas extra tienen la funcion de funcionar como bordes del mundo. Al permanecer siempre "vacias"
(con celulas muertas), facilitan desarrollar el codigo que testea los casilleros vecinos de cada celula (estos bordes
no son actualizados, y para toda celula actualizada, los 8 casilleros vecinos se encuentran DENTRO de la matriz).
	La ventaja ya mencionada es la mayor simpleza del codigo. La evidente desventaja es el hecho de que hay varias
posiciones de memoria (mas especificamente, dentro del Stack) que no son eficazmente utilizadas, en terminos de espacio.
	El grupo decidio que, para este trabajo, las ventajas eran mas significativas que los sacrificios.

	Siguiendo esta lógica, y para una mejor correspondencia entre la matriz del mundo y la auxiliar (Next), esta
ultima tiene la misma cantidad de filas y columnas
*/ 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int main(void){

	int Matriz[FILAS+2][COLUMNAS+2]; //Matriz del mundo
	int Next[FILAS+2][COLUMNAS+2]; //Matriz auxiliar, donde se indica el estado del mundo para la proxima generacion
	unsigned int time=0; //generaciones transcurridas desde el inicio
	int exit=FALSO; //indica si el usuario deseo salir del programa
	int key; //indica la tecla ingresada por el usuario
	int read_again; //indica que se debe volver a leer el teclado antes de imprimir nuevamente la configuracion actual

	bienvenida(); //da la bienvenida al usuario
	clean(Matriz); //limpia el mundo

	while(exit==FALSO){ //mientras el usuario no quiera salir del programa, este ciclo se repite indefinidamente
		display(Matriz,time); //Primero, se imprime en pantalla la configuracion actual del mundo
		do{
			read_again=FALSO; //Se setea en falso la re-lectura del teclado
			key=teclado(); //Espera hasta que el usuario ingrese un caracter
			switch(key){
				case 'I': case 'i': //Si oprimio I...
					inicializacion(Matriz);//... el usuario desea definir el estado inicial del mundo
					time=0; //Se reinicia el contador de generaciones
					break;
				case '\n': //Si oprimio enter...
					evolution(Matriz,Next); //...se evalua la configuracion de las celulas para la generacion proxima
					replace(Matriz,Next); //Dicha configuracion reemplaza a la actual
					time++; //El contador de generaciones es incrementado
					break;
				case 'H': case 'h': //Si oprimio H...
					help(); //...vuelve a mostrar cuales son las opciones disponibles
					read_again=VERDAD;//Como no hubo ningun avance en el mundo, el teclado sera re-leido
					break;
				case 'B': case 'b': //Si oprimio B...
					printf("\n\n\t  (\\(\\\n\t (=\'.\')\n\t0(_\")\")\n\n"); //Imprime el conejo
					read_again=VERDAD;//Como no hubo ningun avance en el mundo, el teclado sera re-leido
					break;
				case 'Q': case 'q': //Si oprimio Q...
					exit=VERDAD; //... el usuario desea salir del programa
					break;
				default: //Si se ingreso otro caracter...
					printf("Caracter no válido\n"); //Notifica que el caracter no es valido
					read_again=VERDAD; //Se lee nuevamente el teclado
					break;
			}
		}while(read_again==VERDAD); //La lectura se repite cuando sea necesario
	}

	return 0; //Fin del programa

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clean (int Matriz[FILAS+2][COLUMNAS+2] ){ //Limpia la matriz del mundo
	int i; //fila actual
	int j; //columna actual

	for (i=0;i<FILAS+2;i++){ // "Por cada fila ..."
		for (j=0;j<COLUMNAS+2;j++){ // "Por cada columna ..."
			Matriz[i][j]=MUERTA; // "...coloca un '0' (celula muerta)"
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void evolution(int Matriz[FILAS+2][COLUMNAS+2], int Next[FILAS+2][COLUMNAS+2]){ //Evalua la configuracion de la proxima generacion
	int i; //fila actual
	int j; //columna actual
	int n; //vecinos vivos de la celula actual

	for (i=1; i<=FILAS; i++){ //Por cada fila...
		for (j=1; j<=COLUMNAS; j++){ // Por cada columna...

			n = vecinos (i,j,Matriz); //... calcula cauntas celulas vivas rodean la posicion actual

			if( Matriz[i][j] == VIVA){ //Si la celula analizada esta viva...

				if(n==2 || n==3){	//Entonces sobrevive solo si sus "vecinos" son 2 o 3
					Next[i][j] = VIVA;
				}else{	// n<2 || n>3
					Next[i][j] = MUERTA;
				}


			}else{ //Matriz[i][j] == MUERTA  	//Si la celula analizada esta muerta...

				if(n==3){		//Entonces cobra vida únicamente si tiene 3 vecinos vivos
					Next[i][j] = VIVA;
				}else{ // n!=3
					Next[i][j] = MUERTA;
				}				

			}
		}
	}

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int vecinos (int y, int x, int Matriz[FILAS+2][COLUMNAS+2] ){//Calcula cuantas celulas vivas rodean una posicion del mundo
	int rta=0; //Define la respuesta
	int i; //Fila actual
	int j; //Columna actial

	for(i=y-1;i<=y+1;i++){ //Desde la fila anterior hasta la siguiente...
		for(j=x-1;j<=x+1;j++){ //Desde la columna anterior hasta la siguiente...
			if (Matriz[i][j]==VIVA){ //.. si encuentra una celula viva...
				rta++; //... incrementa el contador
			}
		}
	}
	//Sin embargo, el programa barrio tambien la celda que se halla en el medio, la cual no debìa contarse

	if (Matriz[y][x]==VIVA){ //Por lo tanto, si habia una celula viva...
		rta--; //...disminuye el contador, corrigiendolo
	}

	return rta; //Devuelve el resultado

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void replace (int Matriz[FILAS+2][COLUMNAS+2], int Next[FILAS+2][COLUMNAS+2]){//Actualiza el Mundo, con el contenido de la matriz auxiliar
	int i; //Fila actual
	int j; //Columna actual

	for (i=1;i<=FILAS;i++){ //Por cada fila...
		for(j=1;j<=COLUMNAS;j++){ //Por cada columna...
			Matriz[i][j] = Next [i][j]; //Transfiere el contenido de Next al mundo
		}
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

