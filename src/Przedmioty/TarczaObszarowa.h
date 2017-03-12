/*
 * TarczaObszarowa.h
 *
 *  Created on: 11 mar 2017
 *      Author: przemo
 */

#ifndef SRC_PRZEDMIOTY_TARCZAOBSZAROWA_H_
#define SRC_PRZEDMIOTY_TARCZAOBSZAROWA_H_

#include "Przedmiot.h"

struct ParametryTarczyObszarowej
{
	int czasWidocznosci;
	double odlegloscOdZiemi;

	ParametryTarczyObszarowej()
	{
		czasWidocznosci=15;
		odlegloscOdZiemi=40;
	}
};


class TarczaObszarowa: public Przedmiot
{
public:

	TarczaObszarowa(Punkt pozycja);
	~TarczaObszarowa();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	virtual void zniszcz();
	void zadajObrazenia(double obrazenia);


private:
	static ParametryTarczyObszarowej parametry;
	int stanWidocznosci;
};

#endif /* SRC_PRZEDMIOTY_TARCZAOBSZAROWA_H_ */
