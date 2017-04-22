/*
 * PomocnikCelowania.h
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#ifndef SRC_POSTACIE_POMOCNIKCELOWANIA_H_
#define SRC_POSTACIE_POMOCNIKCELOWANIA_H_

#include "../Obiekty/Punkt.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <utility>

class PomocnikCelowania
{
private:
	double v1;
	double g;

	double x1,x2;
	int iteracjaCelowania;

	double a1,a2;
public:
	enum Kat {katWprost, katZGory};

	PomocnikCelowania()
	{
		a1=a2=0;
		x1=x2=-1;
		iteracjaCelowania=-1;
		v1=g=0;
	}

	void ustawParametry(double nv1, double ng)
	{
		v1=nv1;
		g=ng;
	}

	double zwrocKat(Kat k)
	{
		if(k==katWprost) return a1;
		else return a2;
	}

	//dPx=P1.x-P2.x	dPy=P1.y-P2.y	cos(a)=x

	/*	g!=0
	 *
	 * P1.x(t) = P1.x + V1.x*t
	 * P1.y(t) = P1.y + V1.y*t-g*t^2
	 * P2.x(t) = P2.x + V2.x*t
	 * P2.y(t) = P2.x + V2.y*t
	 *
	 * dla V2!=0
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

	/* g==0
	 *
	 * P1.x(t) = P1.x + V1.x*t
	 * P1.y(t) = P1.y + V1.y*t
	 * P2.x(t) = P2.x + V2.x*t
	 * P2.y(t) = P2.x + V2.y*t
	 *
	 * P1.x(tk)=P2.x(tk) => tk = ...
	 * P1.y(tk)=P2.y(tk) => A*cos(a) - B*sin(a) + C = 0
	 * A=dPy*V1		B=dPx*V1	C=dPx*V2y-dPy*V2x
	 *
	 * f(x) = a*x^2 + b*x + c
	 * a=A^2+B^2	b=2*A*C		c=C^2-B^2
	 */
	bool czyMozliwyStrzal(Punkt dP)
	{
		if(g==0)
		{
			return dP.y<0;
		}

		//do wzoru
		double B = -dP.x*v1*v1;
		double D =  dP.y*v1*v1;
		double E1 = dP.x*dP.x*g/2;

		//do rownania kwadratowego
		double a = -B*B-D*D;
		double b =  B*B+2*D*E1;
		double c = -E1*E1;

		//rownanie kwadratowe
		double delta = b*b-4*a*c;

		if(delta>=0 && (-b -sqrt(delta))/(2*a)>=0)
		{
			return true;
		}
		else
			return false;
	}

	void wyznaczKatStrzalu(Punkt dP)
	{
		if(g==0)
		{
			a1 = atan2(dP.x,dP.y)+M_PI/2;
			if(a1<0) a1+=M_PI*2;
			//a1 = M_PI*2-a1;
			a2 = a1;
			return;
		}
		else
		{
			//do wzoru
			double B = -dP.x*v1*v1;
			double D =  dP.y*v1*v1;
			double E1 = dP.x*dP.x*g/2;

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
				return;
			}
			if(x1<x2)
			{
				double tmp = x1;x1=x2;x2=tmp;
			}

			if(dP.x<0)
			{
				x1 = -sqrt(x1);
				x2 = -sqrt(x2);
			}
			else
			{
				x1 = sqrt(x1);
				x2 = sqrt(x2);
			}

			a1 = acos(x1);
			a2 = acos(x2);

			a1+= 3.14;
			a2+= 3.14;

			if((dP.x<0 && a1<4.71) || (dP.x>0 && a1>4.71))
			{
				a1=3*M_PI-a1;
				a2=3*M_PI-a2;
			}

			iteracjaCelowania=0;
		}
	}

	void wyznaczKatStrzalu(Punkt dP, Punkt v2)
	{
		if(v2.y>-7 && v2.y<9 && fabs(v2.x)<18) v2.y=0;
		v2.x=-v2.x;
		v2.y=-v2.y;

		if(g==0)
		{
			if(v2.x==0 && v2.y==0)
			{
				wyznaczKatStrzalu(dP);
				return;
			}

			if(fabs(v2.x)>v1)
			{
				return;
			}

			//do wzoru
			double A = dP.y*v1;
			double B = dP.x*v1;
			double C = dP.x*v2.y-dP.y*v2.x;

			//do rowniania
			double a = A*A + B*B;
			double b = 2*A*C;
			double c = C*C - B*B;

			//rownanie kwadratowe
			double delta = b*b-4*a*c;

			if(delta<0)
			{
				return;
			}
			x1 = (-b -sqrt(delta))/(2*a);
			x2 = (-b +sqrt(delta))/(2*a);

			a1 = acos(x1);
			a2 = acos(x2);

			double f1 = fabs(A*cos(a1) - B*sin(a1) + C);
			double f2 = fabs(A*cos(a2) - B*sin(a2) + C);
			if( (f1 < f2))
			{
				a1=a2;
			}

			a1+=M_PI;
			a2+=M_PI;
		}
		else
		{
			if(iteracjaCelowania==-1 || (v2.x==0 && v2.y==0))
			{
				wyznaczKatStrzalu(dP);
				return;
			}

			if(fabs(v2.x)>v1)
			{
				iteracjaCelowania=-1;
				return;
			}

			//do wzoru
			double A = dP.x*v2.x*v1;
			double B = -dP.x*v1*v1;
			double C = v1*(v2.y*dP.x-2*dP.y*v2.x);
			double D = dP.y*v1*v1;
			double E = (dP.x*dP.x*g/2)-(dP.y*v2.x*v2.x)+(v2.y*dP.x*v2.x);

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
			a1 = acos(x1);
			a2 = acos(x2);

			if(dP.y<0 && ((dP.x<=0 && v2.x>0) || (dP.x>0 && v2.x<0)))
			{
				double b1 = 3*M_PI-a1;
				double f1 = fabs(A*sin(a1) + B*sin(a1)*cos(a1) + C*cos(a1) + D*cos(a1)*cos(a1) - E);
				double f2 = fabs(A*sin(b1) + B*sin(b1)*cos(b1) + C*cos(b1) + D*cos(b1)*cos(b1) - E);
				std::cout << f1 << " " << f2 << "\n";
				if( (f1 < f2))
				{
					a1=3*M_PI-a1;
					a2=3*M_PI-a2;
				}
			}
			else
			{
				if((dP.x<0 && a1<M_PI/2) || (dP.x>0 && a1>M_PI/2))
				{
					a1=3*M_PI-a1;
					a2=3*M_PI-a2;
				}
			}

			a1+= 3.14;
			a2+= 3.14;
		}
	}

	void resetCelowania()
	{
		x1=x2=iteracjaCelowania=-1;
	}
};

#endif /* SRC_POSTACIE_POMOCNIKCELOWANIA_H_ */
