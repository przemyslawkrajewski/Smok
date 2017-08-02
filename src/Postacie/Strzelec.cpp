/*
 * Strzelec.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Strzelec.h"
#include "PomocnikCelowania.h"

Strzelec::Strzelec(): Postac()
{
	pozycja.x=2000;
	pozycja.y=parametryObiektow.poziomZiemi+50;
	stan = stoi;
	stanBiegu=0;
	stanNaciagania=-1;
	stanCelowania=0;
	stanRzucaniaZaklec=0;

	katCelowania=0;

	zycie=100;
	obrazenia=5;
	iloscStrzalWSerii=10;
	gotowoscSwietejStrzaly=0;

	pozycjaStrzelecka=false;
	wSerii=false;
	najblizszaZaslona=0;
}

void Strzelec::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		zablokowany=false;
		if (klawiatura->czyWcisnietoPrawo())
		{
			if(przeszkodaPoPrawej)
			{
				zablokowany=true;
				stan=stoi;
			}
			else
			{
				zwroconyWPrawo=true;
				if(!myszka->zwrocLPM())
				{
					stan = biegnie;

					if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
					else stanBiegu += parametry.predkoscAnimacjiBiegu1;

					if(stanBiegu>=parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
					pozycja.x+=parametry.predkoscBiegu;
					if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
					stanCelowania=0;
				}
			}
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
		}
		else if (klawiatura->czyWcisnietoLewo())
		{
			if(przeszkodaPoLewej)
			{
				zablokowany=true;
				stan=stoi;
			}
			else
			{
				zwroconyWPrawo=false;
				if(!myszka->zwrocLPM())
				{
					stan = biegnie;

					if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
					else stanBiegu += parametry.predkoscAnimacjiBiegu1;

					if(stanBiegu>=parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
					pozycja.x-=parametry.predkoscBiegu;
					if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
					stanCelowania=0;
				}
			}
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
		}
		else if(myszka->zwrocLPM())
		{
			if(cel->zwrocPozycje().x-pozycja.x>0) zwroconyWPrawo=true;
			else zwroconyWPrawo=false;

			stanBiegu=0;
			if(stanNaciagania<0)
			{
				stan = strzela;
				stanCelowania++;
				if(stanCelowania > parametry.maxCelowania)
				{
					double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					kat=-kat+((double)(rand()%100)/100)*parametry.celnosc - parametry.celnosc/2;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscStrzaly*cos(kat);
					v.y=parametry.predkoscStrzaly*sin(kat);
					if(kat>6.28) kat-=6.28;
					if(parametry.spust) FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::belt,p,v,parametry.czasTrwaniaStrzaly,kat,parametry.obrazenia);
					else FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::strzala,p,v,parametry.czasTrwaniaStrzaly,kat,parametry.obrazenia);
					stanNaciagania=parametry.maxNaciagniecie;
					stanCelowania=0;
				}
			}
			else
			{
				stanCelowania=0;
				stan = naciaga;
				stanNaciagania--;
			}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(0) && !czyPosiadaTarcze())
		{
			// Tarcza personalna
			stan = tarczaPersonalna;
			stanRzucaniaZaklec++;

			if(stanRzucaniaZaklec>parametry.czasRzucaniaPersonalnejTarczy)
			{
				stanRzucaniaZaklec=0;
				FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalna,Punkt(),this);
				ustawCzyPosiadaTarcze(true);
			}
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(1) && parametry.obrazeniaSwietejStrzaly!=0)
		{
			// Swieta Strzala
			if(cel->zwrocPozycje().x-pozycja.x>0) zwroconyWPrawo=true;
			else zwroconyWPrawo=false;

			stanBiegu=0;
			if(stanNaciagania<0)
			{
				stan = strzela;
				if(stanCelowania <= parametry.maxCelowania) stanCelowania++;
				if(stanCelowania > parametry.maxCelowania && gotowoscSwietejStrzaly >= parametry.czasOdnawianiaSwietejStrzaly)
				{
					double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					kat=-kat+((double)(rand()%100)/100)*parametry.celnosc - parametry.celnosc/2;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscSwietejStrzaly*cos(kat);
					v.y=parametry.predkoscSwietejStrzaly*sin(kat);
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::swietaStrzala,p,v,parametry.czasTrwaniaSwietejStrzaly,kat,parametry.obrazeniaSwietejStrzaly);
					stanNaciagania=parametry.maxNaciagniecie;
					stanCelowania=0;
					gotowoscSwietejStrzaly=0;
				}
			}
			else
			{
				stanCelowania=0;
				stan = naciaga;
				stanNaciagania--;

			}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(2) && iloscStrzalWSerii>=1)
		{
			// Seria Strzal
			if(cel->zwrocPozycje().x-pozycja.x>0) zwroconyWPrawo=true;
			else zwroconyWPrawo=false;

			stanBiegu=0;
			if(stanNaciagania<0)
			{
				stan = strzela;
				stanCelowania++;
				if(stanCelowania > parametry.maxSzybkiegoCelowania)
				{
					double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					kat=-kat+((double)(rand()%100)/100)*parametry.celnosc - parametry.celnosc/2;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscStrzaly*cos(kat);
					v.y=parametry.predkoscStrzaly*sin(kat);
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::strzala,p,v,parametry.czasTrwaniaSwietejStrzaly,kat,parametry.obrazenia);
					stanCelowania=0;
					stanNaciagania=parametry.maxSzybkiegoNaciagania;
					stan = strzela;
					iloscStrzalWSerii--;
				}
			}
			else
			{
				stanCelowania=0;
				if(stan!=strzela) stan = naciaga;
				stanNaciagania--;

			}
		}
		else
		{
			stan = stoi;
			stanBiegu=0;
			stanCelowania=0;
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
		}

		if(!klawiatura->czyWcisnietoKlawiszFunkcyjny(0)) stanRzucaniaZaklec=0;
		if(gotowoscSwietejStrzaly < parametry.czasOdnawianiaSwietejStrzaly) gotowoscSwietejStrzaly++;
		if(!klawiatura->czyWcisnietoKlawiszFunkcyjny(2))
		{
			iloscStrzalWSerii+=parametry.predkoscOdnawianiaSerii;
			if(iloscStrzalWSerii>parametry.maksymalnaIloscStrzalWSerii) iloscStrzalWSerii=parametry.maksymalnaIloscStrzalWSerii;
		}


		if(pozycja.y<=parametry.wysokosc+parametryObiektow.poziomZiemi)
		{
			pozycja.y=parametry.wysokosc+parametryObiektow.poziomZiemi;
			naZiemi=true;
		}
		if(!naZiemi)
		{
			pozycja.y-=10;
		}
		naZiemi=false;
		przeszkodaPoPrawej=false;
		przeszkodaPoLewej=false;
		czlowiekPoPrawej=false;
		czlowiekPoLewej=false;

		if(zycie<=0) zniszcz();
	}
	else
	{
		stan = umiera;
		std::vector<ProstokatKolizji> p;
		ustawPrzestrzenKolizji(p);
	}
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################

std::pair<Klawiatura,Myszka> Strzelec::wyznaczSterowanie()
{
	int odleglosc=200;

	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	Klawiatura k;
	Myszka m;

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}

	bool mozliwyStrzal = pomocnikCelowania.czyMozliwyStrzal(pozycja-pozycjaCelu);
	Punkt poprawka;
	if(mozliwyStrzal)
	{
		Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
		poprawka.y=-poprawka.y+10;
		poprawka.x=-poprawka.x;
		if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
		else poprawka.x-=30;
	}

	if(typZachowania==0) // Primitywny Lucznik
	{
		double maxOdleglosc=1250;
		double minOdleglosc=900;

		if(mozliwyStrzal) pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka);

		double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;//*/

		if(abs(pozycjaCelu.x-pozycja.x)>maxOdleglosc) mozliwyStrzal=false;
		if(abs(pozycja.x-pozycjaCelu.x)>maxOdleglosc) pozycjaStrzelecka=false;
		else if((abs(pozycja.x-pozycjaCelu.x)<minOdleglosc && !(zwroconyWPrawo && czlowiekPoPrawej) && !(!zwroconyWPrawo && czlowiekPoLewej)) || zablokowany) pozycjaStrzelecka=true;

		if(pozycja.x-pozycjaCelu.x>0 && !pozycjaStrzelecka && najblizszaZaslona==0)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if(pozycja.x-pozycjaCelu.x<0 && !pozycjaStrzelecka && najblizszaZaslona==0)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if(pozycjaStrzelecka)
		{
			m.ustawLPM(true);
		}
	}
	if(typZachowania==1) // Stacjonarny
	{
		double maxOdleglosc=2000;

		if(mozliwyStrzal) pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka,cel->zwrocPredkosc());

		double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;//*/

		if(abs(pozycja.x-pozycjaCelu.x)<maxOdleglosc && mozliwyStrzal)
		{
			m.ustawLPM(true);
		}
	}
	if(typZachowania==2) // Lucznik Zawodowy
	{
		double maxOdleglosc=3050;
		double minOdleglosc=1500;

		if(mozliwyStrzal) pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka,cel->zwrocPredkosc());

		double kat;
		if(pozycja.y-pozycjaCelu.y<=0 && abs(pozycja.x-pozycjaCelu.x)<1000) kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
		else kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katZGory);

		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;//*/

		double odlegloscOdZaslony;
		bool zaslonaWPoblizu=false;
		bool podZaslona=false;

		if(najblizszaZaslona!=0)
		{
			if(abs(pozycja.x-najblizszaZaslona->zwrocPozycje().x)>100)
			{
				zaslonaWPoblizu=true;
				odlegloscOdZaslony=pozycja.x-najblizszaZaslona->zwrocPozycje().x;
			}
			else
			{
				podZaslona=true;
			}
		}
		if(abs(pozycja.x-pozycjaCelu.x)>maxOdleglosc)
		{
			mozliwyStrzal=false;
			pozycjaStrzelecka=false;
		}

		pozycjaStrzelecka=true;

		if((!podZaslona && pozycja.x-pozycjaCelu.x>0) && !pozycjaStrzelecka)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if( (!podZaslona && pozycja.x-pozycjaCelu.x<0) && !pozycjaStrzelecka)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if(pozycjaStrzelecka)
		{
			m.ustawLPM(true);
		}
	}
	if(typZachowania==3) // Rycerz
	{
		double maxOdleglosc=3000;
		double minOdleglosc=2000;

		if(mozliwyStrzal) pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka,cel->zwrocPredkosc());

		double kat;
		if(pozycja.y-pozycjaCelu.y<=0) kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
		else kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katZGory);

		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;//*/

		double odlegloscOdZaslony;
		bool zaslonaWPoblizu=false;
		bool podZaslona=false;

		if(abs(pozycja.x-pozycjaCelu.x)>maxOdleglosc || pozycja.y-pozycjaCelu.y>60)
		{
			mozliwyStrzal=false;
			pozycjaStrzelecka=false;
		}

		if(abs(pozycja.x-pozycjaCelu.x)<maxOdleglosc) pozycjaStrzelecka=true;
		if((zwroconyWPrawo && przeszkodaPoPrawej) || (!zwroconyWPrawo && przeszkodaPoLewej)) pozycjaStrzelecka=true;

		if((!podZaslona && pozycja.x-pozycjaCelu.x>0) && !pozycjaStrzelecka && abs(pozycja.x-pozycjaCelu.x)>minOdleglosc)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if( (!podZaslona && pozycja.x-pozycjaCelu.x<0) && !pozycjaStrzelecka && abs(pozycja.x-pozycjaCelu.x)>minOdleglosc)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if((mozliwyStrzal && pozycjaStrzelecka) || stanNaciagania>0)
		{
			m.ustawLPM(true);
		}
	}
	if(typZachowania==4) // Krzyzowiec
	{
		double maxOdleglosc=6000;
		double minOdleglosc=2000;

		if(mozliwyStrzal) pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka,cel->zwrocPredkosc());

		double kat;
		kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);

		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;//*/

		double odlegloscOdZaslony;
		bool zaslonaWPoblizu=false;
		bool podZaslona=false;

		if(abs(pozycja.x-pozycjaCelu.x)>maxOdleglosc || pozycja.y-pozycjaCelu.y>60)
		{
			mozliwyStrzal=false;
			pozycjaStrzelecka=false;
		}

		if(abs(pozycja.x-pozycjaCelu.x)<maxOdleglosc) pozycjaStrzelecka=true;
		if((zwroconyWPrawo && przeszkodaPoPrawej) || (!zwroconyWPrawo && przeszkodaPoLewej)) pozycjaStrzelecka=true;

		if((!podZaslona && pozycja.x-pozycjaCelu.x>0) && !pozycjaStrzelecka && abs(pozycja.x-pozycjaCelu.x)>minOdleglosc)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if( (!podZaslona && pozycja.x-pozycjaCelu.x<0) && !pozycjaStrzelecka && abs(pozycja.x-pozycjaCelu.x)>minOdleglosc)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if((mozliwyStrzal && pozycjaStrzelecka) || stanNaciagania>0)
		{
			if(staraPredkoscCelu.x==cel->zwrocPredkosc().x && fabs(staraPredkoscCelu.y-cel->zwrocPredkosc().y)<10 && parametry.czasOdnawianiaSwietejStrzaly==gotowoscSwietejStrzaly) k.ustawWcisnietoKlawiszFunkcyjny(true,1);
			else m.ustawLPM(true);
		}
		staraPredkoscCelu=cel->zwrocPredkosc();
	}
	else if(typZachowania==99)
	{
/*		double kat = 0;
		if(pozycja.y<pozycjaCelu.y) kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
		else kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katZGory);

		if(mozliwyStrzal) pomocnikCelowania.wyznaczKatStrzalu(pozycja-pozycjaCelu+poprawka,cel->zwrocPredkosc());

		m.ustawX(1000*cos(-kat));
		m.ustawY(1000*sin(-kat));
		katCelowania=kat;

		if(iloscStrzalWSerii == parametry.maksymalnaIloscStrzalWSerii) wSerii=true;
		else if(iloscStrzalWSerii<1) wSerii=false;

		if(abs(pozycjaCelu.x-pozycja.x)>maxOdleglosc) mozliwyStrzal=false;
		if( (stanNaciagania>0 && parametry.spust) || (mozliwyStrzal && wSerii))
		{
			m.ustawLPM(true);
		}*/
	}

	if(m.zwrocLPM()==false || (m.zwrocLPM()==true && stanNaciagania==-1 && parametry.maxCelowania==stanCelowania))
	{
		pomocnikCelowania.resetCelowania();
	}
	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

//#####################################################################################################
//Podfunkcje Kolizje
//#####################################################################################################
void Strzelec::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki = 100/2;
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(),100));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-30+rozmiarKlatki),10));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-50+rozmiarKlatki),14));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-70+rozmiarKlatki),14));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(50-rozmiarKlatki,-88+rozmiarKlatki),14));
	ustawPrzestrzenKolizji(okregi);
}
//#####################################################################################################
//Podfunkcje Grafika
//#####################################################################################################
void Strzelec::wyznaczKlatkeAnimacji()
{
	double kat;
	switch(stan)
	{
	case naciaga:
		if(parametry.spust)
		{
			if(klatkaAnimacji.x!=2 || klatkaAnimacji.y<4)
			{
				klatkaAnimacji.x=2;
				klatkaAnimacji.y=4;
			}
			klatkaAnimacji.y+=0.3;
			if(klatkaAnimacji.y>=7)klatkaAnimacji.y=4;
		}
		else
		{
			klatkaAnimacji.x=2;
			klatkaAnimacji.y=9-4*(stanNaciagania/parametry.maxNaciagniecie);
			if(klatkaAnimacji.y>=8)
			{
				klatkaAnimacji.y=0;
			}
		}
		break;
	case naciagaWSerii:
		//Zamiast niego wykorzystywany jest stan Strzela
		klatkaAnimacji.x=2;
		klatkaAnimacji.y=7;
		break;
	case stoi:
		klatkaAnimacji.x=0;
		klatkaAnimacji.y=0;
		break;
	case biegnie:
		klatkaAnimacji.x=1;
		klatkaAnimacji.y=(double)((int)stanBiegu);
		break;
	case strzela:
		klatkaAnimacji.x=2;
		klatkaAnimacji.y=0;

		kat = katCelowania-3*3.14/2;
		if(kat<0) kat=-kat;
		//double poprawka=0;
		//if(zwroconyWPrawo) poprawka=6.28/16;
		//else poprawka=6.28/16;
		klatkaAnimacji.y=4-((double)(kat)/(6.28/16));
		klatkaAnimacji.y= (int)klatkaAnimacji.y;
		if(klatkaAnimacji.y>3) klatkaAnimacji.y=3;
		if(klatkaAnimacji.y<0) klatkaAnimacji.y=0;
		break;
	case tarczaPersonalna:
		klatkaAnimacji.x=0;
		klatkaAnimacji.y=6;
		break;
	case umiera:
		if(klatkaAnimacji.x!=0 || klatkaAnimacji.y<1 || klatkaAnimacji.y>5)
		{
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=1;
		}
		else
			klatkaAnimacji.y+=0.3;
		if (klatkaAnimacji.x!=0 || klatkaAnimacji.y>=5) usun();
		break;
	}
}
