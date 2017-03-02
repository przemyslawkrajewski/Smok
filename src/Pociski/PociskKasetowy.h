/*
 * Strzala.h
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#ifndef POCISKKASETOWY_H_
#define POCISKKASETOWY_H_

#include <iostream>
#include <math.h>
#include "Pocisk.h"

struct ParametryPociskuKasetowego
{
	double sredniaPredkoscOdlamkow;
	double odchyleniePredkosciOdlamkow;
	double iloscOdlamkow;
	double czasTrwaniaOdlamkow;

	double minimalnaOdleglosc;
	ParametryPociskuKasetowego()
	{
		sredniaPredkoscOdlamkow=15;
		odchyleniePredkosciOdlamkow=10;
		iloscOdlamkow=40;
		czasTrwaniaOdlamkow=50;

		minimalnaOdleglosc=60;
	}
};

class PociskKasetowy: public Pocisk
{
public:
	PociskKasetowy(Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
	virtual void zniszcz();

	int zwrocCzasTrwania() {return czasTrwania;}
	double zwrocKat();
	ParametryPociskuKasetowego zwrocParametry() {return parametry;}

	static ParametryPociskuKasetowego parametry;
private:

};

#endif /* POCISKKASETOWY_H_ */
