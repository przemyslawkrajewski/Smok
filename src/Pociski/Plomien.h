/*
 * Plomien.h
 *
 *  Created on: 21-08-2013
 *      Author: przemo
 */

#include <iostream>
#include <math.h>
#include "Pocisk.h"

#ifndef PLOMIEN_H_
#define PLOMIEN_H_

class Plomien: public Pocisk
{
public:
	Plomien(double nx,double ny, double nvx, double nvy, double nczasTrwania,double nKat);
	Plomien(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);
	~Plomien();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();
private:
	int czasTrwania;
};

#endif /* PLOMIEN_H_ */
