/*
 * Zaslona.h
 *
 *  Created on: 27-09-2016
 *      Author: przemo
 */

#ifndef SRC_PRZEDMIOTY_ZASLONA_H_
#define SRC_PRZEDMIOTY_ZASLONA_H_

#include "Przedmiot.h"

class Zaslona: public Przedmiot
{
public:

	Zaslona(Punkt pozycja);
	~Zaslona();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	void ulepsz() {ulepszona=true;zycie=4000;}
	void oznaczJakoOzdobe(int i) {ozdoba=i;}

	bool ulepszona;
	int ozdoba;
private:
};

#endif /* SRC_PRZEDMIOTY_ZASLONA_H_ */
