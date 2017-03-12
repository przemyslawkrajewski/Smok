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
	katCelowaniaWprost=0;
	katCelowaniaZGory=0;
	katCelowania=0;
	stanNaciagania=-1;
	stanCelowania=0;
	mozliwyStrzal=false;

	zycie=100;
	obrazenia=5;
}

void Strzelec::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		if (klawiatura->czyWcisnietoPrawo())
		{
			zwroconyWPrawo=true;
			stan = biegnie;

			if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
			else stanBiegu += parametry.predkoscAnimacjiBiegu1;

			if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
			pozycja.x+=parametry.predkoscBiegu;
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
			stanCelowania=0;
		}
		else if (klawiatura->czyWcisnietoLewo())
		{
			zwroconyWPrawo=false;
			stan = biegnie;

			if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
			else stanBiegu += parametry.predkoscAnimacjiBiegu1;

			if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
			pozycja.x-=parametry.predkoscBiegu;
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
			stanCelowania=0;
		}
		else if(myszka->zwrocLPM())
		{
			stanBiegu=0;
			if(stanNaciagania<0)
			{
				stan = strzela;
				stanCelowania++;

				if(stanCelowania > parametry.maxCelowania)
				{
					double kat=-katCelowania+((double)(rand()%100)/100)*parametry.celnosc - parametry.celnosc/2;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscStrzaly*cos(kat);
					v.y=parametry.predkoscStrzaly*sin(kat);
					kat = katCelowania+1.57;//+3.14+6.28
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
		else
		{
			stan = stoi;
			stanBiegu=0;
			stanCelowania=0;
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
		}
		if(stanNaciagania<-1) stanNaciagania=-1;
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
	int maxOdleglosc=200;
	int minOdleglosc=100;
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

	wyznaczKatStrzalu(Punkt((m.zwrocX()),-(m.zwrocY())));
	if(abs(pozycjaCelu.x-pozycja.x)>maxOdleglosc) mozliwyStrzal=false;
	if((stanNaciagania>0 && parametry.spust) || (mozliwyStrzal && ((pozycjaCelu.x>=pozycja.x && zwroconyWPrawo==true) || (pozycjaCelu.x<=pozycja.x && zwroconyWPrawo!=true))))
	{
		m.ustawLPM(true);
		if(abs(pozycja.x-pozycjaCelu.x)<odleglosc) katCelowania=katCelowaniaWprost; //TODO: komunikacja tylko przez myszke i klawiature
		else katCelowania=katCelowaniaZGory;
	}
	else if(pozycjaCelu.x>pozycja.x && zwroconyWPrawo==true)
	{
		k.ustawWcisnietoPrawo(true);
	}
	else if(pozycjaCelu.x<pozycja.x && zwroconyWPrawo!=true)
	{
		k.ustawWcisnietoLewo(true);
	}
	else if(pozycjaCelu.x>pozycja.x )
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

void Strzelec::wyznaczKatStrzalu(Punkt cel)
{
	mozliwyStrzal=true;

	if(parametry.spust)
	{
		katCelowaniaWprost = atan2((-cel.x),(cel.y))-1.57;
		if(katCelowaniaWprost<0) katCelowaniaWprost+=M_PI*2;
		katCelowaniaZGory = katCelowaniaWprost;
		return;
	}

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
