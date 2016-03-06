/*
 * Pocisk.h
 *
 *  Created on: 13-02-2015
 *      Author: przemo
 */

#ifndef POCISK_H_
#define POCISK_H_

#include "../Obiekty/Obiekt.h"

class Pocisk : public Obiekt
{
protected:
	double katNachylenia;

public:
	Pocisk();
	virtual ~Pocisk();

	virtual void wyznaczKolejnyStan()=0;
	virtual void wyznaczKlatkeAnimacji() = 0;
	virtual void wyznaczPrzestrzenKolizji() = 0;

	double zwrocKatNachylenia() {return katNachylenia;}
};

#endif /* POCISK_H_ */
