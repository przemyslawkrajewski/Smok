/*
 * TarczaPersonalna.cpp
 *
 *  Created on: 27-09-2016
 *      Author: przemo
 */

#include "TarczaPersonalna.h"

ParametryTarczyPersonalnej TarczaPersonalna::parametry = ParametryTarczyPersonalnej();

TarczaPersonalna::TarczaPersonalna(Punkt p)
{
	pozycja=p;
	zycie=100;
	stanWidocznosci=parametry.czasWidocznosci;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
}

TarczaPersonalna::~TarczaPersonalna()
{

}

void TarczaPersonalna::zniszcz()
{
	Obiekt::usun();
	if(punktZaczepu!=0)	punktZaczepu->ustawCzyPosiadaTarcze(false);
}

void TarczaPersonalna::zadajObrazenia(double obrazenia)
{
	zycie-=obrazenia;
	stanWidocznosci=parametry.czasWidocznosci;
}

void TarczaPersonalna::wyznaczPrzestrzenKolizji()
{
	//Wymiary wymiary = Wymiary(230,30);
	std::vector<OkragKolizji> okregi;
	okregi.clear();

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(0,0),50));
	ustawPrzestrzenKolizji(okregi);
}

void TarczaPersonalna::wyznaczKolejnyStan()
{
	if(zycie<0 || punktZaczepu==0)
	{
		zycie=0;
		przestrzenKolizji.wyczyscFigury();
		zniszcz();
	}
	else
	{
		if(stanWidocznosci>0) stanWidocznosci--;
	}

}

void TarczaPersonalna::wyznaczKlatkeAnimacji()
{
	klatkaAnimacji.y=0;
	klatkaAnimacji.x=4-stanWidocznosci/(parametry.czasWidocznosci/5);
}
