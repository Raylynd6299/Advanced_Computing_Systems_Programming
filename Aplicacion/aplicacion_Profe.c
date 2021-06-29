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
	int fdIrq, fdComando, fdDatos;
	char irq[N], comando[N], datos[N];

	fdIrq 	  = abrirParametro("/sys/module/param3/parameters/irq"	   );
	fdComando = abrirParametro("/sys/module/param3/parameters/comando");
	fdDatos   = abrirParametro("/sys/module/param3/parameters/datos"  );

	leerParametro( fdIrq	, irq	 , N );
	leerParametro( fdComando, comando, N );
	leerParametro( fdDatos	, datos	 , N );

	strcpy( irq, "7" );
	escribirParametro( fdIrq, irq );
	strcpy( comando, "atras" );
	escribirParametro( fdComando, comando );
	strcpy( datos, "6,7,8,9" );
	escribirParametro( fdDatos, datos );

	close( fdIrq );
	close( fdComando );
	close( fdDatos );

	return 0;
}
void escribirParametro( int fd, char *parametro ){
	int nbytes;

	nbytes = write( fd, parametro, strlen(parametro)+1 );
	if( nbytes == -1 ){
		perror("Error al escribir en el parametro\n");
		exit(EXIT_FAILURE);
	}
	printf("Bytes enviados al parametro: %d\n", nbytes);
}

void leerParametro( int fd, char *parametro, int Nbytes ){
	int nbytes;

	nbytes = read( fd, parametro, Nbytes );
	if( nbytes == -1 ){
		perror("Error al leer el parametro\n");
		exit(EXIT_FAILURE);
	}
	parametro[nbytes-1] = 0;
	printf("Bytes recibidos del parametro: %d\n", nbytes);
	printf("El valor del parametro es: %s\n", parametro);
}

int abrirParametro( char *parametroSysfs ){
	int fd;

	fd = open(parametroSysfs, O_RDWR);
	if( fd == -1 ){
		perror("Error al abrir el parametro\n");
		exit(EXIT_FAILURE);
	}
	printf("El descriptor del parametro es: %d\n", fd);

	return fd;
}


