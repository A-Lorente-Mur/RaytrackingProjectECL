#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Scene.h"
#include "Bbox.h"
#include "Bvh.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <limits>
#include <vector>
#include <algorithm>
#include <random>


//Constructeurs
Bbox::Bbox():
bmin(Vector(0,0,0)), bmax(Vector(1,1,1))
{}

Bbox::Bbox(const Vector & bmin,const Vector & bmax):
bmin(bmin), bmax(bmax)
{}

void Bbox::setbmin(const Vector & V)
{
	this->bmin = V;
}

void Bbox::setbmax(const Vector & V)
{
	this->bmax = V;
}

Vector Bbox::getbmin() const
{
	return bmin;
}

Vector Bbox::getbmax() const
{
	return bmax;
}

Intersection Bbox::intersect(const Ray & r)
{
	Vector O=r.centre();
	Vector u=r.direction();
	
	double t1x=(bmin.getX()-O.getX())/u.getX();
	double t2x=(bmax.getX()-O.getX())/u.getX();
	double txmin=min(t1x,t2x);
	double txmax=max(t1x,t2x);
	
	double t1y=(bmin.getY()-O.getY())/u.getY();
	double t2y=(bmax.getY()-O.getY())/u.getY();
	double tymin=min(t1y,t2y);
	double tymax=max(t1y,t2y);
	
	double t1z=(bmin.getZ()-O.getZ())/u.getZ();
	double t2z=(bmax.getZ()-O.getZ())/u.getZ();
	double tzmin=min(t1z,t2z);
	double tzmax=max(t1z,t2z);
	
	double tloin=min(txmax,min(tymax,tzmax));
	double tproche=max(txmin,max(tymin,tzmin));
	
	
	if(tloin<0){
		Intersection Inter(false,Vector(0,0,0),Vector(0,0,0),0);
		Inter.feuil.clear();
		return Inter;
	}
	if(tloin-tproche>0){
		Intersection Inter(true,Vector(0,0,0),Vector(0,0,0),0);
		Inter.feuil.clear();
		return Inter;	
	}
	Intersection Inter(false,Vector(0,0,0),Vector(0,0,0),0);
	Inter.feuil.clear();
	return Inter;
}







