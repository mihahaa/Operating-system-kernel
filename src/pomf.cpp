/*
 * pomf.cpp
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#include <dos.h>
#include <stdio.h>
#include "thread.h"
#include "pcb.h"
#include <IOSTREAM.H>
#include "pomf.h"
#include "bzvz.h"
#include "SCHEDULE.H"
#include "pcblista.h"
#include "kersem.h"
#include"semlist.h"

PCB* pomocni;
unsigned tsp,tss,tbp;
Thread* pomf::starting=0;
InterruptRoutine pomf::stara = 0;
bzvz* pomf::idle=0;
unsigned volatile pomf::counter=0;
volatile int pomf::demanded=0;
volatile int pomf::locki=1;
extern void tick();



void unload()
{
	pomf::raskloni();
}
void pomf::postavi()
{starting=new Thread();
starting->getpcb()->status=PCB::READY;
PCB::running=starting->getpcb();
idle= new bzvz();
idle->getpcb()->status=PCB::BUSYWAIT;

#ifndef BCC_BLOCK_IGNORE
asm cli
pomf::stara = getvect(0x08);
setvect(0x08, timerr);
setvect(0x60,stara);
asm sti
#endif
	}
void load()
{

	pomf::postavi();


	}
void pomf::_dispatch(){
	asm cli;
	demanded=1;
	timerr();
asm sti;
}

void pomf::raskloni()
{
	#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(0x08, stara);
	asm sti;

	delete starting;
	delete idle;
#endif
	}
void interrupt timerr(...)
{
	if (!pomf::demanded)
	{
		pomf::counter--;
		tick();
		asm int 60h;
		KernelSem::svisem->kucg();
	}
	if (pomf::demanded || (PCB::running->timeslice!=0 && pomf::counter<=0))
		{
		if (pomf::locki>0)
		{

		#ifndef BCC_BLOCK_IGNORE
					asm {
						mov tsp, sp
						mov tss, ss
						mov tbp, bp
					}
		#endif
					PCB::running->sp = tsp;
					PCB::running->ss = tss;
					PCB::running->bp = tbp;
					if(PCB::running->status == PCB::READY)
									{
										Scheduler::put((PCB*)PCB::running);
									}
										pomocni = Scheduler::get();
										if (pomocni == 0) {
											pomocni = pomf::idle->getpcb();
										}
					if (pomocni!=0)
					PCB::running = pomocni;
					else PCB::running=0;
					tsp = PCB::running->sp;
					tss = PCB::running->ss;
					tbp = PCB::running->bp;
		#ifndef BCC_BLOCK_IGNORE
					asm {
						mov sp, tsp
						mov ss, tss
						mov bp, tbp
					}
		#endif
					pomf::counter=((PCB*)PCB::running)->timeslice;
					pomf::demanded=0;
		}
		else pomf::demanded=1;
		}

		return;
	}



