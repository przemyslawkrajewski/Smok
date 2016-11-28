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

	parametryLucznika.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznika.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznika.iloscKlatekAnimacjiBiegu = 8;
	parametryLucznika.predkoscBiegu=9;
	parametryLucznika.czasTrwaniaStrzaly=200;
	parametryLucznika.minimalnaOdleglosc=10;
	parametryLucznika.spust=false;
	parametryLucznika.predkoscStrzaly=35;
	parametryLucznika.celnosc=3.14/16;
	parametryLucznika.maxNaciagniecie=30;
	parametryLucznika.maxCelowania=30;
	parametryLucznika.maxZycia=200;

	parametryKrzyzowca.predkoscAnimacjiBiegu1=0.4;
	parametryKrzyzowca.predkoscAnimacjiBiegu2=0.2;
	parametryKrzyzowca.iloscKlatekAnimacjiBiegu = 8;
	parametryKrzyzowca.predkoscBiegu=3;
	parametryKrzyzowca.czasTrwaniaStrzaly=100;
	parametryKrzyzowca.minimalnaOdleglosc=10;
	parametryKrzyzowca.spust=true;
	parametryKrzyzowca.predkoscStrzaly=35;
	parametryKrzyzowca.celnosc=0;
	parametryKrzyzowca.maxNaciagniecie=60;
	parametryKrzyzowca.maxCelowania=20;
	parametryKrzyzowca.maxZycia=200;

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
		assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
		Strzelec strzelec;
		strzelec.ustawTypPostaci(Postac::krzyzowiec);
		strzelec.ustawPozycje(nPozycja);
		strzelec.ustawParametry(parametryKrzyzowca);
		(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji(); //Taki myk ze dodaje nowego strzelca i od razu wyznacza jego przestrzen kolizji
																//Nie mozna zrobic przez konstruktor bo wskaznik pokazuje na argument funkcji a nie obiekt w liscie
		break;
	}
	case lucznik:
	{
		assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
		Strzelec strzelec;
		strzelec.ustawTypPostaci(Postac::lucznik);
		strzelec.ustawPozycje(nPozycja);
		strzelec.ustawParametry(parametryLucznika);
		(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji(); //Taki myk ze dodaje nowego strzelca i od razu wyznacza jego przestrzen kolizji
																//Nie mozna zrobic przez konstruktor bo wskaznik pokazuje na argument funkcji a nie obiekt w liscie
		break;
	}
	default:
		break;
	}
}
