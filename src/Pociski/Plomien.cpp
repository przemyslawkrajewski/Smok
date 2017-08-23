/*
 * Plomien.cpp
 *
 *  Created on: 21-08-2013
 *      Author: przemo
 */

#include "Plomien.h"

ParametryOgnia Plomien::parametry;

Plomien::Plomien(double nx,double ny, double nvx, double nvy, double nczasTrwania,double nKat) : Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja.x=nx;
	pozycja.y=ny;
	predkosc.x=nvx;
	predkosc.y=nvy;
	katNachylenia = nKat;
	stan = wPowietrzu;
	bylZaczepiony=false;
	obrazenia = 0;
	spopielenie = false;
}

Plomien::Plomien(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat) : Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	stan = wPowietrzu;
	bylZaczepiony=false;
	obrazenia = 0;
	spopielenie = false;
}

Plomien::~Plomien()
{

}

void Plomien::zniszcz()
{
	if(!zniszczony)
	{
		Obiekt::zniszcz();
		predkosc.x=predkosc.y=0;
		czasTrwania=parametry.czasPalenia;
		if(!spopielenie) czasTrwania*=2;
		stan = naCelu;
		obrazenia=bazoweObrazenia*parametry.obrazeniaNaCelu;
	}
}

double Plomien::zwrocKat()
{
	return katNachylenia;
}

void Plomien::wyznaczKolejnyStan()
{
	if(!zniszczony) //Plomien leci
	{

		pozycja.x+=predkosc.x;
		pozycja.y+=predkosc.y;

		if(pozycja.y<parametryObiektow.poziomZiemi) //Jesli dotknie ziemi to zaczyna plonac
		{
			pozycja.x=((parametryObiektow.poziomZiemi-pozycja.y)/predkosc.y)*predkosc.x+pozycja.x;
			pozycja.y=parametryObiektow.poziomZiemi;
			zniszcz();
		}
	}
	else //Plomien na celu
	{
		if(!czyZaczepiony && pozycja.y>parametryObiektow.poziomZiemi)
		{
			pozycja.y-=parametry.predkoscOpadania;
		}
		if(!czyZaczepiony) obrazenia=bazoweObrazenia*parametry.obrazeniaNaZiemi;

		if(czyZaczepiony) bylZaczepiony=true;
	}

	czasTrwania--;
	if(czasTrwania<0) usun();
}

void Plomien::wyznaczKlatkeAnimacji()
{
	if(spopielenie) klatkaAnimacji.y = 1;
	else klatkaAnimacji.y = 0;

	switch(stan)
	{
	case wPowietrzu:
		klatkaAnimacji.x=1;
		klatkaAnimacji.x=(0.5+(double)(katNachylenia)/(6.28/32));
		klatkaAnimacji.x=(int)klatkaAnimacji.x;
		if(klatkaAnimacji.x>31) klatkaAnimacji.x=0;
		break;
	case naCelu:
		if(czasTrwania>parametry.czasWygasania)
		{
			klatkaAnimacji.x+=0.5;
			if(klatkaAnimacji.x>=35) klatkaAnimacji.x=32;
			if(klatkaAnimacji.x<32) klatkaAnimacji.x=32+rand()%4;
		}
		else
		{
			klatkaAnimacji.x+=0.5;
			if(klatkaAnimacji.x>=38) klatkaAnimacji.x=35;
			if(klatkaAnimacji.x<35) klatkaAnimacji.x=35+rand()%4;
		}
		break;
	}
}

void Plomien::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki = 70/2;
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(35-rozmiarKlatki,-35+rozmiarKlatki),14));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(35-rozmiarKlatki,-35+rozmiarKlatki),7));
	ustawPrzestrzenKolizji(okregi);

}
