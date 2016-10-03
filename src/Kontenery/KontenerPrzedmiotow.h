/*
 * KontenerPrzedmiotow.h
 *
 *  Created on: 24-04-2016
 *      Author: przemo
 */

#ifndef SRC_KONTENERY_KONTENERPRZEDMIOTOW_H_
#define SRC_KONTENERY_KONTENERPRZEDMIOTOW_H_


#include <list>
#include "KontenerObiektow.h"
#include "../Przedmioty/Przedmiot.h"

template <class T>
class KontenerPrzedmiotow : public KontenerObiektow<T>
{
private:

public:
	KontenerPrzedmiotow();
	virtual ~KontenerPrzedmiotow();

	virtual void wyznaczKolejnyStan();

private:
	void testujDziedziczenie() {T t = T(Punkt());Przedmiot *p = &t;}
};
//##################################################################################################################################
template <class T>
KontenerPrzedmiotow<T>::KontenerPrzedmiotow()
{
	testujDziedziczenie();
}

template <class T>
KontenerPrzedmiotow<T>::~KontenerPrzedmiotow()
{

}

template <class T>
void KontenerPrzedmiotow<T>::wyznaczKolejnyStan()
{
	for(typename std::list<T>::iterator i=KontenerObiektow<T>::obiekty.begin();i!=KontenerObiektow<T>::obiekty.end();)
	{
		i->zwrocPozycje();
		if(!i->czyIstnieje())
		{
			i=KontenerObiektow<T>::obiekty.erase(i);
			continue;
		}

		i->wyznaczKolejnyStan();
		i++;

	}
}

#endif /* SRC_KONTENERY_KONTENERPRZEDMIOTOW_H_ */
