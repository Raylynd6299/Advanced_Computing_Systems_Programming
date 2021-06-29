#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

void configGPIO( volatile uint32_t *gpio_virtual, int gpio, int modo );
void valueGPIO( volatile uint32_t *gpio_virtual, int gpio, int valor );


int main( ){
	int fd ;
    volatile uint32_t *gpio;
	/* Se obtiene un manejador a la memoria física
	 * /dev/mem es un device driver de caracter que contiene una imagen de la
	 * memoria principal de la computadora.
	 *
     	 * Los Bytes de direcciones en /dev/mem son interpretados como direcciones de
	 * la memoria física.
	 * O_RDWR - Bandera para lectura y escritura
	 * O_SYNC - Bandera para sincronia. El archivo es abierto para acceso de I/O sincrono
	 * Cualquier escritura en el despriptor de archivo bloqueara la llamada a proceso hasta
	 * que el dato se haya escrito fisicamente.
	 */

	fd = open ("/dev/mem", O_RDWR | O_SYNC);
	if( fd == -1 ){
		printf("Error al abrir /dev/mem %s \n", strerror(errno) );
		exit( EXIT_FAILURE );
  	}

	//Se obtiene una pagina de memoria en el espacio de direcciones virtuales
	//a partir del offset 0x3f200000. En este offset se encuentran
	//mapeados los perifericos. Consultar en el FHS en /proc/interrupts
	//El primer parametro indica que la Direccion de inicio del mapa es cero
	//El segundo parametro es el número de bytes a mapear
	//El tercer parametro indica que la pagina puede ser de lectura y escritura
	//El cuarto parametro indica que las modificaciones al mapa seran visibles a otros procesos
	//El quinto parametro es el manejador de la memoria fisica
	//El sexto parametro es la dirección de inicio del segmento 
        gpio = (uint32_t *)mmap(0, getpagesize(), PROT_READ | PROT_WRITE,
				MAP_SHARED, fd, 0x3f200000);

        if (gpio == MAP_FAILED){
                printf("Error al obtener direcion virtual: %s\n", strerror(errno));
                return -1;
        }
        printf("La direccion virtual es: %x\n", gpio);
        configGPIO( gpio, 16, 0 );

        for(int i = 0; i < 5; i++){
                //Se pone en uno el GPIO 16
                //*(gpio + 7) = *(gpio + 7) | (1 << 16);
                valueGPIO(gpio, 16, 1);
                sleep(1);
                //Se pone en cero el GPIO 16
                //*(gpio + 10) = *(gpio + 10) | (1 << 16);
                valueGPIO(gpio, 16, 0);
                sleep(1);
        }
	return 0;
}

/*  asignar valor de salida
 *  gpio_virtual: Direccion virtual
 *  gpio: Numero de gpio 
 *  valor: 0, 1
 */
void valueGPIO( volatile uint32_t *gpio_virtual, int gpio, int valor ){
    int GPSET_CLR = ( valor == 0 ) ? ( gpio/32 ) +  10 : ( gpio/32 ) + 7 ;  // CLR = 10 offset, SET = 7 offset

    *( gpio_virtual + GPSET_CLR ) = *( gpio_virtual + GPSET_CLR ) | ( 1 << (gpio%32) );
}

/*  Configuracion entrada o salida
 *  gpio_virtual: Direccion virtual
 *  gpio: Numero de gpio 
 *  modo: 0-Salida, 1-Entrada
 */
void configGPIO( volatile uint32_t *gpio_virtual, int gpio, int modo ){

    int GPFSEL = gpio / 10;
    int bitRango = (gpio % 10) * 3;

    *(gpio_virtual + GPFSEL ) = ( *( gpio_virtual + GPFSEL ) & ~(7 << bitRango) ) | ( ((modo == 0) ? 1: 0) << bitRango ) ;
}