#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
using namespace std;

#include "Vector.h"
#include "Ray.h"
#include "Light.h"
#include "Intersection.h"
#include "Sphere.h"
#include "Scene.h"
#include "Objet.h"
#include "Triangle.h"
//#include "TriangleIndices.h"
#include "Geometry.h"
#include "Bbox.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#ifdef _OPENMP
#include <omp.h>
#endif


void save_image(const char* filename, const unsigned char* tableau,int w,int h){  
    FILE *f;
 
    int filesize = 54 + 3 * w*h;  
 
    unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
    unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
    unsigned char bmppad[3] = { 0,0,0 };
 
    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);
 
    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);
 
    f = fopen(filename, "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    unsigned char *row = new unsigned char[w * 3];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++) {
            row[j * 3] = tableau[(w*(h - i - 1) * 3) + j * 3+2];
            row[j * 3+1] = tableau[(w*(h - i - 1) * 3) + j * 3+1];
            row[j * 3+2] = tableau[(w*(h - i - 1) * 3) + j * 3];
        }
        fwrite(row, 3, w, f);
        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
    }
    fclose(f);
    delete[] row;
}



int main() 
{
	#ifdef _OPENMP
	int nbThreads=omp_get_max_threads();
	cout<<"Nombre de threads utilisés : "<<nbThreads<<endl;
	omp_set_num_threads(nbThreads);
	#endif
	
	int start_s=clock();
	
	double g_Pi = 3.14159265358979323846;
	int W = 1024;
    int H = 1024;
	double alpha=60*g_Pi/180;
    vector<unsigned char> img(W*H * 3, 0);
    img[(10 * W + 50)*3] = 255; // pixel at (x, y) = (50, 10) is red
    
    
	// Camera
	Vector Camera(0,0,55);
	
	
	//Souce de lumière
	double Intensity=100000000;
	Vector LL(-10,20,40);
//	Vector LL(20,0,40);
	Vector Dirlum(0,0,0);
	bool within=false;
	Ray rayonlum(Dirlum,LL);
	Light L(rayonlum, Intensity, within);
	
	
	//Lumiere Spherique
	double Emissivite=5000000000;
	double Rlum=5;
	Vector colorlum(1.0,1.0,1.0);
	double nlum=1.0;
	int MateriauLumineaux=4;
	Sphere Slum(LL,Rlum,colorlum,MateriauLumineaux,nlum);
	Slum.setE(Emissivite);
	
	
	
	
	//Définition sphères au centre
	Vector C0(20,10,0);
	Vector color0(0.7,0.7,0.7);
	double R0=10;
	int platre=1;
	double nsph=0.85;
	Sphere S0(C0,R0,color0,platre,nsph);
	Vector C01(-20,20,0);
	Vector color01(0.2,0.2,0.2);
	Sphere S01(C01,R0,color01,platre,nsph);
	Vector C02(0,20,0);
	Vector color02(0.7,0.7,0.7);
	Sphere S02(C02,R0,color02,platre,nsph);
	
	int mirroir=2;
	int verre=3;
	S0.setmateriau(verre);
	double nverre=3.5;
	S0.setindice(nverre);
	S01.setmateriau(mirroir);
	
	
//	Vector Cet(0,0,0);
//	Sphere Set(Cet,R0,color0,platre,nsph);
	

	//Definition Triangle
//	Triangle T1(Vector(-10,-10,0),Vector(10,-10,0), Vector(-10,10,0));
//	T1.setmateriau(platre);
//	T1.setindice(nsph);
//	T1.setcolor(Vector(1,0,0));
	

	
	cout<<"Avant Geometry"<<nbThreads<<endl;
	//Definition Geometrie
	Geometry g1("girl.obj",10,Vector(0,-10,0));
	g1.add_texture("textures/visage.bmp");
	g1.add_texture("textures/cheveux.bmp");
	g1.add_texture("textures/corps.bmp");
    g1.add_texture("textures/pantalon.bmp");
    g1.add_texture("textures/accessoires.bmp");
    g1.add_texture("textures/mains.bmp");
	g1.setmateriau(platre);
	g1.setcolor(color0);
	Bvh BV=g1.BV;
	
	vector<TriangleIndices> indices=g1.indices;
	g1.setBvh(&BV,0,indices.size(),12, 3);
	g1.BV=BV;
		
	cout<<"Apres Geometry"<<nbThreads<<endl;
	
	
	/*
	Définition du décor
	*/
	
	Vector C1(0,1000,0);
	double R1=940;
	Vector color1(0.9,0.2,0.2);
	Sphere S1(C1,R1,color1,platre,nsph);
	Vector C2(0,-1000,0);
	double R2=990;
	Vector color2(0.2,0.2,0.9);
	Sphere S2(C2,R2,color2,platre,nsph);
	Vector C3(0,0,1000);
	double R3=940;
	Vector color3(0.9,0.2,0.9);
	Sphere S3(C3,R3,color3,platre,nsph);
	Vector C4(0,0,-1000);
	double R4=940;
	Vector color4(0.2,0.9,0.2);
	Sphere S4(C4,R4,color4,platre,nsph);
	Vector C5(-1000,0,0);
	double R5=940;
	Vector color5(0.9,0.9,0.9);
	Sphere S5(C5,R5,color5,platre,nsph);
	Vector C6(1000,0,0);
	double R6=940;
	Vector color6(0.9,0.9,0.9);
	Sphere S6(C6,R6,color6,platre,nsph);


	/*
	Initialisation de la scène
	*/
	vector<Objet*> Sp;
	Sp.push_back(&Slum);
	Sp.push_back(&S1);
	Sp.push_back(&S2);
	Sp.push_back(&S3);
	Sp.push_back(&S4);
	Sp.push_back(&S5);
	Sp.push_back(&S6);
	Sp.push_back(&S0);
	Sp.push_back(&S01);
	Sp.push_back(&S02);
//	Sp.push_back(&T1);
	Sp.push_back(&g1);
//	Sp.push_back(&Set);
	Scene Sc(Sp);
	Sc.setlightindex(0);
	

	/*
	Initialisation d'éléments de rebond
	*/
	int rbmax=5; // Nombre de rebonds maximal
	int nrd=20; // Nombre de rayons par pixel
	//Parcours de l'ensemble des pixels
	
	#pragma omp parallel for schedule(dynamic)
	for (int i=0;i<H;i++){
		for (int j=0;j<W;j++){
			double x=j-W/2+0.5;
			double y=i-H/2+0.5;
			double z=-W/(2*tan(alpha/2));
			Vector DirCam(x,y,z);
			Ray RayonCamera(DirCam,Camera);
			if(j==W/2){
				cout<<"Fin de ligne  : "<<i<<endl;
			}
			Vector colorimg=Sc.getcolorAntiAliasing2(RayonCamera, rbmax,nrd);
			img[((H-i-1)*W+j)*3]=colorimg.getX();
			img[((H-i-1)*W+j)*3+1]=colorimg.getY();
			img[((H-i-1)*W+j)*3+2]=colorimg.getZ();
					


		}
	}
	
	
	
    save_image("test.bmp", &img[0], W, H);
    
    int stop_s=clock();
	cout << "temps : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< " secondes" << endl;
    
    return 0;
}




