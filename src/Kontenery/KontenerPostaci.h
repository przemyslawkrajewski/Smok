/*
 * Kontener.h
 *
 *  Created on: 11-02-2016
 *      Author: przemo
 */

#ifndef SRC_KONTENERY_KONTENERPOSTACI_H_
#define SRC_KONTENERY_KONTENERPOSTACI_H_

#include <list>
#include "KontenerObiektow.h"
#include "../Pociski/Pocisk.h"
#include "../Postacie/Postac.h"

template <class T>
class KontenerPostaci : public KontenerObiektow<T>
{
private:
	Punkt cel;
public:
	KontenerPostaci();
	virtual ~KontenerPostaci();

	virtual void wyznaczKolejnyStan();
	void ustawCel(Punkt c) {cel=c;}

	std::list<Postac*> zwrocObiekty();

private:
	void testujDziedziczenie() {T t = T();Postac *p = &t;}
};
//##################################################################################################################################
template <class T>
KontenerPostaci<T>::KontenerPostaci()
{
	testujDziedziczenie();
}

template <class T>
KontenerPostaci<T>::~KontenerPostaci()
{

}

template <class T>
void KontenerPostaci<T>::wyznaczKolejnyStan()
{
	for(typename std::list<T>::iterator i=KontenerObiektow<T>::obiekty.begin();i!=KontenerObiektow<T>::obiekty.end();)
	{
		i->ustawCel(cel);
		std::pair<Klawiatura,Myszka> sterowanie = i->wyznaczSterowanie();
		i->wyznaczKolejnyStan(&sterowanie.first,&sterowanie.second);

		if(!i->czyIstnieje())
		{
			i=KontenerObiektow<T>::obiekty.erase(i);
		}
		else i++;
	}
}

template <class T>
std::list<Postac*>  KontenerPostaci<T>::zwrocObiekty()
{
	std::list<Postac*> postac;

	for(typename std::list<T>::iterator i=KontenerObiektow<T>::obiekty.begin();i!=KontenerObiektow<T>::obiekty.end();i++)
	{
		postac.push_back(&(*i));
	}

	return postac;
}


#endif /* SRC_KONTENERY_KONTENERPOSTACI_H_ */
