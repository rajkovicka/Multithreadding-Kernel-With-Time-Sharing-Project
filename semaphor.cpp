/*
 * semaphor.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "semaphor.h"
#include "kernelSe.h"
#include "lock.h"
#include "thread.h"

Semaphore::Semaphore(int init){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif
	myImpl=new KernelSem(init,this);
#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif
}

Semaphore::~Semaphore(){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif
	if(myImpl->semValue<0)
		myImpl->wakeUp();

	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif

}

int Semaphore::wait(int toBlock){
	int result=myImpl->wait(toBlock);
	if(result==1)
		dispatch();
	return result;
}

void Semaphore::signal(){
	if(myImpl!=0)
		myImpl->signal();
}

int Semaphore::val()const{
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif

	int result=myImpl->semValue;

#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif

	return result;
}
