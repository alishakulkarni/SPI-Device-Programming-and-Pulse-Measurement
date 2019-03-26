#ifndef MATRIX_KERNEL_H
#define MATRIX_KERNEL_H
 
typedef struct{

uint16_t p0[14];
uint16_t p1[14];
uint16_t p2[14];
uint16_t p3[14];
uint16_t p4[14];
uint16_t p5[14];
uint16_t p6[14];
uint16_t p7[14];
uint16_t p8[14];
uint16_t p9[14];
uint16_t poff[5];
} patterns;

typedef struct{

int pattern1;
int time1;
int pattern2;
int time2;
int termination1;
int termination2;
} inputs;

#define SET_DATA _IOW(100, 3, patterns *)

#endif
