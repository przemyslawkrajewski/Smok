/*
 * FabrykaPrzedmiotow.h
 *
 *  Created on: 24-04-2016
 *      Author: przemo
 */

#ifndef FABRYKAPRZEDMIOTOW_H_
#define FABRYKAPRZEDMIOTOW_H_

#include "../Przedmioty/Mur.h"
#include "../Przedmioty/Zaslona.h"
#include "../Przedmioty/TarczaPersonalna.h"
#include "../Przedmioty/TarczaObszarowa.h"
#include "../Kontenery/KontenerPrzedmiotow.h"
#include <assert.h>

class FabrykaPrzedmiotow
{
private:
	static FabrykaPrzedmiotow* ptr;

	static KontenerPrzedmiotow<Mur>* mury;
	static KontenerPrzedmiotow<Zaslona>* zaslony;
	static KontenerPrzedmiotow<TarczaPersonalna>* tarczePersonalne;
	static KontenerPrzedmiotow<TarczaObszarowa>* tarczeObszarowe;

	FabrykaPrzedmiotow();
public:
	~FabrykaPrzedmiotow();

	enum TypPrzedmiotu {sredniMur,duzyMur,zaslona,tarczaPersonalna,tarczaObszarowa};

	static FabrykaPrzedmiotow* zwrocInstancje();


	void ustawKontenery(KontenerPrzedmiotow<Mur>* m, KontenerPrzedmiotow<Zaslona>* z, KontenerPrzedmiotow<TarczaPersonalna>* tp, KontenerPrzedmiotow<TarczaObszarowa>* to);
	Obiekt* stworzPrzedmiot(TypPrzedmiotu typ, Punkt pozycja, Obiekt* cel=0);
};

#endif /* FABRYKAPRZEDMIOTOW_H_ */
