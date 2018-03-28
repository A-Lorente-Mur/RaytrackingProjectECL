#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Scene.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
#include <random>



//Constructeurs
Sphere::Sphere() : Objet(), O(Vector(0,0,0)), R(0)
{}

Sphere::Sphere(Vector O, double R, Vector Col, int m, double n) :  \
Objet(Col,m,n), O(O), R(R)
{}

Sphere::Sphere(Vector O, double R, Vector Col, int m, double n, double E) : \
Objet(Col, m, n, E), O(O), R(R)
{}
// Destructeur
Sphere::~Sphere(){}

// Accesseurs
void Sphere::setcentre(const Vector & V)
{
    this->O = V;
}
void Sphere::setrayon(double r)
{
    this->R = r;
}

// Mutateurs
Vector Sphere::getcentre() const
{
	return O;
}
double Sphere::getrayon() const
{
	return R;
}
// Autres méthodes

Intersection Sphere::intersect(const Ray & r)
{
	Vector C=r.centre();
	Vector u=r.direction();
	Vector OC=C-O;
	double a = u.norm2();
	double b = 2*u.dot(OC);
	double c = OC.norm2()-R*R;
	double delta=b*b-4*a*c;
	Vector useless;
	if(delta >= 0) {
		double t1=(-b-sqrt(delta))/(2*a);
		double t2=(-b+sqrt(delta))/(2*a);
		if(t2 < 0) {
			Intersection Inter(false,useless,useless,0);
			return Inter;
			}else if(t1 < 0){
			Intersection Inter(true,C+u*t2,this->getcolor(),0);
			return Inter;
		}else {
			Intersection Inter(true,C+u*t1,this->getcolor(),0);
			return Inter;
			}
	} else {
		Intersection Inter(false,useless,useless,0);
		return Inter;
	}
}



Vector Sphere::normale(const Intersection & I)
{
	Vector V=I.getptint();
	Vector OV=V-O;
	OV.normalize();
	return OV; 
}

Vector Sphere::tangente1(const Intersection & I)
{
	Vector n=this->normale(I);
	Vector randomvector=this->tripletAleatoire();
	Vector tan =  n.prodvect(randomvector);
	return tan;
}

Vector Sphere::incidence(const Light & l,const Intersection & I)
{
	Ray r=l.rayon();
	Vector P=r.centre();
	Vector V= I.getptint();
	Vector i=P-V;
	return i;
}




Vector Sphere::randomreflect(const Light & l,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector i=this->incidence(l,I);
	Vector t1=this->tangente1(I);
	Vector t2=N.prodvect(t1);
	t2.normalize();
	i.normalize();
	i=i*(-1);
	double g_Pi = 3.14159265358979323846;
	Vector randomvector=this->tripletAleatoire();
	double r1=randomvector.getX();
	double r2=randomvector.getY();
	double Rq=sqrt(1-r2);
	double x=cos(2*g_Pi*r1)*Rq;
	double y=sin(2*g_Pi*r1)*Rq;
	double z=sqrt(r2);
	Vector r=t1*x+t2*y+N*z;
	r.normalize();
	return r;
}

Vector Sphere::normale2(const Ray & r, const Intersection & I)
{
	Vector V=I.getptint();
	Vector OV=V-O;
	OV.normalize();
	return OV; 
}
Vector Sphere::incidence2(const Ray & r,const Intersection & I)
{
	Vector P=r.centre();
	Vector V= I.getptint();
	Vector i=P-V;
	return i;
}
Vector Sphere::reflexion2(const Ray & r,const Intersection & I)
{
	Vector P=I.getptint();
	Vector N=this->normale(I);
	Vector i=this->incidence2(r,I);
	i.normalize();
	i=i*(-1);
	Vector ref=i-N*i.dot(N)*2;
	ref.normalize();
	return ref;
}
Vector Sphere::randomreflect2(const Ray & r,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector i=this->incidence2(r,I);
	Vector t1=this->tangente1(I);
	Vector t2=N.prodvect(t1);
	t2.normalize();
	i.normalize();
	i=i*(-1);
	double g_Pi = 3.14159265358979323846;
	Vector randomvector=this->tripletAleatoire();
	double r1=randomvector.getX();
	double r2=randomvector.getY();
	double Rq=sqrt(1-r2);
	double x=cos(2*g_Pi*r1)*Rq;
	double y=sin(2*g_Pi*r1)*Rq;
	double z=sqrt(r2);
	Vector ref=t1*x+t2*y+N*z;
	ref.normalize();
	return ref;
}
Vector Sphere::transmission2(const Ray & r,const Intersection & I, double nair)
{
	Vector P=I.getptint();
	Vector N=this->normale(I);
	Vector i=r.direction();
	i.normalize();
	double ns=this->getindice();
	double n1;
	double n2;
	double k=i.dot(N);
	if(k>0){
		N=N*(-1);
		n1=ns;
		n2=nair;
	}else{
		n1=nair;
		n2=ns;
	}
	double a=1-(n1/n2)*(n1/n2)*(1-k*k);
	Vector t;
	if(a>0){
		t= i*n1/n2-N*((n1/n2)*k+sqrt(a));
		t.normalize();
		return t;
	}else{
		t=reflexion2(r,I);
		t.normalize();
		return t*(-1);
	}	
}
Vector Sphere::rdPointOnSurface(const Intersection & I)
{
	double g_Pi = 3.14159265358979323846;
	Vector P=I.getptint();
	Vector N=P-O;
	N.normalize();
	
	Vector randomvector=this->tripletAleatoire();
	Vector tan1 =  N.prodvect(randomvector);
	tan1.normalize();
	
	Vector tan2 = N.prodvect(tan1);
	tan2.normalize();
	
	Vector randomvector2=this->tripletAleatoire();
	double r1=randomvector2.getX();
	double r2=randomvector2.getY();
	double Rq=sqrt(1-r2);
	double x=cos(2*g_Pi*r1)*Rq;
	double y=sin(2*g_Pi*r1)*Rq;
	double z=sqrt(r2);
	
	Vector ref=tan1*x+tan2*x+N*z;
	ref.normalize();
	ref=ref*R;
	Vector Pprim=O+ref;
	return Pprim;
	
}
