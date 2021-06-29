#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define N 1024

int main(){
	char irq[N];
	int nbytes;
	int fd = open("/sys/module/param3/parameters/irq",O_RDWR);
	if(fd == -1){
		perror("Error al abrir el parametro");
		exit(EXIT_FAILURE);
	}
	printf("El descriptor de archivo es: %d\n",fd);
	nbytes = read( fd, irq,N);	
	if(nbytes == -1){
		perror("Error al abrir el parametro");
	    exit(EXIT_FAILURE);
	}
	irq[nbytes-1] = '\0';
	printf("Bytes recibidos del parametros %d\n", nbytes);
	printf("El valor del parametro es: %s\n",irq);
	strcpy(irq,"5");
	nbytes = write(fd,irq,strlen(irq)+1);	
	if(nbytes == -1){
		perror("Error al abrir el parametro");
        exit(EXIT_FAILURE);
	}
	printf("Bytes enviados al parametro %d\n",nbytes);
	close(fd);
	return 0;
}
