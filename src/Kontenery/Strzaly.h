/*
 * Strzaly.h
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#ifndef STRZALY_H_
#define STRZALY_H_

#include <list>
#include "../Pociski/Strzala.h"

class Strzaly: public Pocisk
{
private:
	std::list<Strzala> strzaly;
public:
	Strzaly();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	Strzala* dodajStrzale(Strzala p);

	std::list< Punkt > zwrocPozycje();
	std::list< Punkt > zwrocKlatkeAnimacji();
	std::list< PrzestrzenKolizji > zwrocPrzestrzenKolizji();
	std::list<Strzala>* zwrocObiekty() {return &strzaly;}

	void sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt));
};

#endif /* STRZALY_H_ */
