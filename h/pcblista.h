/*
 * pcblista.h
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#ifndef PCBLISTA_H_
#define PCBLISTA_H_


#include"thread.h"

class PCB;

class PCBList{
private:
	struct elem {
				public:
					PCB *sadrzaj;
					elem *sled;
					elem(PCB* p)
					{
						sadrzaj=p;
						sled=0;
					}
				};
public:
	void put(PCB* p);
	PCB* get();
	~PCBList();
	PCBList();
	int length();
	PCB* getpcbid(int idn);
	elem *head;
	elem *tail;
	elem *pom;
	int size;





};
#endif /* PCBLISTA_H_ */
