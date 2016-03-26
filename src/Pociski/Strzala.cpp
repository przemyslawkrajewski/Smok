/*
 * Strzala.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Strzala.h"

ParametryStrzaly Strzala::parametry;

Strzala::Strzala(double nx,double ny, double nvx, double nvy, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja.x=nx;
	pozycja.y=ny;
	predkosc.x=nvx;
	predkosc.y=nvy;
	katNachylenia = nKat;
}

Strzala::Strzala(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	obrazenia=5;
}

void Strzala::zniszcz()
{
	Obiekt::zniszcz();
	predkosc.x=predkosc.y=0;
	//czasTrwania=-1;
}

double Strzala::zwrocKat()
{
	return katNachylenia;
}

void Strzala::wyznaczKolejnyStan()
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
		predkosc.y-=parametry.wspolczynnikGrawitacji;
	}
	else
	{
		czasTrwania--;
	}
	if(pozycja.y<parametryObiektow.poziomZiemi)
	{
		pozycja.x=((parametryObiektow.poziomZiemi-pozycja.y)/predkosc.y)*predkosc.x+pozycja.x;
		pozycja.y=parametryObiektow.poziomZiemi;
		zniszcz();
	}
	if(czasTrwania<0) usun();
}

void Strzala::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=1;
	klatkaAnimacji.x=(0.5+(double)(katNachylenia)/(6.28/32));
	klatkaAnimacji.x=(int)klatkaAnimacji.x;
	if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
}

void Strzala::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki = 30/2;
	std::vector<OkragKolizji> f;
	f.clear();
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(15-rozmiarKlatki,-15+rozmiarKlatki),7));
	ustawPrzestrzenKolizji(f);
}
