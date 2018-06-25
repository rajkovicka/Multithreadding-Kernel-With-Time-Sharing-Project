/*
 * semBList.h
 *
 *  Created on: Jun 23, 2018
 *      Author: OS1
 */

#ifndef SEMBLIST_H_
#define SEMBLIST_H_

#include "pcb.h"

class SemBlockList{

	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* p):pcb(p),next(0){}
	};

	int listSize;
	Elem *head, *tail;

public:

	SemBlockList();
	~SemBlockList();

	void pushBlocked(PCB* p);
	void deleteFromBlocked(PCB* p);
	PCB* getFirst();
	int size()const;

};


#endif /* SEMBLIST_H_ */
