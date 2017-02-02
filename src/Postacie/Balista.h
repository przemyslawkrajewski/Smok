/*
 * Balista.h
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#ifndef SRC_POSTACIE_BALISTA_H_
#define SRC_POSTACIE_BALISTA_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>

#include "Postac.h"

struct ParametryBalisty
{

	int predkoscAnimacjiNaciagania;
	int predkoscAnimacjiCelowania;
	double predkoscCelowania;
	double maxKatCelowania;
	double minKatCelowania;
	int maxNaciagania;
	double maxZycia;

	double predkoscStrzaly;

	ParametryBalisty()
	{
		predkoscAnimacjiNaciagania=20;
		predkoscAnimacjiCelowania=20;
		predkoscCelowania=0.04;

		predkoscStrzaly=40;

		maxKatCelowania=3.14;
		minKatCelowania=0;
		maxNaciagania=200;
		maxZycia=10;
	}
};

class Balista: public Postac
{
public:
	enum StanBalisty {naciaga, naladowany, rozladowany, rozpadaSie};

	Balista();

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka);
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	std::pair<Klawiatura,Myszka> wyznaczSterowanie();

	void ustawParametry(ParametryBalisty p) {parametry=p;}

	ParametryBalisty parametry;
	StanBalisty stan;

private:

	void wyznaczKatStrzalu(Punkt cel);

	double katCelowaniaWprost;
	double katCelowaniaZGory;
	double katCelowania;
	bool mozliwyStrzal;

	int stanNaciagania;
	int stanCelowania;

};

#endif /* SRC_POSTACIE_BALISTA_H_ */
