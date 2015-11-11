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

class Postac : public Obiekt
{
protected:
	FabrykaPociskow *fabrykaPociskow;

public:
	Postac();
	virtual ~Postac() {}

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)=0;
	virtual void wyznaczKlatkeAnimacji() = 0;

	void ustawFabrykePociskow(FabrykaPociskow *fp);
	void ustawCel(Punkt p) {cel=p;}
	void ustawCzyIstniejePrzeszkoda(bool poLewej, bool poPrawej) {przeszkodaPoLewej=poLewej;przeszkodaPoPrawej=poPrawej;}

	Punkt cel;
	bool przeszkodaPoLewej,przeszkodaPoPrawej;
};

#endif /* POSTAC_H_ */
