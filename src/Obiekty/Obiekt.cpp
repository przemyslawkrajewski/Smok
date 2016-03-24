/*
 * Obiekt.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include "Obiekt.h"

Obiekt::Obiekt()
{
	istnieje=true;
	zniszczony=false;
	punktZaczepu=0;
	czyZaczepiony=false;

	zwroconyWPrawo=true;
	zycie=1000;
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
	if(przestrzenKolizji.zwrocFigury()->empty()) return Punkt();

	return przestrzenKolizji.zwrocFigury()->begin()->zwrocPozycje();
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
	}
}

void Obiekt::usunPunktZaczepu()
{
	pozycja.x = punktZaczepu->zwrocPozycje().x;
	pozycja.y = punktZaczepu->zwrocPozycje().y;
	punktZaczepu=0;
	czyZaczepiony=false;
}
