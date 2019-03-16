#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define BUFSIZE  50
 
 
static char mode[BUFSIZE]="no";
module_param_string(cparam,mode,sizeof(mode),0660);
 
static struct proc_dir_entry *ent;
 
static ssize_t usb_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) 
{
	
	int num,c;
	char m[BUFSIZE];
	char buf[BUFSIZE];
	if(*ppos > 0 || count > BUFSIZE)
		return -EFAULT;
	if(copy_from_user(buf, ubuf, count))
		return -EFAULT;
	
	num = sscanf(buf,"%s",m);
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
	len += sprintf(buf + len,"%s\n",mode);
	
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


int get_password(void) {
	char buf[BUFSIZE];
	char pas[3];
   	 mm_segment_t fs;
	
    	printk(KERN_INFO "My module is loaded\n");
	struct file *f = filp_open("/proc/ae", O_RDONLY|O_WRONLY, 0);
	//struct file *fp = filp_open("/proc/auth", O_RDONLY|O_WRONLY, 0);
	
    		if(IS_ERR(f)){
        printk(KERN_ALERT "filp_open error!!.\n");
	return -1;
	}
    
        fs = get_fs();
        set_fs(get_ds());
	//kernel_read(f, buf, BUFSIZE,&f->f_pos);
	f->f_op->read(f, buf, BUFSIZE, &f->f_pos);
        set_fs(fs);
     
        printk(KERN_INFO "%s\n",buf);
	
	printk(KERN_INFO "lala %s\n",sizeof(pas));


	/*if(strcmp(buf,"no")!=0){
	//strcpy(buf, "no");

	kernel_write(fp,"no", BUFSIZE,&fp->f_pos);
	filp_close(f,NULL);
	//return 1;
	}*/
	//strcpy(buf, "yes");
	//kernel_write(fp, "yes", BUFSIZE,&fp->f_pos);
    filp_close(f,NULL);
    return 0;

}

 
static int my_init(void)
{
	ent=proc_create("rev",0666,NULL,&myops);
	int si=get_password();
	printk(KERN_ALERT "hello %d\n ",si);
	return 0;
}
 
static void my_cleanup(void)
{
	proc_remove(ent);
	printk(KERN_WARNING "bye ...\n");
}
 
module_init(my_init);
module_exit(my_cleanup);
