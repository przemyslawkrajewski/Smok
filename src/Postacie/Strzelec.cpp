/*
 * Strzelec.cpp
 *
 *  Created on: 11-07-2015
 *      Author: przemo
 */

#include "Strzelec.h"

Strzelec::Strzelec(): Postac()
{
	pozycja.x=2000;
	pozycja.y=parametryObiektow.poziomZiemi+50;
	stan = stoi;
	stanBiegu=0;
	katCelowaniaWprost=0;
	katCelowaniaZGory=0;
	katCelowania=0;
	stanNaciagania=-1;
	stanCelowania=0;

	zycie=100;
	obrazenia=5;
	x1=x2=-1;
	iteracjaCelowania=-1;
}

void Strzelec::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		if (klawiatura->czyWcisnietoPrawo() && !przeszkodaPoPrawej)
		{
			zwroconyWPrawo=true;
			if(!myszka->zwrocLPM())
			{
				stan = biegnie;

				if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
				else stanBiegu += parametry.predkoscAnimacjiBiegu1;

				if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
				pozycja.x+=parametry.predkoscBiegu;
				if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
				stanCelowania=0;
			}
		}
		else if (klawiatura->czyWcisnietoLewo() && !przeszkodaPoLewej)
		{
			zwroconyWPrawo=false;
			if(!myszka->zwrocLPM())
			{
				stan = biegnie;

				if((stanBiegu>2 && stanBiegu<3) || (stanBiegu>6 && stanBiegu<7)) stanBiegu += parametry.predkoscAnimacjiBiegu2;
				else stanBiegu += parametry.predkoscAnimacjiBiegu1;

				if(stanBiegu>parametry.iloscKlatekAnimacjiBiegu) stanBiegu=0;
				pozycja.x-=parametry.predkoscBiegu;
				if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
				stanCelowania=0;
			}
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
					double kat=-katCelowania+((double)(rand()%100)/100)*parametry.celnosc - parametry.celnosc/2;
					if((-kat>4.71 && katCelowania<4.71) || (-kat<4.71 && katCelowania>4.71)) kat = -4.71;

					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=parametry.predkoscStrzaly*cos(kat);
					v.y=parametry.predkoscStrzaly*sin(kat);
					kat = katCelowania+1.57;//+3.14+6.28
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

		if(!myszka->zwrocLPM() && !klawiatura->czyWcisnietoLewo() && !klawiatura->czyWcisnietoPrawo())
		{
			stan = stoi;
			stanBiegu=0;
			stanCelowania=0;
			if(!parametry.spust || stanNaciagania>0) stanNaciagania=parametry.maxNaciagniecie;
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
	int maxOdleglosc=5200;
	int minOdleglosc=5200;
	int odleglosc=00;

	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	Klawiatura k;
	Myszka m;

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}

	m.ustawX(pozycja.x-pozycjaCelu.x);
	m.ustawY(pozycja.y-pozycjaCelu.y);

	bool mozliwyStrzal = czyMozliwyStrzal(Punkt((m.zwrocX()),(m.zwrocY())));

	if(abs(pozycjaCelu.x-pozycja.x)>maxOdleglosc) mozliwyStrzal=false;
	if( (stanNaciagania>0 && parametry.spust) || (mozliwyStrzal && (mozliwyStrzal)))
	{
		m.ustawLPM(true);
		if(mozliwyStrzal)
		{
			if(iteracjaCelowania==-1) wyznaczKatStrzalu(Punkt((m.zwrocX()),(m.zwrocY())));
			else poprawKatStrzalu(Punkt((m.zwrocX()),(m.zwrocY())),cel->zwrocPredkosc());
			ustalKatStrzalu();
		}
		//if(abs(pozycja.x-pozycjaCelu.x)<odleglosc) katCelowania=katCelowaniaWprost; //TODO: komunikacja tylko przez myszke i klawiature
		//else
		katCelowania=katCelowaniaWprost;
	}
	else if(pozycjaCelu.x>pozycja.x )
	{
		k.ustawWcisnietoPrawo(true);
	}
	else if(pozycjaCelu.x<pozycja.x)
	{
		k.ustawWcisnietoLewo(true);
	}

	if(m.zwrocLPM()==false || (m.zwrocLPM()==true && stanNaciagania==-1 && parametry.maxCelowania==stanCelowania))
	{
		iteracjaCelowania=-1;
	}
	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

/*
 * P1.x(t) = P1.x + V1.x*t
 * P1.y(t) = P1.y + V1.y*t-g*t^2
 * P2.x(t) = P2.x + V2.x*t
 * P2.y(t) = P2.x + V2.y*t
 *
 * dPx=P1.x-P2.x	dPy=P1.y-P2.y	cos(a)=x
 *
 * P1.x(tk)=P2.x(tk) => tk = ...
 * P1.y(tk)=P2.y(tk) => A*sin(a) + B*sin(a)cos(a) + C*cos(a) + D*cos(a)^2 = E
 * A=dPx*V2.x*V1	B=-dPx*V1^2		C=V1*(V2.y*dPx-2*dPy*V2.x)	D=dPy*V1^2	E=g*dPx^2-dPy*V2.x^2+v2.y*dPx*V2.x
 *
 * f(x)=a*x^4 + b*x^3 + c*x^2 + d*x + e
 * f'(x)=4a*x^3 + 3b*x^2 + 2c*x + d
 * a=-B^2-D^2	b=2CD-2AB	c=B^2-A^2-C^2-2DE	d=2AB+2EC	e=A^2-E^2
 *
 *
 * dla V2=0
 *
 * B*sin(a)*cos(a)+D*cos(a)^2 = E1
 * B=-dPx*V1^2	D=dPy*V1^2	E=g*dPx^2
 *
 * x = cos(a)^2
 */

bool Strzelec::czyMozliwyStrzal(Punkt dP)
{
	if(parametry.spust)
	{
		katCelowaniaWprost = atan2((-dP.x),(dP.y))-1.57;
		if(katCelowaniaWprost<0) katCelowaniaWprost+=M_PI*2;
		katCelowaniaZGory = katCelowaniaWprost;
		return true;
	}

	//do wzoru
	double B = -dP.x*parametry.predkoscStrzaly*parametry.predkoscStrzaly;
	double D =  dP.y*parametry.predkoscStrzaly*parametry.predkoscStrzaly;
	double E1 = dP.x*dP.x*Strzala::parametry.wspolczynnikGrawitacji/2;

	//do rownania kwadratowego
	double a = -B*B-D*D;
	double b =  B*B+2*D*E1;
	double c = -E1*E1;

	//rownanie kwadratowe
	double delta = b*b-4*a*c;

	if(delta<0)
	{
		return false;
	}

	if((-b -sqrt(delta))/(2*a)<0)
	{
		return false;
	}

	return true;
}

void Strzelec::wyznaczKatStrzalu(Punkt dP)
{
	if(parametry.spust)
	{
		katCelowaniaWprost = atan2((-dP.x),(dP.y))-1.57;
		if(katCelowaniaWprost<0) katCelowaniaWprost+=M_PI*2;
		katCelowaniaZGory = katCelowaniaWprost;
		return;
	}

	//do wzoru
	double B = -dP.x*parametry.predkoscStrzaly*parametry.predkoscStrzaly;
	double D =  dP.y*parametry.predkoscStrzaly*parametry.predkoscStrzaly;
	double E1 = dP.x*dP.x*Strzala::parametry.wspolczynnikGrawitacji/2;

	//do rownania kwadratowego
	double a = -B*B-D*D;
	double b =  B*B+2*D*E1;
	double c = -E1*E1;

	//rownanie kwadratowe
	double delta = b*b-4*a*c;

	if(delta<0)
	{
		return;
	}
	x1 = (-b -sqrt(delta))/(2*a);
	x2 = (-b +sqrt(delta))/(2*a);

	if(x1<0)
	{
		return ;
	}
	if(x1<x2)
	{
		double tmp = x1;x1=x2;x2=tmp;
	}

	if(zwroconyWPrawo)
	{
		x1 = -sqrt(x1);
		x2 = -sqrt(x2);
	}
	else
	{
		x1 = sqrt(x1);
		x2 = sqrt(x2);
	}
	iteracjaCelowania=0;
}

void Strzelec::poprawKatStrzalu(Punkt dP, Punkt v2)
{
	if(iteracjaCelowania==-1) return;

	if(fabs(v2.x)>parametry.predkoscStrzaly)
	{
		iteracjaCelowania=-1;
		return;
	}
	if(v2.y>-7 && v2.y<8) v2.y=0;
	v2.x=-v2.x;
	v2.y=-v2.y;

	//do wzoru
	double A = dP.x*v2.x*parametry.predkoscStrzaly;
	double B = -dP.x*parametry.predkoscStrzaly*parametry.predkoscStrzaly;
	double C = parametry.predkoscStrzaly*(v2.y*dP.x-2*dP.y*v2.x);
	double D = dP.y*parametry.predkoscStrzaly*parametry.predkoscStrzaly;
	double E = (dP.x*dP.x*Strzala::parametry.wspolczynnikGrawitacji/2)-(dP.y*v2.x*v2.x)+(v2.y*dP.x*v2.x);

	//wielomian ultra giga nigga
	double a = -B*B - D*D;
	double b = -2*C*D - 2*A*B;
	double c =  B*B - A*A - C*C + 2*D*E;
	double d =  2*A*B + 2*E*C;
	double e =  A*A - E*E;

	double f;
	double df;
	double y0;

	f = a*x1*x1*x1*x1 + b*x1*x1*x1 + c*x1*x1 + d*x1 + e;
	df = 4*a*x1*x1*x1 + 3*b*x1*x1 + 2*c*x1 + d;
	y0 = f-x1*df;
	if(df!=0) x1 = -y0/df;

	f = a*x2*x2*x2*x2 + b*x2*x2*x2 + c*x2*x2 + d*x2 + e;
	df = 4*a*x2*x2*x2 + 3*b*x2*x2 + 2*c*x2 + d;
	y0 = f-x2*df;
	if(df!=0) x2 = -y0/df;

	iteracjaCelowania++;
}

void Strzelec::ustalKatStrzalu()
{
	if(x1!=-1 && x2!=-1)
	{
		katCelowaniaWprost = acos(x1);
		katCelowaniaZGory = acos(x2);

		katCelowaniaWprost+=3.14;
		katCelowaniaZGory+=3.14;
	}
}

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
	case umiera:
		if(klatkaAnimacji.x!=0 || klatkaAnimacji.y<1)
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
