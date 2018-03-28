#ifndef SCENE_H
#define SCENE_H
#include <iostream>
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "Light.h"
#include "Intersection.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
//#include "TriangleIndices.h"
#include "Geometry.h"
#include "Bbox.h"
using namespace std;
#include <random>


class Scene 
{
public:
  // Constructeurs
  Scene(vector<Objet*> Obj);//
  // Acesseurs, et mutateurs
  void setlightindex(int i);
  int getlightindex() const;
  void push(Objet* O);//
  Scene GenNewScene(int index);//
  //Methodes
  Intersection intersect(const Ray & r)const;//
  bool SceneBetween(const Intersection & Inter,const Vector & CentreLum);//
  Vector getcolorLumSpherique(Ray ra, Intersection Inter, int rbmax);
  Vector getcolorLumSpheriquerd(Ray r, int rbmax, int nrd);
  
  Light RandomLightGenerator(const Intersection & Inter);
  Vector getcolor2(const Intersection & Inter,const Ray & rayon, const Light & l, int rbmax);
  Vector getcolorAntiAliasing2(const Ray r,int rbmax,int nrd);
//  Vector getcolorAntiAliasing3(int i,int j,Vector Camera,int W,int H,double alpha,int rbmax,int nrd);
//  
//  Ray GenereRayon(int i, int j, Vector Camera,int W,int H,double alpha);
//  
  
  
private: 
  vector<Objet*> Obj;//. devient ->, et Sph->Obj
  int lightindex;//dynamic_cast<Sphere*>(obj[lightindex])->
};

#endif
