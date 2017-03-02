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
#include "../Postacie/Balista.h"
#include "../Postacie/Kaplan.h"
#include "FabrykaPociskow.h"
#include <assert.h>


class FabrykaLudzi
{
private:
	static FabrykaLudzi* ptr;

	static KontenerPostaci<Strzelec>* strzelcy;
	static KontenerPostaci<Balista>* balisty;
	static KontenerPostaci<Kaplan>* kaplani;

	ParametryStrzelca parametryLucznika;
	ParametryStrzelca parametryKrzyzowca;
	ParametryBalisty parametryBalisty;
	ParametryKaplana parametryKaplana;

	FabrykaLudzi();
public:
	~FabrykaLudzi();

	enum TypCzlowieka {lucznik,wyborowyLucznik,rycerz,krzyzowiec,kaplan,biskup,balista};

	static FabrykaLudzi* zwrocInstancje();

	void ustawKontenery(KontenerPostaci<Strzelec>* s, KontenerPostaci<Balista>* b, KontenerPostaci<Kaplan>* k);
	void stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja, bool zwroconyWPrawo = true);
};

#endif /* FABRYKALUDZI_H_ */
