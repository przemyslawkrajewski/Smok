/*
 * Plomien.cpp
 *
 *  Created on: 21-08-2013
 *      Author: przemo
 */

#include "Plomien.h"

Plomien::Plomien(double nx,double ny, double nvx, double nvy, double nczasTrwania,double nKat) : Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja.x=nx;
	pozycja.y=ny;
	predkosc.x=nvx;
	predkosc.y=nvy;
	katNachylenia = nKat;
}

Plomien::Plomien(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat)
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
}

Plomien::~Plomien()
{

}

double Plomien::zwrocKat()
{
	//double k = atan2(-(predkosc.y),(predkosc.x))+3.14 + 1.57;
	//if(k>6.28) k-=6.28;

	return katNachylenia;
}

void Plomien::wyznaczKolejnyStan()
{
	pozycja.x+=predkosc.x;
	pozycja.y+=predkosc.y;
	//predkosc.y-=0.51;
	czasTrwania--;
	if(pozycja.y<parametryObiektow.poziomZiemi) usun();
	if(czasTrwania<0) usun();
}

void Plomien::wyznaczKlatkeAnimacji()
{

	klatkaAnimacji.x=1;
	klatkaAnimacji.x=(0.5+(double)(katNachylenia)/(6.28/32));
	klatkaAnimacji.x=(int)klatkaAnimacji.x;
	if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
}

void Plomien::wyznaczPrzestrzenKolizji()
{
	std::vector<OkragKolizji> f;
	f.clear();
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(35,-35),7));
	ustawPrzestrzenKolizji(f);
}
