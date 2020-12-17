#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/sysinfo.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/timekeeping.h>

#define for_each_process(p) \
for (p = &init_task ; (p = next_task(p)) != &init_task ; )


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Inti Samayoa");
MODULE_DESCRIPTION("201504002");

static int cpu_show(struct seq_file*m,void *v){
    unsigned int usuario;
    char user[16];
    char estado;
    
    int proc_ejec = 0;
    int proc_susp = 0;
    int proc_stop = 0;
    int proc_zombie = 0;
    int proc_otro =0;
    int total;
    struct task_struct *task;
    struct task_struct *task_child;
    
    seq_printf(m,"{\n\"procesos\":[");
    for_each_process(task){ 
        struct list_head *list;

        if(task->state == TASK_RUNNING){
            estado = 'R';
            proc_ejec++;
        }else if((task->state == TASK_STOPPED)||(task->state == TASK_TRACED)){
            estado = 'T';
            proc_stop++;
        }else if((task->state == TASK_INTERRUPTIBLE)||(task->state == TASK_UNINTERRUPTIBLE)){
            estado = 'S';
            proc_susp++;
        }else if(task->state == EXIT_ZOMBIE){
            estado = 'Z';		
            proc_zombie++;
        }else{
            estado = 'X';
            proc_otro++;
        }

        usuario = task->cred->uid.val;
        if( usuario == 0){
            strcpy(user,"root");
        }else{
            strcpy(user,"inti");
        }
        //imprimir proceso padre
        seq_printf(m,"{\n \"pid\":\"%d\",\n \"nombre\":\"%s0\",\n \"usuario\":\"%s\",\n \"estado\":\"%c\"}",
        task->pid,
        task->comm,
        user,
        estado);
        list_for_each(list,&task->children){
            task_child=list_entry(list,struct task_struct,sibling);

            if(task_child->state == TASK_RUNNING){
                estado = 'R';
                proc_ejec++;
            }else if((task_child->state == TASK_STOPPED)||(task->state == TASK_TRACED)){
                estado = 'T';
                proc_stop++;
            }else if((task_child->state == TASK_INTERRUPTIBLE)||(task->state == TASK_UNINTERRUPTIBLE)){
                estado = 'S';
                proc_susp++;
            }else if(task_child->state == EXIT_ZOMBIE){
                estado = 'Z';		
                proc_zombie++;
            }else{
                estado = 'X';
                proc_otro++;
            }

            usuario = task_child->cred->uid.val;
            if( usuario == 0){
                strcpy(user,"root");
            }else{
                strcpy(user,"inti");
            }
            //imprimir proceso padre
            seq_printf(m,",{\n \"pid\":\"%d\",\n \"nombre\":\"%s0\",\n \"usuario\":\"%s\",\n \"estado\":\"%c\"}",
            task_child->pid,
            task_child->comm,
            user,
            estado);
        }
        if((next_task(task)) != &init_task){
            seq_printf(m,",");
        }
    }
    seq_printf(m,"]\n");
    total = proc_ejec+proc_susp+proc_stop+proc_zombie+proc_otro;
    seq_printf(m,",\n\"ejecucion\":\"%d\",\"suspendido\":\"%d\",\"detenido\":\"%d\",\"zombie\":\"%d\",\"otros\":\"%d\",\"total\":\"%d\"\n}",
    proc_ejec,
    proc_susp,
    proc_stop,
    proc_zombie,
    proc_otro,
    total);

    return 0;
}

static int cpu_open(struct inode *inode,struct file *file){
    return single_open(file,cpu_show,NULL);
}

static struct file_operations cpu_fops = {
    .owner = THIS_MODULE,
    .open = cpu_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init inicio(void) {
 printk(KERN_INFO "Inti\n");
 proc_create("cpu_201504002",0,NULL,&cpu_fops);
 return 0;
}
static void __exit salida(void) {
    remove_proc_entry("cpu_201504002",NULL);
 printk(KERN_INFO "Sistemas Operativos 1\n");
}
module_init(inicio);

module_exit(salida);
