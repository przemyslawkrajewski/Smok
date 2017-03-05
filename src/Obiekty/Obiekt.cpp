/*
 * Obiekt.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include "Obiekt.h"

Obiekt::Obiekt(): przestrzenKolizji(PrzestrzenKolizji(&pozycja,&predkosc))
{
	przestrzenKolizji=PrzestrzenKolizji(&pozycja,&predkosc);
	istnieje=true;
	zniszczony=false;
	punktZaczepu=0;
	czyZaczepiony=false;

	zwroconyWPrawo=true;
	naZiemi=false;
	maTarcze=false;
	zycie=1;
	obrazenia=0;
}

Punkt Obiekt::zwrocPozycje()
{
	if(czyZaczepiony)
	{
		if(!punktZaczepu->czyIstnieje())
		{
			usun();
			return Punkt();
		}
		if(punktZaczepu->czyZniszczony())
		{
			usunPunktZaczepu();
		}
		else
		{
			pozycja.x=punktZaczepu->zwrocPozycje().x+pozycjaWzgledemObiektu.x;
			pozycja.y=punktZaczepu->zwrocPozycje().y+pozycjaWzgledemObiektu.y;

		}
	}

	return pozycja;
}

Punkt Obiekt::zwrocPozycjeCelu()
{
	if(!przestrzenKolizji.zwrocProstokaty()->empty()) return przestrzenKolizji.zwrocProstokaty()->begin()->zwrocPozycje();
	else if(!przestrzenKolizji.zwrocOkregi()->empty()) return przestrzenKolizji.zwrocOkregi()->begin()->zwrocPozycje();
	return Punkt();
}

void Obiekt::ustawPunktZaczepu(Obiekt *p)
{

	if(!czyZaczepiony)
	{
		pozycjaWzgledemObiektu.x = pozycja.x-p->zwrocPozycje().x;
		pozycjaWzgledemObiektu.y = pozycja.y-p->zwrocPozycje().y;
		punktZaczepu=p;
		pozycja.x=punktZaczepu->zwrocPozycje().x;
		pozycja.y=punktZaczepu->zwrocPozycje().y;
		czyZaczepiony=true;
		zwrocPozycje();
	}
}

void Obiekt::usunPunktZaczepu()
{
	pozycja.x = punktZaczepu->zwrocPozycje().x+pozycjaWzgledemObiektu.x;
	pozycja.y = punktZaczepu->zwrocPozycje().y+pozycjaWzgledemObiektu.y;
	punktZaczepu=0;
	czyZaczepiony=false;
}

void Obiekt::postawNaZiemi(double wysokosc)
{
	naZiemi=true;
	pozycja.y=wysokosc;
	predkosc.y=0;
}

void Obiekt::zatrzymajNaScianie()
{
	predkosc.x=0;
}

void Obiekt::zatrzymajNaSuficie()
{
	predkosc.y=0;
}
