/*
 * IVTEntry.h
 *
 *  Created on: Jun 23, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "KernelEv.h"

#define PREPAREENTRY(ivt,flag)\
void interrupt newRout##ivt(...);\
IVTEntry entry##ivt(ivt,&newRout##ivt);\
void interrupt newRout##ivt(...){\
	if(flag)\
		entry##ivt.callOldRout();\
	if(entry##ivt.getEv())\
		entry##ivt.getEv()->signal();\
	dispatch();\
}

class KernelEv;
typedef void interrupt (*interruptRoutine)(...);

class IVTEntry{

private:

	KernelEv* k;
	IVTNo ivt;
	interruptRoutine oldRout;

public:

	friend class KernelEv;
	const static unsigned short numOfEntries;
	static IVTEntry* allEntries[];
	IVTEntry(IVTNo i, interruptRoutine newRout);
	~IVTEntry();
	void callOldRout();

	static IVTEntry* get(IVTNo ivtNo);
	KernelEv* getEv();

};

#endif /* IVTENTRY_H_ */
