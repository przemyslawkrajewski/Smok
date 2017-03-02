/*
 * Strzala.h
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#ifndef ODLAMEK_H_
#define ODLAMEK_H_

#include <iostream>
#include <math.h>
#include "Pocisk.h"

struct ParametryOdlamka
{
	double wspolczynnikGrawitacji;
	ParametryOdlamka()
	{
		wspolczynnikGrawitacji=0.40;
	}
};

class Odlamek: public Pocisk
{
public:
	Odlamek(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();

	static ParametryOdlamka parametry;
};

#endif /* ODLAMEK_H_ */
