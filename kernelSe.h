/*
 * kernelSe.h
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#ifndef KERNELSE_H_
#define KERNELSE_H_

class SemList;
class SemBlockList;
class Semaphore;

class KernelSem{

public:

	Semaphore* sem;
	int semValue;

	SemBlockList* blocked;

	static SemList* allSems;

	KernelSem(int init, Semaphore* s);
	~KernelSem();
	int wait(int toBlock);
	void signal();
	void wakeUp();

};

#endif /* KERNELSE_H_ */
