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
	Zaslona* z;
	switch(typ)
	{
	case jaskinia:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(2400,2400),Mur::czarneTlo,pozycja+Punkt(10,1290))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(2400,2400),Mur::skala,pozycja+Punkt(0,1500))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(2400,2400),Mur::skala,pozycja+Punkt(1800,1270))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,2400),Mur::szareTlo,pozycja+Punkt(600,1505))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case bmalyMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja+Punkt(420,260))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja+Punkt(-420,260))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(900,120),Mur::mur,pozycja+Punkt(0,200))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case malyMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja+Punkt(1020,380))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja+Punkt(-1020,380))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(2100,300),Mur::mur,pozycja+Punkt(0,230))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case sredniMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja+Punkt(1170,570))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja+Punkt(-1170,570))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(2400,480),Mur::mur,pozycja+Punkt(0,330))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case bduzyMur:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(1800,12000),Mur::mur,pozycja+Punkt(0,6080))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case bwysokaWieza:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(600,12000),Mur::mur,pozycja+Punkt(0,6080))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case wysokaWieza:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja-Punkt(270,-3080))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja-Punkt(-270,-3080))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(600,3000),Mur::mur,pozycja+Punkt(0,1580))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case sredniaWieza:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja-Punkt(240,-1580))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja-Punkt(-240,-1580))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(540,1500),Mur::mur,pozycja+Punkt(0,830))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case niskaWieza:
		assert("Kontener 'Mury' nie ustawiony" && mury!=0);
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja-Punkt(240,-800))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(60,120),Mur::mur,pozycja-Punkt(-240,-800))))->wyznaczPrzestrzenKolizji();
		(mury->dodaj(Mur(Wymiary(540,720),Mur::mur,pozycja+Punkt(0,440))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case zaslona:
		assert("Kontener 'Zaslony' nie ustawiony" && zaslony!=0);
		(zaslony->dodaj(Zaslona(pozycja+Punkt(0,170))))->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case ulZaslona:
		assert("Kontener 'Zaslony' nie ustawiony" && zaslony!=0);
		z=zaslony->dodaj(Zaslona(pozycja+Punkt(0,170)));
		z->ulepsz();
		z->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case martwySmok:
		assert("Kontener 'Zaslony' nie ustawiony" && zaslony!=0);
		z=zaslony->dodaj(Zaslona(pozycja+Punkt(-130,120)));
		z->oznaczJakoOzdobe(2);
		z->wyznaczPrzestrzenKolizji();
		z=zaslony->dodaj(Zaslona(pozycja+Punkt(130,120)));
		z->oznaczJakoOzdobe(3);
		z->wyznaczPrzestrzenKolizji();
		return 0;
		break;
	case tarczaPersonalna:
		assert("Kontener 'TarczePersonalne' nie ustawione" && tarczePersonalne!=0);
		assert("Do stworzenia tarczy personalnej potrzebny jest cel" && cel!=0);
		tp=tarczePersonalne->dodaj(TarczaPersonalna(cel->zwrocPozycje()+Punkt(0,-5)));
		tp->wyznaczPrzestrzenKolizji();
		tp->ustawPunktZaczepu(cel);
		cel->ustawCzyPosiadaTarcze(true);
		return tp;
		break;
	case tarczaPersonalnaRegen:
		assert("Kontener 'TarczePersonalne' nie ustawione" && tarczePersonalne!=0);
		assert("Do stworzenia tarczy personalnej potrzebny jest cel" && cel!=0);
		tp=tarczePersonalne->dodaj(TarczaPersonalna(cel->zwrocPozycje()+Punkt(0,-5)));
		tp->wyznaczPrzestrzenKolizji();
		tp->ustawPunktZaczepu(cel);
		tp->ustawPredkoscOdnawiania(0.01);
		cel->ustawCzyPosiadaTarcze(true);
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

