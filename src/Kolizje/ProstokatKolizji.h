/*
 * ProstokatKolizji.h
 *
 *  Created on: 08-04-2016
 *      Author: przemo
 */

#ifndef PROSTOKATKOLIZJI_H_
#define PROSTOKATKOLIZJI_H_

#include <iostream>
#include <math.h>
#include <utility>
#include "../Obiekty/Punkt.h"
#include "FiguraKolizji.h"

class ProstokatKolizji: public FiguraKolizji
{
public:
	ProstokatKolizji(const Punkt *po, const Punkt *v,Punkt p, double b1, double b2);
	ProstokatKolizji(const Punkt *po, const Punkt *v,Punkt p, double b);

	double zwrocBok1() {return bok1;}
	double zwrocBok2() {return bok2;}
	double zwrocDluzszyBok() {return bok1>bok2?bok1:bok2;}

	std::pair<bool,Punkt> sprawdzKolizje(ProstokatKolizji *prostokat);

private:
	std::pair<bool,Punkt> punktPrzecieciaOdcinkaZProstaPionowa(Punkt p1, Punkt p2, double X);
	std::pair<bool,Punkt> punktPrzecieciaOdcinkaZProstaPozioma(Punkt p1, Punkt p2, double Y);

private:
	double bok1;	//Szerokosc
	double bok2;	//Wysokosc
};

#endif /* PROSTOKATKOLIZJI_H_ */
