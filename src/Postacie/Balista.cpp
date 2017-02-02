/*
 * Balista.cpp
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#include "Balista.h"

Balista::Balista() {
	stan=rozladowany;

}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################
void Balista::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(myszka->zwrocLPM() && stanNaciagania==0)
	{
		//Fabryka->stworz pocisk
		stanNaciagania=parametry.maxNaciagania;
	}
	else
	{
		if(stanNaciagania>0)
		{
			if(katCelowania==0) stanNaciagania--;
			else katCelowania-=parametry.predkoscCelowania;
		}
		else
		{
			double kat = atan2(myszka->zwrocY(),myszka->zwrocX());
			kat=-kat;

			std::cout << katCelowania << "  " << kat<< "\n";
			if(abs(katCelowania-kat)>parametry.predkoscCelowania)
			{
				if(katCelowania > kat) katCelowania-=parametry.predkoscCelowania;
				else if(katCelowania < kat) katCelowania+=parametry.predkoscCelowania;
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

	m.ustawX(-cos(katCelowaniaWprost)*1000);
	m.ustawY(sin(katCelowaniaWprost)*1000);

	//std::cout << m.zwrocX() << "  " << m.zwrocY() << "\n";

	if(abs(katCelowania-katCelowaniaWprost)<parametry.predkoscCelowania) m.ustawLPM(true);

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
	double C=B*B*Strzala::parametry.wspolczynnikGrawitacji/(2*parametry.predkoscStrzaly*parametry.predkoscStrzaly);

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

	//std::cout << "\n";
	//std::cout  << "a:"<< a << " b:" << b << " c:" << c << "\n";
	//std::cout  << "A:"<< A << " B:" << B << " C:" << C << "\n";
	//std::cout  << "delta:" << delta << "\n";

	if(delta<0)
	{
		mozliwyStrzal=false;
		return;
	}
	double kat1 = -(-b -sqrt(delta))/(2*a);
	double kat2 = -(-b +sqrt(delta))/(2*a);
	//std::cout << "kat1:" << kat1 << " kat2:" << kat2 << "\n";

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
	klatkaAnimacji.x=4-((double)(kat)/(6.28/16));
	if(klatkaAnimacji.x>3) klatkaAnimacji.x=3;
	if(klatkaAnimacji.x<0) klatkaAnimacji.x=0;
	if(stanNaciagania<=0) klatkaAnimacji.x+=4;

	//y/4 stan celowania
	//y%4 stan naciagania
	klatkaAnimacji.y=stanNaciagania%parametry.predkoscAnimacjiNaciagania;
	klatkaAnimacji.y=(stanCelowania%parametry.predkoscAnimacjiCelowania)*4;
}
