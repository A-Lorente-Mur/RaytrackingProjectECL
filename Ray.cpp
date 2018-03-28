#include "Vector.h"
#include "Ray.h"
#include <cmath>
#include <iostream>
using namespace std;
//Constructeur

Ray::Ray(Vector U, Vector C) : U(U), C(C)
{}
// Methodes et acesseurs
Vector Ray::direction()const
{
    return U;
}
Vector Ray::centre()const
{
    return C;
}
void Ray::setd(const Vector &P)
{
	this->U = P;
}
void Ray::setc(const Vector &P)
{
	this->C = P;
}
