/*
 * Strzala.h
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#ifndef POCISKKIEROWANY_H_
#define POCISKKIEROWANY_H_

#include <iostream>
#include <math.h>
#include "Pocisk.h"

struct ParametryPociskuKierowanego
{
	double maksymalnePrzyspieszenie;
	double wzmocnienieSterowania;
	ParametryPociskuKierowanego()
	{
		maksymalnePrzyspieszenie=10;
		wzmocnienieSterowania=0.02;
	}
};

class PociskKierowany: public Pocisk
{
public:
	PociskKierowany(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
	virtual void zniszcz();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();

	static ParametryPociskuKierowanego parametry;
private:
	double maksymalnaPredkosc;
};

#endif /* POCISKKIEROWANY_H_ */
