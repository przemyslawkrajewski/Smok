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

struct ParametryStrzaly
{
	double wspolczynnikGrawitacji;
	ParametryStrzaly()
	{
		wspolczynnikGrawitacji=0.30;
	}
};

class Strzala: public Pocisk
{
public:
	Strzala(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
	virtual void zniszcz();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();
	void ustawCzyCicha(bool b) {cicha=b;}
	bool czyCicha() {return cicha;}

	static ParametryStrzaly parametry;
private:
	bool cicha;
};

#endif /* STRZALA_H_ */
