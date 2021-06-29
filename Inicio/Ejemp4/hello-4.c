/*
	hello-4.c Macro __initdata
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL");
MODULE_INFO(driver,"PULSO CARDIACO");
MODULE_INFO(interface,"UART");
MODULE_VERSION("1.0");

static int mivar1 __initdata = 10;

static int __init funcion_inicio(void){
	printk(KERN_INFO "Hola mundo en el modulo 4\n");
	printk(KERN_INFO "Mi variable es:%d \n",mivar1);
	return 0;
}
static void __exit funcion_final(void){
	printk(KERN_INFO "Terminando la ejecucion del modulo 4\n");
}
module_init( funcion_inicio );
module_exit( funcion_final );
