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
	parametryLucznikaLv1.maxZycia=75;
	parametryLucznikaLv1.obrazenia=5;
	parametryLucznikaLv1.celnosc=3.14/8;
	parametryLucznikaLv1.predkoscStrzaly=30;
	parametryLucznikaLv1.maxNaciagniecie=35;
	parametryLucznikaLv1.maxCelowania=70;
	parametryLucznikaLv1.predkoscAnimacjiBiegu1=0.25;
	parametryLucznikaLv1.predkoscAnimacjiBiegu2=0.20;
	parametryLucznikaLv1.predkoscBiegu=3;
	parametryLucznikaLv1.czasTrwaniaStrzaly=300;
	parametryLucznikaLv1.spust=false;

	parametryLucznikaLv2.maxZycia=75;
	parametryLucznikaLv2.obrazenia=5;
	parametryLucznikaLv2.celnosc=3.14/16;
	parametryLucznikaLv2.predkoscStrzaly=30;
	parametryLucznikaLv2.maxNaciagniecie=25;
	parametryLucznikaLv2.maxCelowania=60;
	parametryLucznikaLv2.predkoscAnimacjiBiegu1=0.3;//0.5
	parametryLucznikaLv2.predkoscAnimacjiBiegu2=0.20;//0.3
	parametryLucznikaLv2.predkoscBiegu=5;
	parametryLucznikaLv2.czasTrwaniaStrzaly=300;
	parametryLucznikaLv2.spust=false;

	parametryLucznikaLv3.maxZycia=200;
	parametryLucznikaLv3.obrazenia=8;
	parametryLucznikaLv3.celnosc=3.14/64;
	parametryLucznikaLv3.predkoscStrzaly=60;
	parametryLucznikaLv3.maxNaciagniecie=25;
	parametryLucznikaLv3.maxCelowania=60;
	parametryLucznikaLv3.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznikaLv3.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznikaLv3.predkoscBiegu=9;
	parametryLucznikaLv3.czasTrwaniaStrzaly=300;
	parametryLucznikaLv3.spust=false;

	parametryLucznikaLv4.maxZycia=1500;
	parametryLucznikaLv4.obrazenia=50;
	parametryLucznikaLv4.celnosc=0;
	parametryLucznikaLv4.predkoscStrzaly=55;
	parametryLucznikaLv4.maxNaciagniecie=12;
	parametryLucznikaLv4.maxCelowania=12;
	parametryLucznikaLv4.predkoscAnimacjiBiegu1=0.5;//0.5
	parametryLucznikaLv4.predkoscAnimacjiBiegu2=0.30;//0.3
	parametryLucznikaLv4.predkoscBiegu=16;
	parametryLucznikaLv4.czasTrwaniaStrzaly=300;
	parametryLucznikaLv4.spust=false;

	parametryRycerzaLv1.maxZycia=200;
	parametryRycerzaLv1.obrazenia=12;
	parametryRycerzaLv1.celnosc=3.14/32;
	parametryRycerzaLv1.czasTrwaniaStrzaly=200;
	parametryRycerzaLv1.predkoscStrzaly=37;
	parametryRycerzaLv1.maxNaciagniecie=60;
	parametryRycerzaLv1.maxCelowania=20;
	parametryRycerzaLv1.predkoscAnimacjiBiegu1=0.4;
	parametryRycerzaLv1.predkoscAnimacjiBiegu2=0.2;
	parametryRycerzaLv1.predkoscBiegu=3;
	parametryRycerzaLv1.spust=true;

	parametryRycerzaLv2.maxZycia=350;
	parametryRycerzaLv2.obrazenia=20;
	parametryRycerzaLv2.celnosc=3.14/64;
	parametryRycerzaLv2.czasTrwaniaStrzaly=300;
	parametryRycerzaLv2.predkoscStrzaly=42;
	parametryRycerzaLv2.maxNaciagniecie=60;
	parametryRycerzaLv2.maxCelowania=20;
	parametryRycerzaLv2.predkoscAnimacjiBiegu1=0.4;
	parametryRycerzaLv2.predkoscAnimacjiBiegu2=0.2;
	parametryRycerzaLv2.predkoscBiegu=3;
	parametryRycerzaLv2.spust=true;
	parametryRycerzaLv2.obrazeniaSwietejStrzaly=60;
	parametryRycerzaLv2.czasOdnawianiaSwietejStrzaly=250;

	parametryRycerzaLv3.maxZycia=500;
	parametryRycerzaLv3.obrazenia=25;
	parametryRycerzaLv3.celnosc=0;
	parametryRycerzaLv3.czasTrwaniaStrzaly=400;
	parametryRycerzaLv3.predkoscStrzaly=47;
	parametryRycerzaLv3.maxNaciagniecie=65;
	parametryRycerzaLv3.maxCelowania=20;
	parametryRycerzaLv3.predkoscAnimacjiBiegu1=0.4;
	parametryRycerzaLv3.predkoscAnimacjiBiegu2=0.2;
	parametryRycerzaLv3.predkoscBiegu=3;
	parametryRycerzaLv3.spust=true;
	parametryRycerzaLv3.obrazeniaSwietejStrzaly=50;
	parametryRycerzaLv3.czasOdnawianiaSwietejStrzaly=250;

	parametryBalistyLv1.maxZycia=2000;
	parametryBalistyLv1.obrazenia=1000;
	parametryBalistyLv1.obnizoneObrazenia=0;
	parametryBalistyLv1.rozrzut=3.14/16;
	parametryBalistyLv1.iloscPociskow=5;
	parametryBalistyLv1.predkoscStrzaly=75;
	parametryBalistyLv1.predkoscCelowania=0.020;
	parametryBalistyLv1.maxKatCelowania=1.29;
	parametryBalistyLv1.minKatCelowania=0.15;
	parametryBalistyLv1.maxNaciagania=200;

	parametryBalistyLv2.maxZycia=10;
	parametryBalistyLv2.obrazenia=500;
	parametryBalistyLv2.obnizoneObrazenia=0;
	parametryBalistyLv2.rozrzut=3.14/16;
	parametryBalistyLv2.iloscPociskow=5;
	parametryBalistyLv2.predkoscStrzaly=60;
	parametryBalistyLv2.predkoscCelowania=0.004;
	parametryBalistyLv2.maxKatCelowania=1.29;
	parametryBalistyLv2.minKatCelowania=0.15;
	parametryBalistyLv2.maxNaciagania=300;

	parametryKaplanaLv1.maxZycia=200;
	parametryKaplanaLv1.predkoscPocisku=15;
	parametryKaplanaLv1.czasRzucaniaKierowanegoPocisku=50;
	parametryKaplanaLv1.obrazeniaKierowanegoPocisku=15;
	parametryKaplanaLv1.czasTrwaniaPocisku=200;
	parametryKaplanaLv1.czasRzucaniaKasetowegoPocisku=0;
	parametryKaplanaLv1.obrazeniaKasetowegoPocisku=0;
	parametryKaplanaLv1.czasRzucaniaPersonalnejTarczy=400;
	parametryKaplanaLv1.czasRzucaniaObszarowejTarczy=50;
	parametryKaplanaLv1.predkoscChodu=0.8;

	parametryKaplanaLv2.maxZycia=250;
	parametryKaplanaLv2.predkoscPocisku=15;
	parametryKaplanaLv2.czasRzucaniaKierowanegoPocisku=50;
	parametryKaplanaLv2.obrazeniaKierowanegoPocisku=20;
	parametryKaplanaLv2.czasTrwaniaPocisku=200;
	parametryKaplanaLv2.czasRzucaniaKasetowegoPocisku=150;
	parametryKaplanaLv2.obrazeniaKasetowegoPocisku=5;
	parametryKaplanaLv2.czasRzucaniaPersonalnejTarczy=400;
	parametryKaplanaLv2.czasRzucaniaObszarowejTarczy=50;
	parametryKaplanaLv2.predkoscChodu=0.8;

	parametryKaplanaLv3.maxZycia=2000;
	parametryKaplanaLv3.predkoscPocisku=25;
	parametryKaplanaLv3.czasRzucaniaKierowanegoPocisku=20;
	parametryKaplanaLv3.obrazeniaKierowanegoPocisku=60;
	parametryKaplanaLv3.czasTrwaniaPocisku=200;
	parametryKaplanaLv3.czasRzucaniaKasetowegoPocisku=30;
	parametryKaplanaLv3.obrazeniaKasetowegoPocisku=8;
	parametryKaplanaLv3.czasRzucaniaPersonalnejTarczy=10;
	parametryKaplanaLv3.czasRzucaniaObszarowejTarczy=20;
	parametryKaplanaLv3.czasRzucaniaSeriiPociskow=100;
	parametryKaplanaLv3.obrazeniaPociskuZSerii=20;
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

void FabrykaLudzi::stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja, int typZachowania, bool zwroconyWPrawo)
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
			strzelec.ustawPoziom(0);
			strzelec.ustawTypZachowania(typZachowania);
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
			strzelec.ustawPoziom(1);
			strzelec.ustawTypZachowania(typZachowania);
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
			strzelec.ustawPoziom(2);
			strzelec.ustawTypZachowania(typZachowania);
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
			strzelec.ustawPoziom(3);
			strzelec.ustawTypZachowania(typZachowania);
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
			strzelec.ustawPoziom(0);
			strzelec.ustawTypZachowania(typZachowania);
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
			strzelec.ustawPoziom(1);
			strzelec.ustawTypZachowania(typZachowania);
			Strzelec *s=(strzelcy->dodaj(strzelec));
			s->wyznaczPrzestrzenKolizji();
			FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalnaRegen,Punkt(),s);
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
			strzelec.ustawPoziom(2);
			strzelec.ustawTypZachowania(typZachowania);
			Strzelec *s=(strzelcy->dodaj(strzelec));
			s->wyznaczPrzestrzenKolizji();
			FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalnaRegen,Punkt(),s);
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
			balista.ustawPoziom(0);
			balista.ustawTypZachowania(typZachowania);
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
			balista.ustawPoziom(1);
			balista.ustawTypZachowania(typZachowania);
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
			kaplan.ustawPoziom(0);
			kaplan.ustawTypZachowania(typZachowania);
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
			kaplan.ustawPoziom(1);
			kaplan.ustawTypZachowania(typZachowania);
			Kaplan *k=(kaplani->dodaj(kaplan));
			k->wyznaczPrzestrzenKolizji();
			FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalnaRegen,Punkt(),k);
			break;
		}
		case glowa:
		{
			assert("Kontener 'Kaplani' nie ustawiony" && kaplani!=0);
			Kaplan kaplan;
			kaplan.ustawPozycje(nPozycja);
			kaplan.ustawCzyZwroconyWPrawo(zwroconyWPrawo);
			kaplan.ustawParametry(parametryKaplanaLv3);
			kaplan.ustawPoziom(2);
			kaplan.ustawTypZachowania(typZachowania);
			Kaplan *k=(kaplani->dodaj(kaplan));
			k->wyznaczPrzestrzenKolizji();
			FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalnaRegen,Punkt(),k);
			break;
		}
		default:
			break;
	}
}
