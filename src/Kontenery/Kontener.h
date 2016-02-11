/*
 * Kontener.h
 *
 *  Created on: 11-02-2016
 *      Author: przemo
 */

#ifndef SRC_KONTENERY_KONTENER_H_
#define SRC_KONTENERY_KONTENER_H_

#include <list>
#include "../Pociski/Pocisk.h"
#include "../Postacie/Postac.h"

template <class T>
class Kontener
{
private:
	std::list<T> obiekty;
	Punkt cel;
public:
	Kontener();
	virtual ~Kontener();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	void ustawCel(Punkt c);

	T* dodaj(T t);

	std::list< Punkt > zwrocPozycje();
	std::list< Punkt > zwrocKlatkeAnimacji();
	std::list< PrzestrzenKolizji > zwrocPrzestrzenKolizji();
	std::list< bool > czyZwroconyWPrawo();
	std::list<T> * zwrocObiekty() {return &obiekty;}

	void sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt));

};
//##################################################################################################################################
template <class T>
Kontener<T>::Kontener()
{

}

template <class T>
Kontener<T>::~Kontener()
{

}

template<class T>
void Kontener<T>::ustawCel(Punkt c)
{
	cel=c;
}

template <class T>
void Kontener<T>::wyznaczKolejnyStan()
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();)
	{
		wyznaczKolejnyStan(&(*i));

		if(!i->czyIstnieje())
		{
			i=obiekty.erase(i);
		}
		else i++;
	}
}

template <class T>
void Kontener<T>::wyznaczKlatkeAnimacji()
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		i->wyznaczKlatkeAnimacji();
	}
}
template <class T>
void Kontener<T>::wyznaczPrzestrzenKolizji()
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		i->wyznaczPrzestrzenKolizji();
	}
}

template <class T>
T* Kontener<T>::dodaj(T t)
{
	obiekty.push_back(t);
	return &(obiekty.back());
}

template <class T>
std::list< Punkt > Kontener<T>::zwrocPozycje()
{
	std::list<Punkt> punkty;

	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		punkty.push_back((i->zwrocPozycje()));
	}

	return punkty;
}

template <class T>
std::list< Punkt > Kontener<T>::zwrocKlatkeAnimacji()
{
	std::list<Punkt> klatki;

	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		klatki.push_back((i->zwrocKlatkeAnimacji()));
	}

	return klatki;
}

template <class T>
std::list< bool > Kontener<T>::czyZwroconyWPrawo()
{
	std::list<bool> prawo;

	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		prawo.push_back((i->czyZwroconyWPrawo()));
	}

	return prawo;
}

template <class T>
std::list< PrzestrzenKolizji > Kontener<T>::zwrocPrzestrzenKolizji()
{
	std::list<PrzestrzenKolizji> przestrzen;

	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		przestrzen.push_back(*(i->zwrocPrzestrzenKolizji()));
	}

	return przestrzen;
}

template <class T>
void Kontener<T>::sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt))
{
	for(typename std::list<T>::iterator i=obiekty.begin();i!=obiekty.end();i++)
	{
		if(!i->czyZniszczony() && i->czyIstnieje())
		{
			std::pair<bool,Punkt> kolizja = i->sprawdzKolizje(obiekt);
			if(kolizja.first)
			{
				obsluzKolizjePocisku(&(*i),obiekt,kolizja.second);
				obsluzKolizjeObiektu(obiekt,&(*i),kolizja.second);
			}
		}
	}
}

#endif /* SRC_KONTENERY_KONTENER_H_ */
