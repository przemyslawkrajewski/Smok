/*
 * ProstokatKolizji.cpp
 *
 *  Created on: 08-04-2016
 *      Author: przemo
 */

#include "ProstokatKolizji.h"

ProstokatKolizji::ProstokatKolizji(const Punkt *po, const Punkt *v,Punkt p, Wymiary w): FiguraKolizji(po,v,p)
{
	wymiary=w;
}

ProstokatKolizji::ProstokatKolizji(const Punkt *po, const Punkt *v,Punkt p, double b): FiguraKolizji(po,v,p)
{
	wymiary = Punkt(b,b);
}

std::pair<bool,Punkt> ProstokatKolizji::punktPrzecieciaOdcinkaZProstaPionowa(Punkt p1, Punkt p2, double X)
{
	if((p1.x<X && p2.x<X) || (p1.x>X && p2.x>X)) return std::pair<bool,Punkt> (false,Punkt());
	double a=(p1.x-X)/(p1.x-p2.x);
	return std::pair<bool,Punkt>(true,Punkt(X,p1.y+(p2.y-p1.y)*a));
}

std::pair<bool,Punkt> ProstokatKolizji::punktPrzecieciaOdcinkaZProstaPozioma(Punkt p1, Punkt p2, double Y)
{
	if((p1.y<Y && p2.y<Y) || (p1.y>Y && p2.y>Y)) return std::pair<bool,Punkt> (false,Punkt());
	double a=(p1.y-Y)/(p1.y-p2.y);
	return std::pair<bool,Punkt>(true,Punkt(p1.x+(p2.x-p1.x)*a,Y));
}

std::pair<bool,Punkt> ProstokatKolizji::sprawdzKolizje(ProstokatKolizji *prostokat)
{
	double d1 = (zwrocBok1()+prostokat->zwrocBok1())/2;
	double d2 = (zwrocBok2()+prostokat->zwrocBok2())/2;

	Punkt v = Punkt(-zwrocPredkoscObiektu().x+prostokat->zwrocPredkoscObiektu().x,-zwrocPredkoscObiektu().y+prostokat->zwrocPredkoscObiektu().y);
	double X1 = prostokat->zwrocPozycje().x-d1;
	double X2 = prostokat->zwrocPozycje().x+d1;
	double Y1 = prostokat->zwrocPozycje().y-d2;
	double Y2 = prostokat->zwrocPozycje().y+d2;
	Punkt srodek = prostokat->zwrocPozycje();
	Punkt p1 = Punkt(zwrocPozycje().x,zwrocPozycje().y);
	Punkt p2 = p1-v;
	if(p1.x>X1 && p1.x<X2 && p1.y>Y1 && p1.y<Y2) return std::pair<bool,Punkt>(true,p1);

	std::pair<bool,Punkt> para;
	if(p1.x<srodek.x)
	{
		para = punktPrzecieciaOdcinkaZProstaPionowa(p1,p2,X1);
		if(para.first && para.second.y>Y1 && para.second.y<Y2) return std::pair<bool,Punkt>(true,para.second);
	}
	if(p1.x>srodek.x)
	{
		para = punktPrzecieciaOdcinkaZProstaPionowa(p1,p2,X2);
		if(para.first && para.second.y>Y1 && para.second.y<Y2) return std::pair<bool,Punkt>(true,para.second);
	}
	if(p1.y<srodek.y)
	{
		para= punktPrzecieciaOdcinkaZProstaPozioma(p1,p2,Y1);
		if(para.first && para.second.x>X1 && para.second.x<X2) return std::pair<bool,Punkt>(true,para.second);
	}
	if(p1.y>srodek.y)
	{
		para= punktPrzecieciaOdcinkaZProstaPozioma(p1,p2,Y2);
		if(para.first && para.second.x>X1 && para.second.x<X2) return std::pair<bool,Punkt>(true,para.second);
	}

	return std::pair<bool,Punkt>(false,Punkt());

}
