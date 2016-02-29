/*
 * FabrykaLudzi.h
 *
 *  Created on: 12-07-2015
 *      Author: przemo
 */

#ifndef FABRYKALUDZI_H_
#define FABRYKALUDZI_H_

#include "../Kontenery/KontenerPostaci.h"
#include "../Postacie/Strzelec.h"
#include "FabrykaPociskow.h"
#include <assert.h>


class FabrykaLudzi
{
private:
	static FabrykaLudzi* ptr;

	static KontenerPostaci<Strzelec>* strzelcy;

	FabrykaLudzi();
public:
	~FabrykaLudzi();

	enum TypCzlowieka {lucznik,wyborowyLucznik,rycerz,krzyzowiec,ksiadz,biskup};

	static FabrykaLudzi* zwrocInstancje();

	void ustawKontenery(KontenerPostaci<Strzelec>* s);
	void stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja);
};

#endif /* FABRYKALUDZI_H_ */
