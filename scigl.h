#ifndef SCIGL_H_INCLUDED
#define SCIGL_H_INCLUDED

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* // {{{
class heightmap
{
	private:
		int NbrOfPointsX, NbrOfPointsY;				// Number of gridpoints in X and Y direction
		int NbrOfFrames;							// Number of available Frames:
													//           1  for a single real-valued frame
													//           5  for a single complex frame
													//           N  for a real-valued movie
													//          5N  for a complex movie
		float*** hmap;								// Array storing heights: hmap[frame_id][x_id][y_id]
		float Xmin, Xmax;							// Range in direction X. Default: [0, NbrOfPointsX]
		float Ymin, Ymax;							// Range in direction Y. Default: [0, NbrOfPointsY]
		float Zmin, Zmax;							// Range in direction Z. Default: [min(hmap), max(hmap)]
		int WindowWidth, WindowHeight;				// Width and height of the graphics window;
		char* WindowTitle;							// Title (Identifier) of the graphics window.
		
		
		void showhelp(void);						// Text output displaying the controls of SciGL in graphics mode
		void showspecifichelp(void);				// Text output displaying the child-specific controls of SciGL in graphics mode
	
	public:
		heightmap(int nx, int ny, double* hm);		// Constructor. Initializes the class
													// nx	: Number of gridpoints in direction x
													// ny	: Number of gridpoints in direction y
													// type	: Type of this 3dmap
													// 			0	Real-valued 3dmap single frame
													// 			1	Complex-valued 3dmap single frame
													// 			2	Real-valued 3dmap movie
													// 			3	Complex-valued 3dmap movie
		~heightmap(void);							// Destructor. Terminates the class
		void state(void);							// Shows the internal state (private variables) of the class
};
// }}} */		

void plot(int maxx, int maxy, float*inputarray);
void plotcomplex(int maxx, int maxy, float*inputarray);
void plotmovie(int NbrOfFrames, int maxx, int maxy, float*inputarray);
void plotcomplexmovie(int NbrOfFrames, int maxx, int maxy, float*inputarray);

void plot(int maxx, int maxy, double*inputarray);
void plotcomplex(int maxx, int maxy, double*inputarray);
void plotmovie(int NbrOfFrames, int maxx, int maxy, double*inputarray);
void plotcomplexmovie(int NbrOfFrames, int maxx, int maxy, double*inputarray);

void plotcomplexfloatmovie(char* filename);

#endif
