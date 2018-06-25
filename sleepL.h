/*
 * sleepL.h
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#ifndef SLEEPL_H_
#define SLEEPL_H_

#include "thread.h"

class PCB;

class SleepList{

	struct Elem{
		PCB* pcb;
		Time time;
		Elem* next;
		Elem(PCB* p, Time t):pcb(p),time(t),next(0){}
	};

	int listSize;
	Elem *head, *tail;

public:

	SleepList();
	~SleepList();
	void pushSleepPCB(PCB* pcb, Time time);
	void deleteFromList(PCB* pcb);
	int getSize() const;
	void checkSleepList();
	void wakeUpFromList(PCB* p);

};

#endif /* SLEEPL_H_ */
