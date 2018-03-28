#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

class Vector
{
public:
  // Constructeurs
  Vector();
  Vector(double x, double y, double z);

  //Mutateurs
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  //Accesseurs
  double getX() const;
  double getY() const;
  double getZ() const;
  
  //Operateurs
  Vector operator+(const Vector & f) const;
  Vector operator-(const Vector & f) const;
  Vector operator*(double a) const;
  Vector operator/(double a) const;
  const double& operator[](int i) const;
  double& operator[](int i);
  
  

  // Autres méthodes
  double distance(const Vector &P) const;
  double distance2(const Vector &P) const;
  double dot(const Vector &P) const;
  double getNorm();
  double norm2();
  Vector milieu(const Vector &P) const;
  Vector mult(const Vector &P) const;
  void normalize();
  Vector prodvect(const Vector &P) const;
  Vector CorrectionGamma();
  
  Vector minimum(const Vector &P) const;
  Vector maximum(const Vector &P) const;

  void saisir();
  void afficher() const;

private: 
  double x,y,z;
};

#endif
