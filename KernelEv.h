/*
 * KernelEv.h
 *
 *  Created on: Jun 23, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

class Event;
class PCB;

typedef unsigned char IVTNo;

class KernelEv{

public:

	IVTNo ivt;
	Event *event;
	PCB* myPCB;
	int eventValue;
	KernelEv(IVTNo iv, Event* e);
	~KernelEv();

	void wait();
	void signal();
	IVTNo ivtNo()const;

};



#endif /* KERNELEV_H_ */
