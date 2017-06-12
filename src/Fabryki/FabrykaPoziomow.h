/*
 * FabrykaPoziomow.h
 *
 *  Created on: 27 maj 2017
 *      Author: przemo
 */

#ifndef SRC_FABRYKI_FABRYKAPOZIOMOW_H_
#define SRC_FABRYKI_FABRYKAPOZIOMOW_H_

#include "../Fabryki/FabrykaPociskow.h"
#include "../Fabryki/FabrykaLudzi.h"
#include "../Fabryki/FabrykaPrzedmiotow.h"

#include "../Postacie/Smok.h"

class FabrykaPoziomow
{
private:
	static FabrykaPoziomow* ptr;
	Smok *smok;

	FabrykaPoziomow();
public:
	virtual ~FabrykaPoziomow();

	static FabrykaPoziomow* zwrocInstancje();

	void ustawSmoka(Smok *s) {smok=s;}

	void stworzPoziom(int numer);
};

#endif /* SRC_FABRYKI_FABRYKAPOZIOMOW_H_ */
