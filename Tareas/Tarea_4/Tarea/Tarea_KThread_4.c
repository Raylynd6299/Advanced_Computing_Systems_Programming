/*
	Tarea_KThread_4.c 
	Tarea 4: ordenamiento, promedio y numeros pares mediante Callback
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#define MAX 8

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido Bejarano");
MODULE_DESCRIPTION("Tarea 4: Modulo de kernel con funciones Callback y parametros");
MODULE_INFO(driver,"Operacion con Numeros");
MODULE_INFO(interface,"UART");
MODULE_VERSION("6.0");

static void SearchEvens(void);
static void BubbleSort(void);
static int ObtenerPromedio(void);

static int Opcion = 0;
static int Promedio = 0;
static int NumElem = MAX;
static int Datos[MAX] = {5,78,-23,97,12,-5,7,44};
static int NumElemPares = MAX;
static int Pares[MAX] = {0,0,0,0,0,0};

int set_param( const char *val, const struct kernel_param *kp ) {
	int paramArg = 0;
	int ret = -1;
	int ind = 0;

	printk(KERN_INFO "Funcion call back set_param_Opcion ejecutada...\n");

	ret = param_set_int( val, kp );
	if( ret == 0 ) {
		paramArg = *(int *)kp->arg;
		if (paramArg > 3 || paramArg < 1){
			printk(KERN_INFO "Opcion Invalida, Asignando 0 a Opcion");
			paramArg = 0;
			Opcion = 0;
		}
		printk(KERN_INFO "Parametro Opcion: %d \n", paramArg);

		switch(paramArg){
			case 1:
				//Promedio
				Promedio = ObtenerPromedio();
				printk(KERN_INFO "Promedio del Arreglo: %d\n",Promedio);
				break;
			case 2:
				//ordenar los elementos
				BubbleSort();
				printk(KERN_INFO "El arreglo ordenado es:");
				for(ind = 0; ind < NumElem ; ind++)
					printk(KERN_INFO "|%d|",Datos[ind]);
				break;
			case 3:
				//Encontrar los numeros pares del arreglo
				SearchEvens();			
				printk(KERN_INFO "Los Pares son:");	
				for(ind = 0; ind < NumElemPares ; ind++)
					printk(KERN_INFO "|%d|",Pares[ind]);
				break;
		}

	}

	return ret;
}

int get_param( char *buffer, const struct kernel_param *kp ) {
	int ret;

	printk(KERN_INFO "Funcion call back get_param_Opcion ejecutada...\n");

	ret = param_get_int( buffer, kp );
	if( ret > 0 ) {
		printk(KERN_INFO "Parametro Opcion: %s \n", buffer);

		return ret;
	}

	return -EPERM;
}

static const struct kernel_param_ops mis_param_ops = {
	.set = set_param,
	.get = get_param
};

module_param_cb( Opcion, &mis_param_ops, &Opcion, 0660 );
MODULE_PARM_DESC(Opcion,"Opcion: 1:Promedio 2:Ordenamiento 3:Numeros Pares");

module_param(Promedio,int,0660);
MODULE_PARM_DESC(Promedio,"Contiene el promedio del arreglo");

module_param_array(Datos,int,&NumElem,0660);
MODULE_PARM_DESC(Datos,"Arreglo de datos");

module_param_array(Pares,int,&NumElemPares,0660);
MODULE_PARM_DESC(Pares,"Elementos Pares de los Arreglos");


static void SearchEvens(){
	int indice,ind=0;
	for( indice = 0 ; indice < NumElem ; indice++){
		if( Datos[indice]%2 == 0 )
			Pares[ind++] = Datos[indice];
	}
	NumElemPares = ind;
}
static void BubbleSort(){
	int indice = 0,aux,i;
	for( i = 0; i < NumElem-1 ; i++){
		for( indice = 0; indice < NumElem-i-1 ; indice++ ){
			if ( Datos[indice] > Datos[indice+1] ) {
				aux = Datos[indice];
				Datos[indice] = Datos[indice+1];
				Datos[indice+1] = aux;
			}
		}
	}
}
static int ObtenerPromedio(){
	register int indice = 0;
	int acumulado = 0;
	for (indice = 0; indice < NumElem ; indice++)
		acumulado = acumulado + Datos[indice];
	return acumulado/NumElem;
}		


static int __init funcion_inicio(void){
	int ind = 0;
	printk(KERN_INFO "Tarea_4_Parametros_CallBack\n");
	printk(KERN_INFO "El Arreglo inicial es: ");
	for(ind = 0; ind < NumElem ; ind++)
		printk(KERN_INFO "|%d|",Datos[ind]);
	printk(KERN_INFO "Listo para trabajar!");
	return 0;
}
static void __exit funcion_final(void){
	printk(KERN_INFO "Terminando la ejecucion de la tarea 4 de parametros\n");
	
}
module_init( funcion_inicio );
module_exit( funcion_final );
