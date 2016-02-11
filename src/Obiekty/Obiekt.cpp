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
			return pozycja;
		}
		else
			return Punkt(punktZaczepu->zwrocPozycje().x+pozycja.x,punktZaczepu->zwrocPozycje().y+pozycja.y);
	}
	else
	{
		return pozycja;
	}
}

void Obiekt::ustawPunktZaczepu(Obiekt *p)
{
	pozycja.x = pozycja.x-p->zwrocPozycje().x;
	pozycja.y = pozycja.y-p->zwrocPozycje().y;
	punktZaczepu=p;
	czyZaczepiony=true;
}

void Obiekt::usunPunktZaczepu()
{
	pozycja.x = punktZaczepu->zwrocPozycje().x+pozycja.x;
	pozycja.y = punktZaczepu->zwrocPozycje().y+pozycja.y;
	punktZaczepu=0;
	czyZaczepiony=false;
}
