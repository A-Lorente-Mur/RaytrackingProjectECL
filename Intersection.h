#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include <vector>
using namespace std;

class Bvh;

class Intersection
{
public:
  // Constructeurs
  
  Intersection(bool inter,Vector I, Vector Col, int index);

  //Mutateurs
  void setptint(const Vector & V);
  void setcolor(const Vector & V);
  void setbary(const Vector & V);
  void setinter(bool r);
  void setindex(int i);
  void setgeoindex(int i);

  
  //Accesseurs
  Vector getptint() const;
  bool getinter() const;
  Vector getcolor() const;
  int getindex()const;
  int getgeoindex()const;
  Vector getbary() const;
  
  vector<Bvh *> feuil;
private: 
  bool inter;
  Vector I,Col;
  int index;
  int geoindex;
  Vector bary;
};
#endif
