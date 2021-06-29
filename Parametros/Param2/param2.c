/*
	param2.c Parametros de kernel
	Para modificar los parametros de kernel escribir el valor en el archivo
	/sys/module/<Nombre_Modulo>/parameters/<Nombre_Parametro>
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymundo Pulido");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL");
MODULE_INFO(driver,"PULSO CARDIACO");
MODULE_INFO(interface,"UART");
MODULE_VERSION("1.0");

static int mivar1 __initdata = 10;
//Declaracion de la variable statica
static char* comando = "derecha";			
//		( Variable, tipo, permisos(Usuario/Grupo del usuario/Demas grupos)
//Integracion como parametro de kernel
module_param( comando, charp, 0660);
MODULE_PARM_DESC( comando,"Comando a ejecutar por el modulo");

static int __init funcion_inicio(void){
	printk(KERN_INFO "Ejemplo 2 de parametros\n");

	printk(KERN_INFO "Mi variable es:%d \n",mivar1);
	printk(KERN_INFO "Mi comando es irq :%s \n",comando);
	return 0;
}
static void __exit funcion_final(void){
	printk(KERN_INFO "Terminando la ejecucion del ejemplo 2 de parametros\n");
 	printk(KERN_INFO "Mi variable comando al terminar: %s \n",comando);
}
module_init( funcion_inicio );
module_exit( funcion_final );
