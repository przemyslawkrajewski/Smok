/*
 * FiguraKolizji.cpp
 *
 *  Created on: 02-04-2016
 *      Author: przemo
 */

#include "FiguraKolizji.h"

FiguraKolizji::FiguraKolizji(const Punkt *po, const Punkt *v, Punkt p) {
	pozycja=p;
	pozycjaObiektu=po;
	predkoscObiektu=v;
}

