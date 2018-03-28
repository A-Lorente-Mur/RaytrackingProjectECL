#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Scene.h"
#include "Bbox.h"
#include "Bvh.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <limits>
#include <vector>
#include <algorithm>
#include <random>


//Constructeurs
Bvh::Bvh() {}
Bvh::Bvh(Bbox box,int pr,int indicedeb,int indicefin,Bvh* filsg,Bvh* filsd):
box(box),pr(pr),indicedeb(indicedeb),indicefin(indicefin),filsg(filsg),filsd(filsd)
{}
//Mutateurs
void Bvh::setprofondeur(int pro)
{
	this->pr = pro;
}
void Bvh::setbox(const Bbox & b)
{
	this->box = b;
}
void Bvh::setfilsdroit(Bvh* fd)
{
	this->filsd = fd;
}
void Bvh::setfilsgauche(Bvh* fg)
{
	this->filsg = fg;
}
void Bvh::setindicedeb(int i)
{
	this->indicedeb = i;
}
void Bvh::setindicefin(int i)
{
	this->indicefin = i;
}
//Accesseurs
int Bvh::profondeur() const
{
	return pr;
}
int Bvh::getindicedeb() const
{
	return indicedeb;
}
int Bvh::getindicefin() const
{
	return indicefin;
}
Bvh* Bvh::filsgauche() const
{
	return filsg;
}
Bvh* Bvh::filsdroit() const
{
	return filsd;
}
Intersection Bvh::intersect(const Ray & r)
{
	Intersection Interbb=this->box.intersect(r);
	if(!Interbb.getinter()){
		return Interbb;
	}else{
		if(this->pr==1){
			Interbb.feuil.push_back(this);
			return Interbb;
		}else{
			Intersection Interbb1=this->box.intersect(r);
			Intersection Interbb2=this->box.intersect(r);
			if(this->filsg){
				Interbb1=this->filsg->intersect(r);
			}
			if(this->filsd){
				Interbb2=this->filsd->intersect(r);
			}
			vector<Bvh*> feuil1=Interbb1.feuil;
			vector<Bvh*> feuil2=Interbb2.feuil;
			feuil1.insert(feuil1.end(), feuil2.begin(), feuil2.end());
			Interbb.feuil=feuil1;
			return Interbb;
		}
	}
}


//print *(BV->filsg->filsg)
//print *(BV->filsg->filsd)
//print *(BV->filsd->filsg)
//print *(BV->filsd->filsd)

