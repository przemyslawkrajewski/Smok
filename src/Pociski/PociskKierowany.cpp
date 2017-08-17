/*
 * Strzala.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "PociskKierowany.h"

ParametryPociskuKierowanego PociskKierowany::parametry;

PociskKierowany::PociskKierowany(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	obrazenia=5;

	maksymalnaPredkosc= sqrt(predkosc.y*predkosc.y+predkosc.x*predkosc.x);
}

void PociskKierowany::zniszcz()
{
	Obiekt::zniszcz();
	predkosc.x=predkosc.y=0;
	//czasTrwania=-1;
}

double PociskKierowany::zwrocKat()
{
	return katNachylenia;
}

void PociskKierowany::wyznaczKolejnyStan()
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
			Punkt koretka = (cel->zwrocPozycje()-pozycja)*parametry.wzmocnienieSterowania;
			predkosc=predkosc+koretka;
			double kat = atan2((-predkosc.x),(predkosc.y))+1.57;
			predkosc.x=cos(kat)*maksymalnaPredkosc;
			predkosc.y=sin(kat)*maksymalnaPredkosc;
		}
		czasTrwania--;
	}

	if(czasTrwania<0)
	{
		maksymalnaPredkosc--;
	}
	if(pozycja.y<parametryObiektow.poziomZiemi || maksymalnaPredkosc<0) usun();
}

void PociskKierowany::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=1;
	klatkaAnimacji.x=(0.5+(double)(katNachylenia)/(6.28/32));
	klatkaAnimacji.x=(int)klatkaAnimacji.x;
	if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
}

void PociskKierowany::wyznaczPrzestrzenKolizji()
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
