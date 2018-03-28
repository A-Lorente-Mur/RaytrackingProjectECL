#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Bvh.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
 


//Constructeur
Intersection::Intersection(bool inter,Vector I, Vector Col, int index) : \
inter(inter), I(I), Col(Col), index(index), geoindex(0), bary(Vector(1,0,0))
{}
// Mutateurs
void Intersection::setptint(const Vector & V)
{
    this->I = V;
}
void Intersection::setcolor(const Vector & V)
{
    this->Col = V;
}
void Intersection::setbary(const Vector & V)
{
    this->bary = V;
}
void Intersection::setinter(bool b)
{
    this->inter = b;
}
void Intersection::setindex(int i)
{
    this->index = i;
}
void Intersection::setgeoindex(int i)
{
    this->geoindex = i;
}
// Accesseurs
Vector Intersection::getptint() const
{
	return I;
}
bool Intersection::getinter() const
{
	return inter;
}
Vector Intersection::getcolor() const
{
	return Col;
}
int Intersection::getindex() const
{
	return index;
}
int Intersection::getgeoindex() const
{
	return geoindex;
}
Vector Intersection::getbary() const
{
	return bary;
}
