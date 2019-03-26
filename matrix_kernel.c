#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/fcntl.h>
#include <linux/input.h>
#include <linux/spi/spidev.h>
#include <linux/spi/spi.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/kthread.h>

#include "matrix_kernel.h" 

#define DEVICENAME 	 "LED-Driver"
#define DEVICECLASS	"LED-MX"
#define CONFIG 1
#define MINNUMBER    0
#define MJNUMBER 154

//structs being used to get data from user app. defined in Matrix_kernel.h
inputs inp; //to take user sequence
patterns sp; //to accepts patterns from user space

static struct spidev_data *device_data;
static struct class *gmem_dev_class;
static struct spi_message mes; //struct type to send message to bus
uint16_t tx_ar[1]; // this will hold the pattern's 16 bits at a time

//data struct used to transfer
struct spi_transfer data_tr = {

	.tx_buf = tx_ar,
	.len = 2,
	.bits_per_word = 16,
	.speed_hz = 200000,
	.cs_change = 1,
};

struct spidev_data {
	dev_t  device;
	struct spi_device *spi;
};

//to open the driver
int gmem_driver_open(struct inode *i, struct file *f){

	printk(KERN_INFO" initializing the gpio pins for the spi LED matrix\n");

	gpio_export(24,true);
	gpio_export(25,true);
	gpio_export(30,true);
	gpio_export(31,true);
	gpio_export(42,true);
	gpio_export(43,true);
	gpio_export(46,true);
	gpio_export(44,true);
	gpio_export(72,true);
	gpio_export(15,true);
	gpio_export(5,true);
	gpio_export(7,true);
	gpio_direction_output(5,1);
	gpio_set_value(5,1);
	gpio_direction_output(7,1);
	gpio_set_value(7,1);
	gpio_direction_output(46,1);
	gpio_set_value(46,1);
	gpio_direction_output(30,1);
	gpio_set_value(30,0);
	gpio_direction_output(31,1);
	gpio_set_value(31,0);
	gpio_set_value(72,0);
	gpio_direction_output(24,1);
	gpio_set_value(24,0);
	gpio_direction_output(25,1);
	gpio_set_value(25,0);
	gpio_direction_output(44,1);
	gpio_set_value(44,1);
	gpio_direction_output(42,1);
	gpio_set_value(42,0);
	gpio_direction_output(43,1);
	gpio_set_value(43,0);
	gpio_direction_output(15,1);
	gpio_set_value(15,0);
	return 0;
}

//to release the driver

int gmem_driver_release(struct inode *i, struct file *flpptr){

	printk(KERN_INFO"\n unexporting the gpio pins and releasing when closing");

	gpio_unexport(24);
	gpio_free(24);
	gpio_unexport(25);
	gpio_free(25);
	gpio_unexport(30);
	gpio_free(30);
	gpio_unexport(31);
	gpio_free(31);
	gpio_unexport(42);
	gpio_free(42);
	gpio_unexport(43);
	gpio_free(43);
	gpio_unexport(46);
	gpio_free(46);
	gpio_unexport(44);
	gpio_free(44);
	gpio_unexport(72);
	gpio_free(72);
	gpio_unexport(15);
	gpio_free(15);
	gpio_unexport(5);
	gpio_free(5);
	gpio_unexport(7);
	gpio_free(7);
	return 0;
}

//to write to the driver

ssize_t gmem_driver_write(struct file *file, const char *buf,size_t count, loff_t *ppos){

	int i;

	//getting pattern sequence from user space
	if(copy_from_user(&inp, (inputs *)buf, sizeof(inputs)))	
		return -EACCES;
	
	if(inp.pattern1==0){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p0[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}

	if(inp.pattern1==1){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p1[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==2){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p2[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==3){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p3[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==4){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p4[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==5){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p5[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==6){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p6[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==7){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p7[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==8){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p8[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern1==9){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){

			tx_ar[0] = sp.p9[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}

	//if time for a pattern is 0, dont display it
	if(inp.time1 == 0){
		
		for(i=0; i<ARRAY_SIZE(sp.poff); i++){

			tx_ar[0] = sp.poff[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	else{
		msleep(inp.time1);
	}

	//-----------------------------------------------------------------------another pattern

	if(inp.pattern2==0){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p0[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==1){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p1[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==2){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p2[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==3){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p3[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==4){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p4[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==5){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p5[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==6){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p6[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==7){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p7[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==8){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p8[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	if(inp.pattern2==9){

		for(i=0; i<ARRAY_SIZE(sp.p0); i++){			
			
			tx_ar[0] = sp.p9[i];
	    		
			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	
	//if time for a pattern is 0, dont display it
	if(inp.time2 == 0){
		
		for(i=0; i<ARRAY_SIZE(sp.poff); i++){

			tx_ar[0] = sp.poff[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	else{
		msleep(inp.time2);
	}
	
	//clearing the display if termination symbols are 0,0

	if(inp.termination1 == 0 && inp.termination2 ==0){
		
		for(i=0; i<ARRAY_SIZE(sp.poff); i++){

			tx_ar[0] = sp.poff[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}
	}
	
	return 0;	
}

//ioctl function to receive 10 patterns from user

static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg) 
{
	
	int i;

	if(copy_from_user(&sp, (patterns *)arg, sizeof(patterns)))	
		return -EACCES;
		
		for(i=0; i<ARRAY_SIZE(sp.poff); i++){

			tx_ar[0] = sp.poff[i];

			spi_message_init(&mes);
			spi_message_add_tail((void *)&data_tr, &mes);
			gpio_set_value(15,0);
			spi_sync(device_data->spi, &mes);
			gpio_set_value(15,1);
		}

	return 0;
}

//file ops for my driver
static const struct file_operations my_operations = {
	.open = gmem_driver_open,
	.release = gmem_driver_release,
	.write	= gmem_driver_write,
	.unlocked_ioctl = my_ioctl,
	
};

//probe function to match a device to its driver

static int probe_device(struct spi_device *spi){
	
	int status = 0;
	struct device *dev;

	
	device_data = kzalloc(sizeof(*device_data), GFP_KERNEL);
	if(!device_data)
	{
		return -ENOMEM;
	}
	device_data->spi = spi;

	device_data->device = MKDEV(MJNUMBER, MINNUMBER);

    dev = device_create(gmem_dev_class, &spi->dev, device_data->device, device_data, DEVICENAME);

    if(dev == NULL)
    {
		printk(" Failed while creating device\n");
		kfree(device_data);
		return -1;
	}
	printk("Spi matrix probled.\n");
	return status;
}

//remove the device's driver instance when device is removed

static int spi_remove(struct spi_device *spi){

	device_destroy(gmem_dev_class, device_data->device);
	kfree(device_data);
	printk(" Driver Removed.\n");
	return 0;
}

struct spi_device_id led_device[] = {
{"spidev",0},
};

//device specific functions
static struct spi_driver my_driver = {
         .driver = {
            .name =         "spidev",
            .owner =        THIS_MODULE,
         },
	 .id_table =   led_device,
         .probe =        probe_device,
         .remove =       spi_remove,
		
};

//init the module

int __init gmem_driver_init(void)
{
	
	int ret;
	
	ret = register_chrdev(MJNUMBER, DEVICENAME, &my_operations);
	if(ret < 0)
	{
		printk(" Registration of the device ailed\n");
		return -1;
	}
	
	//Create the class
	gmem_dev_class = class_create(THIS_MODULE, DEVICECLASS);
	if(gmem_dev_class == NULL)
	{
		printk("Class Creation Failed\n");
		unregister_chrdev(MJNUMBER, my_driver.driver.name);
		return -1;
	}
	
	//Register the Driver
	ret = spi_register_driver(&my_driver);
	if(ret < 0)
	{
		printk("Driver Registraion Failed\n");
		class_destroy(gmem_dev_class);
		unregister_chrdev(MJNUMBER, my_driver.driver.name);
		return -1;
	}
	
	printk("Initialized.\n");
	return 0;
}

//exiting the module
void __exit gmem_driver_exit(void)
{
	spi_unregister_driver(&my_driver);
	class_destroy(gmem_dev_class);
	unregister_chrdev(MJNUMBER, my_driver.driver.name);
	
}

module_init(gmem_driver_init);
module_exit(gmem_driver_exit);
MODULE_LICENSE("GPL v2");
