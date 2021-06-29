/*
	hello-3.c Macros de Informacion
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL");
MODULE_INFO(driver,"PULSO CARDIACO");
MODULE_INFO(interface,"UART");


static int __init funcion_inicio(void){
	printk(KERN_INFO "Hola mundo en el modulo 3\n");
	return 0;
}
static void __exit funcion_final(void){
	printk(KERN_INFO "Terminando la ejecucion del modulo 3\n");
}
module_init( funcion_inicio );
module_exit( funcion_final );
