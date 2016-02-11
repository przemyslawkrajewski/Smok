/*
 * Strzaly.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Strzaly.h"

Strzaly::Strzaly()
{

}

void Strzaly::wyznaczKolejnyStan()
{
	//std::cout << "Strzaly: " << strzaly.size() << "\n";
	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();)
	{
		i->wyznaczKolejnyStan();

		if(!i->czyIstnieje())
		{
			i=strzaly.erase(i);
		}
		else i++;
	}
}

void Strzaly::wyznaczKlatkeAnimacji()
{
	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();i++)
	{
		i->wyznaczKlatkeAnimacji();
	}
}

void Strzaly::wyznaczPrzestrzenKolizji()
{
	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();i++)
	{
		i->wyznaczPrzestrzenKolizji();
	}
}

std::list<Punkt> Strzaly::zwrocPozycje()
{
	std::list<Punkt> punkty;

	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();i++)
	{
		punkty.push_back((i->zwrocPozycje()));
	}

	return punkty;
}

std::list<Punkt> Strzaly::zwrocKlatkeAnimacji()
{
	std::list<Punkt> klatki;

	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();i++)
	{
		klatki.push_back((i->zwrocKlatkeAnimacji()));
	}

	return klatki;
}

Strzala* Strzaly::dodajStrzale(Strzala p)
{
	strzaly.push_back(p);
	return &(strzaly.back());
}

std::list< PrzestrzenKolizji > Strzaly::zwrocPrzestrzenKolizji()
{
	std::list<PrzestrzenKolizji> przestrzen;

	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();i++)
	{
		przestrzen.push_back(*(i->zwrocPrzestrzenKolizji()));
	}

	return przestrzen;
}

void Strzaly::sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt))
{
	for(std::list<Strzala>::iterator i=strzaly.begin();i!=strzaly.end();i++)
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
