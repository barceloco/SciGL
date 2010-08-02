// XXX XXX XXX     C O M P I L E   C O M M A N D     XXX XXX XXX
//  g++ 01_minimalistic.cpp -framework OpenGL -framework GLUT;
// XXX XXX XXX     C O M P I L E   C O M M A N D     XXX XXX XXX

#include <stdlib.h>
#include <math.h>
#include "scigl.h"
//#include "imglib.h"
int main(int argc, char** argv) {
	int height=50;
	int width=50;
	

	//double* hmap = (double*) malloc(iwidth*iheight*sizeof(double));
	double* hmap = (double*) malloc(width*height*sizeof(double));
	double h;
	int x;
	int y;
	for(x = 0; x < width; x++) {
		for(y = 0; y < height; y++) {
			h = 10.0*exp(-(x-30.)*(x-30.)/20.-(y-20.)*(y-20.)/40.);
			hmap[x*height+y]=h;
		}
	}
	
	plot (width, height, hmap);
	free (hmap);
	return 0;
}


