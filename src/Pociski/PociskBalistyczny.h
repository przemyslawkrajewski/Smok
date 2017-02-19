/*
 * Pocisk.h
 *
 *  Created on: 13-02-2015
 *      Author: przemo
 */

#ifndef POCISKBALISTYCZNY_H_
#define POCISKBALISTYCZNY_H_

#include <math.h>
#include "Pocisk.h"

struct ParametryPociskuBalistycznego
{
	double wspolczynnikGrawitacji;
	ParametryPociskuBalistycznego()
	{
		wspolczynnikGrawitacji=0.40;
	}
};

class PociskBalistyczny : public Pocisk
{
public:
	PociskBalistyczny(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
	virtual void zniszcz();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();

static ParametryPociskuBalistycznego parametry;
};

#endif /* POCISKBALISTYCZNY_H_ */