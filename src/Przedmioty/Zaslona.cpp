/*
 * Zaslona.cpp
 *
 *  Created on: 27-09-2016
 *      Author: przemo
 */

#include "Zaslona.h"

Zaslona::Zaslona(Punkt p)
{
	pozycja=p;
	zycie=1;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
}

Zaslona::~Zaslona()
{

}

void Zaslona::wyznaczPrzestrzenKolizji()
{
	Wymiary wymiary = Wymiary(230,70);
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(0,0),wymiary));
	ustawPrzestrzenKolizji(prostokaty);
}


void Zaslona::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.x=0;
	klatkaAnimacji.y=0;
}
