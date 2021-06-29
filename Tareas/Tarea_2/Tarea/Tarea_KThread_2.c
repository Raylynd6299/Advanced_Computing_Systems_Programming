/*
	Tarea_KThread_2.c 
	Tarea 2: letra, Cadena, Opcion, resultado
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido Bejarano");
MODULE_DESCRIPTION("Tarea 2: Modulo de kernel con hilos y parametros");
MODULE_INFO(driver,"Pulso cardiaco");
MODULE_INFO(interface,"UART");
MODULE_VERSION("1.0");

static int Opcion = 0;
module_param(Opcion,int,0660);
MODULE_PARM_DESC(Opcion,"Opcion: 1:Contar ocurrencias de letra 2:Ordenamiento 3:Numeros Pares");

static int longitud = 0;
module_param(longitud,int,0660);
MODULE_PARM_DESC(Resultado,"Contiene el promedio del arreglo");

static char* letra = "a";
module_param(letra,charp,0660);
MODULE_PARM_DESC(letra,"letra a comprobar ocurrencias");

static char* cadena = "esta es la optativa de advanced computing systems programming";
module_param(cadena,charp,0660);
MODULE_PARM_DESC(cadena,"Cadena en la que buscar ocurrencias");

struct task_struct *khilo;

static int BuscarLetrasCadena(void);
static int LongitudCad(char*);

static int hilo_kernel(void* ident){
	int id = *(int*)ident;
	printk(KERN_INFO "Iniciando hilo de Kernel");
	while(!kthread_should_stop()){	
		schedule();
		//ssleep(1);
		if ( Opcion == 1){
			 
			longitud = BuscarLetrasCadena();
			printk(KERN_INFO "La letra %c se repite %d, en: %s\n",*letra,longitud,cadena);

			Opcion = 0;

		}else if( Opcion == 2){
				
			longitud = LongitudCad(cadena)-1;
			printk(KERN_INFO "Longitud de la cadena es: %d",longitud);
		
			Opcion = 0;
		}
	}
	return id;
}
static int BuscarLetrasCadena(void){
	register int indice = 0;
	int acumulado = 0;
	for (indice = 0; indice < LongitudCad(cadena) ; indice++)
		if ( cadena[indice] == letra[0] )
			acumulado++;
	return acumulado;
}		

static int LongitudCad(char *cadena){
	int len = 0;
	while( cadena[len] != '\0' )
		len++;

	return len;
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
