/*
 * Przedmiot.h
 *
 *  Created on: 18-04-2016
 *      Author: przemo
 */

#ifndef SRC_PRZEDMIOT_H_
#define SRC_PRZEDMIOT_H_

#include "../Obiekty/Obiekt.h"

class Przedmiot : public Obiekt
{
public:
	Przedmiot();

	virtual void wyznaczKolejnyStan() {}

};

#endif /* SRC_PRZEDMIOT_H_ */
