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
#include "../Pociski/PociskBalistyczny.h"
#include "../Pociski/PociskKierowany.h"
#include "../Pociski/PociskKasetowy.h"
#include "../Pociski/Odlamek.h"
#include "../Kontenery/KontenerPociskow.h"
#include <assert.h>

class FabrykaPociskow
{
private:
	static FabrykaPociskow* ptr;

	static KontenerPociskow<Plomien>* plomienie;
	static KontenerPociskow<Strzala>* strzaly;
	static KontenerPociskow<Belt>* belty;
	static KontenerPociskow<PociskBalistyczny>* pociskiBalistyczne;
	static KontenerPociskow<PociskKierowany>* pociskiKierowane;
	static KontenerPociskow<PociskKasetowy>* pociskiKasetowe;
	static KontenerPociskow<Odlamek>* odlamki;

	FabrykaPociskow();
public:
	~FabrykaPociskow();

	enum TypPocisku {plomien,belt,strzala,cichaStrzala, swietaStrzala, pociskBalistyczny, pociskKierowany, pociskKasetowy, odlamek};

	static FabrykaPociskow* zwrocInstancje();


	void ustawKontenery(KontenerPociskow<Plomien>* p,KontenerPociskow<Strzala>* s, KontenerPociskow<Belt>* b,KontenerPociskow<PociskBalistyczny> *pb, KontenerPociskow<PociskKierowany> *pk, KontenerPociskow<PociskKasetowy> *pkas, KontenerPociskow<Odlamek>* o);
	void stworzPocisk(TypPocisku typ, Punkt nPozycja, Punkt nPredkosc, double nczasTrwania,double nKat,double obrazenia, Obiekt* cel=0);
};

#endif /* FABRYKAPOCISKOW_H_ */
