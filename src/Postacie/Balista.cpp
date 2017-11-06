/*
 * Balista.cpp
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#include "Balista.h"

Balista::Balista() {
	stan=rozladowany;
	stanCelowania=0;

	mozliwyStrzal=false;
	katCelowania=0;

	stanNaciagania=0;
	zwroconyWPrawo=true;
	zycie=300;
	obrazenia=500;
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################
void Balista::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		if(zycie<0)
		{
			//Na razie po prostu znika
			zniszcz();
			klatkaAnimacji.x=0;
		}
		//Strzal
		if(myszka->zwrocLPM() && stanNaciagania==0 )
		{
			double katMyszki = atan2(myszka->zwrocY(),myszka->zwrocX());
			if(czyKatPrzekraczaMaks(-katMyszki) || czyKatPrzekraczaMin(-katMyszki)) return;
			double kat = -katMyszki;
			//Fabryka->stworz pocisk
			Punkt p;
			p.x=pozycja.x;//+(parametry.predkoscStrzaly)*cos(katCelowania);
			p.y=pozycja.y;//+(parametry.predkoscStrzaly)*sin(katCelowania);
			Punkt v;
			v.x=parametry.predkoscStrzaly*cos(kat);
			v.y=parametry.predkoscStrzaly*sin(kat);
			double katStrzaly = kat+M_PI/2;//+3.14+6.28
			if(katStrzaly>6.28) katStrzaly-=6.28;
			FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskBalistyczny,p,v,parametry.predkoscStrzaly,katStrzaly,parametry.obrazenia);

			stanNaciagania=parametry.maxNaciagania;
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(0) && stanNaciagania==0 )
		{
			double katMyszki = atan2(myszka->zwrocY(),myszka->zwrocX());
			if(czyKatPrzekraczaMaks(-katMyszki) || czyKatPrzekraczaMin(-katMyszki)) return;
			for(int i=0;i<parametry.iloscPociskow;i++)
			{
				double kat;
				kat=katCelowania+((double)(rand()%100)/100)*parametry.rozrzut - parametry.rozrzut/2;
				if(fabs(katMyszki-katCelowania)<parametry.predkoscCelowania)
				{
					kat=-katMyszki;
				}
				//Fabryka->stworz pocisk
				Punkt p;
				p.x=pozycja.x;//+(parametry.predkoscStrzaly)*cos(katCelowania);
				p.y=pozycja.y;//+(parametry.predkoscStrzaly)*sin(katCelowania);
				Punkt v;
				v.x=parametry.predkoscStrzaly*cos(kat);
				v.y=parametry.predkoscStrzaly*sin(kat);
				double katStrzaly = kat+M_PI/2;//+3.14+6.28
				if(katStrzaly>6.28) katStrzaly-=6.28;
				FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskBalistyczny,p,v,parametry.predkoscStrzaly,katStrzaly,parametry.obnizoneObrazenia);
			}
			stanNaciagania=parametry.maxNaciagania;
		}
		else
		{
			//Naciaganie
			if(stanNaciagania>0)
			{
				if(czyPrzekroczonoMaksKatCelowania())
				{
					stanNaciagania--;
					if(stanNaciagania==0) pomocnikCelowania.resetCelowania();
				}
				else podniesCelownik();
			}
			//Celowanie
			else if(cel != 0)
			{
				double katMyszki = atan2(myszka->zwrocY(),myszka->zwrocX());

				if(fabs(katCelowania-katMyszki)>parametry.predkoscCelowania && (zwroconyWPrawo == (pozycja.x<cel->zwrocPozycje().x))  )
				{
					if(zwroconyWPrawo==(katCelowania > -katMyszki) && !czyPrzekroczonoMinKatCelowania()) opuscCelownik();
					else if(zwroconyWPrawo==(katCelowania < -katMyszki) && !czyPrzekroczonoMaksKatCelowania()) podniesCelownik();
				}
			}
		}
	}
	else
	{
		if( klatkaAnimacji.x >= 4 ) usun();
	}
}

std::pair<Klawiatura,Myszka> Balista::wyznaczSterowanie()
{
	Klawiatura k;
	Myszka m;

	if(cel == 0) return std::pair<Klawiatura,Myszka>(k,m);

	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}


	Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
	poprawka.y=-poprawka.y+40;
	poprawka.x=-poprawka.x;
	if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
	else poprawka.x-=30;

	double czyMozliwyStrzal=pomocnikCelowania.czyMozliwyStrzal(Punkt(pozycja.x-pozycjaCelu.x,pozycja.y-pozycjaCelu.y)+poprawka);

	pomocnikCelowania.wyznaczKatStrzalu(Punkt(pozycja.x-pozycjaCelu.x,pozycja.y-pozycjaCelu.y)+poprawka,cel->zwrocPredkosc());
	double kat = M_PI*2-pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);

	m.ustawX(cos(kat)*10000);
	m.ustawY(-sin(kat)*10000);


	if(fabs(kat-katCelowania)<=parametry.predkoscCelowania && czyMozliwyStrzal && fabs(staraPredkoscCelu.x-cel->zwrocPredkosc().x) < 5 && fabs(staraPredkoscCelu.y-cel->zwrocPredkosc().y) < 10)
	{
		if(typZachowania==0)
		{
			m.ustawLPM(true);
		}
		else
		{
			//Inne zachowanie
			k.ustawWcisnietoKlawiszFunkcyjny(true,0);
		}
	}

	staraPredkoscCelu = cel->zwrocPredkosc();
	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

bool Balista::czyPrzekroczonoMaksKatCelowania()
{
	if(zwroconyWPrawo)
		return katCelowania>parametry.maxKatCelowania;
	else
		return katCelowania<M_PI-parametry.maxKatCelowania;
}
bool Balista::czyPrzekroczonoMinKatCelowania()
{
	if(zwroconyWPrawo)
		return katCelowania<parametry.minKatCelowania;
	else
		return katCelowania>M_PI-parametry.minKatCelowania;
}

bool Balista::czyKatPrzekraczaMaks(double kat)
{
	if(zwroconyWPrawo)
		return kat>parametry.maxKatCelowania;
	else
		return kat<M_PI-parametry.maxKatCelowania;
}

bool Balista::czyKatPrzekraczaMin(double kat)
{
	if(zwroconyWPrawo)
		return kat<parametry.minKatCelowania;
	else
		return kat>M_PI-parametry.minKatCelowania;
}

void Balista::opuscCelownik()
{
	if(zwroconyWPrawo)
		katCelowania-=parametry.predkoscCelowania;
	else
		katCelowania+=parametry.predkoscCelowania;
	stanCelowania--;
	if(stanCelowania<=0) stanCelowania=parametry.predkoscAnimacjiCelowania*4-1;
}
void Balista::podniesCelownik()
{
	if(zwroconyWPrawo)
		katCelowania+=parametry.predkoscCelowania;
	else
		katCelowania-=parametry.predkoscCelowania;
	stanCelowania++;
	if(stanCelowania>=parametry.predkoscAnimacjiCelowania*4) stanCelowania=0;
}

//#####################################################################################################
//Podfunkcje Kolizje
//#####################################################################################################
void Balista::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki = 100/2;
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(25,-120),Punkt(140,5)));
	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(-30,-100),Punkt(30,40)));
	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(27,-60),Punkt(15,130)));
	ustawPrzestrzenKolizji(prostokaty);

	//ustawPrzestrzenKolizji(okregi);
}

//#####################################################################################################
//Podfunkcje Grafika
//#####################################################################################################
void Balista::wyznaczKlatkeAnimacji()
{
	if(zycie > 0)
	{
		//x/4- naladowany/rozladowany
		//x%4 -kat celowania
		double kat=katCelowania;
		if(zwroconyWPrawo)
			klatkaAnimacji.x=((double)(kat-M_PI/32)/(M_PI/16));
		else
			klatkaAnimacji.x=((double)(M_PI-kat+M_PI/32)/(6.28/16));

		if(klatkaAnimacji.x>3) klatkaAnimacji.x=3;
		if(klatkaAnimacji.x<0) klatkaAnimacji.x=0;
		if(stanNaciagania>0) klatkaAnimacji.x+=5;

		if(stanNaciagania!=0 && stanNaciagania!=parametry.maxNaciagania)
			klatkaAnimacji.x=9;
		//y/4 stan celowania
		//y%4 stan naciagania
		if(stanNaciagania==0 || stanNaciagania==parametry.maxNaciagania)
			klatkaAnimacji.y=0;
		else
			klatkaAnimacji.y=(stanNaciagania/parametry.predkoscAnimacjiNaciagania)%4+1;

		if(stanNaciagania==0 || stanNaciagania==parametry.maxNaciagania)
			klatkaAnimacji.y+=((int)stanCelowania/parametry.predkoscAnimacjiCelowania)* 5+5;
	}
	else
	{
		klatkaAnimacji.y=0;
		klatkaAnimacji.x+=0.4;
	}
}
