/*
 * FabrykaLudzi.cpp
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#include "FabrykaLudzi.h"

FabrykaLudzi::FabrykaLudzi(FabrykaPociskow* nFabrykaPociskow,Strzelcy* nStrzelcy)
{
	fabrykaPociskow=nFabrykaPociskow;
	strzelcy=nStrzelcy;
}

void FabrykaLudzi::stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja)
{
	switch(typ)
	{
	case krzyzowiec:
	{
		Strzelec strzelec;
		strzelec.ustawFabrykePociskow(fabrykaPociskow);
		strzelec.ustawPozycje(nPozycja);
		(strzelcy->dodajStrzelca(strzelec))->wyznaczPrzestrzenKolizji(); //Taki myk ze dodaje nowego strzelca i od razu wyznacza jego przestrzen kolizji
		break;
	}
	default:
		break;
	}
}
