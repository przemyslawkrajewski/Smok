/*
 * Smok.h
 *
 *  Created on: 11-08-2013
 *      Author: przemo
 */

#ifndef SMOK_H_
#define SMOK_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Postac.h"
#include "../Pociski/Plomien.h"

struct ParametrySmoka
{
	double wysokosc;

	//Parametry związane z ogniem
	double maksymalnailoscOgnia;
	double regeneracjaOgnia;
	double zuzycieOgnia; //ile ognia zuzywa na zianie
	double przerwaMiedzyMiotaniem;  //Ile czasu musi upłynąć po zianiu ogniem zanim smok będzie mógł ponownie
	double odchylenieKataOgnia;
	double minimalnaPredkoscOgnia;  //Minimalna predkosc ognia w zaleznosci od sily losowy czynnik predkosci jest po prostu dodawany
	double maksymalnaPredkoscOgnia;
	double odchyleniePredkosciOgnia;
	double sredniCzasTrwaniaOgnia;
	double odchylenieCzasuTrwaniaOgnia;
	double minimalnaOdleglosc;
	Punkt poprawkaOgnia;	//Poprawienie żeby na prawde z pyska ogien wylatywal, zalezy od animacji


	//Parametry związane z lotem
	double maksymalnaPredkoscX;
	double predkoscZblizaniaSie;
	double maksymalnaPredkoscTylemX;
	double maksymalnaPredkoscY;
	double wspolczynnikRozpedzaniaSieX;
	double wspolczynnikHamowaniaX;
	double wspolczynnikHamowaniaY;
	double predkoscWznoszeniaSieY;
	double wspolczynnikGrawitacji;
	double wspolczynnikSilniejszegoUnoszenia;
	double wspolczynnikSlabszegoUnoszenia;
	double predkoscOpadaniaPrzySzybowaniu;
	double przyspieszenieChodu;
	double hamowanieChodu;
	double maksPredkoscChodu;
	double silaWybicia;

	double predkoscOpadania;

	double vyPrzyUnoszeniu; //minimalna wartosc vy przy machnieciu skrzydlami wyznaczana eksperymentalnie

	ParametrySmoka()
	{
		wysokosc=80;

		maksymalnailoscOgnia=10;
		regeneracjaOgnia=0.08;
		zuzycieOgnia=0.05;
		przerwaMiedzyMiotaniem=20;
		odchylenieKataOgnia=5*3.14/180;
		minimalnaPredkoscOgnia=20;	//srednia
		maksymalnaPredkoscOgnia=35;  //srednia
		odchyleniePredkosciOgnia=40; // od 0 do X  i liniowo zalezy od ilosci ognia
		sredniCzasTrwaniaOgnia=10;
		odchylenieCzasuTrwaniaOgnia=5;
		minimalnaOdleglosc=40;
		poprawkaOgnia.x=0;
		poprawkaOgnia.y=-10;

		maksymalnaPredkoscX=30;
		predkoscZblizaniaSie=10;
		maksymalnaPredkoscTylemX=10;
		maksymalnaPredkoscY=30;
		wspolczynnikRozpedzaniaSieX=0.2;
		wspolczynnikHamowaniaX=0.6;
		wspolczynnikHamowaniaY=1.5;
		predkoscWznoszeniaSieY=2;
		wspolczynnikGrawitacji=0.35;
		wspolczynnikSilniejszegoUnoszenia=10;
		wspolczynnikSlabszegoUnoszenia=8;
		predkoscOpadaniaPrzySzybowaniu=1;
		przyspieszenieChodu=0.7;
		hamowanieChodu=1.5;
		maksPredkoscChodu=6;
		silaWybicia=12;

		predkoscOpadania=0.2;

		vyPrzyUnoszeniu=10;
	}
};

class Smok: public Postac
{
public:
	enum StanSmoka {stoi,idzie,
					unosi,leciTylem,zbliza,leci,
					szybuje,szybujacWznosi,szybujacSpada,
					wznosi,nurkuje,stabilizuje, //stabilizuje gdy spadajac zamienia predkoscY na predkoscX
					spada,hamujeX,hamujeY,
					spadaZabity,spadlZabity,opadaZabity}; //Opada gdy stoi na ziemi, a spada gdy jest w powietrzu

	static ParametrySmoka parametry;

private:

	//Metody zwiazane z ruchem
	void hamowanieIUnoszenieY(double unoszenie, double wznoszenie);
	void hamowanieX();
	void szybowanie(double predkosc,bool wznoszenie,bool spadekSwobodny);
	void rozpedzanie(double przyspieszenie,double maksPredkosc);
	void stabilizacjaX(double kierunek); //1 prawo -1 lewo
	void stabilizacjaY(double kierunek); //1 gora -1 dol
	void rozpedzanieNaZiemi(double przyspieszenie);
	void hamowanieNaZiemi();

	virtual void postawNaZiemi(double wysokosc);
	virtual void zatrzymajNaScianie();
	virtual void zatrzymajNaSuficie();

	//Metody do przetwarzania kolejnego stanu Smoka
	void wyznaczLot(Klawiatura* klawiatura, Myszka *myszka);
	void wyznaczGlowe(Klawiatura* klawiatura, Myszka *myszka);
	void wyznaczSmierc();

	StanSmoka stan;
	bool zieje;
	Punkt maksymalnaPozycja;
	Punkt minimalnaPozycja;

	Punkt pozycjaGlowy;
	double obrotGlowy;
	double maksKatGlowy;
	double minKatGlowy;

	double zadaneY;

	double iloscOgnia; //rezerwy ognia czyli ile jeszcze moze ziac i wskazuje ile plomieni na raz wytwarza smok w czasie petli
	double przerwaOgnia;

	Punkt klatkaAnimacjiGlowy;

public:

	Smok();

	virtual void reset();
	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka);
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	//Gety glowy
	Punkt zwrocPozycjeGlowy() {return pozycjaGlowy;}
	double zwrocKatObrotuGlowy() {return obrotGlowy;}
	Punkt zwrocKlatkeAnimacjiGlowy() {return klatkaAnimacjiGlowy;}

	//Gety stan Smoka
	double zwrocStanOgnia() {return iloscOgnia/parametry.maksymalnailoscOgnia;}

};

#endif /* SMOK_H_ */
