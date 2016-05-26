/*
 * Mur.h
 *
 *  Created on: 18-04-2016
 *      Author: przemo
 */

#ifndef SRC_MUR_H_
#define SRC_MUR_H_

#include "Przedmiot.h"

class Mur : public Przedmiot
{
public:
	enum RozmiarMuru {maly,sredni,duzy};

	Mur(RozmiarMuru rozmiar,Punkt pozycja);
	Mur(Punkt pozycja);
	~Mur();

	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();
private:
	RozmiarMuru rozmiar;
};

#endif /* SRC_MUR_H_ */
