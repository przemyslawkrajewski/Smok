/*
 * PrzestrzenKolizji.cpp
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#include "PrzestrzenKolizji.h"

PrzestrzenKolizji::PrzestrzenKolizji()
{
	figury.clear();
}

std::pair<bool,Punkt> PrzestrzenKolizji::sprawdzKolizje(PrzestrzenKolizji *przestrzen)
{
	int sumaPromieni = promien+przestrzen->zwrocPromien();
	int roznicaX = zwrocPozycje().x-przestrzen->zwrocPozycje().x;
	if(roznicaX<0) roznicaX=-roznicaX;
	int roznicaY = zwrocPozycje().y-przestrzen->zwrocPozycje().y;
	if(roznicaY<0) roznicaY=-roznicaY;
	if(roznicaY>sumaPromieni || roznicaX>sumaPromieni) return std::pair<bool,Punkt>(false,Punkt());

	std::vector<OkragKolizji> *figury2=przestrzen->zwrocFigury();
	for(std::vector<OkragKolizji>::iterator i = figury.begin(); i!=figury.end(); i++)
	{
		for(std::vector<OkragKolizji>::iterator j = figury2->begin(); j!=figury2->end(); j++)
		{
			std::pair<bool,Punkt> kolizja = i->sprawdzKolizje(&(*j));
			if(kolizja.first) return std::pair<bool,Punkt>(true,Punkt(kolizja.second));
		}
	}
	return std::pair<bool,Punkt>(false,Punkt());
}

void PrzestrzenKolizji::ustawFigury(std::vector<OkragKolizji> f, Punkt* p)
{
	figury.clear();
	figury=f;
	pozycjaObiektu = p;
	std::vector<OkragKolizji>::iterator i=figury.begin();
	Punkt maksP(i->zwrocPozycjeWzgledemObiektu());
	Punkt minP(i->zwrocPozycjeWzgledemObiektu());
	double maksR = i->zwrocPromien();
	for(;i!=figury.end();i++)
	{
		if(maksP.x<i->zwrocPozycjeWzgledemObiektu().x) maksP.x=i->zwrocPozycjeWzgledemObiektu().x;
		if(maksP.y<i->zwrocPozycjeWzgledemObiektu().y) maksP.y=i->zwrocPozycjeWzgledemObiektu().y;
		if(minP.x>i->zwrocPozycjeWzgledemObiektu().x) minP.x=i->zwrocPozycjeWzgledemObiektu().x;
		if(minP.y>i->zwrocPozycjeWzgledemObiektu().y) minP.y=i->zwrocPozycjeWzgledemObiektu().y;
		if(maksR<i->zwrocPromien()) maksR=i->zwrocPromien();
	}
	pozycja.x=minP.x+(maksP.x-minP.x)/2;
	pozycja.y=minP.y+(maksP.y-minP.y)/2;
	if((maksP.x-minP.x) > (maksP.y-minP.y)) promien = maksR+(maksP.x-minP.x);
	else promien = maksR+(maksP.y-minP.y);

}
