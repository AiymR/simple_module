#include <linux/module.h>	/* Specifically, a module */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/proc_fs.h>	/* Necessary because we use the proc fs */

#define procfs_name "authenticated"

struct proc_dir_entry *proc_entry;

static const struct file_operations proc_fops = {
 .owner = THIS_MODULE,
 .write = write_file,
};

static write_file(){

}
int init_module() {
 	proc_entry = proc_create(procfs_name, 0, NULL, &proc_fops);
  	if(proc_entry == NULL)
   		return -ENOMEM;
	printk(KERN_INFO "/proc/%s created\n", procfs_name);
  	return 0;
}
void cleanup_module() {
 remove_proc_entry(procfs_name, NULL);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);
}

