#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
using namespace std;
#include <random>


class Sphere:public Objet
{
public:
  // Constructeurs
  Sphere();//
  Sphere(Vector O, double R, Vector Col, int m,  double n);//
  Sphere(Vector O, double R, Vector Col, int m,  double n, double E);//
  /*Col est la couleur de la sphere, 
  m le type de sphère (1 platre, 2 mirroir, 3 transparence, 4 lumiere),
  n est l'indice optique du milieu (si m!=3, on le mettra à 1)
  */
  // Destructeur
  virtual ~Sphere();
  
  //Accesseurs et mutateurs
  void setcentre(const Vector & V);//
  void setrayon(double r);//
  Vector getcentre() const;//
  double getrayon() const;//
  
  // Autres méthodes
  Intersection intersect(const Ray & r);//
  Vector normale(const Intersection & I);//
  Vector tangente1(const Intersection & I);
  Vector incidence(const Light & l,const Intersection & I);
  Vector randomreflect(const Light & l,const Intersection & I);
  Vector normale2(const Ray & r, const Intersection & I);//
  Vector incidence2(const Ray & r,const Intersection & I);
  Vector reflexion2(const Ray & r,const Intersection & I);
  Vector randomreflect2(const Ray & r,const Intersection & I);
  Vector transmission2(const Ray & r,const Intersection & I, double nair);
////   Encore d'autres methodes 
  Vector rdPointOnSurface(const Intersection & I);
  
  
  
private: 
  double R;
  Vector O;
};
#endif
