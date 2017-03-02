/*
 * Kaplan.cpp
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#include "Kaplan.h"

Kaplan::Kaplan() {
	stan=stoi;

	zwroconyWPrawo=true;
	zycie=30;
	obrazenia=5;
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################
void Kaplan::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		if (klawiatura->czyWcisnietoPrawo())
		{
			zwroconyWPrawo=true;
			stan = idzie;

			stanChodu ++;

			if(stanChodu>=parametry.predkoscAnimacjiChodu*parametry.iloscKlatekAnimacjiChodu) stanChodu=0;
			pozycja.x+=parametry.predkoscChodu;
			stanRzucaniaZaklec=-1;
		}
		else if (klawiatura->czyWcisnietoLewo())
		{
			zwroconyWPrawo=false;
			stan = idzie;

			stanChodu ++;

			if(stanChodu>=parametry.predkoscAnimacjiChodu*parametry.iloscKlatekAnimacjiChodu) stanChodu=0;
			pozycja.x-=parametry.predkoscChodu;
			stanRzucaniaZaklec=-1;
		}
		else if(myszka->zwrocLPM())
		{
			stan = zaklecieKierowany;
			stanChodu=0;
			stanRzucaniaZaklec++;

				if(stanRzucaniaZaklec>parametry.czasRzucaniaKierowanegoPocisku)
				{
					stanRzucaniaZaklec=0;

					double kat = atan2((-myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscPociskuKierowanego*cos(kat);
					v.y=parametry.predkoscPociskuKierowanego*sin(kat);
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskKierowany,p,v,parametry.czasTrwaniaPocuskuKierowanego,kat,parametry.obrazeniaKierowanegoPocisku,cel);
				}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(0))
		{
			stan = zaklecieKasetowy;
			stanChodu=0;
			stanRzucaniaZaklec++;

				if(stanRzucaniaZaklec>parametry.czasRzucaniaKasetowegoPocisku)
				{
					stanRzucaniaZaklec=0;

					double kat = atan2((-myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscPociskuKierowanego*cos(kat);
					v.y=parametry.predkoscPociskuKierowanego*sin(kat);
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskKasetowy,p,v,parametry.czasTrwaniaPocuskuKierowanego,kat,parametry.obrazeniaKasetowegoPocisku,cel);
				}
		}
		else
		{
			stan = stoi;
			stanChodu=0;
			stanRzucaniaZaklec=0;
		}
		if(stanRzucaniaZaklec<0) stanRzucaniaZaklec=0;
		if(zycie<=0) zniszcz();
	}
	else
	{
		stan = umiera;
		std::vector<OkragKolizji> p;
		ustawPrzestrzenKolizji(p);
	}
}

std::pair<Klawiatura,Myszka> Kaplan::wyznaczSterowanie()
{
	int maxOdleglosc=4000;
	int minOdleglosc=600;
	int odleglosc=400;

	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	Klawiatura k;
	Myszka m;

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}

	m.ustawX(pozycja.x-pozycjaCelu.x);
	m.ustawY(pozycja.y-pozycjaCelu.y);

	if(fabs(pozycjaCelu.x-pozycja.x)<minOdleglosc && ((pozycjaCelu.x>=pozycja.x && zwroconyWPrawo==true) || (pozycjaCelu.x<=pozycja.x && zwroconyWPrawo!=true)))
	{
		//m.ustawLPM(true);
		k.ustawWcisnietoKlawiszFunkcyjny(true,0);
	}
	else if(pozycjaCelu.x>pozycja.x)
	{
		k.ustawWcisnietoPrawo(true);
	}
	else if(pozycjaCelu.x<pozycja.x)
	{
		k.ustawWcisnietoLewo(true);
	}

	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

//#####################################################################################################
//Podfunkcje Kolizje
//#####################################################################################################
void Kaplan::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki=40;
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(),100));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(40-rozmiarKlatki,-15+rozmiarKlatki),10));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(40-rozmiarKlatki,-35+rozmiarKlatki),14));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(40-rozmiarKlatki,-60+rozmiarKlatki),14));
	ustawPrzestrzenKolizji(okregi);
}

//#####################################################################################################
//Podfunkcje Grafika
//#####################################################################################################
void Kaplan::wyznaczKlatkeAnimacji()
{
	switch(stan)
	{
		case stoi:
			klatkaAnimacji=Punkt(0,0);
			break;
		case idzie:
			klatkaAnimacji.x=1;
			klatkaAnimacji.y=stanChodu/((int)(parametry.predkoscAnimacjiChodu));
			break;
		case zaklecieKierowany:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaKierowanegoPocisku/3);
			break;
		case zaklecieKasetowy:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaKasetowegoPocisku/3);
			break;
		case umiera:
			if(klatkaAnimacji.x!=0 || klatkaAnimacji.y<2)
			{
				klatkaAnimacji.x=0;
				klatkaAnimacji.y=2;
			}
			else if(klatkaAnimacji.y<7)
				klatkaAnimacji.y+=0.3;
			else
				klatkaAnimacji.y+=0.1;
			if (klatkaAnimacji.x==0 && klatkaAnimacji.y>=8) usun();
			break;
		default:
			klatkaAnimacji=Punkt();
	}
}
