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

#include "PomocnikCelowania.h"
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
	double obrazenia;

	double predkoscStrzaly;

	int iloscPociskow;
	double rozrzut;
	double obnizoneObrazenia;

	ParametryBalisty()
	{
		predkoscAnimacjiNaciagania=20;
		predkoscAnimacjiCelowania=5;
		predkoscCelowania=0.004;

		predkoscStrzaly=100;

		maxKatCelowania=1.29;
		minKatCelowania=0.15;
		maxNaciagania=200;
		maxZycia=10;
		obrazenia=0;

		iloscPociskow=5;
		rozrzut=3.14/16;
		obnizoneObrazenia=0;
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

	void ustawKatCelowania(double kat) {katCelowania=kat;}

	void ustawParametry(ParametryBalisty p)
	{
		parametry=p;
		zycie=p.maxZycia;
		pomocnikCelowania.ustawParametry(p.predkoscStrzaly,PociskBalistyczny::parametry.wspolczynnikGrawitacji);
	}

	ParametryBalisty parametry;
	StanBalisty stan;

private:

	bool czyPrzekroczonoMaksKatCelowania();
	bool czyPrzekroczonoMinKatCelowania();
	bool czyKatPrzekraczaMaks(double kat);
    bool czyKatPrzekraczaMin(double kat);
	void opuscCelownik();
	void podniesCelownik();

	double katCelowania;
	bool mozliwyStrzal;

	PomocnikCelowania pomocnikCelowania;

	int stanNaciagania;
	int stanCelowania;

	double przyspieszenieCelu;
	Punkt staraPredkoscCelu;

};

#endif /* SRC_POSTACIE_BALISTA_H_ */
