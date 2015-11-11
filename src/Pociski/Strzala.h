/*
 * Strzala.h
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#ifndef STRZALA_H_
#define STRZALA_H_

#include <iostream>
#include <math.h>
#include "Pocisk.h"

class Strzala: public Pocisk
{
public:
	Strzala(double nx, double ny, double nvx, double nvy, double nCzasTrwania, double nKat);
	Strzala(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();
private:
	int czasTrwania;
};

#endif /* STRZALA_H_ */
