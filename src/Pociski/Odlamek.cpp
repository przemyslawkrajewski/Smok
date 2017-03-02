/*
 * Strzala.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Odlamek.h"

ParametryOdlamka Odlamek::parametry;

Odlamek::Odlamek(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat): Pocisk()
{
	czasTrwania=nczasTrwania;
	pozycja=nPozycja;
	predkosc=nPredkosc;
	katNachylenia = nKat;
	obrazenia=5;
}

double Odlamek::zwrocKat()
{
	return 0;
}

void Odlamek::wyznaczKolejnyStan()
{
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
		usun();
	}
	if(czasTrwania<0) usun();
}

void Odlamek::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji=Punkt(32,0);
}

void Odlamek::wyznaczPrzestrzenKolizji()
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
