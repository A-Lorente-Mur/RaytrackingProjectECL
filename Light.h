#ifndef LIGHT_H
#define LIGHT_H
#include <iostream>
#include "Vector.h"
#include "Ray.h"
using namespace std;

class Light
{
public:
  // Constructeurs
  Light(Ray r, double I, bool interior);

  //Accesseurs et mutateurs
  Ray rayon()const;
  double Intensity()const;
  bool interieur()const;
  void setr(Ray R);
  void setI(double LL);
  void changemilieu(bool b);
  
private: 
  Ray r;
  double I;
  bool interior;
};
#endif
