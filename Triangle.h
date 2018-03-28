#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
using namespace std;
#include <random>


class Triangle:public Objet
{
public:
  // Constructeurs
  Triangle();//
  Triangle(Vector A, Vector B, Vector C);//
  Triangle(Vector A, Vector B, Vector C, Vector Col, int m,  double n);//
  Triangle(Vector A, Vector B, Vector C, Vector Col, int m,  double n, double E);//
  /*Col est la couleur de la Triangle, 
  m le type de sphère (1 platre, 2 mirroir, 3 transparence, 4 lumiere),
  n est l'indice optique du milieu (si m!=3, on le mettra à 1)*/
  
  // Destructeur
  virtual ~Triangle();
  
  
  //Accesseurs
  void setA(const Vector & V);//
  void setB(const Vector & V);//
  void setC(const Vector & V);//
  //Mutateurs
  Vector getA() const;//
  Vector getB() const;//
  Vector getC() const;//

  
// Autres méthodes
  Intersection intersect(const Ray & r);//
  Vector normale(const Intersection & I);//
  Vector tangente1(const Intersection & I);//
  Vector incidence(const Light & l,const Intersection & I);//
  Vector randomreflect(const Light & l,const Intersection & I);
  Vector normale2(const Ray & r, const Intersection & I);//
  Vector incidence2(const Ray & r,const Intersection & I);
  Vector reflexion2(const Ray & r,const Intersection & I);
  Vector randomreflect2(const Ray & r,const Intersection & I);
  Vector transmission2(const Ray & r,const Intersection & I, double nair);
////   Encore d'autres methodes 
  Vector rdPointOnSurface(const Intersection & I);
  
  
  
private:
  Vector A,B,C;
  
};
#endif
