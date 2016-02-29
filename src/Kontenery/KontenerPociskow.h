/*
 * Kontener.h
 *
 *  Created on: 11-02-2016
 *      Author: przemo
 */

#ifndef SRC_KONTENERY_KONTENERPOCISKOW_H_
#define SRC_KONTENERY_KONTENERPOCISKOW_H_

#include <list>
#include "../Pociski/Pocisk.h"
#include "KontenerObiektow.h"

template <class T>
class KontenerPociskow : public KontenerObiektow<T>
{
private:

public:
	KontenerPociskow();
	virtual ~KontenerPociskow();

	virtual void wyznaczKolejnyStan();

	std::list<T> * zwrocObiekty() {return &(KontenerObiektow<T>::obiekty);}



private:
	void testujDziedziczenie() {T t = T(0,0,0,0,0,0);Pocisk *p = &t;}
};
//##################################################################################################################################
template <class T>
KontenerPociskow<T>::KontenerPociskow()
{
	testujDziedziczenie();
}

template <class T>
KontenerPociskow<T>::~KontenerPociskow()
{

}


template <class T>
void KontenerPociskow<T>::wyznaczKolejnyStan()
{
	for(typename std::list<T>::iterator i=KontenerObiektow<T>::obiekty.begin();i!=KontenerObiektow<T>::obiekty.end();)
	{
		i->wyznaczKolejnyStan();

		if(!i->czyIstnieje())
		{
			i=KontenerObiektow<T>::obiekty.erase(i);
		}
		else i++;
	}
}



#endif /* SRC_KONTENERY_KONTENERPOCISKOW_H_ */
