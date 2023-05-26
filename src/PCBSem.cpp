/*
 * PCBSem.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */


#include"PCBSem.h"
#include"pcb.h"
#include"SCHEDULE.h"
#include"kersem.h"

PCBSem::PCBSem(KernelSem* mk)
{
	mojker=mk;
	head=0;
	tail=0;
	size=0;
	pom=0;
	}

void PCBSem::put(PCB* p, int v)
{
	pom=new elem(p,v);
	if (head==0)
	{
		head=pom;
		tail=pom;
		tail->sled=0;
		head->sled=0;
		size++;
		return;
	}
	tail->sled=pom;
	tail=tail->sled;
	size++;
	return;


	}


PCBSem::~PCBSem()
{
	while (size>0)
	{
		pom=head;
		head=head->sled;
		delete pom;
		size--;
	}
	head=0;
	size=0;
	pom=0;
	tail=0;
	}

int PCBSem::length()
{
	return size;

	}

PCB* PCBSem::get()
{
	if (head==0) {tail=0; return 0;}
	pom=head;
	PCB* p=head->sadrzaj;
	head=head->sled;
	if (head==0) tail=0;
	size--;
	delete pom;
	return p;
	}
void PCBSem::kucl()
{
	if (head==0) return;
	pom=head;
	elem* pre;
	while (pom!=0)
	{
		if (pom->vreme==-1) {pre=pom;pom=pom->sled; continue;}

			pom->vreme-=1;
			if (pom->vreme == 0) {
						pom->sadrzaj->status = PCB::READY;
						Scheduler::put(pom->sadrzaj);
						mojker->incvalue();
						if (pom==head)
								{
									head=head->sled;
									size--;
									delete pom;
									pre=0;
									pom=head;
								}
						else
								if (pom==tail)
								{
									tail=pre;
									tail->sled=0;
									size--;
									delete pom;
									break;
								}
								else
								{
								pre->sled=pom->sled;
								size--;
								delete pom;
								pom=pre->sled;
								}
						continue;
								}


						pre=pom;
								pom=pom->sled;
	}

	}

