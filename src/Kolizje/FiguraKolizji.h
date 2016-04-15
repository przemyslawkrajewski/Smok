/*
 * FiguraKolizji.h
 *
 *  Created on: 02-04-2016
 *      Author: przemo
 */

#ifndef SRC_KOLIZJE_FIGURAKOLIZJI_H_
#define SRC_KOLIZJE_FIGURAKOLIZJI_H_

#include <math.h>
#include <utility>
#include "../Obiekty/Punkt.h"

class FiguraKolizji {
public:

	FiguraKolizji(const Punkt *po, const Punkt *v, Punkt p);

	void ustawPozycje(Punkt p) {pozycja=p;}

	Punkt zwrocPozycje() {return Punkt(pozycja.x+pozycjaObiektu->x,pozycja.y+pozycjaObiektu->y);}
	Punkt zwrocPozycjeWzgledemObiektu() {return Punkt(pozycja.x,pozycja.y);}

	Punkt zwrocPozycjeObiektu() {return *pozycjaObiektu;}
	Punkt zwrocPredkoscObiektu() {return * predkoscObiektu;}


protected:
	Punkt pozycja;	//pozycja wzgledem obiektu
	const Punkt *pozycjaObiektu;
	const Punkt *predkoscObiektu;
};

#endif /* SRC_KOLIZJE_FIGURAKOLIZJI_H_ */
