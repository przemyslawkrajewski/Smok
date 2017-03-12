/*
 * Zaslona.h
 *
 *  Created on: 27-09-2016
 *      Author: przemo
 */

#ifndef SRC_TARCZAPERSONALNA_H_
#define SRC_TARCZAPERSONALNA_H_

#include "Przedmiot.h"

struct ParametryTarczyPersonalnej
{
	int czasWidocznosci;
	int granicaUbytkuZycia;

	ParametryTarczyPersonalnej()
	{
		czasWidocznosci=15;
		granicaUbytkuZycia=0.5;
	}
};

class TarczaPersonalna: public Przedmiot
{
public:

	TarczaPersonalna(Punkt pozycja);
	~TarczaPersonalna();

	virtual void wyznaczKolejnyStan();
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	virtual void zniszcz();
	void zadajObrazenia(double obrazenia);


private:
	static ParametryTarczyPersonalnej parametry;
	int stanWidocznosci;

};

#endif /* SRC_TARCZAPERSONALNA_H_ */
