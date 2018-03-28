#include "Vector.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
//COnstructeur
Vector::Vector() : x(0), y(0), z(0)
{}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z)
{}
// Mutateurs
void Vector::setX(double x)
{
    this->x = x;
}
void Vector::setY(double y)
{
    this->y = y;
}
void Vector::setZ(double z)
{
    this->z = z;
}
//Accesseurs
double Vector::getX() const
{
    return this->x;
} 
double Vector::getY() const
{
    return this->y;
}
double Vector::getZ() const
{
    return this->z;
}
//Operateurs
Vector Vector::operator+(const Vector & f) const
{
    Vector r;
    r.x = f.x+x;
    r.y = f.y+y;
    r.z = f.z+z;
    return r;
} 
Vector Vector::operator-(const Vector & f) const
{
    Vector r;
    r.x = x-f.x;
    r.y = y-f.y;
    r.z = z-f.z;
    return r;
} 
Vector Vector::operator*(double a) const
{
    Vector r;
    r.x = x*a;
    r.y = y*a;
    r.z = z*a;
    return r;
}
Vector Vector::operator/(double a) const
{
    Vector r;
    r.x = x/a;
    r.y = y/a;
    r.z = z/a;
    return r;
}
const double& Vector::operator[](int i) const
{
    if(i==0){
    	return x;
    }else if(i==1){
    	return y;
    }else{
    	return z;
    }
}
double& Vector::operator[](int i)
{
    if(i==0){
    	return x;
    }else if(i==1){
    	return y;
    }else{
    	return z;
    }
}
//Autres Methodes
double Vector::distance(const Vector &P) const
{
    double dx = this->x - P.x;
    double dy = this->y - P.y;
    double dz = this->z - P.z;
    return sqrt(dx*dx + dy*dy + dz*dz); 
}
double Vector::distance2(const Vector &P) const
{
    double dx = this->x - P.x;
    double dy = this->y - P.y;
    double dz = this->z - P.z;
    return dx*dx + dy*dy + dz*dz; 
}
double Vector::dot(const Vector &P) const
{
    double dx = this->x * P.x;
    double dy = this->y * P.y;
    double dz = this->z * P.z;
    return dx+dy+dz; 
}
double Vector::getNorm()
{
    double dx = this->x;
    double dy = this->y;
    double dz = this->z;
    return sqrt(dx*dx+dy*dy+dz*dz); 
}
double Vector::norm2()
{
    double dx = this->x;
    double dy = this->y;
    double dz = this->z;
    return dx*dx+dy*dy+dz*dz; 
}
Vector Vector::milieu(const Vector &P) const
{
    Vector result;
    result.x = (P.x + this->x) / 2;
    result.y = (P.y + this->y) / 2;
    result.z = (P.z + this->z) / 2;
    return result;
}
Vector Vector::mult(const Vector &P) const
{
    Vector result;
    result.x = (P.x * this->x);
    result.y = (P.y * this->y);
    result.z = (P.z * this->z) ;
    return result;
}
Vector Vector::prodvect(const Vector &P) const
{
    Vector result;
    result.x = (P.z*this->y-P.y*this->z);
    result.y = (P.x*this->z-P.z*this->x);
    result.z = (P.y*this->x-P.x*this->y);
    return result;
}
Vector Vector::CorrectionGamma()
{
    Vector result;
    result.x = min(pow(this->x,1/2.2),255.0);
    result.y = min(pow(this->y,1/2.2),255.0);
    result.z = min(pow(this->z,1/2.2),255.0);
    return result;
}

Vector Vector::minimum(const Vector &P) const
{
    Vector result;
    result.x = min(P.x,this->x);
    result.y = min(P.y,this->y);
    result.z = min(P.z,this->z);
    return result;
}
Vector Vector::maximum(const Vector &P) const
{
    Vector result;
    result.x = max(P.x,this->x);
    result.y = max(P.y,this->y);
    result.z = max(P.z,this->z);
    return result;
}
void Vector::normalize()
{
	double dx = this->x;
    double dy = this->y;
    double dz = this->z;
    double N=sqrt(dx*dx + dy*dy+dz*dz);
    x=x/N;
    y=y/N;
    z=z/N;
}

void Vector::saisir()
{
    cout << "Tapez x : ";  cin >> this->x;
    cout << "Tapez y : ";  cin >> this->y;
    cout << "Tapez z : ";  cin >> this->z;
} 

void Vector::afficher() const
{
    cout << "x= " << this->x << endl;
    cout << "y= " << this->y << endl;
    cout << "z= " << this->z << endl;
}






