/*
 * PrzestrzenKolizji.cpp
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#include "PrzestrzenKolizji.h"

PrzestrzenKolizji::PrzestrzenKolizji(const Punkt* p, const Punkt* v): FiguraKolizji(p,v,Punkt(0,0))
{
	okregi.clear();
	dlugoscBoku=0;
}

std::pair<bool,Punkt> PrzestrzenKolizji::sprawdzKolizje(PrzestrzenKolizji *przestrzen)
{
	int sumaPromieni = dlugoscBoku+przestrzen->zwrocDlugoscBoku();
	int roznicaX = zwrocPozycje().x-przestrzen->zwrocPozycje().x;
	if(roznicaX<0) roznicaX=-roznicaX;
	int roznicaY = zwrocPozycje().y-przestrzen->zwrocPozycje().y;
	if(roznicaY<0) roznicaY=-roznicaY;
	if(roznicaY>sumaPromieni || roznicaX>sumaPromieni) return std::pair<bool,Punkt>(false,Punkt());

	if(false)
	{
		std::vector<ProstokatKolizji> *prostokaty2=przestrzen->zwrocProstokaty();
		for(std::vector<ProstokatKolizji>::iterator i = prostokaty.begin(); i!=prostokaty.end(); i++)
		{
			for(std::vector<ProstokatKolizji>::iterator j = prostokaty2->begin(); j!=prostokaty2->end(); j++)
			{
				std::pair<bool,Punkt> kolizja = i->sprawdzKolizje(&(*j));
				if(kolizja.first) return std::pair<bool,Punkt>(true,Punkt(kolizja.second));
			}
		}
	}
	else
	{
		std::vector<OkragKolizji> *okregi2=przestrzen->zwrocOkregi();
		for(std::vector<OkragKolizji>::iterator i = okregi.begin(); i!=okregi.end(); i++)
		{
			for(std::vector<OkragKolizji>::iterator j = okregi2->begin(); j!=okregi2->end(); j++)
			{
				std::pair<bool,Punkt> kolizja = i->sprawdzKolizje(&(*j));
				if(kolizja.first) return std::pair<bool,Punkt>(true,Punkt(kolizja.second));
			}
		}
	}
	return std::pair<bool,Punkt>(false,Punkt());
}

void PrzestrzenKolizji::ustawOkregi(std::vector<OkragKolizji> f)
{
	okregi.clear();
	okregi=f;
	std::vector<OkragKolizji>::iterator i=okregi.begin();
	Punkt maksP(i->zwrocPozycjeWzgledemObiektu());
	Punkt minP(i->zwrocPozycjeWzgledemObiektu());
	double maksR = i->zwrocPromien();
	for(;i!=okregi.end();i++)
	{
		if(maksP.x<i->zwrocPozycjeWzgledemObiektu().x) maksP.x=i->zwrocPozycjeWzgledemObiektu().x;
		if(maksP.y<i->zwrocPozycjeWzgledemObiektu().y) maksP.y=i->zwrocPozycjeWzgledemObiektu().y;
		if(minP.x>i->zwrocPozycjeWzgledemObiektu().x) minP.x=i->zwrocPozycjeWzgledemObiektu().x;
		if(minP.y>i->zwrocPozycjeWzgledemObiektu().y) minP.y=i->zwrocPozycjeWzgledemObiektu().y;
		if(maksR<i->zwrocPromien()) maksR=i->zwrocPromien();
	}
	pozycja.x=minP.x+(maksP.x-minP.x)/2;
	pozycja.y=minP.y+(maksP.y-minP.y)/2;
	if((maksP.x-minP.x) > (maksP.y-minP.y)) dlugoscBoku = maksR+maksR+(maksP.x-minP.x);
	else dlugoscBoku = maksR+maksR+(maksP.y-minP.y);
}

void PrzestrzenKolizji::ustawProstokaty(std::vector<ProstokatKolizji> f)
{
	prostokaty.clear();
	prostokaty=f;
	if(prostokaty.size()==0)
	{
		pozycja=Punkt();
		dlugoscBoku=0;
		return;
	}

	std::vector<ProstokatKolizji>::iterator i=prostokaty.begin();
	Punkt maksP(i->zwrocPozycjeWzgledemObiektu());
	Punkt minP(i->zwrocPozycjeWzgledemObiektu());
	double maksR = i->zwrocDluzszyBok();
	for(;i!=prostokaty.end();i++)
	{
		if(maksP.x<i->zwrocPozycjeWzgledemObiektu().x) maksP.x=i->zwrocPozycjeWzgledemObiektu().x;
		if(maksP.y<i->zwrocPozycjeWzgledemObiektu().y) maksP.y=i->zwrocPozycjeWzgledemObiektu().y;
		if(minP.x>i->zwrocPozycjeWzgledemObiektu().x) minP.x=i->zwrocPozycjeWzgledemObiektu().x;
		if(minP.y>i->zwrocPozycjeWzgledemObiektu().y) minP.y=i->zwrocPozycjeWzgledemObiektu().y;
		if(maksR<i->zwrocDluzszyBok()) maksR=i->zwrocDluzszyBok();
	}
	pozycja.x=minP.x+(maksP.x-minP.x)/2;
	pozycja.y=minP.y+(maksP.y-minP.y)/2;
	if((maksP.x-minP.x) > (maksP.y-minP.y)) dlugoscBoku = maksR+(maksP.x-minP.x);
	else dlugoscBoku = maksR+(maksP.y-minP.y);
}
