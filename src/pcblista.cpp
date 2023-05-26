/*
 * pcblista.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */



#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include "pcblista.h"





	void PCBList::put(PCB* p)
	{
		if (head==0)
		{
			pom=new elem(p);
			head=pom;
			tail=pom;
			tail->sled=pom;
			head->sled=pom;
			size++;
			return;
		}
		pom=new elem(p);
		tail->sled=pom;
		tail=pom;
		size++;
		return;
	}
	PCB* PCBList::get()
	{
		if (head==0) return 0;
		pom=head;
		PCB* p=head->sadrzaj;
		head=head->sled;
		if (head==0) tail=0;
		size--;
		delete pom;
		return p;
	}
	 PCB* PCBList::getpcbid(int idn)
	{
		pom=head;
		PCB* pomp;
		if (pom==0) return 0;
		while (pom!=0)
		{
			pomp=pom->sadrzaj;
			if (pomp->id==idn) return pom->sadrzaj;
			pom=pom->sled;
		}
		return 0;
	}
	PCBList::~PCBList()
	{
		while (size>0)
		{
			size--;
			pom=head;
			head=head->sled;
			if (pom) delete pom;
		}
	}
	PCBList::PCBList()
	{
		head=0;
		tail=0;
		size=0;
		pom=0;
	}
	int PCBList::length()
	{return size;}






