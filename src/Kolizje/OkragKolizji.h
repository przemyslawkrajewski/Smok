/*
 * OkragKolizji.h
 *
 *  Created on: 10-08-2015
 *      Author: przemo
 */

#ifndef OKRAGKOLIZJI_H_
#define OKRAGKOLIZJI_H_

#include <iostream>
#include <math.h>
#include "../Obiekty/Punkt.h"

class OkragKolizji
{
public:
	OkragKolizji(const Punkt *po, const Punkt *v,Punkt p, double r);

	void ustawPozycje(Punkt p) {pozycja=p;}
	void ustawPromien(double r) {promien=r;}

	Punkt zwrocPozycje() {return Punkt(pozycja.x+pozycjaObiektu->x,pozycja.y+pozycjaObiektu->y);}
	Punkt zwrocPozycjeWzgledemObiektu() {return Punkt(pozycja.x,pozycja.y);}
	double zwrocPromien() {return promien;}
	Punkt zwrocPozycjeObiektu() {return *pozycjaObiektu;}
	Punkt zwrocPredkoscObiektu() {return * predkoscObiektu;}

	bool sprawdzKolizje(OkragKolizji *okrag);

private:
	const Punkt *pozycjaObiektu;
	const Punkt *predkoscObiektu;
	Punkt pozycja;
	double promien;
};

#endif /* OKRAGKOLIZJI_H_ */
