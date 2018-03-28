#ifndef RAY_H
#define RAY_H
#include <iostream>
#include "Vector.h"
using namespace std;

class Ray
{
public:
  // Constructeurs
  Ray(Vector U, Vector C);

  //Accesseurs et mutateurs
  Vector direction()const;
  Vector centre()const;
  void setd(const Vector &P);
  void setc(const Vector &P);
  
private: 
  Vector U,C;
};
#endif
