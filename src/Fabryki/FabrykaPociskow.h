/*
 * FabrykaPociskow.h
 *
 *  Created on: 12-02-2015
 *      Author: przemo
 */

#ifndef FABRYKAPOCISKOW_H_
#define FABRYKAPOCISKOW_H_

#include "../Pociski/Plomien.h"
#include "../Pociski/Strzala.h"
#include "../Pociski/Belt.h"
#include "../Kontenery/KontenerPociskow.h"
#include <assert.h>

class FabrykaPociskow
{
private:
	static FabrykaPociskow* ptr;

	static KontenerPociskow<Plomien>* plomienie;
	static KontenerPociskow<Strzala>* strzaly;
	static KontenerPociskow<Belt>* belty;

	FabrykaPociskow();
public:
	~FabrykaPociskow();

	enum TypPocisku {plomien,belt,strzala,cichaStrzala};

	static FabrykaPociskow* zwrocInstancje();


	void ustawKontenery(KontenerPociskow<Plomien>* p,KontenerPociskow<Strzala>* s, KontenerPociskow<Belt>* b);
	void stworzPocisk(TypPocisku typ, Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat);
};

#endif /* FABRYKAPOCISKOW_H_ */
