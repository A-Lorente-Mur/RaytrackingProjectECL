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
using namespace std;
#include <limits>
#include <vector>
#include <algorithm>
#include <random>


#ifndef BBOX_H
#define BBOX_H

class Bbox
{
public:
  // Constructeurs
  Bbox();
  Bbox(const Vector & bmin,const Vector & bmax);  
  //Mutateurs
  void setbmin(const Vector & V);
  void setbmax(const Vector & V);
  //Accesseurs
  Vector getbmin() const;
  Vector getbmax() const;
  
  // Autres méthodes
  Intersection intersect(const Ray & r);
  
private:
  Vector bmin, bmax;
  
};
#endif
