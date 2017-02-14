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
	katCelowaniaZGory=0;
	katCelowaniaWprost=0;
	katCelowania=0;

	stanNaciagania=0;
	zwroconyWPrawo=true;
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################
void Balista::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	//Strzal
	if(myszka->zwrocLPM() && stanNaciagania==0)
	{
		//Fabryka->stworz pocisk
		Punkt p;
		p.x=pozycja.x+(100)*cos(katCelowania);
		p.y=pozycja.y+(100)*sin(katCelowania);
		Punkt v;
		v.x=parametry.predkoscStrzaly*cos(katCelowania);
		v.y=parametry.predkoscStrzaly*sin(katCelowania);
		double katStrzaly = katCelowania+1.57;//+3.14+6.28
		if(katStrzaly>6.28) katStrzaly-=6.28;
		FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::belt,p,v,100,katStrzaly);

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
			}
			else podniesCelownik();
		}
		//Celowanie
		else
		{
			double katMyszki = atan2(myszka->zwrocY(),myszka->zwrocX());

			if(fabs(katCelowania-katMyszki)>parametry.predkoscCelowania && (zwroconyWPrawo == (pozycja.x<cel->zwrocPozycje().x))  )
			{
				if(zwroconyWPrawo==(katCelowania > katMyszki) && !czyPrzekroczonoMinKatCelowania()) opuscCelownik();
				else if(zwroconyWPrawo==(katCelowania < katMyszki) && !czyPrzekroczonoMaksKatCelowania()) podniesCelownik();
			}
		}
	}
}

std::pair<Klawiatura,Myszka> Balista::wyznaczSterowanie()
{
	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	Klawiatura k;
	Myszka m;

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}


	wyznaczKatStrzalu(Punkt((pozycja.x-pozycjaCelu.x),-(pozycja.y-pozycjaCelu.y)));

	m.ustawX(cos(katCelowaniaWprost)*1000);
	m.ustawY(-sin(katCelowaniaWprost)*1000);

	if(fabs((double)katCelowaniaWprost+katCelowania-M_PI*2)<parametry.predkoscCelowania)
	{
		m.ustawLPM(true);
	}

	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

void Balista::wyznaczKatStrzalu(Punkt cel)
{
	mozliwyStrzal=true;

	//do wzoru, jak zgubisz kartke to zle
	double A=-abs(cel.y);
	double B=abs(cel.x);
	double C=B*B*Strzala::parametry.wspolczynnikGrawitacji/(2*10000);

	if(B==0)
	{
		mozliwyStrzal=false;
		return;
	}

	//do rownania kwadratowego
	double a=A*A+B*B;
	double b=B*B+2*A*C;
	double c=C*C;

	//rownanie kwadratowe
	double delta = b*b-4*a*c;

	if(delta<0)
	{
		mozliwyStrzal=false;
		return;
	}
	double kat1 = -(-b -sqrt(delta))/(2*a);
	double kat2 = -(-b +sqrt(delta))/(2*a);

	if(kat1<0)
	{
		mozliwyStrzal=false;
		return ;
	}
	if(kat1<kat2)
	{
		double tmp = kat1;kat1=kat2;kat2=tmp;
	}

	if(cel.x<0)
	{
		katCelowaniaWprost = acos(-sqrt(kat1));
		katCelowaniaZGory = acos(-sqrt(kat2));
	}
	else
	{
		katCelowaniaWprost = acos(sqrt(kat1));
		katCelowaniaZGory = acos(sqrt(kat2));
	}

	katCelowaniaWprost+=3.14;
	katCelowaniaZGory+=3.14;


}

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

}

//#####################################################################################################
//Podfunkcje Grafika
//#####################################################################################################
void Balista::wyznaczKlatkeAnimacji()
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
