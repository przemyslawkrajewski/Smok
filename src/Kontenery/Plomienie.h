/*
 * Plomienie.h
 *
 *  Created on: 12-02-2015
 *      Author: przemo
 */

#ifndef PLOMIENIE_H_
#define PLOMIENIE_H_

#include <list>
#include "../Pociski/Plomien.h"

class Plomienie : public Pocisk
{
private:
	std::list<Plomien> plomienie;
public:
	Plomienie();
	virtual ~Plomienie();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	Plomien* dodajPlomien(Plomien p);

	std::list< Punkt > zwrocPozycje();
	std::list< Punkt > zwrocKlatkeAnimacji();
	std::list< PrzestrzenKolizji > zwrocPrzestrzenKolizji();
	std::list<Plomien> * zwrocObiekty() {return &plomienie;}

	void sprawdzKolizje(Obiekt* obiekt,void (obsluzKolizjePocisku)(Obiekt*,Obiekt*,Punkt),void (obsluzKolizjeObiektu)(Obiekt*,Obiekt*,Punkt));

};

#endif /* PLOMIENIE_H_ */
