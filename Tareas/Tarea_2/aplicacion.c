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
	int fdOpcion, fdCadena, fdletra, fdResultado, op=0;
	char Opcion[N], Cadena[N], letra[4],Resultado[N];

	fdOpcion = abrirParametro("/sys/module/Tarea_KThread_2/parameters/Opcion");

	while(op != 4){
		printf("Opciones: \n1 -> Numero de letras repetidas\n2 -> Longitud de Cadena\n3 -> Cargar Cadena\n4 -> Salir\nOpcion:  ");
		fgets(Opcion,N,stdin);
		op = atoi(Opcion);

		if ( op == 1){

			fdCadena = abrirParametro("/sys/module/Tarea_KThread_2/parameters/cadena");
			fdResultado = abrirParametro("/sys/module/Tarea_KThread_2/parameters/longitud");
			fdletra = abrirParametro("/sys/module/Tarea_KThread_2/parameters/letra");
			
			printf("Ingresa al letra: ");
			fgets(letra,4,stdin);			
				
			escribirParametro( fdletra, letra );
			escribirParametro( fdOpcion, Opcion );	
			leerParametro( fdCadena, Cadena, N );
			leerParametro( fdResultado, Resultado, N );
				
			printf("\nEn la Cadena: '%s', hay %s letras %s\n",Cadena,Resultado,letra);			

			close( fdResultado );
			close( fdletra );
			op = 0;

		}else if ( op == 2 ){

			fdCadena = abrirParametro("/sys/module/Tarea_KThread_2/parameters/cadena");
			fdResultado = abrirParametro("/sys/module/Tarea_KThread_2/parameters/longitud");

			escribirParametro( fdOpcion, Opcion );
			leerParametro( fdCadena, Cadena, N );
			leerParametro( fdResultado, Resultado, N );

			printf("\nLa longitud de la cadena '%s', es %s \n\n",Cadena, Resultado);

			close( fdResultado );

		}else if ( op == 3 ){

			fdCadena = abrirParametro("/sys/module/Tarea_KThread_2/parameters/cadena");
			printf("Ingrese la cadena que guste trabajar: ");
			fgets(Cadena,N,stdin);	
			
			escribirParametro( fdCadena, Cadena );
			
			close ( fdCadena );

		}
	}
	close( fdOpcion );

	return 0;
}
void escribirParametro( int fd, char *parametro ){
	int nbytes = 0;
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
	parametro[nbytes-1] = '\0';
	//printf("Bytes recibidos del parametro: %d\n", nbytes);
	//printf("El valor del parametro es: %s\n", parametro);
	
	nbytes = 0;
	while(parametro[nbytes] != '\0'){
		if(parametro[nbytes] == '\n'){
			parametro[nbytes] = '\0';
		}
		
		nbytes++;
	}
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


