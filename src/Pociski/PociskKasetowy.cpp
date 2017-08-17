/*
 * Strzala.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "PociskKasetowy.h"

ParametryPociskuKasetowego PociskKasetowy::parametry;

PociskKasetowy::PociskKasetowy(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	obrazenia=5;
	odleglosc=-1;
}

void PociskKasetowy::zniszcz()
{
	Obiekt::zniszcz();
	predkosc.x=predkosc.y=0;
	//czasTrwania=-1;
}

double PociskKasetowy::zwrocKat()
{
	return katNachylenia;
}

void PociskKasetowy::wyznaczKolejnyStan()
{
	if(!(predkosc.x==0 && predkosc.y==0))
	{
		katNachylenia=1.57-atan2(predkosc.y,predkosc.x);
		if(katNachylenia<0) katNachylenia+=6.28;
	}

	if(istnieje && !zniszczony)
	{
		pozycja.x+=predkosc.x;
		pozycja.y+=predkosc.y;
		if(cel)
		{
			Punkt p = (pozycja-cel->zwrocPozycje());
			double d = sqrt(p.x*p.x+p.y*p.y);
			if(d>odleglosc && odleglosc>0) zniszcz();
			if( d<parametry.minimalnaOdleglosc) zniszcz();
			odleglosc=d;
		}
		czasTrwania--;
	}

	if(pozycja.y<parametryObiektow.poziomZiemi || czasTrwania<0) zniszcz();
}

void PociskKasetowy::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=1;
	klatkaAnimacji.x=(0.5+(double)(katNachylenia)/(6.28/32));
	klatkaAnimacji.x=(int)klatkaAnimacji.x;
	if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
}

void PociskKasetowy::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki = 30/2;
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(15-rozmiarKlatki,-15+rozmiarKlatki),8));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(15-rozmiarKlatki,-15+rozmiarKlatki),4));
	ustawPrzestrzenKolizji(okregi);
}
