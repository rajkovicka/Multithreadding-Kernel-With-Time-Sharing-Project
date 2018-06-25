/*
 * semList.h
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

class KernelSem;

class SemList{

	struct Elem{
		KernelSem* sem;
		Elem* next;
		Elem(KernelSem* s):sem(s),next(0){}
	};

	int listSize;
	Elem *head, *tail;

public:

	friend class KernelSem;

	SemList();
	~SemList();

	void pushSem(KernelSem* sem);
	void deleteFromList(KernelSem* sem);
	KernelSem* getFirst();
	int getSize() const;

};

#endif /* SEMLIST_H_ */
