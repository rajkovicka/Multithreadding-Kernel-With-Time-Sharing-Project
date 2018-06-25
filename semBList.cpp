/*
 * semBList.cpp
 *
 *  Created on: Jun 23, 2018
 *      Author: OS1
 */

#include "semBList.h"
#include "SCHEDULE.H"

SemBlockList::SemBlockList(){
	head=0;
	tail=0;
	listSize=0;
}

SemBlockList::~SemBlockList(){
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

void SemBlockList::pushBlocked(PCB* pcb){
	Elem *elem=new Elem(pcb);
	if(head==0)
		head=elem;
	else
		tail->next=elem;
	tail=elem;
	listSize++;
}

void SemBlockList::deleteFromBlocked(PCB* p){
	Elem *curr=head, *prev=0;
	while(curr!=0 && curr->pcb!=p){
		prev=curr;
		curr=curr->next;
	}
	if(curr!=0){
		if(prev==0){
			head=head->next;
			if(head==0)
				tail==0;
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

PCB* SemBlockList::getFirst(){
	if(head!=0){
		Elem *curr=head;
		head=head->next;
		if(head==0)
			tail=0;
		PCB* pcb=curr->pcb;
		delete curr;
		return pcb;
	}
	else
		return 0;
}

int SemBlockList::size()const{
	return listSize;
}
