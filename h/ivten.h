/*
 * ivten.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef IVTEN_H_
#define IVTEN_H_

typedef unsigned char IVTNo;
typedef void interrupt(*InterruptRoutine)(...);


#define PREPAREENTRY(numEntry, callOld)\
	void interrupt inter##numEntry(...);\
		IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
		void interrupt inter##numEntry(...) {\
			newEntry##numEntry.signal();\
			if (callOld == 1)\
			newEntry##numEntry.starica();\
	}

class KernelEv;




class IVTEntry

{
public:
	IVTEntry(IVTNo e, InterruptRoutine nr);
	~IVTEntry();
	void signal();
	static KernelEv** entries;
	KernelEv* mojkerev;
	InterruptRoutine starica;
	unsigned char ulaz ;
protected:
		friend class KernelEv;
private:
		int proveri();

	};


#endif /* IVTEN_H_ */
