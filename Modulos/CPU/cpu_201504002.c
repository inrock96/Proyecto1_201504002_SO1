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

static int __init lkm_example_init(void) {
 printk(KERN_INFO "Hello, World!\n");
 return 0;
}
static void __exit lkm_example_exit(void) {
 printk(KERN_INFO "Goodbye, World!\n");
}
module_init(lkm_example_init);

module_exit(lkm_example_exit);
