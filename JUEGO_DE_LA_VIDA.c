#include <stdio.h>

#define COLUMNAS 9	//Cantidad de columnas activas del mundo
#define FILAS 9	//Cantidad de filas activas del mundo

//Lògica Booleana
#define FALSO 0
#define VERDAD 1

//Posibles estados para las celulas
#define MUERTA 0
#define VIVA 1

void bienvenida(void); //Imprime el mensaje de bienvenida al programa
void help(void); //Indica las teclas asignadas a las opciones disponibles (salir, inicializar, etc)
void clean (int Matriz[FILAS+2][COLUMNAS+2] ); //Limpia la matriz del mundo

int teclado (void); //Recibe un caracter del teclado

void inicializacion(int Matriz[FILAS+2][COLUMNAS+2] ); //Permite el ingreso de las condiciones iniciales de mundo

void evolution(int Matriz[FILAS+2][COLUMNAS+2], int Next[FILAS+2][COLUMNAS+2]); //Evalua el estado de la siguiente generacion, colocando...
										//... el resultado en la matriz auxiliar Next
int vecinos (int y, int x, int Matriz[FILAS+2][COLUMNAS+2] ); //Cuenta la cantidad de celulas vivas que rodean a una determinada posicion
void replace (int Matriz[FILAS+2][COLUMNAS+2], int Next[FILAS+2][COLUMNAS+2]);//Reemplaza el contenido del mundo por el de la matriz Next

void display(int Matriz[FILAS+2][COLUMNAS+2] ,unsigned int time);//Muestra en pantalla la configuracion actual del mundo


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

void bienvenida(void){ //Da la bienvenida al usuario...

	printf("\nBienvenido al Juego de la Vida.\n");
	printf("\nEn este programa, usted puede ingresar la configuración inicial del mundo.\n");
	printf("\nEl mundo cuenta con %d filas y %d columnas.\n\n",FILAS,COLUMNAS);

	help(); //... y le informa las opciones disponibles

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void help(void){ //Informa las opciones disponibles
	printf("Opciones:\n");
	printf("I + ENTER	[Inicialización]: Ingresa la configuración inicial del mundo\n");
	printf("ENTER (sólo)	[Siguiente]: Avanza a la próxima generación\n");
	printf("Q + ENTER	[Quit]: Sale del programa\n");
	printf("H + ENTER	[Help]: Vuelve a mostrar las opciones\n");
	printf("B + ENTER	[Bunny]: Muestra un conejito\n\n");
}

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


int teclado(void){ //Lectura del teclado. El usuario puede ingresar un caracter
	int rta=getchar(); //Devuelve el primer caracter colocado
			//Entonces, ignora los demas caracteres, hasta terminar la linea (con un Enter):
	if (rta!='\n'){ //Si no se ingreso un enter como primer caracter
		while(getchar()!='\n'){} //Se vacia el buffer al tomar los demas caracteres hasta acabar la linea
	}

	return rta;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void inicializacion(int Matriz[FILAS+2][COLUMNAS+2]){ //Permite al usuario definir la configuracion inicial del mundo
	int i;	//Fila actual
	int j;	//Columna actual
	int enter;	//Indica si se oprimió ENTER en la fila actual
	int c;	//Caracter ingresado por teclado
	int repetir; //debe ingresarse la fila nuevamente?

	printf("Ingrese el estado de las células por cada fila.\n");
	printf("0 = célula muerta\n");
	printf("1 = célula viva\n");
	printf("Los espacios serán ignorados. Ningún otro caracter es válido.\n");
	printf("Si no definió todas las células de la fila, las restantes se considerarán muertas.\n");
	printf("Si definió celulas en exceso, las sobrantes serán ignoradas\n\n");
	printf("El mundo cuenta con %d filas y %d columnas.\n\n",FILAS,COLUMNAS);

	i=0;	//Inicializa fila 0 con celulas muertas
	for(j=0;j<=COLUMNAS+1;j++){
		Matriz[i][j]=0;
	}

	i=FILAS+1;	//Inicializa ultima fila con celulas muertas
	for(j=0;j<=COLUMNAS+1;j++){
		Matriz[i][j]=0;
	}



	for (i=1; i<=FILAS ; i++){ //Avanza fila por fila, colocando las celulas ingresadas por teclado
		repetir=FALSO;

		printf("Ingrese Fila %2i: ",i);
		
		Matriz[i][0] = MUERTA;	//La columna 0 y la ultima tendran celulas muertas que no se actualizaran
		Matriz[i][COLUMNAS+1] = MUERTA;
		
		for (j=1, enter=FALSO ; j<=COLUMNAS && repetir==FALSO ; j++){ //Realiza el barrido de la fila actual
			if(enter==VERDAD){ //Si habia oprimido enter, las celulas posiciones restantes se completan con celulas muertas
				Matriz[i][j]=MUERTA;
				continue;
			}
			
			switch (c=getchar()){ //Lee un caracter ingresado
				case '\n': //si encontró un ENTER con anterioridad...
					enter=VERDAD;
					Matriz[i][j]=MUERTA; //...la celula actual, y las siguientes, estaran muertas
					break;
				case ' ':	//si encontro un espacio
					j--;	//debe repetirse la lectura para esta columna (el espacio es por lo tanto ignorado)
					break;
				case '0':	//0 = La celula ingresada esta muerta
					Matriz[i][j]=MUERTA;
					break;
				case '1':	//1 = La celula ingresada esta viva
					Matriz[i][j]=VIVA;
					break;
				default:	//Se ingreso un caracter invalido
					printf("Se ingresó un caracter inválido. Repita la fila.\n\n");
					i--;	//Debe repetirse la fila actual
					repetir = VERDAD;
					break;


			}


		}

		while (enter==FALSO){ //extrae del Buffer todos los caracteres ingresados hasta el Enter
			if ((c=getchar())=='\n'){
				enter = VERDAD;
			}
		}

	}
	printf("\n");
	return;
}

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
