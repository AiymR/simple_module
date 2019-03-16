#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define BUFSIZE  50
 
static char mode[BUFSIZE]="yes";
module_param_string(cparam,mode,sizeof(mode),0660);
 
static struct proc_dir_entry *ent;
 
static ssize_t usb_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) 
{
	int num,c;
	char m[BUFSIZE];
	char buf[BUFSIZE];
	if(*ppos > 0 || count > BUFSIZE)
		return -EFAULT;
	if(copy_from_user(buf, ubuf, count))//copy nlock of data from user
		return -EFAULT;
	num = sscanf(buf,"%s",m);//data from buf
	if(num != 1)
		return -EFAULT;
	strcpy(mode, m);
	c = strlen(buf);
	*ppos = c;
	return c;
}
 
static ssize_t usb_read(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	char buf[BUFSIZE];
	int len=0;
	if(*ppos > 0 || count < BUFSIZE)
		return 0;
	len += sprintf(buf,"%s\n",mode);//insert
	
	if(copy_to_user(ubuf,buf,len))
		return -EFAULT;
	*ppos = len;
	return len;
}
 
static struct file_operations myops = 
{
	.owner = THIS_MODULE,
	.read = usb_read,
	.write = usb_write,
};
 
static int my_init(void)
{
	ent=proc_create("ae",0666,NULL,&myops);
	printk(KERN_INFO "hello...\n");
	return 0;
}
 
static void my_cleanup(void)
{
	proc_remove(ent);
	printk(KERN_INFO "bye ...\n");
}
 
module_init(my_init);
module_exit(my_cleanup);
