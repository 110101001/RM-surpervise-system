#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <asm/io.h>

#define IO_MAGIC '?'

#define LED_OFF _IO(IO_MAGIC,0)
#define LED_ON _IO(IO_MAGIC,1)

#define GPIO1_BASE 0x4804C000
#define GPIO1_OE (GPIO1_BASE+0x134)
#define GPIO1_OUT (GPIO1_BASE+0x13c)

#define OUT1(x) *pOut |= (1<<x)
#define OUT0(x) *pOut &= ~(1<<x)

#define SETOUT(x) *pConf &= ~(1<<x);
volatile int * pConf,*pOut;
int LED_open(struct inode *node,struct file *fd);
int LED_close(struct inode *node,struct file *fd);

ssize_t LED_write(struct file *fd,const char *buf,size_t len,loff_t *offset);

long LED_ioctl(struct file *fp,unsigned int cmd, unsigned long arg);

struct file_operations fops={
//	llseek:LED_seek,
//	read:LED_read,
	write:LED_write,
	unlocked_ioctl:LED_ioctl,
	open:LED_open,
	release:LED_close,
};

int dev_index=0;

int init_module(void){
	struct cdev *LEDdev=cdev_alloc();
	printk("<1>installing LED.V1\n");	
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

long LED_ioctl(struct file *fp,unsigned int cmd, unsigned long arg){
	if(_IOC_TYPE(cmd)!=IO_MAGIC) return -ENOTTY;
	if(_IOC_NR(cmd)==1){
		printk("LED ON\n");
		OUT1(22);	
	}
	else if(_IOC_NR(cmd)==0){
		printk("LED OFF\n");
		OUT0(22);
	}
	return 0;
}

int LED_open(struct inode *node,struct file *fd){
	printk("Open LED\n");
	pConf=ioremap(GPIO1_OE , 4);
	pOut=ioremap(GPIO1_OUT, 4);
	SETOUT(22);
	return 0;
}
int LED_close(struct inode *node,struct file *fd){
	printk("Close LED\n");
	iounmap(pConf);
	iounmap(pOut);
	return 0;
}


ssize_t LED_write(struct file *fd,const char *buf,size_t len,loff_t *offset){
	printk("Writing\n");
	return len;
}
