/*
 *  param-3.c - Demostracion de parametros en el modulo de kernel
 *  se usa un parametro entero (int), una cadena (charp) y un arreglo(int)
 */
#include <linux/module.h>	/* Necesaria para todos los modulos 		*/
#include <linux/kernel.h>	/* Necesaria para KERN_INFO 			*/
#include <linux/init.h>		/* Necesaria para las macros de documentacion	*/
#include <linux/moduleparam.h>	/* Necesaria para las macros de parametros 	*/
#define MAX 5

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VICTOR HUGO GARCIA ORTEGA");
MODULE_DESCRIPTION("ESTE ES UN EJEMPLO DE MODULO DE KERNEL");
MODULE_VERSION("4.0");
MODULE_INFO(driver, "PULSO CARDIACO");
MODULE_INFO(interfaz, "UART");

static int irq = 10;
module_param( irq, int, 0660 );
MODULE_PARM_DESC( irq, "Número de interrupción" );

static char *comando = "derecha";
module_param( comando, charp, 0660 );
MODULE_PARM_DESC( comando, "Comando del motor" );

static int datos[MAX] = {1, 2, 3, 4, 5};
static int numEle = MAX;
module_param_array( datos, int, &numEle, 0660 );
MODULE_PARM_DESC( datos, "Muestras" );

static int __init funcion_inicio(void)
{
	register int i;

	printk(KERN_INFO "Iniciando el ejemplo 3 de parametros\n");
	printk(KERN_INFO "La irq en la funcion inicio es: %d \n", irq);
	printk(KERN_INFO "El comando en la funcion inicio es: %s \n", comando);
	printk(KERN_INFO "Numero de elementos en la funcion de inicio: %d \n", numEle);
	for( i = 0; i < numEle; i++ )
	{
		printk(KERN_INFO "Datos[%d] = %d \n", i, datos[i]);
	}
	/*
	 * Un valor de retorno diferente de 0 significa que
	 * init_module fallo; el modulo no se puede cargar
	 */
	return 0;
}

static void __exit funcion_exit(void)
{
	register int i;

	printk(KERN_INFO "Terminando la ejecucion del ejemplo 3 de parametros\n");
	printk(KERN_INFO "La irq en la funcion exit es: %d \n", irq);
	printk(KERN_INFO "El comando en la funcion exit es: %s \n", comando);
	printk(KERN_INFO "Numero de elementos en la funcion de salida: %d \n", numEle);
	for( i = 0; i < numEle; i++ )
	{
		printk(KERN_INFO "Datos[%d] = %d \n", i, datos[i]);
	}
}

module_init( funcion_inicio );
module_exit( funcion_exit );
