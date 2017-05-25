/*
 * Mur.cpp
 *
 *  Created on: 18-04-2016
 *      Author: przemo
 */

#include "Mur.h"

Mur::Mur(Wymiary r, TypMuru t, Punkt p): Przedmiot()
{
	pozycja=p;
	rozmiar = r;
	typ = t;
	zycie=1;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
}

Mur::Mur(Punkt p)
{
	pozycja=p;
	rozmiar = Wymiary(60,60);
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

	if(typ!=czarneTlo && typ!=szareTlo)
		prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(0,0),wymiary));
	ustawPrzestrzenKolizji(prostokaty);
}

Wymiary Mur::zwrocWymiary()
{
	return rozmiar;
}

Mur::TypMuru Mur::zwrocTyp()
{
	return typ;
}

void Mur::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=0;
	klatkaAnimacji.y=0;
}
