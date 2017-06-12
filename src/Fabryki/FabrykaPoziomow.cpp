/*
 * FabrykaPoziomow.cpp
 *
 *  Created on: 27 maj 2017
 *      Author: przemo
 */

#include "FabrykaPoziomow.h"

FabrykaPoziomow* FabrykaPoziomow::ptr=0;

FabrykaPoziomow* FabrykaPoziomow::zwrocInstancje()
{
	if(!ptr) ptr= new FabrykaPoziomow();
	return ptr;
}

FabrykaPoziomow::FabrykaPoziomow()
{
	smok=0;
}

FabrykaPoziomow::~FabrykaPoziomow()
{
	delete ptr;
}

void FabrykaPoziomow::stworzPoziom(int numer)
{
	double poziomZiemi = 130;
	if(numer==1) //################################ POZIOM 1: OBLAWA CZ.1 ###############################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(12000,1800));
		smok->ustawPozycje(Punkt(7000,100));
		smok->ustawCzyZwroconyWPrawo(false);

		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(6000+odchylenie,poziomZiemi));
		}

		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8000+odchylenie,poziomZiemi));
		}
	}
	else if(numer==2) //################################ POZIOM 2: OBLAWA CZ.2 ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(15000,1500));
		smok->ustawPozycje(Punkt(10800,100));
		smok->ustawCzyZwroconyWPrawo(false);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::jaskinia,Punkt(10400,0));
	}
	else if(numer==101)
	{

	} else if(numer==102)
	{
		smok->ustawPozycje(Punkt(1000,100));
		smok->ustawWymiaryManewruSmoka(Punkt(1000,0),Punkt(30000,3000));
		for(int i=0;i<200;i++)
		{
			int x = rand()%30000+5000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(x,130));
		}
	}
}
