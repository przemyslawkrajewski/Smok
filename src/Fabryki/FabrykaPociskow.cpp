/*
 * FabrykaPociskow.cpp
 *
 *  Created on: 12-02-2015
 *      Author: przemo
 */

#include "FabrykaPociskow.h"

FabrykaPociskow::FabrykaPociskow(Plomienie* nPlomienie,Strzaly* nStrzaly)
{
	plomienie = nPlomienie;
	strzaly = nStrzaly;
}

FabrykaPociskow::~FabrykaPociskow()
{

}

void FabrykaPociskow::stworzPocisk(TypPocisku typ,Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat)
{
	switch(typ)
	{
	case plomien:
		(plomienie->dodajPlomien(Plomien(nPozycja,nPredkosc,nczasTrwania,nKat)))->wyznaczPrzestrzenKolizji();
		break;
	case strzala:
		(strzaly->dodajStrzale(Strzala(nPozycja,nPredkosc,nczasTrwania,nKat)))->wyznaczPrzestrzenKolizji();
		break;
	case belt:
		strzaly->dodajStrzale(Strzala(nPozycja,nPredkosc,nczasTrwania,nKat));
		break;
	}
}
