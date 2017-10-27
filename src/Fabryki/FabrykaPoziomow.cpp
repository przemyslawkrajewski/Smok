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
	if(numer==1) //################################ POZIOM 1: OBLAWA ###############################################
	{
		std::cout << "Poziom 1: Obława\n";
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(12000,1800));
		smok->ustawPozycje(Punkt(7000,100));
		smok->ustawCzyZwroconyWPrawo(false);

		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(6000+odchylenie,poziomZiemi),0);
		}

		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8000+odchylenie,poziomZiemi),0);
		}
	}
	else if(numer==2) //################################ POZIOM 2: OBLAWA CZ.2 ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(15000,1500));
		smok->ustawPozycje(Punkt(10800,100));
		smok->ustawCzyZwroconyWPrawo(false);

		//W srodku
		for(int i=0;i<16;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(9700+odchylenie,poziomZiemi),1);
		}

		//Na zewnatrz
		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8400+odchylenie,poziomZiemi),1);
		}

		for(int i=0;i<16;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8400+odchylenie,poziomZiemi),1);
		}

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(8200,poziomZiemi),1);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::jaskinia,Punkt(10400,0));
	}
	else if(numer==3) //################################ POZIOM 3: WYGNANIE ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(12000,4000));
		smok->ustawPozycje(Punkt(4000,100));
		smok->ustawCzyZwroconyWPrawo(true);

		for(int i=0;i<18;i++)
		{
			int odchylenie = rand() % 100-50;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10400+odchylenie,poziomZiemi+1600),2);
		}
		for(int i=0;i<50;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(9000+odchylenie,poziomZiemi),2);
		}
		for(int i=0;i<20;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(9000+odchylenie,poziomZiemi),0);
		}

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(10400,0));
	}
	else if(numer==4) //################################ POZIOM 4: GLOD ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(14000,5000));
		smok->ustawPozycje(Punkt(4000,100));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(8000,0));

		//Ludzie na murze
		for(int i=0;i<8;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8000,poziomZiemi+800),2);
		}

		//Ludzie pod zaslonami
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(9500,0));
		for(int i=0;i<5;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(9500,poziomZiemi),2);
		}
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(10500,0));
		for(int i=0;i<5;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10500,poziomZiemi),2);
		}

		//Wolnobiegajacy ludzie
		for(int i=0;i<6;i++)
		{
			int odchylenie = i*75;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8600+odchylenie,poziomZiemi),0);
		}
		for(int i=0;i<6;i++)
		{
			int odchylenie = i*75;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(9850+odchylenie,poziomZiemi),0);
		}
		for(int i=0;i<6;i++)
		{
			int odchylenie = i*75;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(11000+odchylenie,poziomZiemi),0);
		}

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bwysokaWieza,Punkt(12000,0));
	}
	else if(numer==5) //################################ POZIOM 5: NAPAD ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(12000,1800));
		smok->ustawPozycje(Punkt(3500,400));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(3000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(8000,0));


		for(int i=0;i<60;i++)
		{
			int odchylenie = rand() % 4000-2000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(6000+odchylenie,poziomZiemi),0);
		}
	}
	else if(numer==6) //################################ POZIOM 6: PRZYSIEGA ZEMSTY ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(4000,0),Punkt(10500,4000));
		smok->ustawPozycje(Punkt(10000,1700));
		smok->ustawCzyZwroconyWPrawo(false);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(10000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(5000,0));


		for(int i=0;i<30;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7500+odchylenie,poziomZiemi),2);
		}
		for(int i=0;i<30;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(5000+odchylenie,poziomZiemi+500),2);
		}

	}
	else if(numer==7) //################################ POZIOM 7: OBLEZENIE ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(10000,4000));
		smok->ustawPozycje(Punkt(4000,200));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(5000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(9000,0));

		//Wieza
		for(int i=0;i<8;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(5000+odchylenie,poziomZiemi+800),2,false);
		}
		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(5000+odchylenie,poziomZiemi+800),3,false);
		}

		//Ziemia
		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6500+odchylenie,poziomZiemi),2,false);
		}

		//Mur
		for(int i=0;i<4;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(8300+odchylenie,poziomZiemi+500),3,false);
		}
		for(int i=0;i<20;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(9300+odchylenie,poziomZiemi+500),2,false);
		}
	}
	else if(numer==8) //################################ POZIOM 8: OBLEZENIE CZ.2 ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(15000,4000));
		smok->ustawPozycje(Punkt(3000,300));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(6000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(9000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7200,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7500,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7800,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(10000,0));

		//Mur
		for(int i=0;i<4;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(6300+odchylenie,poziomZiemi+300),3,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(9000+odchylenie,poziomZiemi+300),3,false);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(9300,poziomZiemi+378),0,false);

		//Ziemia
		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7200,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7500,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7800,poziomZiemi),2,false);
		}

		//Wieza
		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(10000,poziomZiemi+1580),3,false);
		}
		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10000+odchylenie,poziomZiemi+1580),2,false);
		}
	}
	else if(numer==9) //################################ POZIOM 9: ZEMSTA ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(15000,4000));
		smok->ustawPozycje(Punkt(3500,200));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(6000,0));

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(12000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(10000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bmalyMur,Punkt(11660,540));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(11000,0));

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bduzyMur,Punkt(13890,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bduzyMur,Punkt(12090,1320));

		//1st wieza
		for(int i=0;i<12;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6000,poziomZiemi+1580),2,false);
		}

		//pod murem
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(6500,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7500,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(8000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(8500,0));
		for(int i=0;i<12;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6500,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7000,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7500,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8000,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8500,poziomZiemi),2,false);
		}


		//mur
		for(int i=0;i<16;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(10000+odchylenie,poziomZiemi+400),3,false);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(10600,375+poziomZiemi),0,false);


		//2nd wieza
		for(int i=0;i<8;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(11000,poziomZiemi+800),2,false);
		}
		for(int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(11000,poziomZiemi+800),3,false);
		}

		//wneka
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(11700,795+poziomZiemi),0,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(11500,380+poziomZiemi),5,false);
		for(int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(12800,poziomZiemi+380),1,false);
		}
	}
	else if(numer==10) //################################ POZIOM 10: NOWA KORONACJA ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(15000,4000));
		smok->ustawPozycje(Punkt(9000,200));
		smok->ustawCzyZwroconyWPrawo(true);


		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(10000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(8000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(11000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(7000,0));

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(10400,565+poziomZiemi),0,true);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(7600,565+poziomZiemi),0,false);
		for(int i=1;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(10400+i*300,565+poziomZiemi),0,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(7600-i*300,565+poziomZiemi),0,true);
		}

		for(int i=0;i<12;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(10000,poziomZiemi+1580),3,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(8000,poziomZiemi+1580),3,false);
		}
		for(int i=0;i<40;i++)
		{
			int odchylenie = rand() % 1500-750;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6850+odchylenie,poziomZiemi+570),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(11150+odchylenie,poziomZiemi+570),2,false);
		}

	}
	else if(numer==11) //################################ POZIOM 11: PRZYGOTOWANIA DO LIKWIDACJI ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(15000,4000));
		smok->ustawPozycje(Punkt(4000,200));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(5000,0));
		for(int i=0;i<14;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(5000,poziomZiemi+1580),3,false);
		}

		for(int i=0;i<10;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(9900+i*20,poziomZiemi),3,false);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(9925,poziomZiemi),4,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(10000,poziomZiemi),4,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(9975,poziomZiemi),4,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(10000,poziomZiemi+70),0,false);
		for(int i=0;i<24;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10300,poziomZiemi),2,false);
		}
	}
	else if(numer==12) //################################ POZIOM 12: NAUKI ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(20000,4000));
		smok->ustawPozycje(Punkt(19000,200));
		smok->ustawCzyZwroconyWPrawo(false);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::wysokaWieza,Punkt(6000,0));
		for(int i=0;i<5;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(6500+i*150,70+poziomZiemi),0,true);
		}
		for(int i=0;i<20;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(7500+i*60,poziomZiemi),3,true);
		}

		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 1200 - 600;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(8100+odchylenie,poziomZiemi),4,true);
		}

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(4000,poziomZiemi+100),0,true);

	}
	else if(numer==13) //################################ POZIOM 13: ZLECENIE ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(4000,0),Punkt(24000,4000));
		smok->ustawPozycje(Punkt(4500,400));
		smok->ustawCzyZwroconyWPrawo(false);

		for(int i=0;i<38 ;i++) FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::ulZaslona,Punkt(5000+i*500,0));

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::skrytobojca,Punkt(12000,poziomZiemi+100),6,true);

	}
	else if(numer==14) //################################ POZIOM 14: DROGA DO FANATYKOW ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(4000,0),Punkt(16000,4000));
		smok->ustawPozycje(Punkt(4500,400));
		smok->ustawCzyZwroconyWPrawo(false);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(5000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(9000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(9000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(14000,0));

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(5500,70+poziomZiemi),0,true);

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(7000,poziomZiemi+600),0,true);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(7000,poziomZiemi+600),0,true);
		for(int i=0;i<12;i++) FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(7000,poziomZiemi),7,true);

		for (int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(8250,poziomZiemi+1700),4,true);
		}

		for (int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(9000,poziomZiemi+1700),4,true);
		}

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(9750,poziomZiemi+600),0,true);

		for (int i=0;i<3;i++)
		{
			double pozycja=11000+500*i;
			FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(pozycja,0));
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(pozycja,poziomZiemi+670),7,true);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(pozycja,poziomZiemi+670),7,true);
		}

		for(int i=0;i<7;i++)
		{
			int odchylenie = rand()%1000 -500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(14000+odchylenie,poziomZiemi+670),7,true);
		}
	}
	else if(numer==15) //################################ POZIOM 15: RZEZ ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(14000,4000));
		smok->ustawPozycje(Punkt(3500,400));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(3000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(11000,0));


		for(int i=0;i<50;i++)
		{
			int odchylenie = rand() % 6000-3000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(7000+odchylenie,poziomZiemi),0,true);
		}
	}
	else if(numer==16) //################################ POZIOM 16: ZRODLO KULTU ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(14000,4000));
		smok->ustawPozycje(Punkt(3500,400));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(6000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(11000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(12000,0));

		for(int i=0;i<2;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(6000+odchylenie,500+poziomZiemi),8,true);
		}

		//FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(8000,poziomZiemi),0,true);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(9000,poziomZiemi),0,true);
		for(int i=0;i<2;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(8000,poziomZiemi),4,true);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(9000,poziomZiemi),4,true);
		}

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(11000,500+poziomZiemi),0,true);
		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(11000,500+poziomZiemi),8,true);
		}

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::mnich,Punkt(12000,1500+poziomZiemi),0,true);
		for(int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(12000,1500+poziomZiemi),7,true);
		}

	}
	else if(numer==17) //################################ POZIOM 17: ALARM ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(20000,1500));
		smok->ustawPozycje(Punkt(20000,000));
		smok->ustawCzyZwroconyWPrawo(false);

		for(int i=0;i<30;i++)
		{
			int odchylenie = rand() % 14000-7000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::kaplan,Punkt(11000+odchylenie,poziomZiemi+10),1,false);
		}
	}
	else if(numer==18) //################################ POZIOM 18: STRAZ ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(20000,1500));
		smok->ustawPozycje(Punkt(3000,000));
		smok->ustawCzyZwroconyWPrawo(true);

		for(int i=0;i<2;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(14000+i*30,500+poziomZiemi),8,true);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::kaplan,Punkt(14090,poziomZiemi+10),2,false);

		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(15500+i*30,500+poziomZiemi),8,true);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(15500+i*30,1500+poziomZiemi),7,true);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(15500+i*30,1500+poziomZiemi),7,true);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::kaplan,Punkt(15530,poziomZiemi+10),2,false);

		for(int i=0;i<10;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(17000+i*30,1500+poziomZiemi),7,true);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::kaplan,Punkt(17030,poziomZiemi+10),2,false);
	}
	else if(numer==19) //################################ POZIOM 19: SERCE KULTU ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(20000,5000));
		smok->ustawPozycje(Punkt(3000,000));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(5000,3000));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(6000,0));

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(13000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::wysokaWieza,Punkt(14000,0));

		//Latajaca Wieza
		for(int i=0;i<10;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(5000,3700+poziomZiemi),7,true);
		}
		//FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::kaplan,Punkt(5000,3700+poziomZiemi),2,false);

		//Wieza1
		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(6000,1500+poziomZiemi),8,true);
		}

		//Ziemia
		for(int i=0;i<8;i++)
		{
			int odchylenie = rand() % 4000-2000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(9000+odchylenie,poziomZiemi),7,true);
		}
		for(int i=0;i<4;i++)
		{
			int odchylenie = rand() % 4000-2000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(9000+odchylenie,poziomZiemi),8,true);
		}
		for(int i=0;i<1;i++)
		{
			int odchylenie = rand() % 4000-2000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::kaplan,Punkt(9000+odchylenie,poziomZiemi),2,false);
		}

		//Mur
		for(int i=0;i<3;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::templariusz,Punkt(12000+i*250,poziomZiemi+500),8,true);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(13500,poziomZiemi+563),0,false);

		//Wieza2
		for(int i=0;i<12;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::wyborowyLucznik,Punkt(14000,poziomZiemi+3060),7,true);
		}
	}
	else if(numer==20) //################################ POZIOM 20: GLOWA ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(20000,1500));
		smok->ustawPozycje(Punkt(12000,200));
		smok->ustawCzyZwroconyWPrawo(false);

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::glowa,Punkt(10000,poziomZiemi),3,true);
	}
	else if(numer==101)
	{
		smok->ustawPozycje(Punkt(2000,100));
		smok->ustawPoziom(6);
		smok->ustawWymiaryManewruSmoka(Punkt(1000,0),Punkt(30000,3000));

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(3000,poziomZiemi+100),2,true);

	}
}
