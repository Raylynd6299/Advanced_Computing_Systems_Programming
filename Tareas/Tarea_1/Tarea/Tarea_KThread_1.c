/*
	Tarea_KThread_1.c 
	Tarea 1: ordenamiento, promedio y numeros pares
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/delay.h>

#define TAM 8

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido Bejarano");
MODULE_DESCRIPTION("Tarea 1: Modulo de kernel con hilos y parametros");
MODULE_INFO(driver,"Pulso cardiaco");
MODULE_INFO(interface,"UART");
MODULE_VERSION("1.0");

static int Opcion = 0;
module_param(Opcion,int,0660);
MODULE_PARM_DESC(Opcion,"Opcion: 1:Promedio 2:Ordenamiento 3:Numeros Pares");

static int Promedio = 0;
module_param(Promedio,int,0660);
MODULE_PARM_DESC(Promedio,"Contiene el promedio del arreglo");

static int NumElem = TAM;
static int Numeros[TAM] = {5,78,-23,97,12,-5,7,44};
module_param_array(Numeros,int,&NumElem,0660);
MODULE_PARM_DESC(Numeros,"Arreglo de datos");

static int NumElemPares = TAM;
static int NumerosPares[TAM] = {0,0,0,0,0,0};
module_param_array(NumerosPares,int,&NumElemPares,0660);
MODULE_PARM_DESC(NumerosPares,"Elementos Pares de los Arreglos");

struct task_struct *khilo;

static void SearchEvens(void);
static void BubbleSort(void);
static int ObtenerPromedio(void);

static int hilo_kernel(void* ident){
	int id = *(int*)ident,ind;
	printk(KERN_INFO "Iniciando hilo de Kernel");
	while(!kthread_should_stop()){	
		schedule();
		if ( Opcion == 1){
			//Promedio
			Promedio = ObtenerPromedio();
			printk(KERN_INFO "Promedio del Arreglo: %d\n",Promedio);
			Opcion = 0;
		}else if( Opcion == 2){
			//ordenar los elementos
			BubbleSort();
			printk(KERN_INFO "El arreglo ordenado es:");
			for(ind = 0; ind < NumElem ; ind++)
				printk(KERN_INFO "|%d|",Numeros[ind]);
			Opcion = 0;
		}else if( Opcion == 3){
			//Encontrar los numeros pares del arreglo
			SearchEvens();			
			printk(KERN_INFO "Los Pares son:");	
			for(ind = 0; ind < NumElemPares ; ind++)
				printk(KERN_INFO "|%d|",NumerosPares[ind]);
			Opcion = 0;
		}
	}
	return id;
}
static void SearchEvens(){
	int indice,ind=0;
	for( indice = 0 ; indice < NumElem ; indice++){
		if( Numeros[indice]%2 == 0 )
			NumerosPares[ind++] = Numeros[indice];
	}
	NumElemPares = ind;
}
static void BubbleSort(){
	int indice = 0,aux,i;
	for( i = 0; i < NumElem-1 ; i++){
		for( indice = 0; indice < NumElem-i-1 ; indice++ ){
			if ( Numeros[indice] > Numeros[indice+1] ) {
				aux = Numeros[indice];
				Numeros[indice] = Numeros[indice+1];
				Numeros[indice+1] = aux;
			}
		}
	}
}
static int ObtenerPromedio(){
	register int indice = 0;
	int acumulado = 0;
	for (indice = 0; indice < NumElem ; indice++)
		acumulado = acumulado + Numeros[indice];
	return acumulado/NumElem;
}		


static int __init funcion_inicio(void){
	static int id_thread = 10;
	printk(KERN_INFO "Tarea_1_Parametros\n");
		
	khilo = kthread_run(hilo_kernel,(void*)&id_thread,"k_Tarea_1");
	
	if( IS_ERR(khilo) ){
		printk(KERN_ERR "Error en la creacion del hilo... \n");
		return PTR_ERR(khilo);
	}
	
	printk( KERN_INFO "Hilo creado con pid: %d y nombre: %s\n",khilo->pid,khilo->comm ); 
	return 0;
}
static void __exit funcion_final(void){
	int retorno;
	printk(KERN_INFO "Terminando la ejecucion de la tarea 1 de parametros\n");
	retorno = kthread_stop(khilo);
	if (retorno == -EINTR){
		printk(KERN_ERR "Error en la terminacion del hilo\n");
	}else{
		printk(KERN_INFO "Hilo retorno: %d\n",retorno);
	}
}
module_init( funcion_inicio );
module_exit( funcion_final );
