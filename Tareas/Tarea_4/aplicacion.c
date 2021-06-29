#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define N 1024

int abrirParametro( char *parametroSysfs );
void leerParametro( int fd, char *parametro, int Nbytes );
void escribirParametro( int fd, char *parametro );

int main(){
	int fdOpcion, fdPromedio, fdNumElem, fdNumElemPares, op=0;
	char Opcion[N], Promedio[N], Numeros[N],NumerosPares[N];

	fdOpcion = abrirParametro("/sys/module/Tarea_KThread_4/parameters/Opcion");

	while(op != 5){
		printf("\n\nOpciones: \n1 -> Promedio\n2 -> BubbleSort\n3 -> NumPares\n4 -> Cargar Datos\n5 -> Salir\nOpcion:  ");
		fgets(Opcion,N,stdin);
		op = atoi(Opcion);

		if ( op == 1){
			fdPromedio = abrirParametro("/sys/module/Tarea_KThread_4/parameters/Promedio");

			escribirParametro( fdOpcion, Opcion );
			leerParametro( fdPromedio, Promedio, N );

			close( fdPromedio );
		}else if ( op == 2 ){
			fdNumElem = abrirParametro("/sys/module/Tarea_KThread_4/parameters/Datos");

			escribirParametro( fdOpcion, Opcion );
			leerParametro( fdNumElem, Numeros, N );

			close( fdNumElem );
		}else if ( op == 3 ){
			fdNumElemPares = abrirParametro("/sys/module/Tarea_KThread_4/parameters/Pares");

			escribirParametro( fdOpcion, Opcion );
			leerParametro( fdNumElemPares, NumerosPares, N );

			close( fdNumElemPares );
		}else if ( op == 4 ){
			fdNumElem = abrirParametro("/sys/module/Tarea_KThread_4/parameters/Datos");
			printf("Ingrese los datos a ingresar:  ");
			fgets(Numeros,N,stdin);
			escribirParametro( fdNumElem, Numeros );

			close( fdNumElem );
		}
	}
	close( fdOpcion );

	return 0;
}
void escribirParametro( int fd, char *parametro ){
	int nbytes;

	nbytes = write( fd, parametro, strlen(parametro)+1 );
	if( nbytes == -1 ){
		perror("Error al escribir en el parametro\n");
		exit(EXIT_FAILURE);
	}
	//printf("Bytes enviados al parametro: %d\n", nbytes);
}

void leerParametro( int fd, char *parametro, int Nbytes ){
	int nbytes;

	nbytes = read( fd, parametro, Nbytes );
	if( nbytes == -1 ){
		perror("Error al leer el parametro\n");
		exit(EXIT_FAILURE);
	}
	parametro[nbytes-1] = 0;
	//printf("Bytes recibidos del parametro: %d\n", nbytes);
	printf("El valor del parametro es: %s\n", parametro);
}

int abrirParametro( char *parametroSysfs ){
	int fd;

	fd = open(parametroSysfs, O_RDWR);
	if( fd == -1 ){
		perror("Error al abrir el parametro\n");
		exit(EXIT_FAILURE);
	}
	//printf("El descriptor del parametro es: %d\n", fd);

	return fd;
}


