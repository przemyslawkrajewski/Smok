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
	enum TypMuru {mur, skala, czarneTlo, szareTlo};

	Mur(Wymiary rozmiar, TypMuru t,Punkt pozycja);
	Mur(Punkt pozycja);
	~Mur();

	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	Wymiary zwrocWymiary();
	TypMuru zwrocTyp();
private:
	Wymiary rozmiar;
	TypMuru typ;
};

#endif /* SRC_MUR_H_ */
