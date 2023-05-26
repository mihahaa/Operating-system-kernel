/*
 * semlist.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include"semlist.h"
#include"kersem.h"
#include"pcbsem.h"
#include"iostream.h"


void SemList::put(KernelSem* p)
	{
		if (head==0)
		{
			pom=new elem(p);
			head=pom;
			tail=pom;
			tail->sled=0;
			head->sled=0;
			size++;
			return;
		}
		pom=new elem(p);
		tail->sled=pom;
		tail=pom;
		size++;
		return;
	}
	void SemList::deletesem(KernelSem* p)
	{
		if (head==0) {tail=0;return;}
		elem* pret;
		pret=head;
		pom=head;
		while (pom && pom->sadrzaj!=p)
		{
			pret=pom;
			pom=pom->sled;
		}
		if (pom==0) return;
		if (pom==head)
		{
			head=head->sled;
			size--;
			delete pom;
			return;
		}
		if (pom==tail)
		{
			tail=pret;
			tail->sled=0;
			size--;
			delete pom;
			return;
		}
		pret->sled=pom->sled;
		size--;
		delete pom;
		return;
	}
	SemList::~SemList()
	{
		while (size>0)
		{
			size--;
			pom=head;
			head=head->sled;
			if (pom) delete pom;
		}
	}
	SemList::SemList()
	{
		head=0;
		tail=0;
		size=0;
		pom=0;
	}
	int SemList::length()
	{return size;}

void SemList::kucg()
{
	if (head==0) return;
	pom=head;
	while (pom!=0)
	{
		pom->sadrzaj->nasemu->kucl();
		pom=pom->sled;
	}
	return;
	}
