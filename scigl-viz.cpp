// XXX XXX XXX     C O M P I L E   C O M M A N D     XXX XXX XXX
//  g++ 01_minimalistic.cpp -framework OpenGL -framework GLUT;
// XXX XXX XXX     C O M P I L E   C O M M A N D     XXX XXX XXX

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "scigl.h"
using namespace std;
//#include "imglib.h"
int main(int argc, char** argv) {
//	heightmap* hm;
	//int ChooseFigure=4;
	int ChooseFigure=2;
	
	int height;
	int width;
	height=500;
	width=500;

	int nbrofframes;
	nbrofframes=50;

	double h;
	double h1,h2, hx;
	//double* hmap = (double*) malloc(iwidth*iheight*sizeof(double));
	double *hmap;
	double *hmapcomplex;
	double *hmapmovie;
	double *hmapcomplexmovie;
	switch (ChooseFigure)
	{
	case 0:
	hmap = (double*) malloc(width*height*sizeof(double));
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
	//		h = 10.0*exp(-(x-30.)*(x-30.)/20.-(y-20.)*(y-20.)/40.);
	//		h += 10.0*exp(-(x-70.)*(x-70.)/65.-(y-60.)*(y-60.)/25.);
	//		hmap[x*height+y]=h+sin(0.3*(x-45)*(y-45));
			h = 10.0*exp(-(x-200.)*(x-200.)/800.-(y-170.)*(y-170.)/600.);
			h += 10.0*exp(-(x-335.)*(x-335.)/1295.-(y-370.)*(y-370.)/995.);
			hmap[x*height+y]=h;
			hmap[x*height+y]+=sin(0.001*(x-250)*(y-250));
			//hmap[x*height+y]+=100.*sin(0.3*(x-250))+100.*cos(0.5*(y-250));
			hmap[x*height+y]+=sin(0.2*(x-250))+cos(0.15*(y-250));
			hmap[x*height+y]*=10.0;
		}
	}
	plot(height, width, hmap);
	break;
	case 1:
	hmapcomplex = (double*) malloc(2*width*height*sizeof(double));
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			// z = exp(x+iy) = exp(x)*exp(iy) = exp(x)*(cos(y) + i*sin(y))
			h1 = exp(50./20.*((double)(x-width/2))/((double) width))*cos(50.*((double)(y-height/2))/((double)height));
			h2 = exp(50./20.*((double)(x-width/2))/((double) width))*sin(50.*((double)(y-height/2))/((double)height));
			hmapcomplex[2*(x*height+y)]   = h1;
			hmapcomplex[2*(x*height+y)+1] = h2;
			hx = h1*h1+h2*h2; 
			//cout << hx << " " ;
		}
		//cout << endl;
	}
	plotcomplex(height, width, hmapcomplex);
	break;
	case 2:
	hmapmovie = (double*) malloc(nbrofframes*width*height*sizeof(double));
	for (int f=0; f<nbrofframes; f++)
	{
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < height; y++) {
				h = 10.0*exp(-(x-200.)*(x-200.)/800.-(y-170.)*(y-170.)/600.);
				h += 10.0*exp(-(x-335.)*(x-335.)/1295.-(y-370.)*(y-370.)/995.);
				//h +=sin(0.001*(x-250)*(y-250)-((double)f)/((double)nbrofframes)*2*3.14159);
				h +=2*sin(0.001*(x-250)*(y-250));
				h +=sin(0.2*(x-250)-((double)f)/((double)nbrofframes)*2*3.14159)+cos(0.15*(y-250));
				//h +=sin(0.2*(x-250))+cos(0.15*(y-250));
				h *=10.0;
				hmapmovie[f*height*width+x*height+y]=h;
			}
		}
	}
	plotmovie(nbrofframes, height, width, hmapmovie);
	break;
	case 3:
	hmapcomplexmovie = (double*) malloc(nbrofframes*2*width*height*sizeof(double));
	for (int f=0; f<nbrofframes; f++)
	{
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < height; y++) {
				// z = exp(x+iy) = exp(x)*exp(iy) = exp(x)*(cos(y) + i*sin(y))
				h1 = exp(50./20.*((double)(x-width/2))/((double) width))*cos(50.*((double)(y-height/2))/((double)height)-((double)f)/((double)nbrofframes)*2*3.14159);
				h2 = exp(50./20.*((double)(x-width/2))/((double) width))*sin(50.*((double)(y-height/2))/((double)height)-((double)f)/((double)nbrofframes)*2*3.14159);
				hmapcomplexmovie[f*2*height*width+2*(x*height+y)]   = h1;
				hmapcomplexmovie[f*2*height*width+2*(x*height+y)+1] = h2;
				hx = h1*h1+h2*h2; 
				//cout << hx << " " ;
			}
			//cout << endl;
		}
	}
	plotcomplexmovie(nbrofframes, height, width, hmapcomplexmovie);
	break;
	case 4:
	if (argc==2) plotcomplexfloatmovie(argv[1]);
	}
	
	//plot(50,50, hmap);
	//free (hmap);
	//free (hmapcomplex);
	//free (hmapmovie);
//	free (hm);
	return 0;
}


