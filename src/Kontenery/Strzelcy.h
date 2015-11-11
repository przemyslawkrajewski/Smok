/*
 * Strzelcy.h
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#ifndef STRZELCY_H_
#define STRZELCY_H_

#include <list>
#include "../Postacie/Strzelec.h"

class Strzelcy: public Postac
{
private:
	std::list<Strzelec> strzelcy;
public:
	Strzelcy();

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka) {wyznaczKolejnyStan();}
	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	Strzelec* dodajStrzelca(Strzelec s);

	std::list< Punkt > zwrocPozycje();
	std::list< Punkt > zwrocKlatkeAnimacji();
	std::list< bool > czyZwroconyWPrawo();
	std::list< PrzestrzenKolizji> zwrocPrzestrzenKolizji();
	std::list<Strzelec>* zwrocObiekty() {return &strzelcy;}
};

#endif /* STRZELCY_H_ */
