/*
 * FabrykaPociskow.cpp
 *
 *  Created on: 12-02-2015
 *      Author: przemo
 */

#include "FabrykaPociskow.h"

FabrykaPociskow* FabrykaPociskow::ptr=0;
KontenerPociskow<Plomien>* FabrykaPociskow::plomienie=0;
KontenerPociskow<Strzala>* FabrykaPociskow::strzaly=0;

FabrykaPociskow* FabrykaPociskow::zwrocInstancje()
{
	if(!ptr) ptr= new FabrykaPociskow();
	return ptr;
}

FabrykaPociskow::FabrykaPociskow()
{
}

FabrykaPociskow::~FabrykaPociskow()
{
	delete ptr;
}

void FabrykaPociskow::ustawKontenery(KontenerPociskow<Plomien>* p,KontenerPociskow<Strzala>* s)
{
	strzaly=s;
	plomienie=p;
}

void FabrykaPociskow::stworzPocisk(TypPocisku typ,Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat)
{
	switch(typ)
	{
	case plomien:
		assert("Kontener Plomienie nie ustawiony" && plomienie!=0);
		(plomienie->dodaj(Plomien(nPozycja,nPredkosc,nczasTrwania,nKat)))->wyznaczPrzestrzenKolizji();
		break;
	case strzala:
		assert("Kontener Strzaly nie ustawiony" && strzaly!=0);
		(strzaly->dodaj(Strzala(nPozycja,nPredkosc,nczasTrwania,nKat)))->wyznaczPrzestrzenKolizji();
		break;
	case belt:
		assert("Kontener Strzaly nie ustawiony" && strzaly!=0);
		strzaly->dodaj(Strzala(nPozycja,nPredkosc,nczasTrwania,nKat));
		break;
	}
}
