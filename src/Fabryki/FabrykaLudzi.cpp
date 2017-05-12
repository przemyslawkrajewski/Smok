/*
 * FabrykaLudzi.cpp
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#include "FabrykaLudzi.h"

FabrykaLudzi* FabrykaLudzi::ptr=0;
KontenerPostaci<Strzelec>* FabrykaLudzi::strzelcy=0;
KontenerPostaci<Balista>* FabrykaLudzi::balisty=0;
KontenerPostaci<Kaplan>* FabrykaLudzi::kaplani=0;

FabrykaLudzi* FabrykaLudzi::zwrocInstancje()
{

	if(!ptr) ptr= new FabrykaLudzi();
	return ptr;
}

FabrykaLudzi::FabrykaLudzi()
{
	parametryLucznikaLv1.maxZycia=200;
	parametryLucznikaLv1.obrazenia=0;
	parametryLucznikaLv1.celnosc=3.14/32;
	parametryLucznikaLv1.predkoscStrzaly=35;
	parametryLucznikaLv1.maxNaciagniecie=10;
	parametryLucznikaLv1.maxCelowania=2;
	parametryLucznikaLv1.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznikaLv1.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznikaLv1.predkoscBiegu=9;
	parametryLucznikaLv1.czasTrwaniaStrzaly=300;
	parametryLucznikaLv1.spust=false;

	parametryLucznikaLv2.maxZycia=200;
	parametryLucznikaLv2.obrazenia=0;
	parametryLucznikaLv2.celnosc=3.14/32;
	parametryLucznikaLv2.predkoscStrzaly=35;
	parametryLucznikaLv2.maxNaciagniecie=10;
	parametryLucznikaLv2.maxCelowania=2;
	parametryLucznikaLv2.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznikaLv2.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznikaLv2.predkoscBiegu=9;
	parametryLucznikaLv2.czasTrwaniaStrzaly=300;
	parametryLucznikaLv2.spust=false;

	parametryLucznikaLv3.maxZycia=200;
	parametryLucznikaLv3.obrazenia=0;
	parametryLucznikaLv3.celnosc=3.14/32;
	parametryLucznikaLv3.predkoscStrzaly=35;
	parametryLucznikaLv3.maxNaciagniecie=10;
	parametryLucznikaLv3.maxCelowania=2;
	parametryLucznikaLv3.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznikaLv3.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznikaLv3.predkoscBiegu=9;
	parametryLucznikaLv3.czasTrwaniaStrzaly=300;
	parametryLucznikaLv3.spust=false;

	parametryLucznikaLv4.maxZycia=200;
	parametryLucznikaLv4.obrazenia=0;
	parametryLucznikaLv4.celnosc=3.14/32;
	parametryLucznikaLv4.predkoscStrzaly=35;
	parametryLucznikaLv4.maxNaciagniecie=10;
	parametryLucznikaLv4.maxCelowania=2;
	parametryLucznikaLv4.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznikaLv4.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznikaLv4.predkoscBiegu=9;
	parametryLucznikaLv4.czasTrwaniaStrzaly=300;
	parametryLucznikaLv4.spust=false;

	parametryRycerzaLv1.maxZycia=200;
	parametryRycerzaLv1.obrazenia=10;
	parametryRycerzaLv1.celnosc=0;
	parametryRycerzaLv1.czasTrwaniaStrzaly=100;
	parametryRycerzaLv1.predkoscStrzaly=35;
	parametryRycerzaLv1.maxNaciagniecie=60;
	parametryRycerzaLv1.maxCelowania=20;
	parametryRycerzaLv1.predkoscAnimacjiBiegu1=0.4;
	parametryRycerzaLv1.predkoscAnimacjiBiegu2=0.2;
	parametryRycerzaLv1.predkoscBiegu=3;
	parametryRycerzaLv1.spust=true;

	parametryRycerzaLv2.maxZycia=200;
	parametryRycerzaLv2.obrazenia=10;
	parametryRycerzaLv2.celnosc=0;
	parametryRycerzaLv2.czasTrwaniaStrzaly=100;
	parametryRycerzaLv2.predkoscStrzaly=35;
	parametryRycerzaLv2.maxNaciagniecie=60;
	parametryRycerzaLv2.maxCelowania=20;
	parametryRycerzaLv2.predkoscAnimacjiBiegu1=0.4;
	parametryRycerzaLv2.predkoscAnimacjiBiegu2=0.2;
	parametryRycerzaLv2.predkoscBiegu=3;
	parametryRycerzaLv2.spust=true;

	parametryRycerzaLv3.maxZycia=200;
	parametryRycerzaLv3.obrazenia=10;
	parametryRycerzaLv3.celnosc=0;
	parametryRycerzaLv3.czasTrwaniaStrzaly=100;
	parametryRycerzaLv3.predkoscStrzaly=35;
	parametryRycerzaLv3.maxNaciagniecie=60;
	parametryRycerzaLv3.maxCelowania=20;
	parametryRycerzaLv3.predkoscAnimacjiBiegu1=0.4;
	parametryRycerzaLv3.predkoscAnimacjiBiegu2=0.2;
	parametryRycerzaLv3.predkoscBiegu=3;
	parametryRycerzaLv3.spust=true;

	parametryBalistyLv1.maxZycia=10;
	parametryBalistyLv1.obrazenia=500;
	parametryBalistyLv1.obnizoneObrazenia=0;
	parametryBalistyLv1.rozrzut=3.14/16;
	parametryBalistyLv1.iloscPociskow=5;
	parametryBalistyLv1.predkoscStrzaly=100;
	parametryBalistyLv1.predkoscCelowania=0.004;
	parametryBalistyLv1.maxKatCelowania=1.29;
	parametryBalistyLv1.minKatCelowania=0.15;
	parametryBalistyLv1.maxNaciagania=300;

	parametryBalistyLv2.maxZycia=10;
	parametryBalistyLv2.obrazenia=500;
	parametryBalistyLv2.obnizoneObrazenia=0;
	parametryBalistyLv2.rozrzut=3.14/16;
	parametryBalistyLv2.iloscPociskow=5;
	parametryBalistyLv2.predkoscStrzaly=100;
	parametryBalistyLv2.predkoscCelowania=0.004;
	parametryBalistyLv2.maxKatCelowania=1.29;
	parametryBalistyLv2.minKatCelowania=0.15;
	parametryBalistyLv2.maxNaciagania=300;

	parametryKaplanaLv1.maxZycia=10;
	parametryKaplanaLv1.predkoscPocisku=15;
	parametryKaplanaLv1.czasRzucaniaKierowanegoPocisku=50;
	parametryKaplanaLv1.obrazeniaKierowanegoPocisku=5;
	parametryKaplanaLv1.czasTrwaniaPocisku=1000;
	parametryKaplanaLv1.czasRzucaniaKasetowegoPocisku=0;
	parametryKaplanaLv1.obrazeniaKasetowegoPocisku=5;
	parametryKaplanaLv1.czasRzucaniaPersonalnejTarczy=150;
	parametryKaplanaLv1.czasRzucaniaObszarowejTarczy=50;
	parametryKaplanaLv1.predkoscChodu=0.8;

	parametryKaplanaLv2.maxZycia=10;
	parametryKaplanaLv2.predkoscPocisku=15;
	parametryKaplanaLv2.czasRzucaniaKierowanegoPocisku=50;
	parametryKaplanaLv2.obrazeniaKierowanegoPocisku=5;
	parametryKaplanaLv2.czasTrwaniaPocisku=1000;
	parametryKaplanaLv2.czasRzucaniaKasetowegoPocisku=0;
	parametryKaplanaLv2.obrazeniaKasetowegoPocisku=5;
	parametryKaplanaLv2.czasRzucaniaPersonalnejTarczy=150;
	parametryKaplanaLv2.czasRzucaniaObszarowejTarczy=50;
	parametryKaplanaLv2.predkoscChodu=0.8;

	parametryKaplanaLv3.maxZycia=10;
	parametryKaplanaLv3.predkoscPocisku=15;
	parametryKaplanaLv3.czasRzucaniaKierowanegoPocisku=50;
	parametryKaplanaLv3.obrazeniaKierowanegoPocisku=5;
	parametryKaplanaLv3.czasTrwaniaPocisku=1000;
	parametryKaplanaLv3.czasRzucaniaKasetowegoPocisku=0;
	parametryKaplanaLv3.obrazeniaKasetowegoPocisku=5;
	parametryKaplanaLv3.czasRzucaniaPersonalnejTarczy=150;
	parametryKaplanaLv3.czasRzucaniaObszarowejTarczy=50;
	parametryKaplanaLv3.predkoscChodu=0.8;
}

FabrykaLudzi::~FabrykaLudzi()
{
	delete ptr;
}

void FabrykaLudzi::ustawKontenery(KontenerPostaci<Strzelec>* s, KontenerPostaci<Balista>* b, KontenerPostaci<Kaplan>* k)
{
	strzelcy=s;
	balisty=b;
	kaplani=k;
}

void FabrykaLudzi::stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja, bool zwroconyWPrawo)
{
	switch(typ)
	{
		case poborowyLucznik:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::lucznik);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryLucznikaLv1);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji(); //Taki myk ze dodaje nowego strzelca i od razu wyznacza jego przestrzen kolizji
																	//Nie mozna zrobic przez konstruktor bo wskaznik pokazuje na argument funkcji a nie obiekt w liscie
			break;
		}
		case zawodowyLucznik:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::lucznik);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryLucznikaLv2);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji();
			break;
		}
		case wyborowyLucznik:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::lucznik);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryLucznikaLv3);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji();
			break;
		}
		case skrytobojca:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::lucznik);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryLucznikaLv4);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji();
			break;
		}
		case rycerz:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::krzyzowiec);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryRycerzaLv1);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji();
			break;
		}
		case krzyzowiec:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::krzyzowiec);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryRycerzaLv2);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji();
			break;
		}
		case templariusz:
		{
			assert("Kontener 'Strzelcy' nie ustawiony" && strzelcy!=0);
			Strzelec strzelec;
			strzelec.ustawTypPostaci(Postac::krzyzowiec);
			strzelec.ustawPozycje(nPozycja);
			strzelec.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			strzelec.ustawParametry(parametryRycerzaLv3);
			(strzelcy->dodaj(strzelec))->wyznaczPrzestrzenKolizji();
			break;
		}
		case balista:
		{
			assert("Kontener 'Balisty' nie ustawiony" && balisty!=0);
			Balista balista;
			balista.ustawPozycje(nPozycja);
			balista.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			if(zwroconyWPrawo) balista.ustawKatCelowania(0.2);
			else balista.ustawKatCelowania(2.9);
			balista.ustawParametry(parametryBalistyLv1);
			(balisty->dodaj(balista))->wyznaczPrzestrzenKolizji();
			break;
		}
		case ulepszonaBalista:
		{
			assert("Kontener 'Balisty' nie ustawiony" && balisty!=0);
			Balista balista;
			balista.ustawPozycje(nPozycja);
			balista.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			if(zwroconyWPrawo) balista.ustawKatCelowania(0.2);
			else balista.ustawKatCelowania(2.9);
			balista.ustawParametry(parametryBalistyLv2);
			(balisty->dodaj(balista))->wyznaczPrzestrzenKolizji();
			break;
		}
		case mnich:
		{
			assert("Kontener 'Kaplani' nie ustawiony" && kaplani!=0);
			Kaplan kaplan;
			kaplan.ustawPozycje(nPozycja);
			kaplan.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			kaplan.ustawParametry(parametryKaplanaLv1);
			(kaplani->dodaj(kaplan))->wyznaczPrzestrzenKolizji();
			break;
		}
		case kaplan:
		{
			assert("Kontener 'Kaplani' nie ustawiony" && kaplani!=0);
			Kaplan kaplan;
			kaplan.ustawPozycje(nPozycja);
			kaplan.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			kaplan.ustawParametry(parametryKaplanaLv2);
			(kaplani->dodaj(kaplan))->wyznaczPrzestrzenKolizji();
			break;
		}
		case glowa:
		{
			assert("Kontener 'Kaplani' nie ustawiony" && kaplani!=0);
			Kaplan kaplan;
			kaplan.ustawPozycje(nPozycja);
			kaplan.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			kaplan.ustawParametry(parametryKaplanaLv3);
			(kaplani->dodaj(kaplan))->wyznaczPrzestrzenKolizji();
			break;
		}
		default:
			break;
	}
}
