#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
#include <random>
default_random_engine engine;
uniform_real_distribution<double> distrib(0,1);


// Constructeurs
Objet::Objet() :
Col(Vector(0,0,0)), m(1), n(1), E(0)
{}
Objet::Objet(Vector Col, int m, double n) :
Col(Col), m(m), n(n), E(0)
{}
Objet::Objet(Vector Col, int m, double n, double E) :
Col(Col), m(m), n(n), E(E)
{}
Objet::~Objet(){}

//Mutateurs
void Objet::setcolor(const Vector & V)
{
    this->Col = V;
}
void Objet::setmateriau(int mat)
{
    this->m = mat;
}
void Objet::setindice(double nopt)
{
    this->n = nopt;
}
void Objet::setE(double Em)
{
    this->E = Em;
}
//Accesseurs
Vector Objet::getcolor() const
{
	return Col;
}
int Objet::getmateriau() const
{
	return m;
}
double Objet::getindice() const
{
	return n;
}
double Objet::getE() const
{
	return E;
}
//Autres Methodes
Vector Objet::randomtriplet() const
{
	double g_Pi = 3.14159265358979323846;
	double x = distrib(engine);
	double y = distrib(engine);
	double Rr = sqrt(-2*log(x));
	double u = Rr*cos(2*g_Pi*y)*0.5;
	double v = Rr*sin(2*g_Pi*y)*0.5;
	double z = 0;
	Vector rd(u,v,z);
	return rd;
}
Vector Objet::tripletAleatoire() const
{
	double x = distrib(engine);
	double y = distrib(engine);
	double z = distrib(engine);
	Vector rd(x,y,z);
	return rd;
}



