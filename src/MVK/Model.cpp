/*
 * Model.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include "Model.h"

ParametryObiektow Obiekt::parametryObiektow;
ParametrySmoka Smok::parametry;

Model::Model(): wymiaryEkranu(Punkt(640,480))
{
	FabrykaPrzedmiotow::zwrocInstancje()->ustawKontenery(&mury);
	FabrykaPociskow::zwrocInstancje()->ustawKontenery(&plomienie,&strzaly);
	FabrykaLudzi::zwrocInstancje()->ustawKontenery(&strzelcy);

	for(int i=0;i<100;i++)
	{
		int x = rand()%3000+5000;
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(x,130));
	}
	smok.ustawPozycje(Punkt(1000,1000));
	FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(1000,1000));
}

//####################################################KOLEJNY STAN#######################################################

void Model::wyznaczKolejnyStan()
{
	//Liczymy wspolrzedne myszki wzgledem glowy Smoka i Wyznaczamy kolejny stan Smoka
	Punkt punktMyszkiSmoka;
	if(kamera.zwrocY()<240) {punktMyszkiSmoka.y=wymiaryEkranu.y-smok.zwrocPozycje().y+smok.zwrocPozycjeGlowy().y-myszka.zwrocY();}
						else {punktMyszkiSmoka.y=wymiaryEkranu.y/2-smok.zwrocPozycje().y+kamera.zwrocY()+smok.zwrocPozycjeGlowy().y-myszka.zwrocY();}
	punktMyszkiSmoka.x=320+smok.zwrocPozycje().x-kamera.zwrocX()+smok.zwrocPozycjeGlowy().x-myszka.zwrocX();
	Myszka myszkaSmoka(punktMyszkiSmoka,myszka.zwrocLPM(),myszka.zwrocPPM());
	smok.wyznaczKolejnyStan(&klawiatura,&myszkaSmoka);
	smok.wyznaczKlatkeAnimacji();
	smok.wyznaczPrzestrzenKolizji();

	//To samo z kamera
	Punkt punktMyszkiKamery(myszka.zwrocX(),myszka.zwrocY());
	Obiekt* obiektDoSledzenia = (&smok);
	if(smok.czyZwroconyWPrawo() && punktMyszkiKamery.x<480) punktMyszkiKamery.x=480;
	if(!smok.czyZwroconyWPrawo() && punktMyszkiKamery.x>160) punktMyszkiKamery.x=160;
	punktMyszkiKamery.x+=obiektDoSledzenia->zwrocPozycje().x+-wymiaryEkranu.x/2;
	punktMyszkiKamery.y=obiektDoSledzenia->zwrocPozycje().y-myszka.zwrocY()+wymiaryEkranu.y/2;
	kamera.wyznaczKolejnyStan(punktMyszkiKamery);


	//TODO: jak ze wszystkim innym tyle że bez liczenia myszki bo od niej nie zależy zachowanie
	//Strzelcy
	strzelcy.ustawCel(&smok);
	strzelcy.wyznaczKolejnyStan();
	strzelcy.wyznaczKlatkeAnimacji();

	plomienie.wyznaczKolejnyStan();
	plomienie.wyznaczKlatkeAnimacji();
	strzaly.wyznaczKolejnyStan();
	strzaly.wyznaczKlatkeAnimacji();

	//									Sadzenie krzyzowcow
	/*
	std::list<Punkt> pozycja = plomienie.zwrocPozycje();
	for(std::list<Punkt>::iterator i=pozycja.begin(); i!=pozycja.end();i++)
	{
		if(i->y<90) fabrykaLudzi.stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(i->x,130));
	}
	//*/
	//std::cout << strzelcy.zwrocObiekty().size() << "\n";
	//								Losowe tworzenie krzyzowcow

	/*if(strzelcy.zwrocObiekty().size()<100)
	{
		int x = rand()%10000+1000;
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(x,130));
	}
	//*/
	obsluzKolizje();
}

//##########################################################KOLIZJE#########################################################

void Model::obsluzKolizje()
{
	//Strzelcy kontra plomienie
	std::list<Postac*> listaStrzelcow = strzelcy.zwrocObiekty();
	for(std::list<Postac*>::iterator i=listaStrzelcow.begin();i!=listaStrzelcow.end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)(*i),zniszczPocisk,zadajObrazenia,PrzestrzenKolizji::okrag,true);
	}

	//Smok kontra strzaly
	strzaly.sprawdzKolizje(&smok,usun,zadajObrazenia,PrzestrzenKolizji::okrag);

	//Mury
	std::list<Mur> *listaMurow = mury.zwrocObiekty();
	for(std::list<Mur>::iterator i=listaMurow->begin();i!=listaMurow->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),zniszczPocisk,nic,PrzestrzenKolizji::prostokat,true);
	}
}

void Model::zniszcz(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	o->zniszcz();
}
void Model::zniszczPocisk(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	if(!o->czyZniszczony())
	{
		o->ustawPozycje(punktKolizji);
		o->ustawPunktZaczepu(o2);
	}
	o->zniszcz();
}

void Model::usun(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	o->zniszcz();
	o->usun();
}

void Model::nic(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	return;
}

void Model::zadajObrazenia(Obiekt*o, Obiekt *o2, Punkt punktKolizji)
{
	o->zadajObrazenia(o2->zwrocObrazenia());
}
