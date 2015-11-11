/*
 * Strzelcy.cpp
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#include "Strzelcy.h"

Strzelcy::Strzelcy()
{
	istnieje=true;
}

void Strzelcy::wyznaczKolejnyStan()
{
	//std::cout << "Strzelcy: " << strzelcy.size() << "\n";
	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();)
	{
		i->ustawCel(cel);
		std::pair<Klawiatura,Myszka> sterowanie = i->wyznaczSterowanie();
		i->wyznaczKolejnyStan(&sterowanie.first,&sterowanie.second);

		if(!i->czyIstnieje())
		{
			i=strzelcy.erase(i);
		}
		else i++;
	}
}

void Strzelcy::wyznaczKlatkeAnimacji()
{
	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();i++)
	{
		i->wyznaczKlatkeAnimacji();
	}
}

void Strzelcy::wyznaczPrzestrzenKolizji()
{
	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();i++)
	{
		i->wyznaczPrzestrzenKolizji();
	}
}

Strzelec* Strzelcy::dodajStrzelca(Strzelec s)
{
	strzelcy.push_back(s);
	return &(strzelcy.back());
}

std::list< Punkt > Strzelcy::zwrocPozycje()
{
	std::list<Punkt> punkty;

	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();i++)
	{
		punkty.push_back((i->zwrocPozycje()));
	}

	return punkty;
}

std::list< Punkt > Strzelcy::zwrocKlatkeAnimacji()
{
	std::list<Punkt> klatki;

	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();i++)
	{
		klatki.push_back((i->zwrocKlatkeAnimacji()));
	}

	return klatki;
}

std::list< bool > Strzelcy::czyZwroconyWPrawo()
{
	std::list<bool> prawo;

	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();i++)
	{
		prawo.push_back((i->czyZwroconyWPrawo()));
	}

	return prawo;
}

std::list< PrzestrzenKolizji > Strzelcy::zwrocPrzestrzenKolizji()
{
	std::list<PrzestrzenKolizji> przestrzen;

	for(std::list<Strzelec>::iterator i=strzelcy.begin();i!=strzelcy.end();i++)
	{
		przestrzen.push_back(*(i->zwrocPrzestrzenKolizji()));
	}

	return przestrzen;
}
