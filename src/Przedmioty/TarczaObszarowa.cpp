/*
 * TarczaObszarowa.cpp
 *
 *  Created on: 11 mar 2017
 *      Author: przemo
 */

#include "TarczaObszarowa.h"

ParametryTarczyObszarowej TarczaObszarowa::parametry = ParametryTarczyObszarowej();

TarczaObszarowa::TarczaObszarowa(Punkt p)
{
	pozycja=p;
	zycie=10;
	stanWidocznosci=parametry.czasWidocznosci;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
}

TarczaObszarowa::~TarczaObszarowa()
{

}

void TarczaObszarowa::zniszcz()
{
	Obiekt::zniszcz();
	if(punktZaczepu!=0)	punktZaczepu->ustawCzyPosiadaTarcze(false);
}

void TarczaObszarowa::zadajObrazenia(double obrazenia)
{
	stanWidocznosci=parametry.czasWidocznosci;
}

void TarczaObszarowa::wyznaczPrzestrzenKolizji()
{
	//Wymiary wymiary = Wymiary(230,30);
	std::vector<OkragKolizji> okregi;
	okregi.clear();

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(0,0),340));
	ustawPrzestrzenKolizji(okregi);
}

void TarczaObszarowa::wyznaczKolejnyStan()
{
	if(stanWidocznosci>0) stanWidocznosci--;
}

void TarczaObszarowa::wyznaczKlatkeAnimacji()
{
	if(pozycja.y<=parametryObiektow.poziomZiemi+parametry.odlegloscOdZiemi) klatkaAnimacji.y=1;
	else klatkaAnimacji.y=0;
	klatkaAnimacji.x=4-stanWidocznosci/(parametry.czasWidocznosci/5);
}

