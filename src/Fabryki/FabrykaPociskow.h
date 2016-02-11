/*
 * FabrykaPociskow.h
 *
 *  Created on: 12-02-2015
 *      Author: przemo
 */

#ifndef FABRYKAPOCISKOW_H_
#define FABRYKAPOCISKOW_H_

#include <iostream>
#include "../Kontenery/Plomienie.h"
#include "../Kontenery/Strzaly.h"
//#include "../Kontenery/Kontener.h"


class FabrykaPociskow
{
private:
	Plomienie* plomienie;
	Strzaly* strzaly;
public:
	enum TypPocisku {plomien,belt,strzala};

	FabrykaPociskow(Plomienie* nPlomienie,Strzaly *nStrzaly);
	virtual ~FabrykaPociskow();

	void stworzPocisk(TypPocisku typ, Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);
};

#endif /* FABRYKAPOCISKOW_H_ */
