/*
 *  DeviceDriverChar_2.c - Asignacion dinamica de numero mayor y numero menor en un
 *  	device driver de caracter
 */

#include <linux/module.h>			/* Necesaria para todos los modulos 	*/
#include <linux/kernel.h>			/* Necesaria para KERN_INFO 			*/
#include <linux/init.h>				/* Necesaria para las macros 			*/
#include <linux/fs.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL");							/* Tipo de licencia								*/
MODULE_AUTHOR("Raymundo Pulido Bejarano");		/* Autor del módulo 							*/
MODULE_DESCRIPTION("DeviceDriverChar");			/* Descripción de la funcionalidad del módulo 	*/
MODULE_VERSION("1.0");							/* Versión del módulo 							*/
MODULE_INFO(driver, "PULSO CARDIACO"); 			/* Información personalizada del usuario		*/

dev_t dispositivo = 0;

static int __init funcion_inicio(void){
	int ret = 0;
	printk(KERN_INFO "---------------------------------");
	printk(KERN_INFO "Iniciando el divice driver de caracter \n ");
	printk(KERN_INFO "Registrando el divice driver de caracter \n ");

	ret = alloc_chrdev_region( &dispositivo, 0, 1, "ESCOM_DDC" );
	
	if ( ret < 0){
		printk(KERN_INFO "Error al asignar el numero mayor y menor del DDC \n ");
		return ret;
	}	

	printk(KERN_INFO "Dispositivo registrado exitosamente \n ");
	printk(KERN_INFO "Numero mayor asignado: %d \n ",MAJOR(dispositivo));
	printk(KERN_INFO "Numero menor asignado: %d \n ",MINOR(dispositivo));
 
	return 0;
}

static void __exit funcion_exit(void){
	
	printk(KERN_INFO "Terminando la ejecucion del modulo 4\n");
	unregister_chrdev_region(dispositivo,1);
}

module_init(funcion_inicio);
module_exit(funcion_exit);
