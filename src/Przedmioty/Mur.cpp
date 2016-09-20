/*
 * Mur.cpp
 *
 *  Created on: 18-04-2016
 *      Author: przemo
 */

#include "Mur.h"

Mur::Mur(RozmiarMuru r,Punkt p): Przedmiot()
{
	pozycja=p;
	rozmiar = r;
	zycie=1;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
}

Mur::Mur(Punkt p)
{
	pozycja=p;
	rozmiar = sredni;
	zycie=1;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
}

Mur::~Mur()
{

}

void Mur::wyznaczPrzestrzenKolizji()
{
	double a; //Szerohosc
	double b; //Wysokosc
	switch(rozmiar)
	{
	case maly:
		a=100;
		b=50;
		break;
	case sredni:
		a=400;
		b=150;
		break;
	case duzy:
		a=1500;
		b=1300;
		break;

	}
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(0,0),a,b));
	ustawPrzestrzenKolizji(prostokaty);
}

void Mur::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=0;
	klatkaAnimacji.y=0;
}
