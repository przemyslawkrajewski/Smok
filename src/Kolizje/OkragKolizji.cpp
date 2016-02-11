/*
 * OkragKolizji.cpp
 *
 *  Created on: 10-08-2015
 *      Author: przemo
 */

#include "OkragKolizji.h"

OkragKolizji::OkragKolizji(const Punkt *po, const Punkt *v, Punkt p, double r)
{
	pozycjaObiektu = po;
	predkoscObiektu = v;
	pozycja = p;
	promien = r;
}

std::pair<bool,Punkt> OkragKolizji::sprawdzKolizje(OkragKolizji *okrag)
{
	//
	double sumaPromieni = promien+okrag->zwrocPromien();

	Wektor wektor=zwrocPredkoscObiektu();
	wektor.x=-wektor.x+okrag->zwrocPredkoscObiektu().x;
	wektor.y=-wektor.y+okrag->zwrocPredkoscObiektu().y;
			//wektor.x=-2;wektor.y=0;
	Punkt srodekOkregu;
	srodekOkregu.x=okrag->zwrocPozycje().x-zwrocPozycje().x;
	srodekOkregu.y=okrag->zwrocPozycje().y-zwrocPozycje().y;
			//srodekOkregu.x=5;srodekOkregu.y=-2;
	double dlugoscWektora = sqrt(wektor.x*wektor.x+wektor.y*wektor.y);
	dlugoscWektora = dlugoscWektora*dlugoscWektora;
	double iloczynSkalarny = wektor.x*srodekOkregu.x+wektor.y*srodekOkregu.y;
	double iloczyn = iloczynSkalarny/dlugoscWektora;
	Wektor rzutWektora;
	rzutWektora.x = wektor.x*iloczyn;
	rzutWektora.y = wektor.y*iloczyn;
	//std::cout << rzutWektora.x << "  " << rzutWektora.y << "\n";

	Punkt p1;
	Punkt p2;
	if(wektor.x>0)
	{
		if(rzutWektora.x<0)
		{
			p1 = srodekOkregu;
			p2 = Punkt(0,0);
		}
		else if(rzutWektora.x<wektor.x)
		{
			p1 = srodekOkregu;
			p2 = rzutWektora;
		}
		else
		{
			p1 = srodekOkregu;
			p2 = wektor;
		}
	}
	else
	{
		if(rzutWektora.x>0)
		{
			p1 = srodekOkregu;
			p2 = Punkt(0,0);
		}
		else if(rzutWektora.x>wektor.x)
		{
			p1 = srodekOkregu;
			p2 = rzutWektora;
		}
		else
		{
			p1 = srodekOkregu;
			p2 = wektor;
		}
	}
	double r = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);

	Punkt punktKolizji = Punkt(zwrocPozycje().x+(p1.x+p2.x)/2,zwrocPozycje().y+(p1.y+p2.y)/2);

	if(r<sumaPromieni*sumaPromieni)
		return std::pair<bool,Punkt>(true,Punkt(punktKolizji));
	else
		return std::pair<bool,Punkt>(false,Punkt());

	/*
	int sumaPromieni = promien+okrag->zwrocPromien();
	int roznicaX = zwrocPozycje().x-okrag->zwrocPozycje().x;
	if(roznicaX<0) roznicaX=-roznicaX;
	int roznicaY = zwrocPozycje().y-okrag->zwrocPozycje().y;
	if(roznicaY<0) roznicaY=-roznicaY;
	//if(roznicaY>sumaPromieni || roznicaX>sumaPromieni) return false;
	double d = roznicaX*roznicaX   +   roznicaY*roznicaY  ;
	if (d< sumaPromieni*sumaPromieni) return true;
	else
		return false;//*/
}
