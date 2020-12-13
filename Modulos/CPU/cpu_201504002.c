#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/sysinfo.h>
#include <linux/fs.h> 
#include <linux/init.h> 
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>
#include <linux/syscalls.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Inti Samayoa");
MODULE_DESCRIPTION("201504002");

static int __init inicio(void) {
 printk(KERN_INFO "Inti\n");
 return 0;
}
static void __exit salida(void) {
 printk(KERN_INFO "Sistemas Operativos 1\n");
}
module_init(inicio);

module_exit(salida);
