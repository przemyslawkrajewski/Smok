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
KontenerPrzedmiotow<TarczaPersonalna>* FabrykaPrzedmiotow::tarczePersonalne=0;
KontenerPrzedmiotow<TarczaObszarowa>* FabrykaPrzedmiotow::tarczeObszarowe=0;


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

void FabrykaPrzedmiotow::ustawKontenery(KontenerPrzedmiotow<Mur>* m, KontenerPrzedmiotow<Zaslona>* z, KontenerPrzedmiotow<TarczaPersonalna>* tp, KontenerPrzedmiotow<TarczaObszarowa>* to)
{
	zaslony=z;
	mury=m;
	tarczePersonalne=tp;
	tarczeObszarowe=to;
}

Obiekt* FabrykaPrzedmiotow::stworzPrzedmiot(TypPrzedmiotu typ, Punkt pozycja, Obiekt* cel)
{
	TarczaPersonalna* tp;
	TarczaObszarowa* to;
	switch(typ)
	{
	case sredniMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,180),Mur::mur,pozycja-Punkt(270,-30))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,180),Mur::mur,pozycja-Punkt(-270,-30))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(600,180),Mur::mur,pozycja)))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case jaskinia:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(2400,2400),Mur::czarneTlo,pozycja+Punkt(10,1290))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(2400,2400),Mur::skala,pozycja+Punkt(0,1500))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(2400,2400),Mur::skala,pozycja+Punkt(1800,1270))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,2400),Mur::szareTlo,pozycja+Punkt(600,1505))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case zaslona:
		assert("Kontener 'Zaslony' nie ustawiony" && zaslony!=0);
		(zaslony->dodaj(Zaslona(pozycja)))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case tarczaPersonalna:
		assert("Kontener 'TarczePersonalne' nie ustawione" && tarczePersonalne!=0);
		assert("Do stworzenia tarczy personalnej potrzebny jest cel" && cel!=0);
		tp=tarczePersonalne->dodaj(TarczaPersonalna(cel->zwrocPozycje()+Punkt(0,-5)));
		tp->wyznaczPrzestrzenKolizji();
		tp->ustawPunktZaczepu(cel);
		return tp;
		break;
	case tarczaObszarowa:
		assert("Kontener 'TarczeObszarowe' nie ustawione" && tarczeObszarowe!=0);
		to=tarczeObszarowe->dodaj(TarczaObszarowa(pozycja-Punkt(0,20)));
		to->wyznaczPrzestrzenKolizji();
		return to;
		break;
	}
}

