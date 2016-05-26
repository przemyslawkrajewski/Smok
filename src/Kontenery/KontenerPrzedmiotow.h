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

#endif /* SRC_KONTENERY_KONTENERPRZEDMIOTOW_H_ */
