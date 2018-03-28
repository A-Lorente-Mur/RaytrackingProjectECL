program : main

main : main.cpp Vector.h Ray.h Light.h Intersection.h Objet.h Sphere.h Triangle.h Scene.h Bbox.h Bvh.h Geometry.h
	g++ -std=c++11 -O3 -w main.cpp -o main -lm -fopenmp Vector.cpp Ray.cpp Light.cpp Intersection.cpp Objet.cpp Sphere.cpp Triangle.cpp Scene.cpp Bbox.cpp Bvh.cpp Geometry.cpp
	
essay : essay.cpp Vector.h Ray.h Light.h Intersection.h Objet.h Sphere.h Triangle.h
	g++ -std=c++11 -O0 -g -w essay.cpp -o essay -lm -fopenmp Vector.cpp Ray.cpp Light.cpp Intersection.cpp Objet.cpp Sphere.cpp Triangle.cpp
	
debug : main.cpp Vector.h Ray.h Light.h Intersection.h Sphere.h Scene.h
	gdb -tui ./main

debugE : essay.cpp Vector.h Ray.h Light.h Intersection.h Objet.h Sphere.h Triangle.h
	gdb -tui ./essay
	
