/*
	hpc_2-c Demostracion de uso de hilos de Kernel
	Uso de HPC para paralelismo en el kernel
	Alternada
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/delay.h>

#define MAX 16
#define NumHilos 4

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL con hilos");
MODULE_INFO(driver,"PULSO CARDIACO");
MODULE_INFO(interface,"UART");
MODULE_VERSION("1.0");

static int A[MAX] = {12,45,87,38,97,-45,44,88,22,43,-5,-23,-34, -8,17,20};
static int B[MAX] = {66, 3,48,23,21,  9, 4, 8, 2,-4,-8,-20,-10,-56,88,54};
static int C[MAX];

struct task_struct *khilo[NumHilos];

static int hilo_kernel(void* datos){
	int nucleo = *(int*)datos; 
	int i= nucleo;

	printk(KERN_INFO "Init kernel thread in function");
	while(!kthread_should_stop()){
		//ssleep(1);
		schedule();
		for( ; i < MAX; i+= NumHilos){
			C[i] = A[i] * B[i];
		}
		//cpu = smp_processor_id();
		//printk(KERN_INFO "Ejecucion en CPU: %d\n",cpu);
	}
	return nucleo;
}
static int __init funcion_inicio(void){
		
	static int id_thread[NumHilos];
	register int nh = 0;
	printk(KERN_INFO "Ejemplo 1 de HPC con hilos de kernel\n");
	
	for( nh = 0; nh < NumHilos; nh++){
		id_thread[nh] = nh;
		khilo[nh] = kthread_create(hilo_kernel,(void*)(id_thread+nh),"kmi_hilo");
	
		if( IS_ERR(khilo) ){
			printk(KERN_ERR "Error en la creacion del hilo... \n");
			return PTR_ERR(khilo);
		}
		//kthread_bind(khilo,7);
		wake_up_process( khilo[nh] );
		printk( KERN_INFO "Hilo creado con pid: %d y nombre: %s\n",khilo[nh]->pid,khilo[nh]->comm ); 
	}
	return 0;
}
static void __exit funcion_final(void){
	int retorno,i;
	printk(KERN_INFO "Terminando la ejecucion del ejemplo 1 de hpc con hilos\n");
	for( i = 0;i < NumHilos; i++){
		retorno = kthread_stop(khilo[i]);
	
		if (retorno == -EINTR){
			printk(KERN_ERR "Error en la terminacion del hilo\n");
		}else{
			printk(KERN_INFO "Stop thread with value %d\n",retorno);
		}
	}
 	
	for(i = 0; i < MAX;i++)		
		printk(KERN_INFO "Elemento C[%d] = %d\n",i,C[i]);
}
module_init( funcion_inicio );
module_exit( funcion_final );
