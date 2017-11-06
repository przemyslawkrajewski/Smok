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
	Obiekt* cel;
public:
	KontenerPostaci();
	virtual ~KontenerPostaci();

	virtual void wyznaczKolejnyStan();
	void ustawCel(Obiekt *c) {cel=c;}

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
		i->zwrocPozycje();
		if(!i->czyIstnieje())
		{
			i=KontenerObiektow<T>::obiekty.erase(i);
			continue;
		}
		i->ustawCel(cel);

		std::pair<Klawiatura,Myszka> sterowanie;
		if(cel != 0) sterowanie = i->wyznaczSterowanie();
		i->wyznaczKolejnyStan(&sterowanie.first,&sterowanie.second);

		i++;
	}
}

#endif /* SRC_KONTENERY_KONTENERPOSTACI_H_ */
