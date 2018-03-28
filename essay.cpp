#include <iostream> 
using namespace std;
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "Objet.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Light.h"
int main(){

	//Variables
	
	
    // Test methodes sur les objets
    cout << endl;
    cout <<"=========================="<< endl;
    cout <<"Début test méthodes Objets"<< endl;
    cout <<"=========================="<< endl;
    cout << endl;
    
    
    cout << endl;
    cout <<"=========================="<< endl;
    cout <<" Fin test méthodes Objets "<< endl;
    cout <<"=========================="<< endl;
    cout << endl;
    
    // Test méthodes Sphères
    cout << endl;
    cout <<"==========================="<< endl;
    cout <<"Début test méthodes Sphères"<< endl;
    cout <<"==========================="<< endl;
    cout << endl;
    
    double Intensity=1000;
    
    Vector O1(0,-1,10);
    double R1=9;
    Vector color1(1,0,1);
    int m1=2;
    double n1=1.3;
    Sphere S1(O1,R1,color1,m1,n1);
    
    Vector O2(-1,0,9);
    S1.setcentre(O2);
    cout << "Sphere Centre :(expected : (-1,0,9))" << endl;
    S1.getcentre().afficher();
    double r2=10;
    S1.setrayon(r2);
    cout << "Sphere Rayon :(expected : 10)"<<S1.getrayon() << endl;
    Vector color2(0,1,1);
    S1.setcolor(color2);
    cout << "Sphere Color :(expected : (0,1,1))" << endl;
    S1.getcolor().afficher();
    int m2=3;
    S1.setmateriau(m2);
    cout << "Sphere materiau :(expected : 3)"<< S1.getmateriau() << endl;
	double n2=1.2;
    S1.setindice(n2);
    cout << "Sphere materiau :(expected : 1.2)"<< S1.getindice() << endl;
    cout << endl;
    cout << endl;
    
    
    
    Vector UU(-1,0,0);
    Vector Centre;
    Ray rr(UU,Centre);
    Intersection ii= S1.intersect(rr);
    cout << "Intersection avec S1 :(expected : 1)"<< ii.getinter() << endl;
    cout << "Intersection avec S1 Point :(expected : (-5.36,0,0))" << endl;
    ii.getptint().afficher();
    cout << "Intersection Color :(expected : (0,1,1))" << endl;
    ii.getcolor().afficher();
    cout << "Intersection index :(expected : 0)"<< ii.getindex() << endl;
    
    
    Vector P=ii.getptint();
    Vector N=S1.normale(P);
    cout <<"Normale de S1 au point (-5.36,0,0):(expected:(-0.436,0,-0.9))" << endl;
    N.afficher();
    
    Vector tan1=S1.tangente1(P);
    cout <<"tangente1 de S1 au point (-5.36,0,0):(expected:(0.9,0,-0.436))" << endl;
    tan1.afficher();
    cout <<"test de tangence normale.tangente1 :(expected:0)"<<tan1.dot(N) << endl;
    
    
    Vector tan2=N.prodvect(tan1);
    cout <<"tangente2 de S1 au point (-5.36,0,0):(expected:(0,-1,0))" << endl;
    tan2.afficher();
    cout <<"test de tangence normale.tangente2 :(expected:0 ) "<<tan2.dot(N) << endl;
    cout <<"test de tangence tangente1.tangente2 :(expected: 0) "<<tan2.dot(tan1) << endl;
    
    
    Vector Centre2(-10,-10,-10);
    Vector dir(1,1,1);
    Ray rl(dir,Centre2);
    Light lum(rl,Intensity,false);
    Vector inci=S1.incidence(lum, ii);
    cout <<"Vecteur incident de S1 au point (-5.36,0,0):(expected:(4.64,10,10))" << endl;
    inci.afficher();
    cout << endl;
    
    Vector refl=S1.reflexion(lum, ii);
    cout <<"Vecteur reflechi de S1 au point (-5.36,0,0):(expected:(?,?,?))" << endl;
    refl.afficher();
    cout << endl;
    
    double nair=1;
    Vector trans=S1.transmission(lum, ii, nair);
    cout <<"Vecteur transmis de S1 au point (-5.36,0,0):(expected:(?,?,?))" << endl;
    trans.afficher();
    cout << endl;
    
    Vector rd1=S1.randomtriplet();
    cout <<"Vecteur triplet Gaussien" << endl;
    rd1.afficher();
    cout << endl;


	Vector rd2=S1.tripletAleatoire();
    cout <<"Vecteur triplet Unioforme" << endl;
    rd2.afficher();
    cout << endl;
    
    Vector rd3=S1.tripletAleatoire();
    cout <<"Vecteur triplet Unioforme(encore)" << endl;
    rd3.afficher();
    cout << endl;
    
    
	cout << endl;
    cout <<"==========================="<< endl;
    cout <<" Fin test méthodes Sphères "<< endl;
    cout <<"==========================="<< endl;
    cout << endl;
    
    // Test methodes sur les Triangles
    cout << endl;
    cout <<"============================"<< endl;
    cout <<"Début test méthodes Triangle"<< endl;
    cout <<"============================"<< endl;
    cout << endl;
    
    Triangle T1(Vector(-3,-10,-10),Vector(-3,10,-10), Vector(-3,0,10));
    cout << "T1 Point A:(expected : (-3,-10,-10))" << endl;
    T1.getA().afficher();
    cout << "T1 Point B:(expected : (-3,10,-10))" << endl;
    T1.getB().afficher();
    cout << "T1 Point C:(expected : (-3,0,10))" << endl;
    T1.getC().afficher();
    
    T1.setcolor(color2);
    cout << "Triangle Color :(expected : (0,1,1))" << endl;
    T1.getcolor().afficher();
    
    
    T1.setmateriau(m2);
    cout << "Triangle materiau T1 :(expected : 3)"<< T1.getmateriau() << endl;
    T1.setindice(n2);
    cout << "Triangle materiau T1 :(expected : 1.2)"<< T1.getindice() << endl;
    cout << endl;


	Intersection iii= T1.intersect(rr);
    
    cout << "Intersection avec T1 :(expected : 1)"<< iii.getinter() << endl;
    cout << "Intersection avec T1 Point :(expected : (-3,0,0)" << endl;
    iii.getptint().afficher();
    cout << "Intersection Color T1:(expected : (0,1,1))" << endl;
    iii.getcolor().afficher();
    cout << "Intersection index T1:(expected : 0)"<< iii.getindex() << endl;
    
    
    
    Triangle T2(Vector(-3,-10,-10),Vector(-3,10,-10), Vector(-3,0,-1));
    cout << "T2 Point A:(expected : (-3,-10,-10))" << endl;
    T2.getA().afficher();
    cout << "T2 Point B:(expected : (-3,10,-10))" << endl;
    T2.getB().afficher();
    cout << "T2 Point C:(expected : (-3,0,-1))" << endl;
    T2.getC().afficher();
    
    T2.setcolor(Vector(0.1,0,0.1));
    cout << "Triangle T2 Color :(expected : (0.1,0,0.1))" << endl;
    T1.getcolor().afficher();
    
    
    T1.setmateriau(4);
    cout << "Triangle materiau T2:(expected : 4)"<< T1.getmateriau() << endl;
    T1.setindice(0.9);
    cout << "Triangle materiau T2:(expected : 0.9)"<< T1.getindice() << endl;
    cout << endl;


	Intersection iv= T2.intersect(rr);
    
    cout << "Intersection avec T2 :(expected : 0)"<< iv.getinter() << endl;
    cout << "Intersection avec T2 Point :(expected : (-3,0,0)" << endl;
    iv.getptint().afficher();
    cout << "Intersection Color T2:(expected : (0.1,0,0.1))" << endl;
    iv.getcolor().afficher();
    cout << "Intersection index T2:(expected : 0)"<< iv.getindex() << endl;
    
    
    
    cout << endl;
    cout <<"============================"<< endl;
    cout <<" Fin test méthodes Triangle "<< endl;
    cout <<"============================"<< endl;
    cout << endl;
    
    return 0;
}

