#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <pthread.h>
#include <inttypes.h>
#include <time.h>
#include <poll.h>
//header file that has all the params that are shared by main and Ultrasound.c
#include "Ultrasound.h"

/*****Function that exports GPIOs, Level Shifters and MUXes required for HC-SR04*****/
/*Trigger pin: IO2
  Echo pin: IO3 */

typedef unsigned long long ticks;
int fd14, fd14v,fd14e,fd13,fd13v,fd64,fd34,fd77,fd76,fd16;
double time_flag;

//function used to gettime from rdtsc
static inline ticks GETTIME(void){
      unsigned a, d;
      asm("cpuid");
      asm volatile("rdtsc" : "=a" (a), "=d" (d));
      return (((ticks)a) | (((ticks)d) << 32));
}

/*****************************************
The function does the following:
1.Generates signal of the trigger
2.Starts the timer
3.Measures the duration of the echo signal
4.Converts duration to distance 
******************************************/

void* Ultrasound_distance_measurement(){
	int ret;
	int timeout = 2000;
	float start=0;
	float finish=0; 
	long time_elapsed;
	double time_to_distance;
	struct pollfd PollEch;
	char* buffer[64];
 
	fd14 = open("/sys/class/gpio/gpio14/direction", O_WRONLY);
	if (fd14 < 0)
		printf("\n gpio14 direction file could not be opened");
	if (0> write(fd14,"in",2))
		printf(" \n in direction writing error fd14");
	fd14v = open("/sys/class/gpio/gpio14/value", O_RDWR);
	if (fd14v<0)
		printf("\n gpio14 value file could not be opened");
	fd14e = open("/sys/class/gpio/gpio14/edge", O_WRONLY);
	if (fd14e< 0)
		printf("\n gpio14 value file could not be opened");
	fd13v = open("/sys/class/gpio/gpio13/value", O_WRONLY);
	if (fd14v< 0)
		printf("\n gpio13 value file could not be opened");

	/* Poll initialisation */
	PollEch.fd = fd14v;
	PollEch.events = POLLPRI|POLLERR;
	PollEch.revents=0;

	/*Wait for echo to begin. Once the echo pin receives a pulse from the trigger, it starts polling*/
	begin:  while(1){
			finish=0;
			start=0;
			lseek(fd14v,0,SEEK_SET);
			write(fd14e,"rising",6);
			write(fd13v,"1",1);
			usleep(10);
			write(fd13v,"0",1);
			/*  rising edge */
			ret=poll(&PollEch,1,timeout);
			if(ret>0){
				if (PollEch.revents & POLLPRI){
					start = GETTIME();
					read(fd14v,buffer,1);
				}
			else{
				printf("Error in detecting Rising Edge\n");
				goto begin;
				}
			}
		
			lseek(fd14v,0,SEEK_SET);
			/* falling edge */
			write(fd14e,"falling",7);
			ret = poll(&PollEch,1,timeout);
			if(ret>0){
				if (PollEch.revents & POLLPRI){
				
					finish= GETTIME();
					read(fd14v,buffer,1);
				}
				else{
					printf("Error in detecting Falling Edge\n");
					goto begin;
				}
					}
  				/*Calculate the time duration*/	
				time_elapsed = (long)(finish-start);								
				/*convert time to distance*/
				time_to_distance =(time_elapsed*340.00)/(4000000*2);
				//capping distance below 10 to 10 and distance higher than 60 to 60
				if(time_to_distance > 60.000000){
					time_to_distance = 60.000000;
				}
				if(time_to_distance <= 10.000000){
					time_to_distance = 10.000000;
				}
				//logic to make animation behave differently on the basis of distance from obstacle
				if(time_to_distance >= 10 && time_to_distance < 25){
					sleep_ultra_used = 1;
				}
				if(time_to_distance >= 25 && time_to_distance <=60){
					sleep_ultra_used = 2;
				}

				usleep(100000);
		}
		return 0;
}
