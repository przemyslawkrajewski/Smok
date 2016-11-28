/*
 * Belt.h
 *
 *  Created on: 28-11-2016
 *      Author: przemo
 */

#ifndef SRC_POCISKI_BELT_H_
#define SRC_POCISKI_BELT_H_

#include <iostream>
#include <math.h>
#include "Pocisk.h"

struct ParametryBeltu
{
	int czasTrwaniaPoZniszczeniu;
	double predkoscObracania;
	double wspolczynnikGrawitacji;
	double wspolczynnikZwalniania;
	ParametryBeltu()
	{
		czasTrwaniaPoZniszczeniu=50;
		predkoscObracania=0.8;
		wspolczynnikGrawitacji=1.00;
		wspolczynnikZwalniania=0.99;
	}
};

class Belt: public Pocisk {
public:
	Belt(double nx, double ny, double nvx, double nvy, double nCzasTrwania, double nKat);
	Belt(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
	virtual void zniszcz();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();

	static ParametryBeltu parametry;
};

#endif /* SRC_POCISKI_BELT_H_ */
