#include <stdio.h>
#include "entrada.h"

int teclado(void){ //Lectura del teclado. El usuario puede ingresar un caracter
	int rta=getchar(); //Devuelve el primer caracter colocado
			//Entonces, ignora los demas caracteres, hasta terminar la linea (con un Enter):
	if (rta!='\n'){ //Si no se ingreso un enter como primer caracter
		while(getchar()!='\n'){} //Se vacia el buffer al tomar los demas caracteres hasta acabar la linea
	}

	return rta;
}

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