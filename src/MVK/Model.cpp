/*
 * Model.cpp
 *
 *  Created on: 09-08-2013
 *      Author: przemo
 */

#include "Model.h"

ParametryObiektow Obiekt::parametryObiektow;
ParametrySmoka Smok::parametry;

Model::Model(int szerOkna,int wysOkna, bool ekran): wymiaryEkranu(Punkt(szerOkna,wysOkna)),pelnyEkran(ekran)
{
	wymiaryEkranu = Wymiary(1024,768);
	pelnyEkran = true;

	wypelnienieCelownika=false;
	typScenerii=1;
	typCelu=0;

	typMenu=-1;
	wyjscie=false;

	licznikCzasuWybychu = 0;

	FabrykaPrzedmiotow::zwrocInstancje()->ustawKontenery(&mury,&zaslony, &tarczePersonalne, &tarczeObszarowe);
	FabrykaPociskow::zwrocInstancje()->ustawKontenery(&plomienie,&strzaly, &belty, &pociskiBalistyczne, &pociskiKierowane, &pociskiKasetowe, &odlamki);
	FabrykaLudzi::zwrocInstancje()->ustawKontenery(&strzelcy,&balisty,&kaplani);
	FabrykaPoziomow::zwrocInstancje()->ustawSmoka(&smok);

	reset();

	ustawMenu(0);
}

void Model::reset()
{
	strzelcy.wyczysc();
	balisty.wyczysc();
	kaplani.wyczysc();

	plomienie.wyczysc();
	strzaly.wyczysc();
	belty.wyczysc();
	pociskiBalistyczne.wyczysc();
	pociskiKierowane.wyczysc();
	pociskiKasetowe.wyczysc();
	odlamki.wyczysc();
	mury.wyczysc();
	zaslony.wyczysc();
	tarczePersonalne.wyczysc();
	tarczeObszarowe.wyczysc();

	smok.reset();

	kamera.ustawPozycje(smok.zwrocPozycje());
	myszka.ustawX(wymiaryEkranu.x/2);
	myszka.ustawY(wymiaryEkranu.y/2);
	wyznaczKolejnyStanObiektow();
	wyznaczKolejnyStanObiektow();
}

void Model::wczytajPoziom(int numer)
{
	reset();
	FabrykaPoziomow::zwrocInstancje()->stworzPoziom(numer);

	if(numer>9) smok.ustawSpopielenie(true);
	else smok.ustawSpopielenie(false);

	kamera.ustawPozycje(smok.zwrocPozycje());
	myszka.ustawX(wymiaryEkranu.x/2);
	myszka.ustawY(wymiaryEkranu.y/2);
	wyznaczKolejnyStanObiektow();

	numerPoziomu = numer;
	czyWyswietlicTytulPoziomu = 200;
	czyWyswietlicZwycienstwo = 0;
	if(numer==1) 	   {typScenerii=1;typCelu=0;samouczek=false;tytulPoziomu=std::string("ob]awa cz.1");}
	else if(numer==2)  {typScenerii=3;typCelu=1;samouczek=false;tytulPoziomu=std::string("ob]awa cz.2");miejsceUcieczki=Punkt(5000,-1);}
	else if(numer==3)  {typScenerii=3;typCelu=1;samouczek=false;tytulPoziomu=std::string("wygnanie");miejsceUcieczki=Punkt(12000,1);}
	else if(numer==4)  {typScenerii=1;typCelu=0;samouczek=false;tytulPoziomu=std::string("g]%d");}
	else if(numer==5)  {typScenerii=2;typCelu=3;samouczek=false;tytulPoziomu=std::string("napad");czas=Punkt(2500,2500);}
	else if(numer==6)  {typScenerii=1;typCelu=0;samouczek=false;tytulPoziomu=std::string("przysi#ga zemsty");}
	else if(numer==7)  {typScenerii=1;typCelu=0;samouczek=false;tytulPoziomu=std::string("obl#*enie");}
	else if(numer==8)  {typScenerii=2;typCelu=0;samouczek=false;tytulPoziomu=std::string("obl#*enie cz.2");}
	else if(numer==9)  {typScenerii=4;typCelu=2;samouczek=false;tytulPoziomu=std::string("zemsta");celDoZniszczenia=&*(strzelcy.zwrocObiekty()->begin());}
	else if(numer==10) {typScenerii=4;typCelu=1;samouczek=false;tytulPoziomu=std::string("nowa koronacja");miejsceUcieczki=Punkt(3000,15000);}
	else if(numer==11) {typScenerii=1;typCelu=0;samouczek=false;tytulPoziomu=std::string("mobilizacja wojsk");}
	else if(numer==12) {typScenerii=3;typCelu=2;samouczek=false;tytulPoziomu=std::string("nauki");celDoZniszczenia=&*(kaplani.zwrocObiekty()->begin());}
	else if(numer==13) {typScenerii=3;typCelu=2;samouczek=false;tytulPoziomu=std::string("zlecenie");celDoZniszczenia=&*(strzelcy.zwrocObiekty()->begin());}
	else if(numer==14) {typScenerii=2;typCelu=0;samouczek=false;tytulPoziomu=std::string("droga do fanatyk%w");}
	else if(numer==15) {typScenerii=2;typCelu=3;samouczek=false;tytulPoziomu=std::string("rze&");czas=Punkt(6000,6000);}
	else if(numer==16) {typScenerii=4;typCelu=0;samouczek=false;tytulPoziomu=std::string("&rod]o kultu");}
	else if(numer==17) {typScenerii=5;typCelu=1;samouczek=false;tytulPoziomu=std::string("alarm");miejsceUcieczki=Punkt(3000,-1);}
	else if(numer==18) {typScenerii=5;typCelu=0;samouczek=false;tytulPoziomu=std::string("gospodarz");}
	else if(numer==19) {typScenerii=5;typCelu=0;samouczek=false;tytulPoziomu=std::string("g]%wna siedziba");}
	else if(numer==20) {typScenerii=5;typCelu=2;samouczek=false;tytulPoziomu=std::string("sprawca");celDoZniszczenia=&*(kaplani.zwrocObiekty()->begin());}
	else if(numer==21) {typScenerii=4;typCelu=5;samouczek=false;tytulPoziomu=std::string(" ");}

	else if(numer==101){typScenerii=1;typCelu=1;samouczek=true;tytulPoziomu=std::string("podstawy poruszania si#");miejsceUcieczki=Punkt(2000,12000);}
	else if(numer==102){typScenerii=1;typCelu=0;samouczek=true;tytulPoziomu=std::string("celowanie");}
	else if(numer==103){typScenerii=1;typCelu=1;samouczek=true;tytulPoziomu=std::string("wzbijanie i nurkowanie");miejsceUcieczki=Punkt(12000,1);}
	else if(numer==104){typScenerii=1;typCelu=0;samouczek=true;tytulPoziomu=std::string("dodatkowe informacje");}
}

//####################################################KOLEJNY STAN#######################################################
void Model::wyznaczKolejnyStan()
{
	if(klawiatura.czyWcisnietoEscape())
	{
		if(typMenu != 6 && typMenu != 0 && typMenu != 3)
		{
			if(typMenu != -1) ustawMenu(-1);
			else ustawMenu(1);
		}
		klawiatura.ustawWcisnietoEscape(false);
	}

	if(typMenu != -1) //Menu
	{
		wyznaczKolejnyStanMenu();
	}
	else//Mechanika gry
	{
		if(czyWyswietlicTytulPoziomu > 0) czyWyswietlicTytulPoziomu--;
		else czyWyswietlicTytulPoziomu = 0;
		if(czyWyswietlicZwycienstwo > 0) czyWyswietlicZwycienstwo--;
		else czyWyswietlicZwycienstwo = 0;

		if(numerPoziomu == 21) czyWyswietlicTytulPoziomu = 1;

		if(samouczek && czyWyswietlicTytulPoziomu == 0) ustawMenu(numerPoziomu-81);

		wyznaczStanCelu();
		wyznaczKolejnyStanObiektow();
	}

}

void Model::wyznaczKolejnyStanMenu()
{
	//Na ktory najechal kursorem
	zaznaczonaOpcjaMenu = -1;
	int wysokoscMenu = listaOpcjiMenu.size() * 90;
	int h = wymiaryEkranu.y/2 - wysokoscMenu/2+40;
	for(int i=0 ; i < listaOpcjiMenu.size() ; i++)
	{
		if(myszka.zwrocY() > h && myszka.zwrocY() < h + 90)
		{
			zaznaczonaOpcjaMenu = i;
			break;
		}
		h += 90;
	}
	if(myszka.zwrocLPM() && !wcisznietyLPM)
	{
		if(typMenu == 0)
		{
			if(zaznaczonaOpcjaMenu == 0)//Nowa gra
			{
				ustawMenu(-1);
				iloscPunktowDoRozdania = 0;
				wczytajPoziom(1);
				smok.ustawPoziom(1);
			}
			else if(zaznaczonaOpcjaMenu == 1)//Samouczek
			{
				ustawMenu(-1);
				iloscPunktowDoRozdania = 0;
				smok.ustawPoziom(5);
				wczytajPoziom(101);
			}
			else if(zaznaczonaOpcjaMenu == 2) ustawMenu(3);//Opcje
			else if(zaznaczonaOpcjaMenu == 3) wyjscie=true;//Wyjscie
		}
		else if(typMenu == 1) //Menu w grze
		{
			if(zaznaczonaOpcjaMenu == 0) ustawMenu(-1); //Wznow gre
			else if(zaznaczonaOpcjaMenu == 1)ustawMenu(5);//Statsy
			else if(zaznaczonaOpcjaMenu == 2) ustawMenu(2);//Opcje
			else if(zaznaczonaOpcjaMenu == 3) ustawMenu(0);//wroc
		}
		else if(typMenu == 2 || typMenu == 3) //Opcje
		{
			if(zaznaczonaOpcjaMenu == 0)//Pelny ekran
			{
				pelnyEkran = !pelnyEkran;
				ustawMenu(typMenu);
			}
			else if(zaznaczonaOpcjaMenu == 1)//Proprorcje ekranu
			{
				if(wymiaryEkranu.y==600)
					wymiaryEkranu = Wymiary(1024,768);
				else
					wymiaryEkranu = Wymiary(1024,600);
				ustawMenu(typMenu);
			}
			else if(zaznaczonaOpcjaMenu == 2) ustawMenu(typMenu==2?1:0);//Wroc
		}
		else if(typMenu == 5) //Statystyki smoka
		{
			if(zaznaczonaOpcjaMenu == 0); //Sila
			else if(zaznaczonaOpcjaMenu == 1);//Wigor
			else if(zaznaczonaOpcjaMenu == 2);//Zdrowie
			else if(zaznaczonaOpcjaMenu == 3);//Zwinnosc
			else if(zaznaczonaOpcjaMenu == 4) ustawMenu(1);//Wroc
		}
		else if(typMenu == 6) //Rozwoj smoka
		{
			if(zaznaczonaOpcjaMenu == 0); //Pozostala ilosc punktow
			else if(zaznaczonaOpcjaMenu == 1 && iloscPunktowDoRozdania > 0 && smok.zwrocStatystyki()[0] < 20)//Sila
			{
				iloscPunktowDoRozdania--;
				smok.zwiekszSile();
				ustawMenu(6);
			}
			else if(zaznaczonaOpcjaMenu == 2 && iloscPunktowDoRozdania > 0 && smok.zwrocStatystyki()[1] < 20)//Wigor
			{
				iloscPunktowDoRozdania--;
				smok.zwiekszWigor();
				ustawMenu(6);
			}
			else if(zaznaczonaOpcjaMenu == 3 && iloscPunktowDoRozdania > 0 && smok.zwrocStatystyki()[2] < 20)//Zdrowie
			{
				iloscPunktowDoRozdania--;
				smok.zwiekszZdrowie();
				ustawMenu(6);
			}
			else if(zaznaczonaOpcjaMenu == 4 && iloscPunktowDoRozdania > 0 && smok.zwrocStatystyki()[3] < 20)//Zwinnosc
			{
				iloscPunktowDoRozdania--;
				smok.zwiekszZwinnosc();
				ustawMenu(6);
			}
			else if(zaznaczonaOpcjaMenu == 5)//Nastepny poziom
			{
				wczytajPoziom(numerPoziomu+1);
				ustawMenu(-1);
			}
		}
		else if(typMenu == 20 || typMenu == 21 || typMenu == 22 || typMenu == 23) //Instrukcja
		{
			if(myszka.zwrocLPM())
			{
				samouczek = false;
				ustawMenu(-1);
			}
		}
		wcisznietyLPM = true;
	}
	if(!myszka.zwrocLPM()) wcisznietyLPM = false;
}

void Model::wyznaczStanCelu()
{

	if(smok.czyZniszczony() && typCelu != -1)
	{
		czyWyswietlicZwycienstwo = 200;
		czyWyswietlicTytulPoziomu = 0;
		typCelu=-1;
	}

	if(typCelu==0) //Zniszcz wszystko
	{
		celDoZniszczenia = 0;
		czas=Punkt();
		if(strzelcy.czyPusty() && balisty.czyPusty() && kaplani.czyPusty())
		{
			czyWyswietlicZwycienstwo = 200;
			czyWyswietlicTytulPoziomu = 0;
			typCelu=4;
		}
	}
	else if(typCelu==1) // Uciekaj
	{
		celDoZniszczenia = 0;
		czas=Punkt();
		if(miejsceUcieczki.y != -1 && miejsceUcieczki.y != 1)
		{
			if(smok.zwrocPozycje().x < miejsceUcieczki.x || smok.zwrocPozycje().x > miejsceUcieczki.y)
			{
				czyWyswietlicZwycienstwo = 200;
				czyWyswietlicTytulPoziomu = 0;
				typCelu=4;
			}
		}
		else if((miejsceUcieczki.y > 0 && smok.zwrocPozycje().x > miejsceUcieczki.x) || (miejsceUcieczki.y < 0 && smok.zwrocPozycje().x < miejsceUcieczki.x))
		{
			czyWyswietlicZwycienstwo = 200;
			czyWyswietlicTytulPoziomu = 0;
			typCelu=4;
		}
	}
	else if(typCelu==2) // Zniszcz cel
	{
		czas=Punkt();
		if(celDoZniszczenia != 0 && celDoZniszczenia->czyZniszczony())
		{
			celDoZniszczenia = 0;
			czyWyswietlicZwycienstwo = 200;
			czyWyswietlicTytulPoziomu = 0;
			typCelu=4;
		}
	}
	else if(typCelu==3) // Zniszcz wszystko na czas
	{
		celDoZniszczenia = 0;
		if(czas.x>0) czas.x--;
		else smok.zniszcz();

		if(strzelcy.czyPusty() && balisty.czyPusty() && kaplani.czyPusty())
		{
			czyWyswietlicZwycienstwo = 200;
			czyWyswietlicTytulPoziomu = 0;
			typCelu=4;
		}
	}
	else if(typCelu==4) // Spacja
	{
		if(klawiatura.czyWcisnietoSpacje())
		{
			if(!smok.czyZniszczony())
			{
				if(numerPoziomu == 21)
				{
					ustawMenu(0);
				}
				else if(numerPoziomu == 20)
				{
					wczytajPoziom(21);
					ustawMenu(-1);
				}
				else if(numerPoziomu < 101)
				{
					iloscPunktowDoRozdania += 4;
					ustawMenu(6);
				}
				else
				{
					if(numerPoziomu<104)
					{
						wczytajPoziom(numerPoziomu+1);
						ustawMenu(-1);
					}
					else ustawMenu(0);
				}
			}
			else
			{
				if(numerPoziomu < 6) numerPoziomu = 1;
				else numerPoziomu -= 5;

				smok.ustawPoziom(numerPoziomu);
				wczytajPoziom(numerPoziomu);
				ustawMenu(-1);
			}
		}
	}
	else if(typCelu==5)
	{
		if(!klawiatura.czyWcisnietoSpacje()) typCelu=4;
	}
	else if(typCelu==-1)
	{
		if(klawiatura.czyWcisnietoSpacje())
		{
			if(numerPoziomu < 3) numerPoziomu = 1;
			else numerPoziomu -= 2;

			smok.ustawPoziom(numerPoziomu);
			wczytajPoziom(numerPoziomu);
			ustawMenu(-1);
		}
	}
}

void Model::wyznaczKolejnyStanObiektow()
{
	if(numerPoziomu == 21 && typMenu == -1)
	{
		klawiatura.ustawWcisnietoLewo(false);
		klawiatura.ustawWcisnietoPrawo(false);
		klawiatura.ustawWcisnietoDol(false);
		klawiatura.ustawWcisnietoGora(false);
		myszka.ustawLPM(false);
		myszka.ustawPPM(false);
		myszka.ustawX(wymiaryEkranu.x/4);
		myszka.ustawY(wymiaryEkranu.y/3);
	}

    if(numerPoziomu == 21)
    {
		if(licznikCzasuWybychu < 0)
		{
			int x = rand()%1050-525;
			int y = rand()%300-150;
			FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::wybuch,Punkt(5750+x,1850+y),Punkt(),0,0,0);
			licznikCzasuWybychu = 60;
		}
		else licznikCzasuWybychu--;
    }

	//Liczymy wspolrzedne myszki wzgledem glowy Smoka i Wyznaczamy kolejny stan Smoka
	Punkt punktMyszkiSmoka;
	if(kamera.zwrocY()<wymiaryEkranu.y/2) {punktMyszkiSmoka.y=wymiaryEkranu.y-smok.zwrocPozycje().y+smok.zwrocPozycjeGlowy().y-myszka.zwrocY();}
						else {punktMyszkiSmoka.y=wymiaryEkranu.y/2-smok.zwrocPozycje().y+kamera.zwrocY()+smok.zwrocPozycjeGlowy().y-myszka.zwrocY();}
	punktMyszkiSmoka.x=wymiaryEkranu.x/2+smok.zwrocPozycje().x-kamera.zwrocX()+smok.zwrocPozycjeGlowy().x-myszka.zwrocX();
	Myszka myszkaSmoka(punktMyszkiSmoka,myszka.zwrocLPM(),myszka.zwrocPPM());
	smok.wyznaczKolejnyStan(&klawiatura,&myszkaSmoka);
	smok.wyznaczKlatkeAnimacji();
	smok.wyznaczPrzestrzenKolizji();

	//Wyznaczamy kolejny stan kamery
	Punkt punktMyszkiKamery(myszka.zwrocX(),myszka.zwrocY());
	Obiekt* obiektDoSledzenia = (&smok);
	if(smok.czyZwroconyWPrawo() && punktMyszkiKamery.x<3*wymiaryEkranu.x/4) punktMyszkiKamery.x=3*wymiaryEkranu.x/4;
	if(!smok.czyZwroconyWPrawo() && punktMyszkiKamery.x>wymiaryEkranu.x/4) punktMyszkiKamery.x=wymiaryEkranu.x/4;
	punktMyszkiKamery.x+=obiektDoSledzenia->zwrocPozycje().x+-wymiaryEkranu.x/2;
	punktMyszkiKamery.y=obiektDoSledzenia->zwrocPozycje().y-myszka.zwrocY()+wymiaryEkranu.y/2;
	kamera.wyznaczKolejnyStan(punktMyszkiKamery);

	//Strzelcy
	strzelcy.ustawCel(typCelu != 4 ? &smok : 0);
    strzelcy.wyznaczKolejnyStan();
	strzelcy.wyznaczKlatkeAnimacji();
	std::list<Strzelec> *s = strzelcy.zwrocObiekty();
	std::list<Zaslona> *z = zaslony.zwrocObiekty();
	for(std::list<Strzelec>::iterator i=s->begin();i!=s->end();i++)
	{
		ustawNajblizszaZaslone(&(*i),z);
	}

	//Balisty
	balisty.ustawCel(typCelu != 4 ? &smok : 0);
	balisty.wyznaczKolejnyStan();
	balisty.wyznaczKlatkeAnimacji();

	//Kaplani
	kaplani.ustawCel(typCelu != 4 ? &smok : 0);
	kaplani.wyznaczKolejnyStan();
	kaplani.wyznaczKlatkeAnimacji();
	std::list<Kaplan> *k = kaplani.zwrocObiekty();
	for(std::list<Kaplan>::iterator i= k->begin();i!=k->end();i++)
	{
		ustawNajblizszegoStrzelca(&(*i),s);
	}

	//Pociski
	plomienie.wyznaczKolejnyStan();
	plomienie.wyznaczKlatkeAnimacji();
	strzaly.wyznaczKolejnyStan();
	strzaly.wyznaczKlatkeAnimacji();
	belty.wyznaczKolejnyStan();
	belty.wyznaczKlatkeAnimacji();
	pociskiBalistyczne.wyznaczKolejnyStan();
    pociskiBalistyczne.wyznaczKlatkeAnimacji();
    pociskiBalistyczne.wyznaczPrzestrzenKolizji();
	pociskiKierowane.wyznaczKolejnyStan();
    pociskiKierowane.wyznaczKlatkeAnimacji();
    pociskiKasetowe.wyznaczKolejnyStan();
    pociskiKasetowe.wyznaczKlatkeAnimacji();
    usunZniszczonePociskiKasetowe();
    odlamki.wyznaczKolejnyStan();
    odlamki.wyznaczKlatkeAnimacji();

    //Przedmioty
	zaslony.wyznaczKolejnyStan();
	zaslony.wyznaczKlatkeAnimacji();
	tarczePersonalne.wyznaczKolejnyStan();
    tarczePersonalne.wyznaczKlatkeAnimacji();
	tarczeObszarowe.wyznaczKolejnyStan();
    tarczeObszarowe.wyznaczKlatkeAnimacji();

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

	/*if(strzelcy.zwrocObiekty().size()<1000000)
	{
		int x = rand()%10000+1000;
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(x,130));
	}
	//*/

    obsluzKolizje();
}
//##########################################################DEDYKOWANE######################################################
void Model::usunZniszczonePociskiKasetowe()
{
	std::list<PociskKasetowy> *pk = zwrocPociskiKasetowe()->zwrocObiekty();

	for(std::list<PociskKasetowy>::iterator i=pk->begin(); i!=pk->end() ;i++)
	{
		if(i->czyZniszczony())
		{
			ParametryPociskuKasetowego parametry = i->zwrocParametry();
			for(int j=0;j<parametry.iloscOdlamkow;j++)
			{
				double v = parametry.sredniaPredkoscOdlamkow+(((double)(rand()%100)/100)*parametry.odchyleniePredkosciOdlamkow-parametry.odchyleniePredkosciOdlamkow/2);
				double a = (double)(rand()%62831)/10000;
				Punkt predkosc = Punkt(v*cos(a),v*sin(a));
				FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::odlamek,i->zwrocPozycje()+predkosc, predkosc , parametry.czasTrwaniaOdlamkow, a, i->zwrocObrazenia());
			}
			i->usun();
		}
	}
}

void Model::ustawNajblizszegoStrzelca(Postac* k, std::list<Strzelec>* s)
{
	double minR;
	Obiekt* o=0;
	for(std::list<Strzelec>::iterator i = s->begin();i!=s->end();i++)
	{
		double r = fabs(i->zwrocPozycje().x-k->zwrocPozycje().x);
		if((r<minR || o==0) && !i->czyPosiadaTarcze())
		{
			o=&(*i);
			minR=r;
		}
	}

	k->ustawNajblizszegoKompana(o);
}

void Model::ustawNajblizszaZaslone(Postac* p, std::list<Zaslona>* s)
{
	double minR;
	Obiekt* o=0;
	if(p->zwrocPozycje().y<300)
	{
		for(std::list<Zaslona>::iterator i = s->begin();i!=s->end();i++)
		{
			double r = fabs(i->zwrocPozycje().x-p->zwrocPozycje().x);
			if((r<minR || o==0) && !i->czyZniszczony())
			{
				o=&(*i);
				minR=r;
			}
		}
	}

	p->ustawNajblizszaZaslone(o);
}

void Model::kolizjeMiedzyLudzmi()
{
	double minD=30;

	//Strzelec VS Strzelec
	if(!strzelcy.czyPusty())
	{
		for(std::list<Strzelec>::iterator i = strzelcy.zwrocObiekty()->begin();i!=strzelcy.zwrocObiekty()->end();i++)
		{
			std::list<Strzelec>::iterator j = i;
			j++;
			for(;j!=strzelcy.zwrocObiekty()->end();j++)
			{
				if(i->zwrocPozycje().x < j->zwrocPozycje().x && i->zwrocPozycje().x+minD >= j->zwrocPozycje().x)
				{
					obsluzKolizjeMiedzyLudzmi(&(*i),&(*j),true);
					continue;
				}
				if(i->zwrocPozycje().x >= j->zwrocPozycje().x && i->zwrocPozycje().x-minD <= j->zwrocPozycje().x)
				{
					obsluzKolizjeMiedzyLudzmi(&(*i),&(*j),false);
					continue;
				}
			}
		}
	}

	//Strzelec VS Kaplan
	if(!strzelcy.czyPusty() && !kaplani.czyPusty())
	{
		for(std::list<Strzelec>::iterator i = strzelcy.zwrocObiekty()->begin();i!=strzelcy.zwrocObiekty()->end();i++)
		{
			for(std::list<Kaplan>::iterator j = kaplani.zwrocObiekty()->begin();j!=kaplani.zwrocObiekty()->end();j++)
			{
				if(i->zwrocPozycje().x <= j->zwrocPozycje().x && i->zwrocPozycje().x+minD >= j->zwrocPozycje().x)
					obsluzKolizjeMiedzyLudzmi(&(*i),&(*j),true);
				if(i->zwrocPozycje().x >= j->zwrocPozycje().x && i->zwrocPozycje().x-minD <= j->zwrocPozycje().x)
					obsluzKolizjeMiedzyLudzmi(&(*i),&(*j),false);
			}
		}
	}
	//Kaplan VS Kaplan
	if(!kaplani.czyPusty())
	{
		for(std::list<Kaplan>::iterator i = kaplani.zwrocObiekty()->begin();i!=kaplani.zwrocObiekty()->end();i++)
		{
			std::list<Kaplan>::iterator j = i;
			j++;
			for(;j!=kaplani.zwrocObiekty()->end();j++)
			{
				if(i->zwrocPozycje().x <= j->zwrocPozycje().x && i->zwrocPozycje().x+minD >= j->zwrocPozycje().x)
					obsluzKolizjeMiedzyLudzmi(&(*i),&(*j),true);
				if(i->zwrocPozycje().x >= j->zwrocPozycje().x && i->zwrocPozycje().x-minD <= j->zwrocPozycje().x)
					obsluzKolizjeMiedzyLudzmi(&(*i),&(*j),false);
			}
		}
	}

}

void Model::obsluzKolizjeMiedzyLudzmi(Obiekt *o1, Obiekt *o2, bool prawo)
{
	double predkoscOdpychania=1.0;
	if(prawo)
	{
		o2->ustawCzyIstniejeCzlowiekPoLewej(true);
		o2->ustawPozycje(o2->zwrocPozycje()+Punkt(predkoscOdpychania,0));
		o1->ustawCzyIstniejeCzlowiekPoPrawej(true);
		o1->ustawPozycje(o1->zwrocPozycje()+Punkt(-predkoscOdpychania,0));
	}
	else
	{
		o2->ustawCzyIstniejeCzlowiekPoPrawej(true);
		o2->ustawPozycje(o2->zwrocPozycje()+Punkt(-predkoscOdpychania,0));
		o1->ustawCzyIstniejeCzlowiekPoLewej(true);
		o1->ustawPozycje(o1->zwrocPozycje()+Punkt(predkoscOdpychania,0));
	}
}
//##########################################################KOLIZJE#########################################################

void Model::obsluzKolizje()
{
	std::list<Zaslona> *listaZaslon = zaslony.zwrocObiekty();
	std::list<TarczaPersonalna> *listaTarczPersonalnych = tarczePersonalne.zwrocObiekty();
	std::list<TarczaObszarowa> *listaTarczObszarowych = tarczeObszarowe.zwrocObiekty();
	std::list<Strzelec> *listaStrzelcow = strzelcy.zwrocObiekty();
	std::list<Balista> *listaBalist = balisty.zwrocObiekty();
	std::list<Kaplan> *listaKaplanow = kaplani.zwrocObiekty();
	std::list<Mur> *listaMurow = mury.zwrocObiekty();

	//Plomienie Zaslony
	for(std::list<Zaslona>::iterator i=listaZaslon->begin();i!=listaZaslon->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),zniszczPocisk,zadajObrazenia,PrzestrzenKolizji::prostokat,true);
	}

	//Plomienie Tarcze Personalne
	for(std::list<TarczaPersonalna>::iterator i=listaTarczPersonalnych->begin();i!=listaTarczPersonalnych->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),rozbijPociskOTarcze,zadajObrazenia,PrzestrzenKolizji::okrag,true);
	}

	//Pociski Tarcze Obszarowe
	for(std::list<TarczaObszarowa>::iterator i=listaTarczObszarowych->begin();i!=listaTarczObszarowych->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),rozbijPociskOTarcze,zadajObrazenia,PrzestrzenKolizji::okrag,true);
		strzaly.sprawdzKolizje((Obiekt*)&(*i),usun,zadajObrazenia,PrzestrzenKolizji::okrag,true);
		belty.sprawdzKolizje((Obiekt*)&(*i),usun,zadajObrazenia,PrzestrzenKolizji::okrag,true);
		pociskiBalistyczne.sprawdzKolizje((Obiekt*)&(*i),usun,zadajObrazenia,PrzestrzenKolizji::okrag,true);
		pociskiKierowane.sprawdzKolizje((Obiekt*)&(*i),usun,zadajObrazenia,PrzestrzenKolizji::okrag,true);
		pociskiKasetowe.sprawdzKolizje((Obiekt*)&(*i),usun,zadajObrazenia,PrzestrzenKolizji::okrag,true);
		odlamki.sprawdzKolizje((Obiekt*)&(*i),usun,zadajObrazenia,PrzestrzenKolizji::okrag,true);
	}

	//Strzelcy kontra plomienie
	for(std::list<Strzelec>::iterator i=listaStrzelcow->begin();i!=listaStrzelcow->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),zniszczPocisk,zadajObrazenia,PrzestrzenKolizji::okrag,true);
	}
	//Balisty kontra plomienie
	for(std::list<Balista>::iterator i=listaBalist->begin();i!=listaBalist->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),zniszczPocisk,zadajObrazenia,PrzestrzenKolizji::prostokat,true);
	}
	//Kaplani kontra plomienie
	for(std::list<Kaplan>::iterator i=listaKaplanow->begin();i!=listaKaplanow->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),zniszczPocisk,zadajObrazenia,PrzestrzenKolizji::okrag,true);
	}

	//Smok kontra pociski
	strzaly.sprawdzKolizje(&smok,usun,zadajObrazenia,PrzestrzenKolizji::okrag);
	belty.sprawdzKolizje(&smok,usun,zadajObrazenia,PrzestrzenKolizji::okrag);
	pociskiBalistyczne.sprawdzKolizje(&smok,nic,zadajObrazenia,PrzestrzenKolizji::okrag);
	pociskiKierowane.sprawdzKolizje(&smok,usun,zadajObrazenia,PrzestrzenKolizji::okrag);
	odlamki.sprawdzKolizje(&smok,usun,zadajObrazenia,PrzestrzenKolizji::okrag);

	//Smok kontra tarcze obszarowe
	tarczeObszarowe.sprawdzKolizje(&smok,nic,odepchnijOdTarczy,PrzestrzenKolizji::okrag);

	//Mury vs pociski
	for(std::list<Mur>::iterator i=listaMurow->begin();i!=listaMurow->end();i++)
	{
		plomienie.sprawdzKolizje((Obiekt*)&(*i),kolizjaPlomieniazMurem,nic,PrzestrzenKolizji::prostokat,true);
		belty.sprawdzKolizje((Obiekt*)&(*i),usun,nic,PrzestrzenKolizji::prostokat,true);
		strzaly.sprawdzKolizje((Obiekt*)&(*i),kolizjaPlomieniazMurem,nic,PrzestrzenKolizji::prostokat,true);
		pociskiBalistyczne.sprawdzKolizje((Obiekt*)&(*i),kolizjaPlomieniazMurem,nic,PrzestrzenKolizji::prostokat,true);
		pociskiKierowane.sprawdzKolizje((Obiekt*)&(*i),usun,nic,PrzestrzenKolizji::prostokat,true);
		pociskiKasetowe.sprawdzKolizje((Obiekt*)&(*i),usun,nic,PrzestrzenKolizji::prostokat,true);
		odlamki.sprawdzKolizje((Obiekt*)&(*i),usun,nic,PrzestrzenKolizji::prostokat,true);
	}
	//Mury vs postacie
	for(std::list<Mur>::iterator i=listaMurow->begin();i!=listaMurow->end();i++)
	{
		strzelcy.sprawdzKolizje((Obiekt*)&(*i),kolizjaCzlowiekaZMurem,nic,PrzestrzenKolizji::prostokat,true);
		kaplani.sprawdzKolizje((Obiekt*)&(*i),kolizjaCzlowiekaZMurem,nic,PrzestrzenKolizji::prostokat,true);
	}
	mury.sprawdzKolizje(&smok,nic,kolizjaSmokaZMurem,PrzestrzenKolizji::prostokat,false);
	zaslony.sprawdzKolizje(&smok,nic,kolizjaSmokaZPlatforma,PrzestrzenKolizji::prostokat,false);

	kolizjeMiedzyLudzmi();
}

void Model::zniszcz(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	o->zniszcz();
}

void Model::zniszczPocisk(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	if(!o->czyZniszczony())
	{
		if(punktKolizji.x>o2->zwrocPozycje().x) punktKolizji.x+=2;
		else punktKolizji.x-=2;
		if(punktKolizji.y>o2->zwrocPozycje().y) punktKolizji.y+=2;
		else punktKolizji.y-=2;

		o->ustawPozycje(punktKolizji);
		o->ustawPunktZaczepu(o2);
	}
	o->zniszcz();
}

void Model::rozbijPociskOTarcze(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	if(!o->czyZniszczony())
	{
		Punkt p1 = o->zwrocPozycje();
		Punkt p2 = o2->zwrocPozycje();
		//Zakladamy ze jak doszlo do kolizji to MUSI cos byc w przestrzeni kolizji
		double r = (*(o2->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPromien();
		double a = atan2(-p2.y+p1.y,-p2.x+p1.x);

		if(punktKolizji.x>o2->zwrocPozycje().x) p2.x+=2;
		else p2.x-=2;
		if(punktKolizji.y>o2->zwrocPozycje().y) p2.y+=2;
		else p2.y-=2;

		o->ustawPozycje(Punkt(p2.x+cos(a)*r,p2.y+sin(a)*r));
		o->ustawPunktZaczepu(o2);
	}
	o->zniszcz();
}

void Model::odepchnijOdTarczy(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	if(!o->czyZniszczony())
	{
		Punkt p1 = o->zwrocPozycje();
		Punkt p2 = o2->zwrocPozycje();
		Wektor v1 = o->zwrocPredkosc();

		double rv = v1.dlugosc();
		double r = 20;
		double a = atan2(-p2.y+p1.y,-p2.x+p1.x);

		o->ustawPredkosc(Wektor(cos(a)*rv,sin(a)*rv));
		o->ustawPozycje(o->zwrocPozycje()-Punkt(cos(a+M_PI)*r,sin(a+M_PI)*r));
	}
	o2->zadajObrazenia(0);
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
	if(!o->czyPosiadaTarcze())
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
			o->ustawPozycje(Punkt(o->zwrocPozycje().x+(minX-prostokat1.zwrocPozycje().x)-2,o->zwrocPozycje().y+(minX-prostokat1.zwrocPozycje().x)/2));
		else if(prostokat1.zwrocPozycje().x+6*prostokat1.zwrocBok1()/8>maxX)
			o->ustawPozycje(Punkt(o->zwrocPozycje().x+(maxX-prostokat1.zwrocPozycje().x)+2,o->zwrocPozycje().y-(maxX-prostokat1.zwrocPozycje().x)/2));
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

void Model::kolizjaCzlowiekaZMurem(Obiekt*o, Obiekt *o2, Punkt punktKolizji)
{
	assert("Czlowiek nie ma ustalonego prostokata kolizji" && !o->zwrocPrzestrzenKolizji()->zwrocProstokaty()->empty());
	ProstokatKolizji prostokat1 = (*(o->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	ProstokatKolizji prostokat2 = (*(o2->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	double minY = o2->zwrocPozycje().y+prostokat1.zwrocBok2()/2+prostokat2.zwrocBok2()/2;
	double maxY = o2->zwrocPozycje().y-prostokat1.zwrocBok2()/2-prostokat2.zwrocBok2()/2;
	double minX = o2->zwrocPozycje().x-prostokat1.zwrocBok1()/2-prostokat2.zwrocBok1()/2;
	double maxX = o2->zwrocPozycje().x+prostokat1.zwrocBok1()/2+prostokat2.zwrocBok1()/2;

	if(o->zwrocPozycje().y+prostokat1.zwrocBok2()/2>=minY)
	{
		if(prostokat1.zwrocPozycje().x-6*prostokat1.zwrocBok1()/8<minX)
			o->ustawCzyIstniejePrzeszkodaPoLewej(true);
		else if(prostokat1.zwrocPozycje().x+6*prostokat1.zwrocBok1()/8>maxX)
			o->ustawCzyIstniejePrzeszkodaPoPrawej(true);
		o->postawNaZiemi(minY-1);
	}
	else if(o->zwrocPozycje().x-prostokat1.zwrocBok1()/2<minX || o->zwrocPredkosc().x>prostokat1.zwrocBok1()/2)
	{

		o->ustawCzyIstniejePrzeszkodaPoPrawej(true);
		o->zatrzymajNaScianie();
		o->ustawPozycje(Punkt(minX+0.01,o->zwrocPozycje().y));
	}
	else if(o->zwrocPozycje().x+prostokat1.zwrocBok1()/2>maxX || o->zwrocPredkosc().x<-prostokat1.zwrocBok1()/2)
	{
		o->ustawCzyIstniejePrzeszkodaPoLewej(true);
		o->zatrzymajNaScianie();
		o->ustawPozycje(Punkt(maxX-0.01,o->zwrocPozycje().y));
	}


}

void Model::kolizjaSmokaZPlatforma(Obiekt*o, Obiekt *o2, Punkt punktKolizji)
{
	assert("Smok nie ma ustalonego prostokata kolizji" && !o->zwrocPrzestrzenKolizji()->zwrocProstokaty()->empty());
	ProstokatKolizji prostokat1 = (*(o->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	ProstokatKolizji prostokat2 = (*(o2->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	double minY = o2->zwrocPozycje().y+prostokat1.zwrocBok2()/2+prostokat2.zwrocBok2()/2;
	double maxY = o2->zwrocPozycje().y-prostokat1.zwrocBok2()/2-prostokat2.zwrocBok2()/2;
	double minX = o2->zwrocPozycje().x-prostokat1.zwrocBok1()/2-prostokat2.zwrocBok1()/2;
	double maxX = o2->zwrocPozycje().x+prostokat1.zwrocBok1()/2+prostokat2.zwrocBok1()/2;


	if((o->zwrocPozycje().y+prostokat1.zwrocBok2()/8>minY || o->zwrocPredkosc().y<-prostokat1.zwrocBok2()/8) && prostokat1.zwrocPozycje().x-6*prostokat1.zwrocBok1()/8>minX && prostokat1.zwrocPozycje().x+6*prostokat1.zwrocBok1()/8<maxX )
	{
			o->postawNaZiemi(minY+prostokat2.zwrocPozycjeWzgledemObiektu().y);
	}


}

void Model::kolizjaPlomieniazMurem(Obiekt *o,Obiekt *o2,Punkt punktKolizji)
{
	ProstokatKolizji prostokat=(*(o2->zwrocPrzestrzenKolizji()->zwrocProstokaty()))[0];
	Punkt pozycja1=o->zwrocPozycje();
	Punkt pozycja2=(o->zwrocPozycje())-(o->zwrocPredkosc());
	if(pozycja1.x>prostokat.zwrocPozycje().x-prostokat.zwrocBok1()/2 && pozycja1.x<prostokat.zwrocPozycje().x+prostokat.zwrocBok1()/2 &&
	   pozycja1.y>prostokat.zwrocPozycje().y-prostokat.zwrocBok2()/2 && pozycja1.y<prostokat.zwrocPozycje().y+prostokat.zwrocBok2()/2 &&
	   (
	     (pozycja2.x>prostokat.zwrocPozycje().x-prostokat.zwrocBok1()/2 && pozycja2.x<prostokat.zwrocPozycje().x+prostokat.zwrocBok1()/2) &&
	     (pozycja2.y>prostokat.zwrocPozycje().y-prostokat.zwrocBok2()/2 && pozycja2.y<prostokat.zwrocPozycje().y+prostokat.zwrocBok2()/2)
	   )
	  ) //Jeśli plomien pojawil sie wewnatrz muru to ma byc zniszczony natychmiastowo
	{
		o->usun();
	}
	else if(!o->czyZniszczony())
	{
		o->ustawPozycje(punktKolizji);
		o->ustawPunktZaczepu(o2);
	}
	o->zniszcz();
}
//#########################################################      MENU       ################################################################

void Model::ustawMenu(int numer)
{
	if(numer == 0)
	{
		reset();
		typScenerii=0;
		kamera.ustawPozycje(Punkt(5000,200));
	}

	listaOpcjiMenu.clear();
	typMenu = numer;
	//numer -1 gra
	if(numer == 0) // glowne menu
	{
		listaOpcjiMenu.push_back("nowa gra");
		listaOpcjiMenu.push_back("samouczek");
		listaOpcjiMenu.push_back("opcje");
		listaOpcjiMenu.push_back("wyj^cie");
	}
	else if(numer == 1) //menu w grze
	{
		listaOpcjiMenu.push_back("wzn%w");
		listaOpcjiMenu.push_back("statystyki smoka");
		listaOpcjiMenu.push_back("opcje");
		listaOpcjiMenu.push_back("zako$cz");
	}
	else if(numer == 2 || numer == 3) //opcje
	{
		if(pelnyEkran) listaOpcjiMenu.push_back("pe]ny ekran w].");
		else listaOpcjiMenu.push_back("pe]ny ekran wy].");

		if(wymiaryEkranu.y == 600) listaOpcjiMenu.push_back("proporcje ekranu 16:9");
		else listaOpcjiMenu.push_back("proporcje ekranu 4:3");

		listaOpcjiMenu.push_back("wr%@");
	}
	else if(numer == 5) //Statystyki smoka
	{
		std::vector<int> statystyki = smok.zwrocStatystyki();
		char a[3]; a[2]=0;
		std::string liczba;

		a[0] = statystyki[0]/10+48; a[1] = statystyki[0]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("si]a " + liczba);

		a[0] = statystyki[1]/10+48; a[1] = statystyki[1]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("wigor " + liczba);

		a[0] = statystyki[2]/10+48; a[1] = statystyki[2]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("zdrowie " + liczba);

		a[0] = statystyki[3]/10+48; a[1] = statystyki[3]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("zwinno^@ " + liczba);
		listaOpcjiMenu.push_back("wr%@");
	}
	else if(numer == 5) //Staty smoka
	{
		std::vector<int> statystyki = smok.zwrocStatystyki();
		char a[3]; a[2]=0;
		std::string liczba;

		a[0] = statystyki[0]/10+48; a[1] = statystyki[0]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("si]a " + liczba);

		a[0] = statystyki[1]/10+48; a[1] = statystyki[1]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("wigor " + liczba);

		a[0] = statystyki[2]/10+48; a[1] = statystyki[2]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("zdrowie " + liczba);

		a[0] = statystyki[3]/10+48; a[1] = statystyki[3]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("zwinno^@ " + liczba);
		listaOpcjiMenu.push_back("wr%@");
	}
	else if(numer == 6) //Rozwoj smoka
	{
		std::vector<int> statystyki = smok.zwrocStatystyki();
		char a[3]; a[2]=0;
		std::string liczba;

		a[0] = iloscPunktowDoRozdania/10+48; a[1] = iloscPunktowDoRozdania%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("pozostalo " + liczba);

		a[0] = statystyki[0]/10+48; a[1] = statystyki[0]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("si]a " + liczba);

		a[0] = statystyki[1]/10+48; a[1] = statystyki[1]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("wigor " + liczba);

		a[0] = statystyki[2]/10+48; a[1] = statystyki[2]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("zdrowie " + liczba);

		a[0] = statystyki[3]/10+48; a[1] = statystyki[3]%10+48; a[0]=a[0]=='0'?' ':a[0];liczba = a;
		listaOpcjiMenu.push_back("zwinno^@ " + liczba);
		listaOpcjiMenu.push_back("nast#pna misja");
	}
}

//#########################################################   ZWRACANIE     ################################################################
std::string Model::zwrocNapisNumeruPoziomu()
{
	switch(numerPoziomu)
	{
	case 1:
		return std::string("poziom 1");
	case 2:
		return std::string("poziom 2");
	case 3:
		return std::string("poziom 3");
	case 4:
		return std::string("poziom 4");
	case 5:
		return std::string("poziom 5");
	case 6:
		return std::string("poziom 6");
	case 7:
		return std::string("poziom 7");
	case 8:
		return std::string("poziom 8");
	case 9:
		return std::string("poziom 9");
	case 10:
		return std::string("poziom 10");
	case 11:
		return std::string("poziom 11");
	case 12:
		return std::string("poziom 12");
	case 13:
		return std::string("poziom 13");
	case 14:
		return std::string("poziom 14");
	case 15:
		return std::string("poziom 15");
	case 16:
		return std::string("poziom 16");
	case 17:
		return std::string("poziom 17");
	case 18:
		return std::string("poziom 18");
	case 19:
		return std::string("poziom 19");
	case 20:
		return std::string("poziom 20");
	case 21:
		return std::string("gratulacje");
	default:
		return std::string("samouczek");
	}
}
