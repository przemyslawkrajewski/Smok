/*
 * Postac.h
 *
 *  Created on: 13-02-2015
 *      Author: przemo
 */

#ifndef POSTAC_H_
#define POSTAC_H_

#include "../WeWy/Klawiatura.h"
#include "../WeWy/Myszka.h"
#include "../Obiekty/Obiekt.h"

#include "../Fabryki/FabrykaPociskow.h"
#include "../Fabryki/FabrykaPrzedmiotow.h"

class Postac : public Obiekt
{

public:
	Postac();
	virtual ~Postac() {}


	enum TypPostaci {smok,lucznik,rycerz,snajper,krzyzowiec};

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)=0;
	virtual void wyznaczKlatkeAnimacji() = 0;
	virtual std::pair<Klawiatura,Myszka> wyznaczSterowanie() {return std::pair<Klawiatura,Myszka>(Klawiatura(),Myszka());};

	void ustawTypPostaci(TypPostaci typ) {typPostaci=typ;}
	TypPostaci zwrocTypPostaci() {return typPostaci;}

	void ustawNajblizszegoKompana(Obiekt *o) {najblizszyKompan=o;}

	void ustawPoziom(int p) {poziom=p;}
	int zwrocPoziom() {return poziom;}

protected:

	int poziom;

	TypPostaci typPostaci;
	Obiekt* najblizszyKompan;
};

#endif /* POSTAC_H_ */
