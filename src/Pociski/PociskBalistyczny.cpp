/*
 * Strzala.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "PociskBalistyczny.h"

ParametryPociskuBalistycznego PociskBalistyczny::parametry;

PociskBalistyczny::PociskBalistyczny(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	obrazenia=500;
	wyznaczKolejnyStan();
	wyznaczKlatkeAnimacji();
}

void PociskBalistyczny::zniszcz()
{
	Obiekt::zniszcz();
	predkosc.x=predkosc.y=0;
}

double PociskBalistyczny::zwrocKat()
{
	return katNachylenia;
}

void PociskBalistyczny::wyznaczKolejnyStan()
{
	if(!(predkosc.x==0 && predkosc.y==0))
	{
		katNachylenia=1.57-atan2(predkosc.y,predkosc.x);
		if(katNachylenia<0) katNachylenia+=M_PI*2;
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

void PociskBalistyczny::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.y=0;
	double kat = katNachylenia;
	if(kat<0) kat+=M_PI*2;
	klatkaAnimacji.x=0.5+((double)(kat)/((M_PI*2)/32));
	klatkaAnimacji.x=(int)klatkaAnimacji.x;
	//if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
}

void PociskBalistyczny::wyznaczPrzestrzenKolizji()
{
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	Punkt korekta;
	korekta.x = 60*cos(katNachylenia-M_PI/2);
	korekta.y = -60*sin(katNachylenia-M_PI/2);

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,korekta,30));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,korekta,20));
	ustawPrzestrzenKolizji(okregi);
}
