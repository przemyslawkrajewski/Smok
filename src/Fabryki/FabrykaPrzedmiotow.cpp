/*
 * FabrykaPrzedmiotow.cpp
 *
 *  Created on: 24-04-2016
 *      Author: przemo
 */

#include "FabrykaPrzedmiotow.h"

FabrykaPrzedmiotow* FabrykaPrzedmiotow::ptr=0;
KontenerPrzedmiotow<Mur>* FabrykaPrzedmiotow::mury=0;
KontenerPrzedmiotow<Zaslona>* FabrykaPrzedmiotow::zaslony=0;


FabrykaPrzedmiotow* FabrykaPrzedmiotow::zwrocInstancje()
{
	if(!ptr) ptr= new FabrykaPrzedmiotow();
	return ptr;
}

FabrykaPrzedmiotow::FabrykaPrzedmiotow()
{
}

FabrykaPrzedmiotow::~FabrykaPrzedmiotow()
{
	delete ptr;
}

void FabrykaPrzedmiotow::ustawKontenery(KontenerPrzedmiotow<Mur>* m, KontenerPrzedmiotow<Zaslona>* z)
{
	zaslony=z;
	mury=m;
}

void FabrykaPrzedmiotow::stworzPrzedmiot(TypPrzedmiotu typ, Punkt pozycja)
{
	switch(typ)
	{
	case sredniMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Mur::sredni,pozycja)))->wyznaczPrzestrzenKolizji();
		break;
	case duzyMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Mur::duzy,pozycja)))->wyznaczPrzestrzenKolizji();
		break;
	case zaslona:
		assert("Kontener 'Mury' nie ustawiony" && zaslony!=0);
		(zaslony->dodaj(Zaslona(pozycja)))->wyznaczPrzestrzenKolizji();
	}
}

