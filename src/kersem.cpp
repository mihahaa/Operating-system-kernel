/*
 * kersem.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */



#include"kersem.h"
#include<dos.h>
#include"PCBSem.h"
#include"semlist.h"
#include"pcb.h"
#include"SCHEDULE.H"
#include"thread.h"
#include"pomf.h"

SemList* KernelSem::svisem=new SemList();



int KernelSem::val() const {
	return value;
}

KernelSem::KernelSem(int init)

{
	value=init;
	nasemu=new PCBSem(this);
		svisem->put(this);
	}
void KernelSem::incvalue()
{
	value++;
	}

KernelSem::~KernelSem()
{
	svisem->deletesem(this);
	delete nasemu;
	}

int KernelSem::wait(unsigned int maxTimeToWait)
{
	pomf::locki--;
	value-=1;
	if (value >= 0) {
		pomf::locki++;
		return 1;
	}

	PCB* p;
	p = (PCB*) PCB::running;
	 int t;
	if (maxTimeToWait==0) t=-1;
	else
		t = maxTimeToWait;
	nasemu->put(p,t);
	((PCB*) PCB::running)->status = PCB::BLOCKED;

	pomf::locki++;
	dispatch();

	if (((PCB*) PCB::running)->status == PCB::SIGNAL) {
		((PCB*) PCB::running)->status = PCB::READY;
		return 1;
	}
	return 0;

	}

void KernelSem::signal()
{
	pomf::locki--;

			if (++value <= 0) {
				PCB* help=nasemu->get();
				help->status = PCB::SIGNAL;
				Scheduler::put(help);
			}
			pomf::locki++;


	}
