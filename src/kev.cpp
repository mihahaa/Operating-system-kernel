/*
 * kev.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include"kev.h"
#include"pcb.h"
#include"ivten.h"
#include"SCHEDULE.h"
#include"pomf.h"

KernelEv::~KernelEv()
	{
		sem=0;
		IVTEntry::entries[bru]=0;
	}
KernelEv::KernelEv(IVTNo i)
{
	moja=(PCB*)PCB::running;
	sem=new elem();
	bru=i;
	IVTEntry::entries[i]=this;
	}
void KernelEv::signal()
{
	int f;
	f=0;
	if (sem->vr) return;
	if (!sem->ima) {f=1;sem->vr=1;}
if(!f){
	moja->status=PCB::READY;
	sem->ima=0;
	Scheduler::put(moja);
}
	}
void KernelEv::wait()
{
	int f;
	f=0;
	if (!sem->vr) f=1;
	else sem->vr=0;
	if(PCB::running==moja){
			if(f) {
				PCB::running->status=PCB::BLOCKED;
				sem->ima=1;
				dispatch();
			}
	}
}
