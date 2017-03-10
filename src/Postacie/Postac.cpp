/*
 * Postac.cpp
 *
 *  Created on: 13-02-2015
 *      Author: przemo
 */

#include "Postac.h"

Postac::Postac() :Obiekt()
{
	cel=0;
	typPostaci=lucznik;

	przeszkodaPoLewej=false;
	przeszkodaPoPrawej=false;

	najblizszyKompan=0;
}
