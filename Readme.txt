Team-4:

RITESH THAKUR (1215283069)
ALISHA KULKARNI (1215311903)
------------------------------------------------------------
As per assignment's requirement, Part-1 and Part-1-Revised code is split into modules named Display.c (to control MAX7219), Ultrasound.c (to control ultrasonic sensor), IOinit.c (to export level shifters and required pin MUXs) and main.c to run the code.
----------------------------------

Important files to be downloaded:

For Part-1 : All the required files are inside the directory Part-1. Part-1 can be found in the .zip provided as submission (ESP-team4-assgn04)
For Part-2 : All the required files are inside the directory Part-2. Part-2 can be found in the .zip provided as submission (ESP-team4-assgn04)
For Part-1-Revised : All the required files are inside the directory Part-1-Revised. Part-1-Revised can be found in the .zip provided as submission (ESP-team4-assgn04) 

PLEASE NOTE: Part-1-Revised is same as Part-1 code, except it opens the new driver created in Part-2 instead of /dev/spidev1.0. That is; after testing Part-2, graders need not restart board to test Part-1-Revised, as Part-1 revised will be using Part-2 driver to recreate Part-1's animation.
These changes are made in Display.c module of Part-1. Minor changes made in Display.c of Part-1 makes animation in Part-1 work exactly the same in Part-1-Revised. (Requirement of the assignment)
------------------------------------------------------------
To run the code:

For Part-1:

. Go inside the directory Part-1 which is a part of zipped file provided as assignment submission.
. Do 'make'.
. Copy unexport and main to Galileo Board. 
. Run './unexport' first.
. Run './main'

Animation made is 'Pacman'. If object is brought closer to Ultrasonic Sensor, Pacman eats the dot. (IDEA: Pacman basically eats the obstacle if it is closer to it. If its taken away it waits for it to come back)

We cap the distance between 10 and 60 cm. 
Any thing less than 10 is taken as 10 and anything more than 60 is taken as 60.

--------------------

For Part-2:

. Go inside the directory Part-2 which is a part of zipped file provided as assignment submission.
. Do 'make'.
. Copy unexport, matrix_kernel.ko and main to Galileo Board.
. Run 'rmmod spidev' to remove Linux's SPI Driver.
. Run 'insmod matrix_kernel.ko' to install MY driver. New driver can be seen in /dev as 'LED-Driver'. (PLEASE NOTE THAT MY DRIVER IS CALLED LED-Driver. IF YOU COINCIDENTLY HAVE A SIMILAR ONE do "rmmod")
. Run './unexport' first.
. Run './main'

When program asks user for input, enter as asked:

'Enter pattern 1:' asks user for the pattern 1 for their sequence. (Input : 0-9)
'Enter time 1:' asks user for the time for which pattern 1 will be displayed. (Input : 0-999) {0 time implies patterns will not be displayed}
'Enter pattern 2:' asks user for the pattern 2 for their sequence. (Input : 0-9)
'Enter time 2:' asks user for the time for which pattern 2 will be displayed. (Input : 0-999) {0 time implies patterns will not be displayed}
'Enter termination 1:' asks user for the termination value 1 for their sequence. (Input : 0-1)
'Enter termination 2:' asks user for the termination value 2 for their sequence. (Input : 0-1)

PLEASE NOTE: Entering 0 for Termination 1 and 0 for Termination 2 is the only way to clear the display. (As per assignment's requirement)

10 patterns used are Digits from 0-9. (For user input 0, pattern number 0 i.e. "0" will be displayed on MAX7219)

--------------------

For Part-1-Revised:

. Go inside the directory Part-1-revised which is a part of zipped file provided as assignment submission.
. Do 'make'.
. Copy unexport and main to Galileo Board. 
. Run './unexport' first.
. Run './main'

Part-1-Revised will be using the same driver we are creating in Part-2 i.e. '/dev/LED-Driver' and NOT '/dev/spidev1.0'. Which means, graders NEED NOT restart the board in order to get '/dev/spidev1.0' back.

Part-1-Revised Animation made is 'Pacman'. If object is brought closer to Ultrasonic Sensor, Pacman eats the dot. (IDEA: Pacman basically eats the obstacle if it is closer to it. If its taken away it wait for it to come back)

PLEASE NOTE: AS PER ASSIGNMENT'S REQUIRMENT WE ARE RECREATING PART-1 ANIMATION BUT USING OUR OWN DRIVER.

We only revise Display.c in Part-1 to achieve Part-1-Revised.

------------------------------------------------------------------------------------------------
MakeFile Instructions:

1. use "make clean" to clean the objects which the .c(s) will create to create the necessary objects.
2. use "make" to compile the code using i586 Poky Linux compiler. (Since this assignment was board specific, we only make the files for board using cross compiler)

Path, KDIR and IOT_HOME can be changed per user's convinience if they have i586-poky-linux kept in some different directory:

IOT_HOME = /opt/iot-devkit/1.7.2/sysroots
PWD:= $(shell pwd)
KDIR:=$(IOT_HOME)/i586-poky-linux/usr/src/kernel
PATH := $(PATH):$(IOT_HOME)/x86_64-pokysdk-linux/usr/bin/i586-poky-linux

-------------------------------------------------------------------------------------------------

PINS:

LED Matrix: DIN - Pin 11, CLK - Pin 13 , CS - Pin 12 and GND - Ground
We dont need Vcc for MAX7219.

Ultrasound: GND - Ground, Vcc - 5 Volts, Trigger - 2 and Echo - 3

----------------------------------------------------------------------------------------------------

*IMPORTANT NOTE: THIS CODE USES THE CODE PROVIDED BY PROFESSOR YANN-HANG LEE AS UNDERLYING CODE FROM WHICH THIS CODE WAS BUILT UPON. ANY SIMILARITY IN VARIABLE NAMES LIKE GMEM_DEVP IS BECAUSE OF THE SAME REASON.*

