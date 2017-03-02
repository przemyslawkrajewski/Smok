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
			double odleglosc = sqrt(p.x*p.x+p.y*p.y);
			if(((p.x<0)==(predkosc.x<0)) || ((p.y<0)==(predkosc.y<0)) || odleglosc<parametry.minimalnaOdleglosc) zniszcz();
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

}
