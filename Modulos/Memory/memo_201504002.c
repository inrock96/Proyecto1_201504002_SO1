#include <linux/fs.h> 
#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/sysinfo.h> 
#include <linux/init.h> 
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>
#define PROCFS_NAME "memo_201504002"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Inti Samayoa");
MODULE_DESCRIPTION("201504002");



static int memo_show(struct seq_file *m, void *v){

struct sysinfo i;
unsigned long porcentaje;


seq_printf(m, "{\n");
seq_printf(m, "\n");
si_meminfo(&i);

porcentaje = i.totalram -i.freeram;
porcentaje = ((porcentaje*100)/i.totalram);

seq_printf(m,"\"MemTotal\":\"%8lu\",\n",(i.totalram*4)/1024);
seq_printf(m,"\"MemFree\":\"%8lu\", \n",(i.freeram*4)/1024);
seq_printf(m,"\"MemPercent\":\"%8lu\"\n",porcentaje);

seq_printf(m, "\n}");
return 0;
}


static int memo_open(struct inode *inode, struct file *file){
return single_open(file, memo_show, NULL);
}

static const struct file_operations memo_fops = {
.owner = THIS_MODULE,
.open = memo_open,
.read = seq_read,
.llseek = seq_lseek,
.release = single_release,
};

static int __init memo_init(void) {
    printk(KERN_INFO "201504002\n");
    proc_create("memo_201504002", 0, NULL, &memo_fops);
    return 0;
}
static void __exit memo_exit(void) {
    remove_proc_entry("memo_201504002", NULL);
    printk(KERN_INFO "Sistemas Operativos 1\n");
}
module_init(memo_init);

module_exit(memo_exit);
