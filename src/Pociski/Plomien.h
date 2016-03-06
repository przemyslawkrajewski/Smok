/*
 * Plomien.h
 *
 *  Created on: 21-08-2013
 *      Author: przemo
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Pocisk.h"

#ifndef PLOMIEN_H_
#define PLOMIEN_H_

struct ParametryOgnia
{
	double czasWygasania;
	double czasPalenia;
	double predkoscOpadania;

	ParametryOgnia()
	{
		czasWygasania=20;
		czasPalenia=50;
		predkoscOpadania=5;
	}
};

class Plomien: public Pocisk
{
public:
	enum StanPlomienia {wPowietrzu, naCelu};

public:
	Plomien(double nx,double ny, double nvx, double nvy, double nczasTrwania,double nKat);
	Plomien(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);
	~Plomien();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
	virtual void zniszcz();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();
	bool czyBylZaczepiony() {return bylZaczepiony;}
private:

	static ParametryOgnia parametry;
	StanPlomienia stan;

	int czasTrwania;

	double bylZaczepiony;
};


#endif /* PLOMIEN_H_ */
