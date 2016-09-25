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
	ProstokatKolizji(const Punkt *po, const Punkt *v,Punkt p, Wymiary w);
	ProstokatKolizji(const Punkt *po, const Punkt *v,Punkt p, double b);

	double zwrocBok1() {return wymiary.x;}
	double zwrocBok2() {return wymiary.y;}
	double zwrocDluzszyBok() {return wymiary.x>wymiary.y?wymiary.x:wymiary.y;}

	std::pair<bool,Punkt> sprawdzKolizje(ProstokatKolizji *prostokat);

private:
	std::pair<bool,Punkt> punktPrzecieciaOdcinkaZProstaPionowa(Punkt p1, Punkt p2, double X);
	std::pair<bool,Punkt> punktPrzecieciaOdcinkaZProstaPozioma(Punkt p1, Punkt p2, double Y);

private:
	Wymiary wymiary;
};

#endif /* PROSTOKATKOLIZJI_H_ */
