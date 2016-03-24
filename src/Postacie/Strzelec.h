/*
 * Strzelec.h
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#ifndef STRZELEC_H_
#define STRZELEC_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>

#include "Postac.h"

struct ParametryStrzelca
{
	double predkoscAnimacjiBiegu;
	double iloscKlatekAnimacjiBiegu;
	double predkoscBiegu;
	double czasTrwaniaStrzaly;
	double minimalnaOdleglosc;

	ParametryStrzelca()
	{
		predkoscAnimacjiBiegu=0.2;
		iloscKlatekAnimacjiBiegu = 8;
		predkoscBiegu=3;
		czasTrwaniaStrzaly=200;
		minimalnaOdleglosc=10;
	}
};

class Strzelec: public Postac
{
public:
	enum StanStrzelca {stoi,biegnie,strzela,naciaga,umiera};

private:
	void bieganie(Klawiatura* klawiatura, Myszka *myszka);
	void strzelanie(Klawiatura* klawiatura, Myszka *myszka);

	void wyznaczKatStrzalu(Punkt cel);

public:
	Strzelec();

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka);
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	std::pair<Klawiatura,Myszka> wyznaczSterowanie();

	ParametryStrzelca parametry;
	StanStrzelca stan;

	//Parametry charakteryzujace kazdego strzelca
	double predkoscStrzaly;
	double celnosc;
	bool spust; // true jesli jest to kusza; false luk
	double maxNaciagniecie;	// czas potrzebny do naciagniecia kuszy
	double maxCelowania; // czas potrzebny do wycelowania

	//Parametry stanu Strzelca
	double katCelowaniaWprost;
	double katCelowaniaZGory;
	double katCelowania;
	bool mozliwyStrzal;

	double stanBiegu;
	double stanNaciagania;
	double stanCelowania;

};

#endif /* STRZELEC_H_ */
