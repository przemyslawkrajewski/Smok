/*
 * Kontroler.h
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#ifndef KONTROLER_H_
#define KONTROLER_H_

#include "Wideo.h"
#include "Model.h"

class Kontroler
{
public:
	Kontroler(Wideo *nWideo, Model *nModel);

	void glownaPetla();
	void obsluzZdarzenia();
	void obsluzZegar();

	void zmienStosunek();
	void zmienTrybEkranu();


private:
	Wideo *wideo;
	Model *model;

	bool zakonczenieAplikacji;
	Uint32 timer;
};

#endif /* KONTROLER_H_ */
