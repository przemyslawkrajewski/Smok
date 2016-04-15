/*
 * OkragKolizji.h
 *
 *  Created on: 10-08-2015
 *      Author: przemo
 */

#ifndef OKRAGKOLIZJI_H_
#define OKRAGKOLIZJI_H_

#include <iostream>
#include <math.h>
#include <utility>
#include "../Obiekty/Punkt.h"
#include "FiguraKolizji.h"

class OkragKolizji :public FiguraKolizji
{
public:
	OkragKolizji(const Punkt *po, const Punkt *v,Punkt p, double r);

	void ustawPozycje(Punkt p) {pozycja=p;}

	double zwrocPromien() {return promien;}

	std::pair<bool,Punkt> sprawdzKolizje(OkragKolizji *okrag);

private:
	double promien;
};

#endif /* OKRAGKOLIZJI_H_ */
