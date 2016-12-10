/*
 * Punkt.h
 *
 *  Created on: 04-03-2014
 *      Author: przemo
 */

#ifndef PUNKT_H_
#define PUNKT_H_

class Punkt
{
public:
	double x;
	double y;

	Punkt()
	{
		x=0;
		y=0;
	}
	Punkt(double nX,double nY)
	{
		x=nX;
		y=nY;
	}
	Punkt(const Punkt& p)
	{
		x=p.x;
		y=p.y;
	}
	bool operator==(Punkt p)
	{
		return (x==p.x && y==p.y);
	}
	Punkt operator+(Punkt p)
	{
		return Punkt(x+p.x,y+p.y);
	}
	Punkt operator-(Punkt p)
	{
		return Punkt(x-p.x,y-p.y);
	}
	Punkt operator/(double d)
	{
		return Punkt(x/d,y/d);
	}
	Punkt operator*(double d)
	{
		return Punkt(x*d,y*d);
	}
};

typedef Punkt Wektor;
typedef Punkt Wymiary;

#endif /* PUNKT_H_ */
