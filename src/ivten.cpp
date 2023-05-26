/*
 * ivten.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include"kev.h"
#include"ivten.h"
#include<dos.h>
#include"pomf.h"

KernelEv** IVTEntry::entries=new KernelEv*[256] ;



IVTEntry::~IVTEntry(){
	pomf::locki--;
#ifndef BCC_BLOCK_IGNORE

	setvect(ulaz,starica);

#endif
	if (proveri()==1)
	entries[ulaz]=0;
	pomf::locki++;
	starica();
}

int IVTEntry::proveri()
{
	if (ulaz>=0 && ulaz<257) return 1;
	return 0;

	}

void IVTEntry::signal()
{
	if (proveri()==1)
	if (entries[ulaz])
		entries[ulaz]->signal();
	return;
	}


IVTEntry::IVTEntry(IVTNo e, InterruptRoutine nr)
{
pomf::locki--;
#ifndef BCC_BLOCK_IGNORE

		starica=getvect(e);
		setvect(e,nr);

	#endif
		pomf::locki++;
	ulaz=e;
	mojkerev=0;
	}


