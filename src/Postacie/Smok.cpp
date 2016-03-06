/*
 * Smok.cpp
 *
 *  Created on: 11-08-2013
 *      Author: przemo
 */

#include "Smok.h"

Smok::Smok(): Postac()
{
	stan=unosi;
	minKatGlowy=0;
	maksKatGlowy=0;
	obrotGlowy=0;
	iloscOgnia=10;
	przerwaOgnia=0;
	zadaneY=100;
	pozycja.x=100;
	pozycja.y=300;
	zwroconyWPrawo=true;
	zieje=false;

	std::vector<OkragKolizji> f;
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(0,0),10));
	ustawPrzestrzenKolizji(f);
}

void Smok::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	Punkt staraPredkosc(predkosc);
	wyznaczLot(klawiatura,myszka);
	wyznaczGlowe(klawiatura,myszka);

	if(pozycja.y-zadaneY>70) zadaneY=pozycja.y-70;
	predkosc.y-=parametry.wspolczynnikGrawitacji;
	if(predkosc.y<-parametry.maksymalnaPredkoscY) predkosc.y=-parametry.maksymalnaPredkoscY;
	if(predkosc.y>parametry.maksymalnaPredkoscY) predkosc.y=parametry.maksymalnaPredkoscY;

	pozycja.x+=predkosc.x;
	pozycja.y+=predkosc.y;

	if(pozycja.y<=parametryObiektow.poziomZiemi+parametry.wysokosc)
	{
		pozycja.y=parametryObiektow.poziomZiemi+parametry.wysokosc;
		zadaneY=parametryObiektow.poziomZiemi+parametry.wysokosc;
		predkosc.y=0;
	}
	if(zadaneY<parametryObiektow.poziomZiemi+parametry.wysokosc) zadaneY=parametryObiektow.poziomZiemi+parametry.wysokosc;

	przyspieszenie.y=staraPredkosc.y-predkosc.y;


}
//#####################################################################################################
//Podfunkcje Smoka Przeliczanie
//#####################################################################################################
void Smok::wyznaczLot(Klawiatura *klawiatura, Myszka *myszka)
{
	//Obsługa klawiszy
	if(klawiatura->czyWcisnietoPrawo() && klawiatura->czyWcisnietoGora())
	{
		if(predkosc.x>0 && myszka->zwrocX()<0) zwroconyWPrawo=true;
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc) //Jesli jestem na ziemi
		{
			predkosc.y=parametry.silaWybicia;	//wybijamy sie
			predkosc.x=parametry.silaWybicia/2;
			pozycja.y=parametryObiektow.poziomZiemi+5+parametry.wysokosc;
			zadaneY=parametryObiektow.poziomZiemi+5+parametry.wysokosc;
			stan=leci;
		}
		else
		{
			if(predkosc.x>=parametry.maksymalnaPredkoscX) //Szybowanie
			{
				szybowanie(parametry.maksymalnaPredkoscX,true,false);
				stan=szybujacWznosi;
			}
			else if(predkosc.x>=0) //Lot
			{
				if(!zwroconyWPrawo)
				{
					rozpedzanie(parametry.wspolczynnikRozpedzaniaSieX,parametry.maksymalnaPredkoscTylemX);
					stan=leciTylem;
				}
				else
				{
					rozpedzanie(parametry.wspolczynnikRozpedzaniaSieX,parametry.maksymalnaPredkoscX);
					if(abs(predkosc.x)<parametry.predkoscZblizaniaSie) stan=zbliza;
					else stan=leci;

				}
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,parametry.predkoscWznoszeniaSieY/2);

			}
			else	//zawracanie
			{
				hamowanieX();
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				if(abs(predkosc.x)>abs(predkosc.y))	//Ustalamy stan
				{
					if(abs(predkosc.x)>2) stan=hamujeX;
					else stan=unosi;
				}
				else
				{
					if(abs(predkosc.y)>parametry.vyPrzyUnoszeniu) stan=hamujeY;
					else stan=unosi;
				}
			}
		}
	}
	else if(klawiatura->czyWcisnietoPrawo() && klawiatura->czyWcisnietoDol())
	{
		if(predkosc.x>0 && myszka->zwrocX()<0) zwroconyWPrawo=true;
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			hamowanieNaZiemi();
			stan=stoi;
		}
		else
		{
			if(predkosc.x>=0) //Szybowanie w dol
			{
				zwroconyWPrawo=true;
				rozpedzanie(parametry.wspolczynnikRozpedzaniaSieX,parametry.maksymalnaPredkoscX);
				szybowanie(parametry.maksymalnaPredkoscX,false,true);
				stan=szybujacSpada;
			}
			else if(predkosc.x<0) //zawracanie
			{
				hamowanieX();
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				stan=hamujeX;
			}
		}
	}
	else if(klawiatura->czyWcisnietoLewo() && klawiatura->czyWcisnietoDol() && pozycja.x>500)
	{
		if(predkosc.x<0 && myszka->zwrocX()>0) zwroconyWPrawo=false;
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			hamowanieNaZiemi();
			stan=stoi;
		}
		else
		{
			if(predkosc.x<=0) //Szybowanie w dol
			{
				zwroconyWPrawo=false;
				rozpedzanie(-parametry.wspolczynnikRozpedzaniaSieX,-parametry.maksymalnaPredkoscX);
				szybowanie(-parametry.maksymalnaPredkoscX,false,true);
				stan=szybujacSpada;
			}
			else if(predkosc.x>0) //zawracanie
			{
				hamowanieX();
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				stan=hamujeX;
			}
		}
	}
	else if(klawiatura->czyWcisnietoLewo() && klawiatura->czyWcisnietoGora() && pozycja.x>500)
	{
		if(predkosc.x<0 && myszka->zwrocX()>0) zwroconyWPrawo=false;
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			predkosc.y=parametry.silaWybicia;
			predkosc.x=-parametry.silaWybicia/2;
			pozycja.y=parametryObiektow.poziomZiemi+5+parametry.wysokosc;
			zadaneY=parametryObiektow.poziomZiemi+5+parametry.wysokosc;
			stan=leci;
		}
		else
		{
			if(predkosc.x<=-parametry.maksymalnaPredkoscX) //Szybowanie
			{
				szybowanie(-parametry.maksymalnaPredkoscX,true,false);
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				stan=szybujacWznosi;
			}
			else if(predkosc.x<=0) //Lot
			{
				if(zwroconyWPrawo)
				{
					rozpedzanie(-parametry.wspolczynnikRozpedzaniaSieX,-parametry.maksymalnaPredkoscTylemX);
					stan=leciTylem;
				}
				else
				{
					rozpedzanie(-parametry.wspolczynnikRozpedzaniaSieX,-parametry.maksymalnaPredkoscX);
					if(abs(predkosc.x)<parametry.predkoscZblizaniaSie) stan=zbliza;
					else stan=leci;
				}
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,parametry.predkoscWznoszeniaSieY);

			}
			else// zawracanie
			{
				hamowanieX();
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				if(abs(predkosc.x)>abs(predkosc.y))
				{
					if(abs(predkosc.x)>2) stan=hamujeX;
					else stan=unosi;
				}
				else
				{
					if(abs(predkosc.y)>parametry.vyPrzyUnoszeniu) stan=hamujeY;
					else stan=unosi;
				}
			}
		}
	}
	else if(klawiatura->czyWcisnietoGora()) //Wznoszenie się, lot w górę
	{
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			predkosc.y=parametry.silaWybicia;
			pozycja.y=parametryObiektow.poziomZiemi+5+parametry.wysokosc;
			zadaneY=parametryObiektow.poziomZiemi+5+parametry.wysokosc;
			stan=unosi;
		}
		else //wznoszenie
		{
			stabilizacjaY(1);
			hamowanieIUnoszenieY(parametry.wspolczynnikSilniejszegoUnoszenia,parametry.predkoscWznoszeniaSieY);

			if(abs(predkosc.y)<abs(parametry.maksymalnaPredkoscY) && abs(predkosc.x)>6) stan=wznosi;
			else
			{
				if(predkosc.y<-parametry.vyPrzyUnoszeniu) stan=hamujeY;
				else stan=unosi;
			}
		}
	}
	else if(klawiatura->czyWcisnietoDol()) //Nurkowanie, opadanie
	{
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			hamowanieNaZiemi();
			stan=stoi;
		}
		else  //spada
		{
			if(predkosc.y>-parametry.maksymalnaPredkoscY) predkosc.y-=abs(predkosc.x)*0.10; //nurkowanie
			predkosc.x*=0.8;

			if(zadaneY>pozycja.y)zadaneY=pozycja.y-1;
			if(abs(predkosc.x)>5) stan=nurkuje;
			else stan=spada;
		}
	}
	else if(klawiatura->czyWcisnietoPrawo()) //Lot,szybowanie, HamowanieX
	{
		if(predkosc.x>0 && myszka->zwrocX()<0) zwroconyWPrawo=true;
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			rozpedzanieNaZiemi(parametry.przyspieszenieChodu);
			stan=idzie;
		}
		else
		{
			stabilizacjaX(1);

			if(predkosc.x>=parametry.maksymalnaPredkoscX) //Szybowanie
			{
				szybowanie(parametry.maksymalnaPredkoscX,false,false);
				stan=szybuje;
			}
			else if(predkosc.x>=0) //Lot
			{
				if(!zwroconyWPrawo)
				{
					rozpedzanie(parametry.wspolczynnikRozpedzaniaSieX,parametry.maksymalnaPredkoscTylemX);
					stan=leciTylem;
				}
				else
				{
					rozpedzanie(parametry.wspolczynnikRozpedzaniaSieX,parametry.maksymalnaPredkoscX);
					if(abs(predkosc.x)<parametry.predkoscZblizaniaSie) stan=zbliza;
					else stan=leci;
				}
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
			}
			else	//zawracanie
			{
				hamowanieX();
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				if(abs(predkosc.x)>abs(predkosc.y))
				{
					if(abs(predkosc.x)>2) stan=hamujeX;
					else stan=unosi;
				}
				else
				{
					if(abs(predkosc.y)>parametry.vyPrzyUnoszeniu) stan=hamujeY;
					else stan=unosi;
				}
			}

			if(abs(predkosc.x)<abs(parametry.maksymalnaPredkoscX) && predkosc.y<-8)
			{
				stan=stabilizuje;
			}
		}
	}
	else if(klawiatura->czyWcisnietoLewo()  && pozycja.x>500)
	{
		if(predkosc.x<0 && myszka->zwrocX()>0) zwroconyWPrawo=false;
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			rozpedzanieNaZiemi(-parametry.przyspieszenieChodu);
			stan=idzie;
		}
		else
		{
			stabilizacjaX(-1); //Stabilizacja

			if(predkosc.x<=-parametry.maksymalnaPredkoscX)  //szybowanie
			{
				szybowanie(-parametry.maksymalnaPredkoscX,false,false);
				stan=szybuje;
			}
			else if(predkosc.x<=0)  //lot
			{
				if(zwroconyWPrawo)
				{
					rozpedzanie(-parametry.wspolczynnikRozpedzaniaSieX,-parametry.maksymalnaPredkoscTylemX);
					stan=leciTylem;
				}
				else
				{
					rozpedzanie(-parametry.wspolczynnikRozpedzaniaSieX,-parametry.maksymalnaPredkoscX);
					if(abs(predkosc.x)<parametry.predkoscZblizaniaSie) stan=zbliza;
					else stan=leci;
				}
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
			}
			else //zawracanie
			{
				hamowanieX();
				hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
				if(abs(predkosc.x)>abs(predkosc.y))
				{
					if(abs(predkosc.x)>2) stan=hamujeX;
					else stan=unosi;
				}
				else
				{
					if(abs(predkosc.y)>parametry.vyPrzyUnoszeniu) stan=hamujeY;
					else stan=unosi;
				}
			}

			if(abs(predkosc.x)<abs(parametry.maksymalnaPredkoscX) && predkosc.y<-8)	stan=stabilizuje;
		}
	}
	else //if(klawiatura.Nic nie wcisnieto)
	{
		if(pozycja.y==parametryObiektow.poziomZiemi+parametry.wysokosc)
		{
			hamowanieNaZiemi();
			stan=stoi;
		}
		else //Hamowanie
		{
			hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
			hamowanieX();
			if(abs(predkosc.x)>abs(predkosc.y))
			{
				if(abs(predkosc.x)>=10) stan=hamujeX;
				else stan=unosi;
			}
			else
			{
				if(abs(predkosc.y)>parametry.vyPrzyUnoszeniu) stan=hamujeY;
				else stan=unosi;
			}
		}
	}
}

void Smok::wyznaczGlowe(Klawiatura* klawiatura, Myszka *myszka)
{
	obrotGlowy=atan2(-(myszka->zwrocY()),(myszka->zwrocX()))+3.14;

	//Limity kata glowy
	if(minKatGlowy>maksKatGlowy)
	{
		if(obrotGlowy<minKatGlowy && obrotGlowy>maksKatGlowy)
		{
			if(abs(obrotGlowy-minKatGlowy)<abs(obrotGlowy-maksKatGlowy)) obrotGlowy=minKatGlowy;
			else obrotGlowy=maksKatGlowy;
		}
	}
	else
	{
		if(obrotGlowy<minKatGlowy || obrotGlowy>maksKatGlowy)
		{
			if(abs(obrotGlowy-minKatGlowy)<abs(obrotGlowy-maksKatGlowy)) obrotGlowy=minKatGlowy;
			else obrotGlowy=maksKatGlowy;
		}
	}

	//Obsluga myszki
	if(myszka->zwrocLPM())
	{
		zieje=true;
		przerwaOgnia=parametry.przerwaMiedzyMiotaniem;
		if(iloscOgnia>0) iloscOgnia-=parametry.zuzycieOgnia;
		for(int i=0; i<iloscOgnia;i++)
		{
			double wspolczynnikSily=pow((iloscOgnia)/parametry.maksymalnaPredkoscOgnia,0.1); //Wspolczynnik od ktorego zalezy aktualna predkosc ognia

			double predkoscOgnia=parametry.minimalnaPredkoscOgnia+(parametry.maksymalnaPredkoscOgnia-parametry.minimalnaPredkoscOgnia)*wspolczynnikSily;
			predkoscOgnia+=((double)(rand()%100)/100)*parametry.odchyleniePredkosciOgnia*wspolczynnikSily;

			double katOgnia=((double)(rand()%100)/100)*parametry.odchylenieKataOgnia - parametry.odchylenieKataOgnia/2 + obrotGlowy;
			double czasTrwania=parametry.sredniCzasTrwaniaOgnia+parametry.odchylenieCzasuTrwaniaOgnia*wspolczynnikSily;

			Punkt p;
			double rozrzut = (rand()%4000)/100;
			p.x=parametry.poprawkaOgnia.x+pozycja.x+pozycjaGlowy.x+(parametry.minimalnaOdleglosc+rozrzut)*cos(katOgnia)-predkosc.x;
			p.y=parametry.poprawkaOgnia.y+pozycja.y-pozycjaGlowy.y+(parametry.minimalnaOdleglosc+rozrzut)*sin(katOgnia);
			Punkt v;
			v.x=predkoscOgnia*cos(katOgnia)+predkosc.x;
			v.y=predkoscOgnia*sin(katOgnia);
			double kat = -obrotGlowy+3.14+1.57+6.28;
			if(kat>6.28) kat-=6.28;
			FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::plomien,p,v,czasTrwania,kat);
		}
	}
	else
	{
		zieje=false;
		if(iloscOgnia<parametry.maksymalnailoscOgnia && przerwaOgnia<=0) iloscOgnia+=parametry.regeneracjaOgnia;
		if(przerwaOgnia>0) przerwaOgnia--;
	}

}
//#####################################################################################################
//Podfunkcje Smoka Ruch
//#####################################################################################################
void Smok::hamowanieIUnoszenieY(double unoszenie, double wznoszenie)
{
	zadaneY+=wznoszenie;
	if(pozycja.y<zadaneY && predkosc.y<0) //HamowanieY i unoszenie
	{
		if(predkosc.y<-parametry.wspolczynnikHamowaniaY)
		{
			predkosc.y+=parametry.wspolczynnikHamowaniaY;
			if(predkosc.y<-parametry.vyPrzyUnoszeniu)zadaneY=pozycja.y-1;
		}
		else
		{
			predkosc.y=unoszenie;
		}
	}
}

void Smok::hamowanieX()
{
	if(predkosc.x>0)
	{
		if(predkosc.x>parametry.wspolczynnikHamowaniaX) predkosc.x-=parametry.wspolczynnikHamowaniaX;
		else predkosc.x=0;
	}
	else
	{
		if(predkosc.x<-parametry.wspolczynnikHamowaniaX) predkosc.x+=parametry.wspolczynnikHamowaniaX;
		else predkosc.x=0;
	}
}

void Smok::szybowanie(double predkoscLotu,bool wznoszenie,bool spadekSwobodny)
{
	if(!spadekSwobodny)
	{
		predkosc.x=predkoscLotu;
		if(predkosc.y<-parametry.predkoscOpadaniaPrzySzybowaniu) predkosc.y=-parametry.predkoscOpadaniaPrzySzybowaniu;
		if(wznoszenie)
		{
			zadaneY+=parametry.predkoscWznoszeniaSieY/2;
			hamowanieIUnoszenieY(parametry.wspolczynnikSlabszegoUnoszenia,0);
		}
		else
		{
			if(zadaneY>pozycja.y)zadaneY=pozycja.y-1;
		}
	}
	else
	{
		if(zadaneY>pozycja.y)zadaneY=pozycja.y-1;
	}
}

void Smok::rozpedzanie(double przyspieszenie,double maksPredkosc)
{
	if(abs(predkosc.x)<abs(maksPredkosc)) predkosc.x+=przyspieszenie;
	else predkosc.x=maksPredkosc;
}

void Smok::stabilizacjaX(double kierunek)
{
	if(abs(predkosc.x)<abs(parametry.maksymalnaPredkoscX) && abs(predkosc.y)>parametry.vyPrzyUnoszeniu)
	{
		if(kierunek==1)	predkosc.x+=abs(predkosc.y)*0.30;
		else predkosc.x-=abs(predkosc.y)*0.30;
		predkosc.y*=0.8;
		zadaneY=pozycja.y-20;
	}
}

void Smok::stabilizacjaY(double kierunek)
{
	if(abs(predkosc.y)<abs(parametry.maksymalnaPredkoscY) && abs(predkosc.x)>6)
	{
		if(stan!=wznosi) predkosc.y=-parametry.predkoscOpadaniaPrzySzybowaniu;
		if(kierunek==1) predkosc.y+=abs(predkosc.x)*0.2;
		else predkosc.y-=abs(predkosc.x)*0.2;
	}
	predkosc.x*=0.8;
}

void Smok::rozpedzanieNaZiemi(double przyspieszenie)
{
	if(abs(predkosc.x)<parametry.maksPredkoscChodu)
	{
		predkosc.x+=przyspieszenie;
	}
	else if (abs(predkosc.x)>parametry.maksPredkoscChodu+parametry.przyspieszenieChodu)
	{
		if(predkosc.x>0) predkosc.x-=parametry.przyspieszenieChodu;
		else predkosc.x+=parametry.przyspieszenieChodu;
	}
	else
	{
		if(przyspieszenie>0) predkosc.x=parametry.maksPredkoscChodu;
		else predkosc.x=-parametry.maksPredkoscChodu;
	}
}

void Smok::hamowanieNaZiemi()
{
	if(abs(predkosc.x)<parametry.hamowanieChodu) predkosc.x=0;
	else
	{
		if(predkosc.x>0) predkosc.x-=parametry.hamowanieChodu;
		else predkosc.x+=parametry.hamowanieChodu;
	}
}
//#####################################################################################################
//Podfunkcje Smoka Kolizje
//#####################################################################################################
void Smok::wyznaczPrzestrzenKolizji()
{
	int prawo;
	if (!zwroconyWPrawo) prawo = 1;
	else prawo = -1;

	std::vector<OkragKolizji> f;
	f.clear();
	if(klatkaAnimacji.x==0)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-35*prawo,10),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-25*prawo,-30),25));
	}
	else if(klatkaAnimacji.x==1)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-30*prawo,-5),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-10*prawo,-40),25));
	}
	else if(klatkaAnimacji.x==2)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-35*prawo,-15),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(00*prawo,-25),25));
	}
	else if(klatkaAnimacji.x==3)
	{
		if(klatkaAnimacji.y==0)
		{
			f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-40*prawo,-05),30));
			f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(+5*prawo,+0),25));
		}
		else if(klatkaAnimacji.y==1)
		{
			f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-50*prawo,-15),30));
			f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-15*prawo,-30),25));
		}
	}
	else if(klatkaAnimacji.x==4)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-35*prawo,10),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-35*prawo,-30),25));
	}
	else if(klatkaAnimacji.x==5)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-45*prawo,-10),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-8*prawo,-22),25));
	}
	else if(klatkaAnimacji.x==6 && klatkaAnimacji.y==1)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-35*prawo,10),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-35*prawo,-30),25));
	}
	else if(klatkaAnimacji.x==6 && klatkaAnimacji.y==0)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-10*prawo,10),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-00*prawo,-30),25));
	}
	else if(klatkaAnimacji.x==7)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-65*prawo,-20),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-30*prawo,05),25));
	}
	else if(klatkaAnimacji.x==8)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-50*prawo,20),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-20*prawo,-15),25));
	}
	else if(klatkaAnimacji.x==9)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-40*prawo,35),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-10*prawo,10),25));
	}
	else if(klatkaAnimacji.x==10)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-55*prawo,-25),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-30*prawo,10),25));
	}
	else if(klatkaAnimacji.x==11)
	{
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-30*prawo,-70),30));
		f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(-30*prawo,-25),25));
	}

	double poprawka=6.28/32;
	if(prawo==-1) poprawka = -6.28/32;

	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(pozycjaGlowy.x-5,-pozycjaGlowy.y-5),25));
	f.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(pozycjaGlowy.x-5+cos(obrotGlowy+poprawka)*35,-pozycjaGlowy.y-5+sin(obrotGlowy+poprawka)*35),15));
	ustawPrzestrzenKolizji(f);

}
//#####################################################################################################
//Podfunkcje Smoka Grafika
//#####################################################################################################
void Smok::wyznaczKlatkeAnimacji()
{
	//int prawo = -1;
	//if(zwroconyWPrawo) prawo=1;

	switch(stan)
	{
	case unosi:
		minKatGlowy=5.7;
		maksKatGlowy=2;
		pozycjaGlowy.x=30;
		pozycjaGlowy.y=-80;
		if(przyspieszenie.y>0)
		{
				 if(predkosc.y>5.5)   klatkaAnimacji.y=3;
			else if (predkosc.y>2.5)  klatkaAnimacji.y=4;
			else if (predkosc.y>-0)  klatkaAnimacji.y=5;
			else if (predkosc.y>-6) klatkaAnimacji.y=0;
			else klatkaAnimacji.y=0;
		}
		else
		{
			 if(predkosc.y>-3)  klatkaAnimacji.y=2;
			 else klatkaAnimacji.y=1;
		}
		klatkaAnimacji.x=0;
		break;
	case zbliza:
		minKatGlowy=5.5;
		maksKatGlowy=2;
		pozycjaGlowy.x=60;
		pozycjaGlowy.y=-67;
		if(przyspieszenie.y>0)
		{
				 if(predkosc.y>5.5)   klatkaAnimacji.y=3;
			else if (predkosc.y>2.5)  klatkaAnimacji.y=4;
			else if (predkosc.y>-0)  klatkaAnimacji.y=5;
			else if (predkosc.y>-6) klatkaAnimacji.y=0;
			else klatkaAnimacji.y=0;
		}
		else
		{
			 if(predkosc.y>-3)  klatkaAnimacji.y=2;
			 else klatkaAnimacji.y=1;
		}
		klatkaAnimacji.x=1;
		break;
	case leci:
		minKatGlowy=5.0;
		maksKatGlowy=0.8;
		pozycjaGlowy.x=95;
		pozycjaGlowy.y=-30;
		if(przyspieszenie.y>0)
		{
				 if(predkosc.y>5.5)   klatkaAnimacji.y=3;
			else if (predkosc.y>2.5)  klatkaAnimacji.y=4;
			else if (predkosc.y>-0)  klatkaAnimacji.y=5;
			else if (predkosc.y>-6) klatkaAnimacji.y=0;
			else klatkaAnimacji.y=0;
		}
		else
		{
			 if(predkosc.y>-3)  klatkaAnimacji.y=2;
			 else klatkaAnimacji.y=1;
		}
		klatkaAnimacji.x=2;
		break;
	case szybuje:
		minKatGlowy=3.8;
		maksKatGlowy=0.4;
		pozycjaGlowy.x=110;
		pozycjaGlowy.y=-5;
		klatkaAnimacji.y=0;
		klatkaAnimacji.x=3;
		break;
	case leciTylem:
		minKatGlowy=5.7;
		maksKatGlowy=2;
		pozycjaGlowy.x=27;
		pozycjaGlowy.y=-85;
		if(przyspieszenie.y>0)
		{
				 if(predkosc.y>5.5)   klatkaAnimacji.y=3;
			else if (predkosc.y>2.5)  klatkaAnimacji.y=4;
			else if (predkosc.y>-0)  klatkaAnimacji.y=5;
			else if (predkosc.y>-6) klatkaAnimacji.y=0;
			else klatkaAnimacji.y=0;
		}
		else
		{
			 if(predkosc.y>-3)  klatkaAnimacji.y=2;
			 else klatkaAnimacji.y=1;
		}
		klatkaAnimacji.x=4;
		break;
	case hamujeX:
		if(abs(predkosc.x)<parametry.maksymalnaPredkoscX-5)
		{
			minKatGlowy=5.7;
			maksKatGlowy=2;
			pozycjaGlowy.x=23;
			pozycjaGlowy.y=-100;
			klatkaAnimacji.x=6;
			klatkaAnimacji.y=1;
		}
		else
		{
			minKatGlowy=4.6;
			maksKatGlowy=0.8;
			pozycjaGlowy.x=95;
			pozycjaGlowy.y=-30;
			klatkaAnimacji.y=2;
			klatkaAnimacji.x=2;
		}
		break;
	case hamujeY:
		if(predkosc.y<-12 || stan!=hamujeY) //Zawsze jest true ale warto się zabezpieczyć
		{
			minKatGlowy=3.8;
			maksKatGlowy=6.1;
			pozycjaGlowy.x=114;
			pozycjaGlowy.y=35;
			klatkaAnimacji.y=0;
			klatkaAnimacji.x=10;
		}
		else
		{
			minKatGlowy=5.7;
			maksKatGlowy=2;
			pozycjaGlowy.x=30;
			pozycjaGlowy.y=-80;
			klatkaAnimacji.y=3;
			klatkaAnimacji.x=0;

		}
		break;
	case szybujacWznosi:
		minKatGlowy=4.6;
		maksKatGlowy=0.8;
		pozycjaGlowy.x=95;
		pozycjaGlowy.y=-30;
		if(predkosc.y<0)
		{
			if(pozycja.y-zadaneY>10)
			{
				minKatGlowy=3.8;
				maksKatGlowy=0.4;
				pozycjaGlowy.x=110;
				pozycjaGlowy.y=-5;
				klatkaAnimacji.y=0;
				klatkaAnimacji.x=3;
			}
			else
			{
				klatkaAnimacji.y=5;
				klatkaAnimacji.x=2;
			}
		}
		else
		{
			klatkaAnimacji.x=2;
			if(predkosc.y>7.5)   klatkaAnimacji.y=0;
			else if (predkosc.y>6.7)  klatkaAnimacji.y=1;
			else if (predkosc.y>6)  klatkaAnimacji.y=2;
			else if (predkosc.y>2.5) klatkaAnimacji.y=3;
			else klatkaAnimacji.y=4;
		}
		break;
	case szybujacSpada:
		if(abs(predkosc.y)<parametry.vyPrzyUnoszeniu)
		{
			minKatGlowy=4.6;
			maksKatGlowy=0.8;
			pozycjaGlowy.x=95;
			pozycjaGlowy.y=-30;
			klatkaAnimacji.x=2;
			klatkaAnimacji.y=1;
		}
		else
		{
			minKatGlowy=3.8;
			maksKatGlowy=6.1;
			pozycjaGlowy.x=114;
			pozycjaGlowy.y=35;
			klatkaAnimacji.y=0;
			klatkaAnimacji.x=10;
		}
		break;
	case wznosi:
		minKatGlowy=5.5;
		maksKatGlowy=1.5;
		pozycjaGlowy.x=70;
		pozycjaGlowy.y=-103;
		klatkaAnimacji.y=0;
		klatkaAnimacji.x=9;
		break;
	case nurkuje:
		minKatGlowy=3.1;
		maksKatGlowy=6.0;
		pozycjaGlowy.x=118;
		pozycjaGlowy.y=64;
		klatkaAnimacji.y=0;
		klatkaAnimacji.x=7;
		break;
	case stabilizuje:
		minKatGlowy=3.8;
		maksKatGlowy=6.1;
		pozycjaGlowy.x=114;
		pozycjaGlowy.y=35;
		klatkaAnimacji.y=0;
		klatkaAnimacji.x=10;
		break;
	case spada:
		if(predkosc.y>-8)
		{
			minKatGlowy=5.7;
			maksKatGlowy=2;
			pozycjaGlowy.x=30;
			pozycjaGlowy.y=-80;
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=0;
		}
		else if(predkosc.y>-10 || stan!=spada)
		{
			minKatGlowy=5.0;
			maksKatGlowy=0.8;
			pozycjaGlowy.x=98;
			pozycjaGlowy.y=-70;
			klatkaAnimacji.y=0;
			klatkaAnimacji.x=8;
		}
		else if(predkosc.y>-12)
		{
			minKatGlowy=3.1;
			maksKatGlowy=6.0;
			pozycjaGlowy.x=118;
			pozycjaGlowy.y=64;
			klatkaAnimacji.y=0;
			klatkaAnimacji.x=7;
		}
		else
		{
			minKatGlowy=2.6;
			maksKatGlowy=5.0;
			pozycjaGlowy.x=32;
			pozycjaGlowy.y=128;
			klatkaAnimacji.y=0;
			klatkaAnimacji.x=11;
		}
		break;
	case stoi:
		if(abs(predkosc.x)>4)
		{
			minKatGlowy=5.3;
			maksKatGlowy=0.2;
			pozycjaGlowy.x=105;
			pozycjaGlowy.y=-26;
			klatkaAnimacji.x=5;
			if(zwroconyWPrawo) klatkaAnimacji.y=(((int)pozycja.x)%180)/30;
			else klatkaAnimacji.y=5-(((int)pozycja.x)%180)/30;
		}
		else
		{
			minKatGlowy=5.3;
			maksKatGlowy=0.8;
			pozycjaGlowy.x=95;
			pozycjaGlowy.y=-40;
			klatkaAnimacji.x=3;
			klatkaAnimacji.y=1;
		}
		break;
	case idzie:
		minKatGlowy=5.3;
		maksKatGlowy=0.2;
		pozycjaGlowy.x=105;
		pozycjaGlowy.y=-26;
		klatkaAnimacji.x=5;
		if(zwroconyWPrawo) klatkaAnimacji.y=(((int)pozycja.x)%180)/30;
		else klatkaAnimacji.y=5-(((int)pozycja.x)%180)/30;
		break;
	default:
		minKatGlowy=5.3;
		maksKatGlowy=2;
		pozycjaGlowy.x=30;
		pozycjaGlowy.y=-80;
		klatkaAnimacji.x=0;
		klatkaAnimacji.y=0;
		break;
	}

	if(!zwroconyWPrawo)
	{
		pozycjaGlowy.x=-pozycjaGlowy.x;
		double tmp=minKatGlowy;
		if(maksKatGlowy<3.14) minKatGlowy=3.14-maksKatGlowy;
		else minKatGlowy=9.42-maksKatGlowy;

		if(tmp<3.14) maksKatGlowy=3.14-tmp;
		else maksKatGlowy=9.42-tmp;

	}

	klatkaAnimacjiGlowy.x=1;
	double poprawka=0;
	if(zwroconyWPrawo) poprawka=6.28/16;
	else poprawka=6.28/16;
	klatkaAnimacjiGlowy.x=(-0.5+(double)(obrotGlowy+poprawka)/(6.28/16));
	klatkaAnimacjiGlowy.x= (int)klatkaAnimacjiGlowy.x;
	if(klatkaAnimacjiGlowy.x>15) klatkaAnimacjiGlowy.x=0;

	if(zieje) klatkaAnimacjiGlowy.y=1;
	else klatkaAnimacjiGlowy.y=0;
	//std::cout << " X:" << predkosc.x << "   Y:" << predkosc.y << "\n";
}
