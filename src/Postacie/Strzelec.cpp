/*
 * Strzelec.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Strzelec.h"
#include "PomocnikCelowania.h"

Strzelec::Strzelec(): Postac()
{
	pozycja.x=2000;
	pozycja.y=parametryObiektow.poziomZiemi+50;
	stan = stoi;
	stanBiegu=0;
	stanNaciagania=-1;
	stanCelowania=0;
	katCelowania=0;

	zycie=100;
	obrazenia=5;
}

void Strzelec::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		if (klawiatura->czyWcisnietoPrawo() && !przeszkodaPoPrawej)
		{
			zwroconyWPrawo=true;
			if(!myszka->zwrocLPM())
			{
				stan = biegnie;

				if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
				else stanBiegu += parametry.predkoscAnimacjiBiegu1;

				if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
				pozycja.x+=parametry.predkoscBiegu;
				if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
				stanCelowania=0;
			}
		}
		else if (klawiatura->czyWcisnietoLewo() && !przeszkodaPoLewej)
		{
			zwroconyWPrawo=false;
			if(!myszka->zwrocLPM())
			{
				stan = biegnie;

				if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
				else stanBiegu += parametry.predkoscAnimacjiBiegu1;

				if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
				pozycja.x-=parametry.predkoscBiegu;
				if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
				stanCelowania=0;
			}
		}
		else if(myszka->zwrocLPM())
		{
			if(cel->zwrocPozycje().x-pozycja.x>0) zwroconyWPrawo=true;
			else zwroconyWPrawo=false;

			stanBiegu=0;
			if(stanNaciagania<0)
			{
				stan = strzela;
				stanCelowania++;
				if(stanCelowania > parametry.maxCelowania)
				{
					double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					kat=-kat+((double)(rand()%100)/100)*parametry.celnosc - parametry.celnosc/2;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscStrzaly*cos(kat);
					v.y=parametry.predkoscStrzaly*sin(kat);
					if(kat>6.28) kat-=6.28;
					if(parametry.spust) FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::belt,p,v,parametry.czasTrwaniaStrzaly,kat,parametry.obrazenia);
					else FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::strzala,p,v,parametry.czasTrwaniaStrzaly,kat,parametry.obrazenia);
					stanNaciagania=parametry.maxNaciagniecie;
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

		if(!myszka->zwrocLPM() && !klawiatura->czyWcisnietoLewo() && !klawiatura->czyWcisnietoPrawo())
		{
			stan = stoi;
			stanBiegu=0;
			stanCelowania=0;
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
		}

		if(pozycja.y<=parametry.wysokosc+parametryObiektow.poziomZiemi)
		{
			pozycja.y=parametry.wysokosc+parametryObiektow.poziomZiemi;
			naZiemi=true;
		}
		if(!naZiemi)
		{
			pozycja.y-=10;
		}
		naZiemi=false;
		przeszkodaPoPrawej=false;
		przeszkodaPoLewej=false;

		if(zycie<=0) zniszcz();
	}
	else
	{
		stan = umiera;
		std::vector<ProstokatKolizji> p;
		ustawPrzestrzenKolizji(p);
	}
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################

std::pair<Klawiatura,Myszka> Strzelec::wyznaczSterowanie()
{
	int maxOdleglosc=15200;
	int minOdleglosc=15200;
	int odleglosc=00;

	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	Klawiatura k;
	Myszka m;

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}

	bool mozliwyStrzal = pomocnikCelowania.czyMozliwyStrzal(pozycja-pozycjaCelu);

	if(abs(pozycjaCelu.x-pozycja.x)>maxOdleglosc) mozliwyStrzal=false;
	if( (stanNaciagania>0 && parametry.spust && mozliwyStrzal) || mozliwyStrzal)
	{
		m.ustawLPM(true);
		if(mozliwyStrzal)
		{
			Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
			poprawka.y=-poprawka.y+10;
			poprawka.x=-poprawka.x;
			if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
			else poprawka.x-=30;
			pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka,cel->zwrocPredkosc());

		}
		double kat = 0;
		if(pozycja.y<pozycjaCelu.y) kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
		else kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katZGory);

		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;
	}
	else if(pozycjaCelu.x>pozycja.x )
	{
		k.ustawWcisnietoPrawo(true);
	}
	else if(pozycjaCelu.x<pozycja.x)
	{
		k.ustawWcisnietoLewo(true);
	}

	if(m.zwrocLPM()==false || (m.zwrocLPM()==true && stanNaciagania==-1 && parametry.maxCelowania==stanCelowania))
	{
		pomocnikCelowania.resetCelowania();
	}
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
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(),100));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-30+rozmiarKlatki),10));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-50+rozmiarKlatki),14));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-70+rozmiarKlatki),14));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-88+rozmiarKlatki),14));
	ustawPrzestrzenKolizji(okregi);
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
		if(parametry.spust)
		{
			if(klatkaAnimacji.x!=2 || klatkaAnimacji.y<4)
			{
				klatkaAnimacji.x=2;
				klatkaAnimacji.y=4;
			}
			klatkaAnimacji.y+=0.3;
			if(klatkaAnimacji.y>=7)klatkaAnimacji.y=4;
		}
		else
		{
			klatkaAnimacji.x=2;
			klatkaAnimacji.y=9-4*(stanNaciagania/parametry.maxNaciagniecie);
			if(klatkaAnimacji.y>=8)
			{
				klatkaAnimacji.y=0;
			}
		}
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
