#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
//#include "TriangleIndices.h"
#include "Bbox.h"
#include "Bvh.h"
#include "Scene.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <limits>
#include <vector>
#include <algorithm>
#include <random>


#ifndef TRIANGLEINDICES_H
#define TRIANGLEINDICES_H
class TriangleIndices {
public:
	TriangleIndices(int vtxi=-1,int vtxj=-1,int vtxk=-1,int ni=-1,int nj=-1,int nk=-1,int uvi=-1,int uvj=-1,int uvk=-1):
	vtxi(vtxi),vtxj(vtxj),vtxk(vtxk),uvi(uvi),uvj(uvj),uvk(uvk),ni(ni),nj(nj),nk(nk)
	{};
	int vtxi, vtxj, vtxk;
	int uvi, uvj, uvk;
	int ni, nj, nk, faceGroup;
};
#endif


#ifndef GEOMETRY_H
#define GEOMETRY_H
class Geometry: public Objet 
{
public:
	//Constructeurs
	Geometry();
	Geometry(const char* obj, double scaling, const Vector& offset);
	
	// Destructeur
  	virtual ~Geometry();
	//Methodes propres aux geometries
	void readOBJ(const char* obj);
	void setBbox();
	void setBvh(Bvh* noeud, int deb, int fin, int p, int taille);
	Bbox buildMFBbox(int deb, int fin);
	void add_texture(const char* filename);
	//Methodes liées aux objets;
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
	//   Encore d'autres methodes 
	Vector rdPointOnSurface(const Intersection & I);
	
	
	//Attributs
	Bvh BV;
	vector<TriangleIndices> indices;
//private:
	vector<Vector> vertices;
	vector<Vector> normals;
	vector<Vector> uvs; // Vector en 3D mais on n'utilise que 2 composantes
	vector<Vector> vertexcolors;

	vector<vector<unsigned char> > textures;
	vector<int> w, h;
	
	Bbox BB;
};
#endif
