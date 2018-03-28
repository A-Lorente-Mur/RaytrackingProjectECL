#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Scene.h"
#include "Bbox.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <limits>
#include <vector>
#include <algorithm>
#include <random>
#ifndef BVH_H
#define BVH_H

class Bvh
{
public:
  // Constructeurs
  Bvh();
  Bvh(Bbox box,int pr,int indicedeb,int indicefin,Bvh* filsg,Bvh* filsd);
  
  
  //Mutateurs
  void setprofondeur(int pro);
  void setbox(const Bbox & b);
  void setfilsdroit(Bvh* fd);
  void setfilsgauche(Bvh* fg);
  void setindicedeb(int i);
  void setindicefin(int i);
  
  //Accesseurs
  int profondeur() const;
  Bbox getbox() const;
  Bvh* filsdroit() const;
  Bvh* filsgauche() const;
  int getindicedeb() const ;
  int getindicefin() const ;
  
  Intersection intersect(const Ray & r);
  
  //Attributs  
  Bbox box;
  int pr;/*Pour le moement p=1 si c'est une feuille, 0 sinon, on vera si je
  donne d'autres usages a cet entier... sinon, je lui aurais donnele type bool*/
  int indicedeb, indicefin;
  Bvh* filsg;
  Bvh* filsd;
  
  
};
#endif
