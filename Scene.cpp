#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Scene.h"
//#include "TriangleIndices.h"
#include "Geometry.h"
#include "Bbox.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <limits>
#include <vector>
#include <algorithm>
#include <random>


//Constructeur
Scene::Scene(vector<Objet*> Obj) : Obj(Obj), lightindex(0)
{}
//Mutateur
void Scene::push(Objet* O)
{
	Obj.push_back (O);
}
// Méthodes
int Scene::getlightindex() const
{
	return lightindex;
}
void Scene::setlightindex(int i)
{
	this->lightindex = i;
}
Scene Scene::GenNewScene(int index){
	vector<Objet*> Ob;
	int n=Obj.size();
	for(int i=0;i<n;i++){
		if(i!=index){
			Ob.push_back(Obj[i]);
		}
	}
	Scene SC(Ob);
	return SC;
}

Intersection Scene::intersect(const Ray & r)const
{
	int n=Obj.size();
	Vector C=r.centre();
	Vector useless(0,0,0);
	Intersection Inter(false,useless,useless,0);
	int index=0;
	double mindist=numeric_limits<double>::infinity();
	Vector Point;
	for (int i=0;i<n;i++){
		Inter=Obj[i]->intersect(r);
		if(Inter.getinter()){
			Point=Inter.getptint();
			if (C.distance2(Point) < mindist) {
				mindist = C.distance2(Point);
				index = i;
			}
		}
	}
	Inter = Obj[index]->intersect(r);
	Inter.setindex(index);
	return Inter;
}

bool Scene::SceneBetween(const Intersection & Inter,const Vector & CentreLum){
	int index=Inter.getindex();
	Vector P=Inter.getptint()+Obj[index]->normale(Inter)*0.0001;
	Vector Dirlum=CentreLum-P;
	Ray Rayonlum(Dirlum,P);
	Intersection II=this->intersect(Rayonlum);
	Vector Pprim=II.getptint();
	double d1=P.distance2(CentreLum);
	double d2=P.distance2(Pprim);
	if(d1>d2){
		return true;
	}else{
		return false;
	}
}

Vector Scene::getcolorLumSpherique(Ray ra, Intersection Inter, int rbmax)
{
	double g_Pi = 3.14159265358979323846;
	Objet* o=Obj[Inter.getindex()];
	int materiau=o->getmateriau();
	Vector Couleur(0,0,0);
	Vector P=Inter.getptint();
	Vector N=o->normale2(ra,Inter);
	Vector r;
	double nair=1;
	double rho=o->getindice();
	Objet* su=Obj[lightindex];
	Sphere* sun=dynamic_cast<Sphere*>(su);
	double E=sun->getE();
	double rlum=sun->getrayon();
	
	if(rbmax>0){
		if(materiau == 1){
			r=o->randomreflect2(ra,Inter);
			Vector Pprim=P+N*0.0000001;
			Ray R(r,Pprim);
			Intersection Interprim=this->intersect(R);
			Vector Couleur1=this->getcolorLumSpherique(R,Interprim,rbmax-1);
			return Couleur1.mult(Inter.getcolor())*rho;
		}else if(materiau == 2){
			r=o->reflexion2(ra,Inter);
			Vector Pprim=P+r*0.0000001;
			Ray R(r,Pprim);
			Intersection Interprim=this->intersect(R);
			Vector Couleur1=this->getcolorLumSpherique(R,Interprim,rbmax-1);
			return Couleur1.mult(Inter.getcolor())*rho;
		}else if(materiau == 4){
			return Inter.getcolor()*(E/(4*g_Pi*g_Pi*rlum*rlum));		
		}else{
			Vector t=o->transmission2(ra,Inter,nair);
			Vector Pprim= P +t*0.000001;
			Ray R(t,Pprim);
			Intersection Interprim=this->intersect(R);
			Vector Couleur1=this->getcolorLumSpherique(R,Interprim,rbmax-1);
			return Couleur1.mult(Inter.getcolor())*rho;
		}
	}else{
		if(materiau == 4){
			return Inter.getcolor()*(E/(4*g_Pi*g_Pi*rlum*rlum));
		}else{
			return Couleur*rho;
		}
	}
}




Vector Scene::getcolorLumSpheriquerd(Ray r, int rbmax, int nrd)
{
	Vector SumColor(0,0,0);
	for(int i=0;i<nrd;i++){
		Vector rdAA=Obj[lightindex]->randomtriplet();
		Vector Camera=r.centre();
		Vector DirCam=r.direction()+rdAA;
		Ray RayonCamera(DirCam,Camera);
		Intersection Inter=this->intersect(RayonCamera);
		if(Inter.getinter()){
			SumColor=SumColor+this->getcolorLumSpherique(RayonCamera,Inter,rbmax);
		}
	}
	SumColor= SumColor/nrd;
	SumColor=SumColor.CorrectionGamma();
	return SumColor;
}




Light Scene::RandomLightGenerator(const Intersection & Inter)
{
	double g_Pi = 3.14159265358979323846;
	Objet* su =Obj[lightindex];
	Sphere* Sun=dynamic_cast<Sphere*>(su);
	double E=Sun->getE();
	double Rlum=Sun->getrayon();
	double I=E/(4*g_Pi*g_Pi*Rlum*Rlum);
	bool within=false;
	Vector LL=Sun->rdPointOnSurface(Inter);
	Vector Dirlum(0,0,0);
	Ray rayonlum(Dirlum,LL);
	Light Lumi(rayonlum, I, within);
	return Lumi;
	
}



Vector Scene::getcolor2(const Intersection & Inter,const Ray & rayon, const Light & l, int rbmax)
{
	double g_Pi = 3.14159265358979323846;
	Objet* o=Obj[Inter.getindex()];
	int materiau=o->getmateriau();
	Vector Couleur(0,0,0);
	double I=l.Intensity();
	Vector P=Inter.getptint();
	Vector N=o->normale2(rayon,Inter);
	Vector LP=o->incidence(l,Inter);
	Vector i=o->incidence(l,Inter);
	Vector r;
	i.normalize();
	double nair=1;
	double rho=o->getindice();
	
	Objet* su=Obj[lightindex];
	Sphere* Sun=dynamic_cast<Sphere*>(su);
	double E=Sun->getE();
	double Rlum=Sun->getrayon();
	Vector Psun=l.rayon().centre();
	
	Vector PPsun=Psun-P;
	Vector OsunPsun=Psun-Sun->getcentre();
	Vector Nprim=Psun-Sun->getcentre();
	Nprim.normalize();
	double costhetaprim=abs(Nprim.dot(PPsun));
	double costhetaprimprim=max(0.0,Nprim.dot(OsunPsun));
	double CorrInd=Rlum*Rlum*g_Pi*costhetaprim/costhetaprimprim;
	
	
	
	bool within=l.interieur();
	bool ombre=this->SceneBetween(Inter, l.rayon().centre());
	if(rbmax>0){
		if(materiau == 1){
			if(ombre){
				r=o->randomreflect2(rayon,Inter);
				Vector Pprim=P+r*0.0000001;
				Ray R(r,Pprim);
				Intersection Interprim=this->intersect(R);
				Light lprim=this->RandomLightGenerator(Interprim);
				Vector Couleur1=this->getcolor2(Interprim,rayon, lprim, rbmax-1);
				return Couleur1.mult(Inter.getcolor())*rho;
			}else{
				r=o->randomreflect2(rayon,Inter);
				Vector Pprim=P+r*0.0000001;
				Ray R(r,Pprim);
				Intersection Interprim=this->intersect(R);
				Light lprim=this->RandomLightGenerator(Interprim);
				Vector Couleur1=this->getcolor2(Interprim,rayon, lprim, rbmax-1);
				Couleur.setX(I*max(N.dot(i),0.0)*\
				Inter.getcolor().getX()/(LP.norm2()*g_Pi));
				Couleur.setY(I*max(N.dot(i),0.0)*\
				Inter.getcolor().getY()/(LP.norm2()*g_Pi));
				Couleur.setZ(I*max(N.dot(i),0.0)*\
				Inter.getcolor().getZ()/(LP.norm2()*g_Pi));
				Couleur=Couleur*CorrInd;
				Couleur1=Couleur1.mult(Inter.getcolor());
				Couleur=Couleur+Couleur1;
				return Couleur*rho;
			}
		}else if(materiau == 2){
			if(ombre){
				r=o->reflexion2(rayon,Inter);
				Vector Pprim=P+r*0.0000001;
				Ray R(r,Pprim);
				Intersection Interprim=this->intersect(R);
				Light lprim=this->RandomLightGenerator(Interprim);
				Vector Couleur1=this->getcolor2(Interprim,rayon, lprim, rbmax-1);
				return Couleur1*rho;
			}else{
				r=o->reflexion2(rayon,Inter);
				Vector Pprim=P+r*0.0000001;
				Ray R(r,Pprim);
				Intersection Interprim=this->intersect(R);
				Light lprim=this->RandomLightGenerator(Interprim);
				Vector Couleur1=this->getcolor2(Interprim,rayon, lprim, rbmax-1);
				Couleur1=Couleur1.mult(Inter.getcolor());
				return Couleur1*rho;
			}
		}else if(materiau == 4){
			return Inter.getcolor()*(E/(4*g_Pi*g_Pi*Rlum*Rlum));
		}else{	
			r=o->transmission2(rayon,Inter,nair);
			Vector Pprim= P +r*0.0001;
			Ray R(r,Pprim);
			Intersection Interprim=this->intersect(R);
			Light lprim=this->RandomLightGenerator(Interprim);
			Vector Couleur1=this->getcolor2(Interprim,rayon, lprim, rbmax-1);
			return Couleur1;
			}
	}else{
		if(materiau == 4){
			return Inter.getcolor()*(E/(4*g_Pi*g_Pi*Rlum*Rlum));
		}else{
			if(ombre){
				return Couleur*rho;
			}else{
				Couleur.setX(I*max(N.dot(i),0.0)*\
				Inter.getcolor().getX()/(LP.norm2()*g_Pi));
				Couleur.setY(I*max(N.dot(i),0.0)*\
				Inter.getcolor().getY()/(LP.norm2()*g_Pi));
				Couleur.setZ(I*max(N.dot(i),0.0)*\
				Inter.getcolor().getZ()/(LP.norm2()*g_Pi));
				return Couleur*rho*CorrInd;
			}	
		}		
	}
}






Vector Scene::getcolorAntiAliasing2(const Ray r,int rbmax,int nrd)
{
	Vector SumColor(0,0,0);
	for(int i=0;i<nrd;i++){
		Vector rdAA=Obj[lightindex]->randomtriplet();
		Vector Camera=r.centre();
		Vector DirCam=r.direction()+rdAA;
		Ray RayonCamera(DirCam,Camera);
		Intersection Inter=this->intersect(RayonCamera);
		Light l=this->RandomLightGenerator(Inter);
		if(Inter.getinter()){
			SumColor=SumColor+this->getcolor2(Inter,RayonCamera,l,rbmax);
		}
	}
	SumColor= SumColor/nrd;
	SumColor=SumColor.CorrectionGamma();
	return SumColor;
}


//Ray Scene::GenereRayon(int i,int j,Vector Camera,int W,int H,double alpha)
//{
//	double g_Pi = 3.14159265358979323846;
//	double x=j-W/2+0.5;
//	double y=i-H/2+0.5;
//	double z=-W/(2*tan(alpha/2));
//	Vector DirCam(x,y,z);
//	Objere Sun=Obj[lightindex];
//	Vector rd=Sun.randomtriplet();
//	double b1=rd.getX();
//	double b2=rd.getY();
//	double b3=0;
//	Vector B(b1,b2,b3);
//	double d=Camera.getZ();
//	Vector uprim=Camera+DirCam*d-B;
//	uprim.normalize();
//	Vector Cameraprim=B;
//	Ray RayonCamera(DirCam, Cameraprim);
//	return RayonCamera;
//}



//Vector Scene::getcolorAntiAliasing3(int i,int j,Vector Camera,int W,int H,double alpha,int rbmax,int nrd)
//{
//	Vector SumColor(0,0,0);
//	for(int i=0;i<nrd;i++){
//		Vector rdAA=Obj[1].randomtriplet();
//		Ray r=this->GenereRayon(i,j,Camera,W,H,alpha);
//		Vector Cam=r.centre();
//		Vector DirCam=r.direction()+rdAA;
//		Ray RayonCamera(DirCam,Cam);
//		Intersection Inter=this->intersect(RayonCamera);
//		Vector colorrd;
//		Light l=this->RandomLightGenerator(Inter);
//		if(Inter.getinter()){
//			SumColor=SumColor+this->getcolor2(Inter,l,rbmax);
//		}
//	}
//	SumColor= SumColor/nrd;
//	SumColor=SumColor.CorrectionGamma();
//	return SumColor;
//}







