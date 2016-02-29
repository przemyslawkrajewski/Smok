/*
 * FabrykaLudzi.cpp
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#include "FabrykaLudzi.h"

FabrykaLudzi* FabrykaLudzi::ptr=0;
 KontenerPostaci<Strzelec>* FabrykaLudzi::strzelcy=0;

FabrykaLudzi* FabrykaLudzi::zwrocInstancje()
{

	if(!ptr) ptr= new FabrykaLudzi();
	return ptr;
}

FabrykaLudzi::FabrykaLudzi()
{

}

FabrykaLudzi::~FabrykaLudzi()
{
	delete ptr;
}

void FabrykaLudzi::ustawKontenery(KontenerPostaci<Strzelec>* s)
{
	strzelcy=s;
}

void FabrykaLudzi::stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja)
{
	switch(typ)
	{
	case krzyzowiec:
	{
		assert("Kontener Strzelcy nie ustawiony" && strzelcy!=0);
		Strzelec strzelec;
		strzelec.ustawPozycje(nPozycja);
		(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji(); //Taki myk ze dodaje nowego strzelca i od razu wyznacza jego przestrzen kolizji
		break;
	}
	default:
		break;
	}
}
