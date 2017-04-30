/*
 * Belt.cpp
 *
 *  Created on: 28-11-2016
 *      Author: przemo
 */

#include "Belt.h"

ParametryBeltu Belt::parametry;

Belt::Belt(double nx,double ny, double nvx, double nvy, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja.x=nx;
	pozycja.y=ny;
	predkosc.x=nvx;
	predkosc.y=nvy;
	katNachylenia = nKat;
	swietaStrzala=false;
}

Belt::Belt(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	obrazenia=5;
	swietaStrzala=false;
}

void Belt::zniszcz()
{
	Obiekt::zniszcz();
	czasTrwania=parametry.czasTrwaniaPoZniszczeniu;
}

double Belt::zwrocKat()
{
	return katNachylenia;
}

void Belt::wyznaczKolejnyStan()
{
	if(!(predkosc.x==0 && predkosc.y==0))
	{
		katNachylenia=1.57-atan2(predkosc.y,predkosc.x);
		if(katNachylenia<0) katNachylenia+=6.28;
	}

	pozycja.x+=predkosc.x;
	pozycja.y+=predkosc.y;
	czasTrwania--;

	if(istnieje && !zniszczony)
	{
		if(czasTrwania<0) zniszcz();
	}
	else
	{
		predkosc.y-=parametry.wspolczynnikGrawitacji;
		predkosc.x=(double)predkosc.x*parametry.wspolczynnikZwalniania;
		if(czasTrwania<0) usun();
	}
	if(pozycja.y<parametryObiektow.poziomZiemi) usun();
}

void Belt::wyznaczKlatkeAnimacji()
{
	if(!zniszczony)
	{
		klatkaAnimacji.x=1;
		klatkaAnimacji.x=(0.5+(double)(katNachylenia)/(6.28/32));
		klatkaAnimacji.x=(int)klatkaAnimacji.x;
		if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
	}
	else
	{
		klatkaAnimacji.x+=parametry.predkoscObracania;
		if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
	}
}

void Belt::wyznaczPrzestrzenKolizji()
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
