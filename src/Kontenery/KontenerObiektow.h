/*
 * Kontener.h
 *
 *  Created on: 12-02-2016
 *      Author: przemo
 */

#ifndef SRC_KONTENERY_KONTENEROBIEKTOW_H_
#define SRC_KONTENERY_KONTENEROBIEKTOW_H_

#include "../Obiekty/Obiekt.h"

template <class T>
class KontenerObiektow
{
public:
	std::list<T> obiekty;
public:
	KontenerObiektow();
	virtual ~KontenerObiektow();

	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	bool czyPusty() {return obiekty.size()==0;}
	void wyczysc() {obiekty.clear();}

	T* dodaj(T t);

	std::list<T> * zwrocObiekty() {return &obiekty;}

	void sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt),PrzestrzenKolizji::TypFigury typ,bool czyTezZniszczone=false);

private:
};
//##################################################################################################################################
template <class T>
KontenerObiektow<T>::KontenerObiektow()
{
}

template <class T>
KontenerObiektow<T>::~KontenerObiektow()
{

}

template <class T>
void KontenerObiektow<T>::wyznaczKlatkeAnimacji()
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		i->wyznaczKlatkeAnimacji();
	}
}
template <class T>
void KontenerObiektow<T>::wyznaczPrzestrzenKolizji()
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		i->wyznaczPrzestrzenKolizji();
	}
}

template <class T>
T* KontenerObiektow<T>::dodaj(T t)
{
	obiekty.push_back(t);
	return &(obiekty.back());
}

template <class T>
void KontenerObiektow<T>::sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt),PrzestrzenKolizji::TypFigury typ,bool czyTezZniszczone)
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		if((!i->czyZniszczony() || czyTezZniszczone)  && i->czyIstnieje())
		{
			std::pair<bool,Punkt> kolizja = i->sprawdzKolizje(obiekt,typ);
			if(kolizja.first)
			{
				obsluzKolizjePocisku(&(*i),obiekt,kolizja.second);
				obsluzKolizjeObiektu(obiekt,&(*i),kolizja.second);
			}
		}
	}
}


#endif /* SRC_KONTENERY_KONTENEROBIEKTOW_H_ */
