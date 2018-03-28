#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
//#include "TriangleIndices.h"
#include "Geometry.h"
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
#include <string>
#include <cstring>
#include <cstdio>
#include <map>


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
//TriangleIndices::TriangleIndices(int vtxi, int vtxj, int vtxk, int ni, int nj, int nk, int uvi, int uvj, int uvk):
//vtxi(vtxi), vtxj(vtxj), vtxk(vtxk), uvi(uvi), uvj(uvj), uvk(uvk), ni(ni), nj(nj), nk(nk)
//{}



//Constructeur
Geometry::Geometry() {};
Geometry::Geometry(const char* obj, double scaling, const Vector& offset) {
	readOBJ(obj);
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] = vertices[i] * scaling + offset;
	}
}
//Destructeur
Geometry::~Geometry(){}
//Methodes propres aux geometries
void Geometry::readOBJ(const char* obj) {
	char matfile[255];
	char grp[255];

	FILE* f;
	f = fopen(obj, "r");

	std::map<std::string, int> groupNames;
	int curGroup = -1;
	while (!feof(f)) {
		char line[255];
		if (!fgets(line, 255, f)) break;

		std::string linetrim(line);
		linetrim.erase(linetrim.find_last_not_of(" \r\t") + 1);
		strcpy(line, linetrim.c_str());

		if (line[0] == 'u' && line[1] == 's') {
			sscanf(line, "usemtl %[^\n]\n", grp);
			if (groupNames.find(std::string(grp)) != groupNames.end()) {
				curGroup = groupNames[std::string(grp)];
			}
			else {
				curGroup = groupNames.size();
				groupNames[std::string(grp)] = curGroup;
			}
		}
		if (line[0] == 'm' && line[1] == 't' && line[2] == 'l') {
			sscanf(line, "mtllib %[^\n]\n", matfile);
		}
		if (line[0] == 'v' && line[1] == ' ') {
			Vector vec;
			Vector col;
			if (sscanf(line, "v %lf %lf %lf %lf %lf %lf\n", &vec[0], &vec[2], &vec[1], &col[0], &col[1], &col[2]) == 6) {
				vertices.push_back(vec);
				vertexcolors.push_back(col);
			}
			else {
				sscanf(line, "v %lf %lf %lf\n", &vec[0], &vec[2], &vec[1]);  // helmet
																			 //vec[2] = -vec[2]; //car2
				vertices.push_back(vec);
			}
		}
		if (line[0] == 'v' && line[1] == 'n') {
			Vector vec;
			sscanf(line, "vn %lf %lf %lf\n", &vec[0], &vec[2], &vec[1]); //girl
			normals.push_back(vec);
		}
		if (line[0] == 'v' && line[1] == 't') {
			Vector vec;
			sscanf(line, "vt %lf %lf\n", &vec[0], &vec[1]);
			uvs.push_back(vec);
		}
		if (line[0] == 'f') {
			TriangleIndices t;
			int i0, i1, i2, i3;
			int j0, j1, j2, j3;
			int k0, k1, k2, k3;
			int nn;

			char* consumedline = line + 1;
			int offset;
			t.faceGroup = curGroup;
			nn = sscanf(consumedline, "%u/%u/%u %u/%u/%u %u/%u/%u%n", &i0, &j0, &k0, &i1, &j1, &k1, &i2, &j2, &k2, &offset);
			if (nn == 9) {
				if (i0 < 0) t.vtxi = vertices.size() + i0; else	t.vtxi = i0 - 1;
				if (i1 < 0) t.vtxj = vertices.size() + i1; else	t.vtxj = i1 - 1;
				if (i2 < 0) t.vtxk = vertices.size() + i2; else	t.vtxk = i2 - 1;
				if (j0 < 0) t.uvi = uvs.size() + j0; else	t.uvi = j0 - 1;
				if (j1 < 0) t.uvj = uvs.size() + j1; else	t.uvj = j1 - 1;
				if (j2 < 0) t.uvk = uvs.size() + j2; else	t.uvk = j2 - 1;
				if (k0 < 0) t.ni = normals.size() + k0; else	t.ni = k0 - 1;
				if (k1 < 0) t.nj = normals.size() + k1; else	t.nj = k1 - 1;
				if (k2 < 0) t.nk = normals.size() + k2; else	t.nk = k2 - 1;

				indices.push_back(t);
			}
			else {
				nn = sscanf(consumedline, "%u/%u %u/%u %u/%u%n", &i0, &j0, &i1, &j1, &i2, &j2, &offset);
				if (nn == 6) {
					if (i0 < 0) t.vtxi = vertices.size() + i0; else	t.vtxi = i0 - 1;
					if (i1 < 0) t.vtxj = vertices.size() + i1; else	t.vtxj = i1 - 1;
					if (i2 < 0) t.vtxk = vertices.size() + i2; else	t.vtxk = i2 - 1;
					if (j0 < 0) t.uvi = uvs.size() + j0; else	t.uvi = j0 - 1;
					if (j1 < 0) t.uvj = uvs.size() + j1; else	t.uvj = j1 - 1;
					if (j2 < 0) t.uvk = uvs.size() + j2; else	t.uvk = j2 - 1;
					indices.push_back(t);
				}
				else {
					nn = sscanf(consumedline, "%u %u %u%n", &i0, &i1, &i2, &offset);
					if (nn == 3) {
						if (i0 < 0) t.vtxi = vertices.size() + i0; else	t.vtxi = i0 - 1;
						if (i1 < 0) t.vtxj = vertices.size() + i1; else	t.vtxj = i1 - 1;
						if (i2 < 0) t.vtxk = vertices.size() + i2; else	t.vtxk = i2 - 1;
						indices.push_back(t);
					}
					else {
						nn = sscanf(consumedline, "%u//%u %u//%u %u//%u%n", &i0, &k0, &i1, &k1, &i2, &k2, &offset);
						if (i0 < 0) t.vtxi = vertices.size() + i0; else	t.vtxi = i0 - 1;
						if (i1 < 0) t.vtxj = vertices.size() + i1; else	t.vtxj = i1 - 1;
						if (i2 < 0) t.vtxk = vertices.size() + i2; else	t.vtxk = i2 - 1;
						if (k0 < 0) t.ni = normals.size() + k0; else	t.ni = k0 - 1;
						if (k1 < 0) t.nj = normals.size() + k1; else	t.nj = k1 - 1;
						if (k2 < 0) t.nk = normals.size() + k2; else	t.nk = k2 - 1;
						indices.push_back(t);
					}
				}
			}


			consumedline = consumedline + offset;

			while (true) {
				if (consumedline[0] == '\n') break;
				if (consumedline[0] == '\0') break;
				nn = sscanf(consumedline, "%u/%u/%u%n", &i3, &j3, &k3, &offset);
				TriangleIndices t2;
				t2.faceGroup = curGroup;
				if (nn == 3) {
					if (i0 < 0) t2.vtxi = vertices.size() + i0; else	t2.vtxi = i0 - 1;
					if (i2 < 0) t2.vtxj = vertices.size() + i2; else	t2.vtxj = i2 - 1;
					if (i3 < 0) t2.vtxk = vertices.size() + i3; else	t2.vtxk = i3 - 1;
					if (j0 < 0) t2.uvi = uvs.size() + j0; else	t2.uvi = j0 - 1;
					if (j2 < 0) t2.uvj = uvs.size() + j2; else	t2.uvj = j2 - 1;
					if (j3 < 0) t2.uvk = uvs.size() + j3; else	t2.uvk = j3 - 1;
					if (k0 < 0) t2.ni = normals.size() + k0; else	t2.ni = k0 - 1;
					if (k2 < 0) t2.nj = normals.size() + k2; else	t2.nj = k2 - 1;
					if (k3 < 0) t2.nk = normals.size() + k3; else	t2.nk = k3 - 1;
					indices.push_back(t2);
					consumedline = consumedline + offset;
					i2 = i3;
					j2 = j3;
					k2 = k3;
				}
				else {
					nn = sscanf(consumedline, "%u/%u%n", &i3, &j3, &offset);
					if (nn == 2) {
						if (i0 < 0) t2.vtxi = vertices.size() + i0; else	t2.vtxi = i0 - 1;
						if (i2 < 0) t2.vtxj = vertices.size() + i2; else	t2.vtxj = i2 - 1;
						if (i3 < 0) t2.vtxk = vertices.size() + i3; else	t2.vtxk = i3 - 1;
						if (j0 < 0) t2.uvi = uvs.size() + j0; else	t2.uvi = j0 - 1;
						if (j2 < 0) t2.uvj = uvs.size() + j2; else	t2.uvj = j2 - 1;
						if (j3 < 0) t2.uvk = uvs.size() + j3; else	t2.uvk = j3 - 1;
						consumedline = consumedline + offset;
						i2 = i3;
						j2 = j3;
						indices.push_back(t2);
					}
					else {
						nn = sscanf(consumedline, "%u//%u%n", &i3, &k3, &offset);
						if (nn == 2) {
							if (i0 < 0) t2.vtxi = vertices.size() + i0; else	t2.vtxi = i0 - 1;
							if (i2 < 0) t2.vtxj = vertices.size() + i2; else	t2.vtxj = i2 - 1;
							if (i3 < 0) t2.vtxk = vertices.size() + i3; else	t2.vtxk = i3 - 1;
							if (k0 < 0) t2.ni = normals.size() + k0; else	t2.ni = k0 - 1;
							if (k2 < 0) t2.nj = normals.size() + k2; else	t2.nj = k2 - 1;
							if (k3 < 0) t2.nk = normals.size() + k3; else	t2.nk = k3 - 1;
							consumedline = consumedline + offset;
							i2 = i3;
							k2 = k3;
							indices.push_back(t2);
						}
						else {
							nn = sscanf(consumedline, "%u%n", &i3, &offset);
							if (nn == 1) {
								if (i0 < 0) t2.vtxi = vertices.size() + i0; else	t2.vtxi = i0 - 1;
								if (i2 < 0) t2.vtxj = vertices.size() + i2; else	t2.vtxj = i2 - 1;
								if (i3 < 0) t2.vtxk = vertices.size() + i3; else	t2.vtxk = i3 - 1;
								consumedline = consumedline + offset;
								i2 = i3;
								indices.push_back(t2);
							}
							else {
								consumedline = consumedline + 1;
							}
						}
					}
				}
			}

		}


	}
	fclose(f);
}



void Geometry::add_texture(const char* filename) {
	textures.resize(textures.size() + 1);
	w.resize(w.size() + 1);
	h.resize(h.size() + 1);
	FILE* f;
	f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	w[w.size() - 1] = *(int*)&info[18]; // extract image height and width from header
	h[h.size() - 1] = *(int*)&info[22];
	int size = 3 * w[w.size() - 1] * h[h.size() - 1];
	textures[textures.size() - 1].resize(size); // allocate 3 bytes per pixel
	fread(&textures[textures.size() - 1][0], sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);
	for (int i = 0; i < size; i += 3) {
		std::swap(textures[textures.size() - 1][i], textures[textures.size() - 1][i + 2]);
	}
}



void Geometry::setBbox(){
	BB.setbmin(vertices[0]);
	BB.setbmax(vertices[0]);
	Vector bmin=BB.getbmin();
	Vector bmax=BB.getbmax();
	for(int i=0;i<vertices.size();i++){
		Vector XX=vertices[i];	
		bmin.setX(min(bmin.getX(),XX.getX()));
		bmin.setY(min(bmin.getY(),XX.getY()));
		bmin.setZ(min(bmin.getZ(),XX.getZ()));
		bmax.setX(max(bmax.getX(),XX.getX()));
		bmax.setY(max(bmax.getY(),XX.getY()));
		bmax.setZ(max(bmax.getZ(),XX.getZ()));
	}
	BB.setbmin(bmin);
	BB.setbmax(bmax);
}


void Geometry::setBvh(Bvh* noeud, int deb, int fin, int p, int taille){
	if(p>0){
		if(fin-deb>taille){
			noeud->indicedeb=deb;
			noeud->indicefin=fin;
			Bbox bb=this->buildMFBbox(deb, fin);
			noeud->box=bb;
			noeud->filsg= NULL;
			noeud->filsd= NULL;
			noeud->pr=0;
			Vector bmin=bb.getbmin();
			Vector bmax=bb.getbmax();
			Vector diag=bmax-bmin;
			int axis;
			if(diag.getX()>diag.getY() && diag.getX()>diag.getZ()){
				axis=0;
			}else if(diag.getY()>diag.getX() && diag.getY()>diag.getZ()){
				axis=1;
			}else{
				axis=2;
			}
			double pivot=bmin[axis]+diag[axis]*0.5;
			vector<TriangleIndices> indicesinf;
			vector<TriangleIndices> indicessup;
			for(int i=deb;i<fin;i++){
				TriangleIndices ti=indices[i];
				Vector A=vertices[indices[i].vtxi];
				Vector B=vertices[indices[i].vtxj];
				Vector C=vertices[indices[i].vtxk];
				double centre=max(A[axis],max(B[axis],C[axis]));
				if(centre<pivot){
					indicesinf.push_back(ti);
				}else{
					indicessup.push_back(ti);
				}
			}
			int indicepivot=indicesinf.size();
			for(int j=0; j<indicepivot; j++){
				indices[deb+j]=indicesinf[j];
			}
			for(int j=0; j<indicessup.size(); j++){
				indices[deb+indicepivot+j]=indicessup[j];
			}
			
			if(indicepivot<=0||indicepivot>=(fin-deb)){
				noeud->pr=1;
				return;
			}
			
			noeud->filsg=new Bvh();
			this->setBvh(noeud->filsg, deb,deb+indicepivot, p-1, taille);
		
			noeud->filsd=new Bvh();
			this->setBvh(noeud->filsd, deb+indicepivot, fin, p-1, taille);
		
		}else{
			noeud->indicedeb=deb;
			noeud->indicefin=fin;
			Bbox bb=this->buildMFBbox(deb, fin);
			noeud->box=bb;
			noeud->filsg= NULL;
			noeud->filsd= NULL;
			noeud->pr=1;
		}
	}else{
		noeud->indicedeb=deb;
		noeud->indicefin=fin;
		Bbox bb=this->buildMFBbox(deb, fin);
		noeud->box=bb;
		noeud->box=bb;
		noeud->filsg= NULL;
		noeud->filsd= NULL;
		noeud->pr=1;
	}
}

Bbox Geometry::buildMFBbox(int deb, int fin){
	Bbox bbb;
	bbb.setbmin(vertices[indices[deb].vtxi]);
	bbb.setbmax(vertices[indices[deb].vtxi]);
	Vector bmin=bbb.getbmin();
	Vector bmax=bbb.getbmax();
	for(int i=deb;i<fin;i++){
		Vector A=vertices[indices[i].vtxi];
		Vector B=vertices[indices[i].vtxj];
		Vector C=vertices[indices[i].vtxk];
		bmin=bmin.minimum(A);
		bmin=bmin.minimum(B);
		bmin=bmin.minimum(C);
		bmax=bmax.maximum(A);
		bmax=bmax.maximum(B);
		bmax=bmax.maximum(C);
	}
	bbb.setbmin(bmin);
	bbb.setbmax(bmax);
	return bbb;
}

Intersection Geometry::intersect(const Ray & r){
	Intersection Interbb=BV.intersect(r);
	if(!Interbb.getinter()){
		return Interbb;
	}
	vector<Bvh*> feuilles=Interbb.feuil;
	int geoindex=0;
	Vector Point;
	double mindist=numeric_limits<double>::infinity();
	Vector C=r.centre();
	for(int j=0; j<feuilles.size();j++){
		int debt=feuilles[j]->indicedeb;
		int fint=feuilles[j]->indicefin;
		for(int i=debt;i<fint;i++){
			Triangle tri(vertices[indices[i].vtxi],vertices[indices[i].vtxj],vertices[indices[i].vtxk]);
			Intersection Inter=tri.intersect(r);
			if(Inter.getinter()){
				Point=Inter.getptint();
				if(C.distance2(Point)<mindist){
					mindist=C.distance2(Point);
					geoindex=i;
				}
			}
		}
	}
	Triangle tri2(vertices[indices[geoindex].vtxi],vertices[indices[geoindex].vtxj],vertices[indices[geoindex].vtxk]);
	Intersection Interf = tri2.intersect(r);
	Interf.setgeoindex(geoindex);
	/*
	*/
	int id_tex=indices[geoindex].faceGroup;
	Vector barycentre = Interf.getbary();
	double u=barycentre.getX()*uvs[indices[geoindex].uvi].getX()+\
	barycentre.getY()*uvs[indices[geoindex].uvj].getX()+\
	barycentre.getZ()*uvs[indices[geoindex].uvk].getX();
	double v=barycentre.getX()*uvs[indices[geoindex].uvi].getY()+\
	barycentre.getY()*uvs[indices[geoindex].uvj].getY()+\
	barycentre.getZ()*uvs[indices[geoindex].uvk].getY();
	
	
	int i=v*(h[id_tex]-1);
	int j=u*(w[id_tex]-1);
	double rouge=static_cast<double>(textures[id_tex][(i*w[id_tex]+j)*3+0])/255;
	double vert=static_cast<double>(textures[id_tex][(i*w[id_tex]+j)*3+1])/255;
	double bleu=static_cast<double>(textures[id_tex][(i*w[id_tex]+j)*3+2])/255;
	Vector colorInter(rouge, vert, bleu);
	Interf.setcolor(colorInter);
	return Interf;
}

Vector Geometry::normale(const Intersection & I)
{
	int geoindex=I.getgeoindex();
	Vector bary=I.getbary();
	Vector n1=normals[indices[geoindex].ni];
	Vector n2=normals[indices[geoindex].nj];
	Vector n3=normals[indices[geoindex].nk];
	Vector N=n1*bary.getX()+n2*bary.getY()+n3*bary.getZ();
//	N=N*(-1);
	return N;
}

Vector Geometry::tangente1(const Intersection & I)
{
	Vector n=this->normale(I);
	Vector randomvector=this->tripletAleatoire();
	Vector tan =  n.prodvect(randomvector);
	return tan;
}

Vector Geometry::incidence(const Light & l,const Intersection & I)
{
	Ray r=l.rayon();
	Vector P=r.centre();
	Vector V= I.getptint();
	Vector i=P-V;
	return i;
}


Vector Geometry::randomreflect(const Light & l,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector t1=this->tangente1(I);
	Vector t2=N.prodvect(t1);
	t2.normalize();
	double g_Pi = 3.14159265358979323846;
	Vector randomvector=this->tripletAleatoire();
	double r1=randomvector.getX();
	double r2=randomvector.getY();
	double Rq=sqrt(1-r2);
	double x=cos(2*g_Pi*r1)*Rq;
	double y=sin(2*g_Pi*r1)*Rq;
	double z=sqrt(r2);
	Vector r=t1*x+t2*y+N*z;
	r.normalize();
	return r;
}


Vector Geometry::normale2(const Ray & r, const Intersection & I)
{
	int geoindex=I.getgeoindex();
	Vector bary=I.getbary();
	Vector n1=normals[indices[geoindex].ni];
	Vector n2=normals[indices[geoindex].nj];
	Vector n3=normals[indices[geoindex].nk];
	Vector N=n1*bary.getX()+n2*bary.getY()+n3*bary.getZ();
//	N=N*(-1);
	return N;
}
Vector Geometry::incidence2(const Ray & r,const Intersection & I)
{
	Vector P=r.centre();
	Vector V= I.getptint();
	Vector i=P-V;
	return i;
}
Vector Geometry::reflexion2(const Ray & r,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector i=this->incidence2(r,I);
	i.normalize();
	i=i*(-1);
	Vector ref=i-N*i.dot(N)*2;
	ref.normalize();
	return ref;
}
Vector Geometry::randomreflect2(const Ray & r,const Intersection & I)
{
	Vector N=this->normale(I);
	Vector t1=this->tangente1(I);
	Vector t2=N.prodvect(t1);
	t2.normalize();
	double g_Pi = 3.14159265358979323846;
	Vector randomvector=this->tripletAleatoire();
	double r1=randomvector.getX();
	double r2=randomvector.getY();
	double Rq=sqrt(1-r2);
	double x=cos(2*g_Pi*r1)*Rq;
	double y=sin(2*g_Pi*r1)*Rq;
	double z=sqrt(r2);
	Vector ref=t1*x+t2*y+N*z;
	ref.normalize();
	return ref;
}

Vector Geometry::transmission2(const Ray & r,const Intersection & I, double nair)
{
	Vector P=I.getptint();
	Vector N=this->normale(I);
	Vector i=r.direction();
	i.normalize();
	double ns=this->getindice();
	double n1;
	double n2;
	double k=i.dot(N);
	if(k>0){
		N=N*(-1);
		n1=ns;
		n2=nair;
	}else{
		n1=nair;
		n2=ns;
	}
	double a=1-(n1/n2)*(n1/n2)*(1-k*k);
	Vector t;
	if(a>0){
		t= i*n1/n2-N*((n1/n2)*k+sqrt(a));
		t.normalize();
		return t;
	}else{
		t=reflexion2(r,I);
		t.normalize();
		return t*(-1);
	}
}


Vector Geometry::rdPointOnSurface(const Intersection & I)
{
	int geoindex=I.getgeoindex();
	Vector A=vertices[indices[geoindex].vtxi];
	Vector B=vertices[indices[geoindex].vtxj];
	Vector C=vertices[indices[geoindex].vtxk];
	Vector AB=B-A;
	Vector AC=C-A;
	Vector randomvector=this->tripletAleatoire();
	Vector Pprim=A+AB*randomvector.getX()+AC*randomvector.getY();	
	return Pprim;
	
}
