/*
 * PCBSem.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef PCBSEM_H_
#define PCBSEM_H_

class PCB;
class KernelSem;


class PCBSem{
private:
	struct elem {
				public:
					PCB *sadrzaj;
					 int vreme;
					elem *sled;
					elem(PCB* p, int v)
					{
						sadrzaj=p;
						sled=0;
						vreme=v;
					}
				};
public:
	void put(PCB* p, int v);
	PCB* get();
	~PCBSem();
	PCBSem(KernelSem* mk);
	int length();
	elem *head;
	elem *tail;
	elem *pom;
	int size;
	void kucl();
	KernelSem* mojker;

};



#endif /* PCBSEM_H_ */
