/*
	hello-2.c Demosttracion de las macros module_init() y module_exit().
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int __init funcion_inicio(void){
	printk(KERN_INFO "Hola mundo en el modulo 2\n");
	return 0;
}
static void __exit funcion_final(void){
	printk(KERN_INFO "Terminando la ejecucion del modulo 2\n");
}
module_init( funcion_inicio );
module_exit( funcion_final );
