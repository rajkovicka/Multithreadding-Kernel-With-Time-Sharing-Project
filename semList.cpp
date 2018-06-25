/*
 * semList.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "semList.h"
#include "pcb.h"

SemList::SemList(){
	head=0;
	tail=0;
	listSize=0;
}

SemList::~SemList(){
	Elem *curr=head;
	while(curr!=0){
		head=head->next;
		if(head==0)
			tail=0;
		delete curr;
		curr=head;
	}
	listSize=0;
}

void SemList::pushSem(KernelSem* sem){
	Elem *elem=new Elem(sem);
	if(head==0)
		head=elem;
	else
		tail->next=elem;
	tail=elem;
	listSize++;
}

void SemList::deleteFromList(KernelSem* s){
	Elem *curr=head, *prev=0;
	while((curr->sem!=s) && curr!=0){
		prev=curr;
		curr=curr->next;
	}
	if(curr!=0){
		if(prev==0){
			head=head->next;
			if(head==0)
				tail=0;
			delete curr;
		}
		else{
			prev->next=curr->next;
			if(curr==tail)
				tail=prev;
			delete curr;
		}
		listSize--;
	}
}

KernelSem* SemList::getFirst(){
	if(head!=0){
		Elem* curr=head;
		head=head->next;
		if(head==0)
			tail=0;
		listSize--;
		KernelSem* sem=curr->sem;
		delete curr;
		return sem;
	}
	else
		return 0;
}

int SemList::getSize()const{
	return listSize;
}
