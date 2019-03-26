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
#include "IOinit.h"
#include "Display.h"
#include "Ultrasound.h"

static uint16_t mode = SPI_MODE_2;
static uint8_t bits = 16;
static uint32_t speed = 200000;

int main()
{

	int fspi,re;
	pthread_t distance_ultra;

	//calling IOinit.c to export required pins
	level_shifter();
	IOSetup();

	//opening Linux's SPIDEV1.0 driver to performLED animation
	fspi = open("/dev/spidev1.0", O_WRONLY);
	if(fspi < 0){
		printf("Couldn't open SPIDEV1.0");
	}


	// SPI mode
	re = ioctl(fspi, SPI_IOC_WR_MODE, &mode);
	if (re < 0) { 
    		printf("Can't set spi mode");
    		exit(1);
	}
	// Bits per word
	re = ioctl(fspi, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (re < 0) { 
    		printf("Can't set bits per word");
    		exit(1);
	}
	// Max speed, 1ms per 32bit command --> 32kHz
	re = ioctl(fspi, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (re < 0) { 
    		printf("Can't set max speed"); 
    		exit(1);
	}
	
	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);	

	//calling ultrasonic thread for distance measurement
	pthread_create (&distance_ultra,NULL,Ultrasound_distance_measurement,NULL);

	usleep(500000);

	//infinite loop to control LED animation. This part access Display.c function to implement animation
	while(1){		

		if(sleep_ultra_used == 1)
			transfer(fspi,2);
		if(sleep_ultra_used == 2)
			transfer(fspi,1);
		usleep(1000000);
		
	}

	pthread_join(distance_ultra,NULL);
	close(fspi);	

	return 0;
}
