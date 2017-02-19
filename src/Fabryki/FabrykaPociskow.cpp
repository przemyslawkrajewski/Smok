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
KontenerPociskow<Belt>* FabrykaPociskow::belty=0;
KontenerPociskow<PociskBalistyczny>* FabrykaPociskow::pociskiBalistyczne=0;

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

void FabrykaPociskow::ustawKontenery(KontenerPociskow<Plomien>* p,KontenerPociskow<Strzala>* s, KontenerPociskow<Belt>* b, KontenerPociskow<PociskBalistyczny> *pb)
{
	strzaly=s;
	plomienie=p;
	belty=b;
	pociskiBalistyczne=pb;
}

void FabrykaPociskow::stworzPocisk(TypPocisku typ,Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat, double obrazenia)
{
	Plomien *p;
	Strzala *s;
	Belt *b;
	PociskBalistyczny *pb;
	switch(typ)
	{
	case plomien:
		assert("Kontener 'Plomienie' nie ustawiony" && plomienie!=0);
		p = plomienie->dodaj(Plomien(nPozycja,nPredkosc,nczasTrwania,nKat));
		p->wyznaczPrzestrzenKolizji();
		p->ustawObrazenia(obrazenia);
		break;
	case strzala:
		assert("Kontener 'Strzaly' nie ustawiony" && strzaly!=0);
		s = strzaly->dodaj(Strzala(nPozycja,nPredkosc,nczasTrwania,nKat));
		s->wyznaczPrzestrzenKolizji();
		s->ustawObrazenia(obrazenia);
		break;
	case cichaStrzala:
		assert("Kontener 'Strzaly' nie ustawiony" && belty!=0);
		s = (strzaly->dodaj(Strzala(nPozycja,nPredkosc,nczasTrwania,nKat)));
		s->wyznaczPrzestrzenKolizji();
		s->ustawCzyCicha(true);
		break;
	case belt:
		assert("Kontener 'Belty' nie ustawiony" && belty!=0);
		b = belty->dodaj(Belt(nPozycja,nPredkosc,nczasTrwania,nKat));
		b->wyznaczPrzestrzenKolizji();
		b->ustawObrazenia(obrazenia);
		break;
	case pociskBalistyczny:
    	assert("Kontener 'PociskiBalistyczne' nie ustawiony" && belty!=0);
    	pb = pociskiBalistyczne->dodaj(PociskBalistyczny(nPozycja,nPredkosc,nczasTrwania,nKat));
    	pb->wyznaczPrzestrzenKolizji();
    	pb->ustawObrazenia(obrazenia);
    	break;
	}
}
