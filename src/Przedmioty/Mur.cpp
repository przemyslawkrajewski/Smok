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
	Wymiary wymiary = zwrocWymiary();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(0,0),wymiary));
	ustawPrzestrzenKolizji(prostokaty);
}

Wymiary Mur::zwrocWymiary()
{
	switch(rozmiar)
	{
	case maly:
		return Wymiary(180,60);
	case sredni:
		return Wymiary(600,180);
	case duzy:
		return Wymiary(1500,900);
	}
}

void Mur::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=0;
	klatkaAnimacji.y=0;
}
