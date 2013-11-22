/*
 * table.h
 *
 *  Created on: Nov 15, 2013
 *      Author: B43657
 */

#ifndef TABLE_H_
#define TABLE_H_

void delay(unsigned int cnt);
#define NrSteps	1000
#define Tosc	0.05 //in ns
#define Tsample 10 // in us

extern unsigned int *ptr;
extern unsigned char *p1;
extern unsigned char *p2;
extern unsigned int Delta;
extern float Fout;
extern unsigned int step;
extern unsigned int tableSize;
extern float newPeriod;
extern float deltaPeriodSample;
extern float newSlotPeriod;
extern unsigned int loadPIT;

extern char doCalc;



unsigned int sineTable[1000];

unsigned int readyTable[256];
#endif /* TABLE_H_ */
