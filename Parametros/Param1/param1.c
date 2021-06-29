/*
	param1.c Parametros de kernel
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

static int irq = 7;				//Declaracion de la variable statica
//		( Variable, tipo, permisos(Usuario/Grupo del usuario/Demas grupos)
module_param( irq, int, 0660);	//Integracion como parametro de kernel
MODULE_PARM_DESC( irq,"Numero de interrupciones");

static int __init funcion_inicio(void){
	printk(KERN_INFO "Ejemplo 1 de parametros\n");

	printk(KERN_INFO "Mi variable es:%d \n",mivar1);
	printk(KERN_INFO "Mi variable es irq :%d \n",irq);
	return 0;
}
static void __exit funcion_final(void){
	printk(KERN_INFO "Terminando la ejecucion del ejemplo 1 de parametros\n");
 	printk(KERN_INFO "Mi variable irq al terminar:%d\n",irq);
}
module_init( funcion_inicio );
module_exit( funcion_final );
