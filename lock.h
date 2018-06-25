/*
 * lock.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef LOCK_H_
#define LOCK_H_

#include <dos.h>

#define asmLock() asm { pushf; \
	cli;}

#define asmUnlock() asm { popf; }

class Lock{

public:

	static int lockFlag;
	static void lock();
	static void unlock();

};

#endif /* LOCK_H_ */
