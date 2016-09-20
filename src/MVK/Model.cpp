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
	wyswietlenieInstrukcji=true;

	FabrykaPrzedmiotow::zwrocInstancje()->ustawKontenery(&mury);
	FabrykaPociskow::zwrocInstancje()->ustawKontenery(&plomienie,&strzaly);
	FabrykaLudzi::zwrocInstancje()->ustawKontenery(&strzelcy);

	reset();
}

void Model::reset()
{
	wyswietlenieOdNowa=false;

	strzelcy.wyczysc();
	plomienie.wyczysc();
	strzaly.wyczysc();
	mury.wyczysc();

	smok.reset();

	FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::duzyMur,Punkt(1200,600));

	/*FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(1300,130));

	for(int i=0;i<100;i++)
	{
		int x = rand()%3000+5000;
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(x,130));
	}*/
	smok.ustawPozycje(Punkt(1000,100));
	kamera.ustawPozycje(smok.zwrocPozycje());
	myszka.ustawX(500);
	myszka.ustawY(240);
	wyznaczKolejnyStanObiektow();
	wyznaczKolejnyStanObiektow();
}

//####################################################KOLEJNY STAN#######################################################

void Model::wyznaczKolejnyStan()
{
	if(wyswietlenieInstrukcji)
	{
		if(klawiatura.czyWcisnietoSpacje()) wyswietlenieInstrukcji=false;
	}
	else
	{
		if(wyswietlenieOdNowa && klawiatura.czyWcisnietoSpacje()) reset();
		wyznaczKolejnyStanObiektow();
	}
}

void Model::wyznaczKolejnyStanObiektow()
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

	if(strzelcy.czyPusty() || smok.czyZniszczony()) wyswietlenieOdNowa=true;

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

		std::pair<bool,Punkt> kolizja = smok.sprawdzKolizje((Obiekt*)&(*i),PrzestrzenKolizji::prostokat);
		if(kolizja.first)
		{
			kolizjaSmokaZMurem(&smok,&(*i),kolizja.second);
		}
	}

	//mury.sprawdzKolizje(&smok,nic,kolizjaSmokaZMurem,PrzestrzenKolizji::prostokat,false);
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

void Model::kolizjaSmokaZMurem(Obiekt*o, Obiekt *o2, Punkt punktKolizji)
{
	assert("Smok nie ma ustalonego prostokata kolizji" && !o->zwrocPrzestrzenKolizji()->zwrocProstokaty()->empty());
	ProstokatKolizji prostokat1 = (*(o->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	ProstokatKolizji prostokat2 = (*(o2->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	double minY = o2->zwrocPozycje().y+prostokat1.zwrocBok2()/2+prostokat2.zwrocBok2()/2;
	double maxY = o2->zwrocPozycje().y-prostokat1.zwrocBok2()/2-prostokat2.zwrocBok2()/2;
	double minX = o2->zwrocPozycje().x-prostokat1.zwrocBok1()/2-prostokat2.zwrocBok1()/2;
	double maxX = o2->zwrocPozycje().x+prostokat1.zwrocBok1()/2+prostokat2.zwrocBok1()/2;


	if(o->zwrocPozycje().y+prostokat1.zwrocBok2()/2>minY || o->zwrocPredkosc().y<-prostokat1.zwrocBok2()/2)
	{
		if(prostokat1.zwrocPozycje().x-6*prostokat1.zwrocBok1()/8<minX)
			o->ustawPozycje(Punkt(o->zwrocPozycje().x+(minX-prostokat1.zwrocPozycje().x)-2,o->zwrocPozycje().y+(minX-prostokat1.zwrocPozycje().x)));
		else if(prostokat1.zwrocPozycje().x+6*prostokat1.zwrocBok1()/8>maxX)
			o->ustawPozycje(Punkt(o->zwrocPozycje().x+(maxX-prostokat1.zwrocPozycje().x)+2,o->zwrocPozycje().y-(maxX-prostokat1.zwrocPozycje().x)));
		else
			o->postawNaZiemi(minY);
	}
	else if(o->zwrocPozycje().x-prostokat1.zwrocBok1()/2<minX || o->zwrocPredkosc().x>prostokat1.zwrocBok1()/2)
	{
		o->zatrzymajNaScianie();
		if(o->zwrocPozycje().y-prostokat1.zwrocBok2()/32>=maxY)
			o->ustawPozycje(Punkt(o->zwrocPozycje().x+(minX-prostokat1.zwrocPozycje().x)-2,o->zwrocPozycje().y));
	}
	else if(o->zwrocPozycje().x+prostokat1.zwrocBok1()/2>maxX || o->zwrocPredkosc().x<-prostokat1.zwrocBok1()/2)
	{
		o->zatrzymajNaScianie();
		if(o->zwrocPozycje().y-prostokat1.zwrocBok2()/32>=maxY)
			o->ustawPozycje(Punkt(o->zwrocPozycje().x+(maxX-prostokat1.zwrocPozycje().x)+2,o->zwrocPozycje().y));
	}

	else if(o->zwrocPozycje().y-prostokat1.zwrocBok2()/2<maxY || o->zwrocPredkosc().y>prostokat1.zwrocBok2()/2)
	{
		o->zatrzymajNaSuficie();
	}

	if(o->zwrocPozycje().y-prostokat1.zwrocBok2()/32<maxY)
	{
		o->zatrzymajNaSuficie();
	}


}
