#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <linux/input.h>
#include <pthread.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>
#include <stdint.h>

//header files to implement modular approach
#include "Display.h"
#include "Ultrasound.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define	SPI_3WIRE	0x10

//transfer structs
struct spi_ioc_transfer tr[256];

//bus configuration
static uint32_t speed = 2000000;
static uint16_t delay;

//pattern for pacman open
uint16_t tx_open[] = {

		0x0F00,	  //Display
		0x0A0F,   //INtensity
		0x0900,	  //Decode
		0x0B07,   //Scan
		0x0C00,

		0x013C,
		0x024E,
		0x03CF,
		0x043F,
		0x059F,
		0X063F,
		0x07FE,
		0x083C,

		0x0C01,
		
	};

//pattern for pacman open
uint16_t tx_close[] = {

		0x0F00,	  //Display
		0x0A0F,   //INtensity
		0x0900,	  //Decode
		0x0C00,   //shutdown
		0x0B07,   //scan	
		0x0C00,

		0x013C,
		0x024E,
		0x03CF,
		0x04FF,
		0x051F,
		0X06FF,
		0x07FE,
		0x083C,

		0x0C01,
		
	};

//function being called by main to control LED animation

void transfer(int fd, int pat_type)
{
	int ret, Fv15, i;

//if condition to display LED sequence based on what user sent
	if(pat_type == 1){
		//for loop to print all the 16 bit values of a pattern
		for(i=0;i<ARRAY_SIZE(tx_close);i++)
		{

			tr[i].tx_buf = (unsigned long)&tx_open[i];
			tr[i].len = 2;
			tr[i].delay_usecs = delay;
			tr[i].speed_hz = speed;
			tr[i].bits_per_word = 16;
			tr[i].cs_change = 1;
			//setting CS to low before transfer
			Fv15 = open("/sys/class/gpio/gpio15/value", O_WRONLY);
			if(0 > write(Fv15,"0",1)){
				printf("Error Fv15");
			}

			ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr[i]);

			if (ret < 1){
				printf("ioctl failed and returned errno %s \n",strerror(errno));
			}
			//setting CS to high after transfer
			if(0 > write(Fv15,"1",1)){
				printf("Error Fv15");
			}
		}
	}

	if(pat_type == 2){

		for(i=0;i<ARRAY_SIZE(tx_close);i++)
		{

			tr[i].tx_buf = (unsigned long)&tx_close[i];
			tr[i].len = 2;
			tr[i].delay_usecs = delay;
			tr[i].speed_hz = speed;
			tr[i].bits_per_word = 16;
			tr[i].cs_change = 1;

			Fv15 = open("/sys/class/gpio/gpio15/value", O_WRONLY);
			if(0 > write(Fv15,"0",1)){
				printf("Error Fv15");
			}

			ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr[i]);

			if (ret < 1){
				printf("ioctl failed and returned errno %s \n",strerror(errno));
			}

			if(0 > write(Fv15,"1",1)){
				printf("Error Fv15");
			}
		}
	}

	
}
