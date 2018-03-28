#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
#include <random>


//Constructeur
Triangle::Triangle() : 
Objet(), A(Vector(0,0,0)), B(Vector(0,0,0)), C(Vector(0,0,0))
{}
Triangle::Triangle(Vector A, Vector B, Vector C) : 
Objet(), A(A), B(B), C(C)
{}
Triangle::Triangle(Vector A, Vector B, Vector C, Vector Col, int m,  double n) : 
Objet(Col, m, n), A(A), B(B), C(C)
{}
Triangle::Triangle(Vector A,Vector B,Vector C,Vector Col,int m,double n,double E) : 
Objet(Col, m, n, E), A(A), B(B), C(C)
{}
//Destructeur
Triangle::~Triangle(){}

// Methodes et acesseurs
void Triangle::setA(const Vector & V)
{
    this->A = V;
}
void Triangle::setB(const Vector & V)
{
    this->B = V;
}
void Triangle::setC(const Vector & V)
{
    this->C = V;
}
Vector Triangle::getA() const
{
	return A;
}
Vector Triangle::getB() const
{
	return B;
}
Vector Triangle::getC() const
{
	return C;
}

// Autres méthodes


Intersection Triangle::intersect(const Ray & r)
{
	Vector AB=B-A;
	Vector AC=C-A;
	Vector N=AB.prodvect(AC);
	Vector Cen=r.centre();
	Vector CO=C-Cen;
	Vector color=this->getcolor();
	Vector u=r.direction();
	double t=CO.dot(N)/u.dot(N);
	Vector P=Cen+u*t;
	if(t<0){
		Intersection Inter(false,P,color,0);
		return Inter;
	}
	Vector AP=P-A;
	
	double ABAB=AB.norm2();
	double ABAC=AB.dot(AC);
	double ACAC=AC.norm2();
	double det1=ABAB*ACAC-ABAC*ABAC;
	
	double APAB=AP.dot(AB);
	double APAC=AP.dot(AC);
	double det2=APAB*ACAC-APAC*ABAC;
	
	double det3=ABAB*APAC-APAB*ABAC;
	
	double beta=det2/det1;
	double gamma=det3/det1;
	double alpha=1-beta-gamma;
	
	if(alpha<0||alpha>1){
		Intersection Inter(false,P,color,0);
		return Inter;
	}
	if(beta<0||beta>1){
		Intersection Inter(false,P,color,0);
		return Inter;
	}
	if(gamma<0||gamma>1){
		Intersection Inter(false,P,color,0);
		return Inter;
	}
	Intersection Inter(true,P,color,0);
	Vector bary(alpha,beta,gamma);
	Inter.setbary(bary);
	return Inter;
}



Vector Triangle::normale(const Intersection & I)
{
	Vector AB=B-A;
	Vector AC=C-A;
	Vector N=AB.prodvect(AC);
	N.normalize();
	return N; 
}

Vector Triangle::tangente1(const Intersection & I)
{
	Vector n=this->normale(I);
	Vector randomvector=this->tripletAleatoire();
	Vector tan =  n.prodvect(randomvector);
	return tan;
}

Vector Triangle::incidence(const Light & l,const Intersection & I)
{
	Ray r=l.rayon();
	Vector P=r.centre();
	Vector V= I.getptint();
	Vector i=P-V;
	return i;
}


Vector Triangle::randomreflect(const Light & l,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector t1=this->tangente1(I);
	Vector t2=N.prodvect(t1);
	t2.normalize();
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


Vector Triangle::normale2(const Ray & r, const Intersection & I)
{
	Vector AB=B-A;
	Vector AC=C-A;
	Vector N=AB.prodvect(AC);
	N.normalize();
	Vector u= r.direction();
	if(N.dot(u)<0){
		N=N*(-1);
	}
	return N; 
}
Vector Triangle::incidence2(const Ray & r,const Intersection & I)
{
	Vector P=r.centre();
	Vector V= I.getptint();
	Vector i=P-V;
	return i;
}
Vector Triangle::reflexion2(const Ray & r,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector i=this->incidence2(r,I);
	i.normalize();
	i=i*(-1);
	Vector ref=i-N*i.dot(N)*2;
	ref.normalize();
	return ref;
}
Vector Triangle::randomreflect2(const Ray & r,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector t1=this->tangente1(I);
	Vector t2=N.prodvect(t1);
	t2.normalize();
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

Vector Triangle::transmission2(const Ray & r,const Intersection & I, double nair)
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


Vector Triangle::rdPointOnSurface(const Intersection & I)
{
	Vector AB=B-A;
	Vector AC=C-A;
	Vector randomvector=this->tripletAleatoire();
	Vector Pprim=A+AB*randomvector.getX()+AC*randomvector.getY();	
	return Pprim;
	
}






