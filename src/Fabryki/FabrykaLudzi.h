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

	ParametryStrzelca parametryLucznikaLv1;
	ParametryStrzelca parametryLucznikaLv2;
	ParametryStrzelca parametryLucznikaLv3;
	ParametryStrzelca parametryLucznikaLv4;
	ParametryStrzelca parametryRycerzaLv1;
	ParametryStrzelca parametryRycerzaLv2;
	ParametryStrzelca parametryRycerzaLv3;
	ParametryBalisty parametryBalistyLv1;
	ParametryBalisty parametryBalistyLv2;
	ParametryKaplana parametryKaplanaLv1;
	ParametryKaplana parametryKaplanaLv2;
	ParametryKaplana parametryKaplanaLv3;

	FabrykaLudzi();
public:
	~FabrykaLudzi();

	enum TypCzlowieka {	poborowyLucznik,	szwadron,
						zawodowyLucznik,	wyborowyLucznik,	skrytobojca,
						rycerz,				krzyzowiec,			templariusz,
						balista,			ulepszonaBalista,
						mnich,				kaplan,				glowa};

	static FabrykaLudzi* zwrocInstancje();

	void ustawKontenery(KontenerPostaci<Strzelec>* s, KontenerPostaci<Balista>* b, KontenerPostaci<Kaplan>* k);
	void stworzCzlowieka(TypCzlowieka typ, Punkt nPozycja, bool zwroconyWPrawo = true);
};

#endif /* FABRYKALUDZI_H_ */
