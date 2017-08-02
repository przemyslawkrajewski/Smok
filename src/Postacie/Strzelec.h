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

#include "PomocnikCelowania.h"
#include "Postac.h"

struct ParametryStrzelca
{
	double wysokosc;

	double predkoscAnimacjiBiegu1;
	double predkoscAnimacjiBiegu2;
	double iloscKlatekAnimacjiBiegu;
	double predkoscBiegu;
	double czasTrwaniaStrzaly;
	double minimalnaOdleglosc;

	bool spust;// true - kusza, false - luk
	double predkoscStrzaly;
	double celnosc;
	double maxNaciagniecie;	// czas potrzebny do naciagniecia kuszy
	double maxCelowania; // czas potrzebny do wycelowania

	double czasRzucaniaPersonalnejTarczy;
	double czasOdnawianiaSwietejStrzaly;
	double czasTrwaniaSwietejStrzaly;
	double predkoscSwietejStrzaly;
	double obrazeniaSwietejStrzaly;
	double maksymalnaIloscStrzalWSerii;
	double maxSzybkiegoNaciagania;
	double maxSzybkiegoCelowania;
	double predkoscOdnawianiaSerii;

	double maxZycia;
	double obrazenia;

	ParametryStrzelca()
	{
		wysokosc=50;

		predkoscAnimacjiBiegu1=0.4;
		predkoscAnimacjiBiegu2=0.2;
		iloscKlatekAnimacjiBiegu = 8;
		predkoscBiegu=5;
		czasTrwaniaStrzaly=200;
		minimalnaOdleglosc=10;

		spust=true;
		predkoscStrzaly=20;
		celnosc=0;
		maxNaciagniecie=100;
		maxCelowania=50;

		czasRzucaniaPersonalnejTarczy=250;
		czasOdnawianiaSwietejStrzaly=200;
		czasTrwaniaSwietejStrzaly=400;
		predkoscSwietejStrzaly=80;
		obrazeniaSwietejStrzaly=10;
		maksymalnaIloscStrzalWSerii=10;
		maxSzybkiegoNaciagania=2;
		maxSzybkiegoCelowania=5;
		predkoscOdnawianiaSerii=0.1;


		maxZycia=10;
		obrazenia=0;
	}
};

class Strzelec: public Postac
{
public:
	enum StanStrzelca {stoi,biegnie,strzela,naciaga,tarczaPersonalna,naciagaWSerii,umiera};

private:
	void bieganie(Klawiatura* klawiatura, Myszka *myszka);
	void strzelanie(Klawiatura* klawiatura, Myszka *myszka);

public:
	Strzelec();

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka);
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	std::pair<Klawiatura,Myszka> wyznaczSterowanie();

	void ustawParametry(ParametryStrzelca p)
	{
		parametry=p;
		zycie=p.maxZycia;
		if(p.spust) pomocnikCelowania.ustawParametry(p.predkoscStrzaly,0);
		else pomocnikCelowania.ustawParametry(p.predkoscStrzaly,Strzala::parametry.wspolczynnikGrawitacji);
	}

	ParametryStrzelca parametry;
	StanStrzelca stan;

	//Parametry stanu Strzelca
	double katCelowania;

	PomocnikCelowania pomocnikCelowania;

	//Stan wykonywania roznych czynnosci
	double stanBiegu;
	double stanNaciagania;
	double stanCelowania;
	double stanRzucaniaZaklec;

	//Uzywane w sterowaniu
	bool wSerii;
	bool pozycjaStrzelecka;
	bool zablokowany;
	Punkt staraPredkoscCelu;

	//Taki odpowiednik many
	double gotowoscSwietejStrzaly;
	double iloscStrzalWSerii;
};

#endif /* STRZELEC_H_ */
