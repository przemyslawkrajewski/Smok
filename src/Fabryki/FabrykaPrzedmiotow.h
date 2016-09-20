/*
 * FabrykaPrzedmiotow.h
 *
 *  Created on: 24-04-2016
 *      Author: przemo
 */

#ifndef FABRYKAPRZEDMIOTOW_H_
#define FABRYKAPRZEDMIOTOW_H_

#include "../Przedmioty/Mur.h"
#include "../Kontenery/KontenerPrzedmiotow.h"
#include <assert.h>

class FabrykaPrzedmiotow
{
private:
	static FabrykaPrzedmiotow* ptr;

	static KontenerPrzedmiotow<Mur>* mury;

	FabrykaPrzedmiotow();
public:
	~FabrykaPrzedmiotow();

	enum TypPrzedmiotu {sredniMur,duzyMur,oslona,tarcza};

	static FabrykaPrzedmiotow* zwrocInstancje();


	void ustawKontenery(KontenerPrzedmiotow<Mur>* m);
	void stworzPrzedmiot(TypPrzedmiotu typ, Punkt pozycja);
};

#endif /* FABRYKAPRZEDMIOTOW_H_ */
