/*
 * FabrykaLudzi.h
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#ifndef FABRYKALUDZI_H_
#define FABRYKALUDZI_H_

#include <iostream>
#include "../Kontenery/Strzelcy.h"
#include "FabrykaPociskow.h"

class FabrykaLudzi
{
public:
	enum TypCzlowieka {lucznik,wyborowyLucznik,rycerz,krzyzowiec,ksiadz,biskup};
private:
	Strzelcy* strzelcy;
	FabrykaPociskow* fabrykaPociskow;
public:
	FabrykaLudzi(FabrykaPociskow* nFabrykaPociskow,Strzelcy* nStrzelcy);

	void stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja);
};

#endif /* FABRYKALUDZI_H_ */
