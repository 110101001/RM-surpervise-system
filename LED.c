#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>

#define IO_MAGIC '?'

#define LED_OFF _IO(IO_MAGIC,0)
#define LED_ON _IO(IO_MAGIC,1)

int LED_open(struct inode *node,struct file *fd);

ssize_t LED_write(struct file *fd,const char *buf,size_t len,loff_t *offset);

struct file_operations fops={
//	llseek:LED_seek,
//	read:LED_read,
	write:LED_write,
	unlock_ioctl:LED_ioctl,
	open:LED_open,
//	release:LED_close,
};

int dev_index=0;

int init_module(void){
	struct cdev *LEDdev=cdev_alloc();
	printk("<1>installing mod\n");	
	if(alloc_chrdev_region(&dev_index,1,1,"LED")!=0) return -1;
	LEDdev->owner=THIS_MODULE;
	LEDdev->ops=&fops;
	cdev_init(LEDdev,&fops);
	cdev_add(LEDdev,dev_index,1);
	printk("<1>Dev_index=%d:%d\n",MAJOR(dev_index),MINOR(dev_index));	
	return 0;
}

void cleanup_module(void){
	unregister_chrdev_region(dev_index,1);
    	printk("<1>GoodBye\n");
}

int LED_ioctl(struct file *fp,unsigned int cmd, unsigned arg){
	if(_IOC_TYPE(cmd)!=MAGIC) return -ENOTTY
	if(_IOC_NR(cmd)==1){
		printk("LED ON\n");
	}
	return 0;
}

int LED_open(struct inode *node,struct file *fd){
	printk("Open\n");
	return 0;
}

ssize_t LED_write(struct file *fd,const char *buf,size_t len,loff_t *offset){
	printk("Writing\n");
	return len;
}
