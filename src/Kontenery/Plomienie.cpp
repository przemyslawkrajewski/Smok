/*
 * Plomienie.cpp
 *
 *  Created on: 12-02-2015
 *      Author: przemo
 */

#include "Plomienie.h"

Plomienie::Plomienie()
{
	istnieje=true;
}

Plomienie::~Plomienie()
{

}

void Plomienie::wyznaczKolejnyStan()
{
	//std::cout << plomienie.size() << "\n";
	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();)
	{
		i->wyznaczKolejnyStan();

		if(!i->czyIstnieje())
		{
			i=plomienie.erase(i);
		}
		else i++;
	}
}

void Plomienie::wyznaczKlatkeAnimacji()
{
	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();i++)
	{
		i->wyznaczKlatkeAnimacji();
	}
}

void Plomienie::wyznaczPrzestrzenKolizji()
{
	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();i++)
	{
		i->wyznaczPrzestrzenKolizji();
	}
}

std::list<Punkt> Plomienie::zwrocPozycje()
{
	std::list<Punkt> punkty;

	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();i++)
	{
		punkty.push_back((i->zwrocPozycje()));
	}

	return punkty;
}

std::list<Punkt> Plomienie::zwrocKlatkeAnimacji()
{
	std::list<Punkt> klatki;

	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();i++)
	{
		klatki.push_back((i->zwrocKlatkeAnimacji()));
	}

	return klatki;
}

Plomien* Plomienie::dodajPlomien(Plomien p)
{
	plomienie.push_back(p);
	return &(plomienie.back());
}

std::list< PrzestrzenKolizji > Plomienie::zwrocPrzestrzenKolizji()
{
	std::list<PrzestrzenKolizji> przestrzen;

	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();i++)
	{
		przestrzen.push_back(*(i->zwrocPrzestrzenKolizji()));
	}

	return przestrzen;
}

void Plomienie::sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt))
{
	for(std::list<Plomien>::iterator i=plomienie.begin();i!=plomienie.end();i++)
	{
		if(!(i->czyZniszczony()) && i->czyIstnieje())
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
