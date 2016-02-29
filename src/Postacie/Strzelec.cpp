/*
 * Strzelec.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Strzelec.h"

Strzelec::Strzelec(): Postac()
{
	pozycja.x=2000;
	pozycja.y=parametryObiektow.poziomZiemi+50;
	stan = stoi;
	stanBiegu=0;
	katCelowania=0;
	stanNaciagania=0;
	stanCelowania=0;

	spust=true;			//kusza/luk
	predkoscStrzaly=18;
	maxNaciagniecie=100;//ile czas trzeba zeby naciagnac
	celnosc=3.14/16;
	maxCelowania=20;   //ile czasu trzeba zeby wycelowac
	zycie=100;
}

void Strzelec::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		if (klawiatura->czyWcisnietoPrawo())
		{
			zwroconyWPrawo=true;
			stan = biegnie;
			stanBiegu += parametry.predkoscAnimacjiBiegu;
			if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
			pozycja.x+=parametry.predkoscBiegu;
			if(!spust || stanNaciagania>0) stanNaciagania=maxNaciagniecie;
			stanCelowania=0;
		}
		else if (klawiatura->czyWcisnietoLewo())
		{
			zwroconyWPrawo=false;
			stan = biegnie;

			stanBiegu += parametry.predkoscAnimacjiBiegu;
			if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
			pozycja.x-=parametry.predkoscBiegu;
			if(!spust || stanNaciagania>0) stanNaciagania=maxNaciagniecie;
			stanCelowania=0;
		}
		else if(myszka->zwrocLPM())
		{
			stanBiegu=0;
			if(stanNaciagania<0)
			{
				stan = strzela;
				katCelowania = atan2(-(myszka->zwrocY()),(myszka->zwrocX()))+3.14;
				stanCelowania++;

				if(stanCelowania > maxCelowania)
				{
					double kat=-katCelowania+((double)(rand()%100)/100)*celnosc - celnosc/2;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=predkoscStrzaly*cos(kat);
					v.y=predkoscStrzaly*sin(kat);
					kat = katCelowania+1.57;//+3.14+6.28
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::strzala,p,v,parametry.czasTrwaniaStrzaly,kat);
					stanNaciagania=maxNaciagniecie;
					stanCelowania=0;
				}
			}
			else
			{
				stanCelowania=0;
				stan = naciaga;
				stanNaciagania--;
			}
		}
		else
		{
			stan = stoi;
			stanBiegu=0;
			if(spust) {stan = strzela;stanNaciagania--;}
			else stanNaciagania=maxNaciagniecie;
			stanCelowania=0;
		}
		if(stanNaciagania<-1) stanNaciagania=-1;
		if(zycie<=0) zniszcz();
	}
	else
	{
		stan = umiera;
		std::vector<OkragKolizji> p;
		ustawPrzestrzenKolizji(p);
	}
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################

std::pair<Klawiatura,Myszka> Strzelec::wyznaczSterowanie()
{
	int maxOdleglosc=500;
	int minOdleglosc=100;

	Klawiatura k;
	Myszka m;
	if(cel.x>pozycja.x && zwroconyWPrawo!=true && (stanNaciagania<0 && spust))
	{
		k.ustawWcisnietoPrawo(true);
	}
	else if(cel.x<pozycja.x && zwroconyWPrawo==true && (stanNaciagania<0 && spust))
	{
		k.ustawWcisnietoLewo(true);
	}
	if(cel.x>pozycja.x+maxOdleglosc  && (stanNaciagania<0 && spust))
	{
		k.ustawWcisnietoPrawo(true);
	}
	else if(cel.x<pozycja.x-maxOdleglosc  && (stanNaciagania<0 && spust))
	{
		k.ustawWcisnietoLewo(true);
	}
	else if(abs(cel.x-pozycja.x)<maxOdleglosc && abs(cel.x-pozycja.x)>minOdleglosc)
	{
		m.ustawLPM(true);
	}

	m.ustawX(pozycja.x-cel.x);
	m.ustawY(pozycja.y-cel.y);

	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

//#####################################################################################################
//Podfunkcje Kolizje
//#####################################################################################################
void Strzelec::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki = 100/2;
	std::vector<OkragKolizji> f;
	f.clear();
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-30+rozmiarKlatki),10));
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-50+rozmiarKlatki),14));
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-70+rozmiarKlatki),14));
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-88+rozmiarKlatki),14));
	ustawPrzestrzenKolizji(f);
}
//#####################################################################################################
//Podfunkcje Grafika
//#####################################################################################################
void Strzelec::wyznaczKlatkeAnimacji()
{
	double kat;
	switch(stan)
	{
	case naciaga:
		if(klatkaAnimacji.x!=2 || klatkaAnimacji.y<4)
		{
			klatkaAnimacji.x=2;
			klatkaAnimacji.y=4;
		}
		klatkaAnimacji.y+=0.3;
		if(klatkaAnimacji.y>=7)klatkaAnimacji.y=4;
		break;
	case stoi:
		klatkaAnimacji.x=0;
		klatkaAnimacji.y=0;
		break;
	case biegnie:
		klatkaAnimacji.x=1;
		klatkaAnimacji.y=(double)((int)stanBiegu);
		break;
	case strzela:
		klatkaAnimacji.x=2;
		klatkaAnimacji.y=0;

		kat = katCelowania-3*3.14/2;
		if(kat<0) kat=-kat;
		//double poprawka=0;
		//if(zwroconyWPrawo) poprawka=6.28/16;
		//else poprawka=6.28/16;
		klatkaAnimacji.y=4-((double)(kat)/(6.28/16));
		klatkaAnimacji.y= (int)klatkaAnimacji.y;
		if(klatkaAnimacji.y>3) klatkaAnimacji.y=3;
		if(klatkaAnimacji.y<0) klatkaAnimacji.y=0;
		break;
	case umiera:
		if(klatkaAnimacji.x!=0 || klatkaAnimacji.y<1)
		{
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=1;
		}
		else
			klatkaAnimacji.y+=0.3;
		if (klatkaAnimacji.x!=0 || klatkaAnimacji.y>=5) usun();
		break;
	}
}
