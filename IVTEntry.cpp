/*
 * IVTEntry.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "KernelEv.h"
#include <dos.h>
#include "lock.h"

const unsigned short IVTEntry::numOfEntries=256;

IVTEntry* IVTEntry::allEntries[256]={0};

IVTEntry::IVTEntry(IVTNo i, interruptRoutine newRout){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif
	ivt=i;
	k=0;
	allEntries[i]=this;
#ifndef BCC_BLOCK_IGNORE
	oldRout=getvect(ivt);
	setvect(ivt,newRout);
	asmUnlock();
#endif
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
	setvect(ivt,oldRout);
#endif
	callOldRout();
#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif
}

IVTEntry* IVTEntry::get(IVTNo ivtNo){
	return allEntries[ivtNo];
}

KernelEv* IVTEntry::getEv(){
	return k;
}

void IVTEntry::callOldRout(){
	if(oldRout!=0)
		(*oldRout)();
}

