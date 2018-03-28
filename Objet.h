#ifndef OBJET_H
#define OBJET_H
#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
using namespace std;
#include <random>


class Objet
{
public:
  //Constructeur
  Objet();//
  Objet(Vector Col, int m, double n);//
  Objet(Vector Col, int m, double n, double E);//
  //Destructeur
  virtual ~Objet();
  
  //Mutateurs
  void setcolor(const Vector & V);
  void setmateriau(int mat);//
  void setindice(double nopt);//
  void setE(double Em);//
  //Accesseurs
  Vector getcolor() const;//
  int getmateriau() const;//
  double getindice() const;//
  double getE() const;//
  //Generation aleatoire de vecteurs
  Vector randomtriplet() const;//triplet gaussien
  Vector tripletAleatoire() const;//triplet suivant une loi uniforme
  
  //Autres Methodes
  virtual Intersection intersect(const Ray & r) =0;
  virtual Vector normale(const Intersection & I)=0;
  virtual Vector tangente1(const Intersection & I)=0;
  virtual Vector incidence(const Light & l,const Intersection & I)=0;
  virtual Vector randomreflect(const Light & l,const Intersection & I)=0;
  virtual Vector normale2(const Ray & r,const Intersection & I)=0;
  virtual Vector incidence2(const Ray & r,const Intersection & I)=0;
  virtual Vector reflexion2(const Ray & r,const Intersection & I)=0;
  virtual Vector randomreflect2(const Ray & r,const Intersection & I)=0;
  virtual Vector transmission2(const Ray & r,const Intersection & I, double nair)=0;
  //   Encore d'autres methodes 
  virtual Vector rdPointOnSurface(const Intersection & I)=0;
  
private:
  int m;
  double n,E;
  Vector Col;
};
#endif
