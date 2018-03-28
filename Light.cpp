#include "Vector.h"
#include "Ray.h"
#include "Light.h"
#include <cmath>
#include <iostream>
using namespace std;
//Constructeur

Light::Light(Ray r, double I, bool interior) : r(r), I(I), interior(interior)
{}
// Methodes et acesseurs
Ray Light::rayon()const
{
    return r;
}
double Light::Intensity()const
{
    return I;
}
bool Light::interieur()const
{
    return interior;
}
void Light::setr(Ray r)
{
	this->r = r;
}
void Light::setI(double LL)
{
	this->I = LL;
}
void Light::changemilieu(bool b)
{
	this->interior = b;
}
