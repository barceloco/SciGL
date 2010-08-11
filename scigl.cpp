#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "scigl.h"

using namespace std;
#define sqr(a) (a)*(a)

// Global Variables and auxiliary functions {{{
float scigl_Xmin;
float scigl_Xmax;
float scigl_Ymin;
float scigl_Ymax;
float scigl_Zmin;
float scigl_Zmax;
float scigl_Zminre;
float scigl_Zmaxre;
float scigl_Zminim;
float scigl_Zmaxim;
float scigl_Zminnorm;
float scigl_Zmaxnorm;
float scigl_Zminphase;
float scigl_Zmaxphase;
float scigl_Zminnorm2;
float scigl_Zmaxnorm2;
float scigl_zoomfactor;
float scigl_scaleX;
float scigl_scaleY;
float scigl_scaleZ;
float scigl_translateX;
float scigl_translateY;
float scigl_translateZ;
float scigl_angleHorizontal;
float scigl_angleVertical;
float scigl_RotationCenterX;
float scigl_RotationCenterY;
float scigl_RotationCenterZ;
float scigl_ColorPrefix;

char *scigl_WindowTitle;

int scigl_IsComplex;
int scigl_IsMovie;
int scigl_PlayMovie;
int scigl_CurrentFrame;
int scigl_NbrOfFrames;
int scigl_NbrOfPointsX;
int scigl_NbrOfPointsY;
int scigl_WindowWidth;
int scigl_WindowHeight;
int scigl_WindowTimer;
int scigl_ShowWireframe;
int scigl_ShowAxis;
int scigl_NormalizeZscaling;
int scigl_dynZoomfactor;
int scigl_dynScaleX;
int scigl_dynScaleY;
int scigl_dynScaleZ;
int scigl_dynTranslateX;
int scigl_dynTranslateY;
int scigl_dynTranslateZ;
int scigl_dynAngleHorizontal;
int scigl_dynAngleVertical;
int scigl_dynColorPrefix;
int scigl_MouseButton;
int scigl_OldMousePosX;
int scigl_OldMousePosY;

float* scigl_heightmap;
float* scigl_heightmapre;
float* scigl_heightmapim;
float* scigl_heightmapnorm;
float* scigl_heightmapphase;
float* scigl_heightmapnorm2;
float** scigl_heightmapmovie;
float** scigl_heightmapremovie;
float** scigl_heightmapimmovie;
float** scigl_heightmapnormmovie;
float** scigl_heightmapphasemovie;
float** scigl_heightmapnorm2movie;

void scigl_InitDefaultVariables(int maxx, int maxy);
void scigl_DefaultViewingParameters(void);
void scigl_ImportMap(float* inputarray);
void scigl_loadheightmap(int mapid);
void scigl_nextframe(void);
void scigl_ShowHelp(void);
void scigl_startGLUT(void);
void scigl_DisplayFunc(void);
void scigl_KeyboardFunc(unsigned char key, int ScreenPosX, int ScreenPosY);
void scigl_SpecialFunc(int key, int ScreenPosX, int ScreenPosY);
void scigl_MouseFunc(int button, int state, int ScreenPosX, int ScreenPosY);
void scigl_MotionFunc(int ScreenPosX, int ScreenPosY);
void scigl_ReshapeFunc(int NewWidth, int NewHeight);
void scigl_TimerFunc(int value);
void tbc_drawAxis(void);
// }}}

/*heightmap::heightmap(int nx, int ny, double* hmin) // {{{
{
	if (nx>0)
	{
		NbrOfPointsX = nx;
		Xmin = (float) 0;
		Xmax = (float) NbrOfPointsX;
	} else {
		cerr << "FATAL ERROR in heightmap: ";
		cerr << "constructor illdefined." << endl;
		cerr << "First argument needs to be greater than zero." << endl;
		exit(1);
	}
	if (ny>0)
	{
		NbrOfPointsY = ny;
		Ymin = (float) 0;
		Ymax = (float) NbrOfPointsY;
	} else {
		cerr << "FATAL ERROR in heightmap: ";
		cerr << "constructor illdefined." << endl;
		cerr << "Second argument needs to be greater than zero." << endl;
		exit(1);
	}
	hmap = NULL;
	NbrOfFrames=0;
	WindowWidth=1200;
	WindowHeight=800;
	WindowTitle = new char[100];
	strcpy(WindowTitle, "libSciGL - version 0.1 beta");
	scigl_WindowTimer			= 25;
	scigl_zoomfactor			= 1.0;
	scigl_scaleX				= 1.0;
	scigl_scaleY				= 1.0;
	scigl_scaleZ				= 1.0;
	scigl_translateX			= 0.0;
	scigl_translY				= 0.0;
	scigl_translZ				= 0.0;
	scigl_angleHorizontal		= 0.0;
	scigl_angleVertical 		= 0.0;
	scigl_ColorPrefix			= 1.0;
	scigl_ShowRenderedScene		= 1;
	scigl_ShowAxis				= 1;
	scigl_dynZoomfactor			= 0;
	scigl_dynScaleX				= 0;
	scigl_dynScaleY				= 0;
	scigl_dynScaleZ				= 0;
	scigl_dynTranslateX			= 0;
	scigl_dynTranslateY			= 0;
	scigl_dynTranslateZ			= 0;
	scigl_dynAngleHorizontal	= 0;
	scigl_dynAngleVertical 		= 0;
	scigl_dynColorPrefix		= 0;
}

heightmap::~heightmap(void)
{
	if (hmap != NULL){
		for (int i=0; i<NbrOfFrames; i++)
		{
			for (int j=0; j<NbrOfPointsX; j++)
			{
				delete [] hmap[i][j];
			}
			delete [] hmap[i];
		}
		delete [] hmap;
	}
}
void heightmap::state(void)
{
	cout << "NbrOfPointsX = " << NbrOfPointsX << endl;
	cout << "NbrOfPointsY = " << NbrOfPointsY << endl;
	cout << "NbrOfFrames  = " << NbrOfFrames << endl;
	cout << "hmap[][][]   = ";
	if (hmap!=NULL) cout << "{defined}"; else cout << "{not defined}";
	cout << endl;
	cout << "Xmin         = " << Xmin << endl;
	cout << "Xmax         = " << Xmax << endl;
	cout << "Ymin         = " << Ymin << endl;
	cout << "Ymax         = " << Ymax << endl;
	cout << "Zmin         = " << Zmin << endl;
	cout << "Zmax         = " << Zmax << endl;
	cout << "WindowWidth  = " << WindowWidth << " pixels." << endl;
	cout << "WindowHeight = " << WindowHeight << " pixels." << endl;
	cout << "WindowTitle  = " << WindowTitle << endl;
	cout << endl;
	//cout << "scigl_WindowTimer        = " << scigl_WindowTimer << "msec." << endl;
	cout << "scigl_zoomfactor         = " << scigl_zoomfactor << endl;
	cout << "scigl_scaleX             = " << scigl_scaleX << endl;
	cout << "scigl_scaleY             = " << scigl_scaleY << endl;
	cout << "scigl_scaleZ             = " << scigl_scaleZ << endl;
	cout << "scigl_translateX         = " << scigl_translateX << endl;
	cout << "scigl_translateY         = " << scigl_translateY << endl;
	cout << "scigl_translateZ         = " << scigl_translateZ << endl;
	cout << "scigl_angleHorizontal    = " << scigl_angleHorizontal << endl;
	cout << "scigl_angleVertical      = " << scigl_angleVertical << endl;
	cout << "scigl_ShowRenderedScene  = " << scigl_ShowRenderedScene << endl;
	cout << "scigl_ShowAxis           = " << scigl_ShowAxis << endl;
	cout << "scigl_dynZoomfactor      = " << scigl_dynZoomfactor << endl;
	cout << "scigl_dynScaleX          = " << scigl_dynScaleX << endl;
	cout << "scigl_dynScaleY          = " << scigl_dynScaleY << endl;
	cout << "scigl_dynScaleZ          = " << scigl_dynScaleZ << endl;
	cout << "scigl_dynTranslateX      = " << scigl_dynTranslateX << endl;
	cout << "scigl_dynTranslateY      = " << scigl_dynTranslateY << endl;
	cout << "scigl_dynTranslateZ      = " << scigl_dynTranslateZ << endl;
	cout << "scigl_dynAngleHorizontal = " << scigl_dynAngleHorizontal << endl;
	cout << "scigl_dynAngleVertical   = " << scigl_dynAngleVertical << endl;
}
void scigl_showhelp(void) {
	cout << "SciGL - The Scientific visualization library based on OpenGL, Version 0.1 beta" << endl;
	cout << "(c) 2010 by Armand Niederberger <Armand.Niederberger@opfocus.net>" << endl << endl;
	cout << "Command keys in graphic mode" << endl;
	cout << "A\ttoggle axis on/off." << endl;
	cout << "W\ttoggle Wireframe on/off. Default: off" << endl;
	cout << "N\ttoggle Normalized heights on/off. Default: off" << endl;
	cout << "+\tzoom in " << endl;
	cout << "-\tzoom out" << endl;
	cout << "up\trotate up" << endl;
	cout << "down\trotate down" << endl;
	cout << "left\trotate left" << endl;
	cout << "right\trotate right" << endl;
	cout << "fn+up\tmove up" << endl;
	cout << "fn+dwn\tmove down" << endl;
	cout << "fn+lft\tmove left" << endl;
	cout << "fn+rgt\tmove right" << endl;
	cout << ">\tincrease frequency of equipotential lines" << endl;
	cout << "<\tdecrease frequency of equipotential lines" << endl;
	cout << "X\tinflate x axis" << endl;
	cout << "x\tdeflate x axis" << endl;
	cout << "Y\tinflate y axis" << endl;
	cout << "y\tdeflate y axis" << endl;
	cout << "Z\tinflate z axis" << endl;
	cout << "z\tdeflate z axis" << endl;
	showspecifichelp();
	cout << "ESC\tQuit" << endl;
}
void heightmap::showspecifichelp(void)
{
	printf("whatever is 'child'-specific\n");
}
void plot(heightmap* heightmapinputpointer)
{
	//scigl_heightmap=new heightmap(width,height);
	scigl_heightmap=heightmapinputpointer;
	int argc=0;
	char** argv=0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(WindowWidth, WindowHeight);
	
//	glutCreateWindow(WindowTitle);
	
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT,GL_LINE); // XXX added by me
	
	glutDisplayFunc(scigl_DisplayFunc);
	glutKeyboardFunc(scigl_KeyboardFunc);
	glutSpecialFunc(scigl_SpecialFunc);
	glutMouseFunc(scigl_MouseFunc);
	glutMotionFunc(scigl_MotionFunc);
	glutReshapeFunc(scigl_ReshapeFunc);
	//glutTimerFunc(scigl_WindowTimer, scigl_TimerFunc, 0);
//	showhelp();
	
	glutMainLoop();
//	free(hmap);
}
*/
// }}}

void plot(int maxx, int maxy, float *inputarray) {{{
{
	scigl_IsMovie   = 0;
	scigl_IsComplex = 0;
	scigl_InitDefaultVariables(maxx, maxy);
	scigl_ImportMap(inputarray);
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotcomplex(int maxx, int maxy, float *inputarray) {{{
{
	scigl_IsMovie   = 0;
	scigl_IsComplex = 1;
	scigl_InitDefaultVariables(maxx, maxy);
	scigl_ImportMap(inputarray);
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotmovie(int NbrOfFrames, int maxx, int maxy, float *inputarray) {{{
{
	scigl_IsMovie		= 1;
	scigl_IsComplex		= 0;
	scigl_InitDefaultVariables(maxx, maxy);
	scigl_NbrOfFrames	= NbrOfFrames;
	scigl_ImportMap(inputarray);
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotcomplexmovie(int NbrOfFrames, int maxx, int maxy, float *inputarray) {{{
{
	scigl_IsMovie		= 1;
	scigl_IsComplex		= 1;
	scigl_InitDefaultVariables(maxx, maxy);
	scigl_NbrOfFrames	= NbrOfFrames;
	scigl_ImportMap(inputarray);
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plot(int maxx, int maxy, double *inputarray) {{{
{
	scigl_IsMovie   = 0;
	scigl_IsComplex = 0;
	scigl_InitDefaultVariables(maxx, maxy);
	float* floatinputarray;
	floatinputarray = new float[maxx*maxy];
	for (int i=0; i<maxx*maxy; i++) floatinputarray[i] = (float) inputarray[i];
	scigl_ImportMap(floatinputarray);
	delete floatinputarray;
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotcomplex(int maxx, int maxy, double *inputarray) {{{
{
	scigl_IsMovie   = 0;
	scigl_IsComplex = 1;
	scigl_InitDefaultVariables(maxx, maxy);
	float* floatinputarray;
	floatinputarray = new float[2*maxx*maxy];
	for (int i=0; i<2*maxx*maxy; i++) floatinputarray[i] = (float) inputarray[i];
	scigl_ImportMap(floatinputarray);
	delete floatinputarray;
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotmovie(int NbrOfFrames, int maxx, int maxy, double *inputarray) {{{
{
	scigl_IsMovie		= 1;
	scigl_IsComplex		= 0;
	scigl_InitDefaultVariables(maxx, maxy);
	scigl_NbrOfFrames	= NbrOfFrames;
	float* floatinputarray;
	floatinputarray = new float[NbrOfFrames*maxx*maxy];
	for (int i=0; i<NbrOfFrames*maxx*maxy; i++) floatinputarray[i] = (float) inputarray[i];
	scigl_ImportMap(floatinputarray);
	delete floatinputarray;
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotcomplexmovie(int NbrOfFrames, int maxx, int maxy, double *inputarray) {{{
{
	scigl_IsMovie		= 1;
	scigl_IsComplex		= 1;
	scigl_InitDefaultVariables(maxx, maxy);
	scigl_NbrOfFrames	= NbrOfFrames;
	float* floatinputarray;
	floatinputarray = new float[2*NbrOfFrames*maxx*maxy];
	for (int i=0; i<2*NbrOfFrames*maxx*maxy; i++) floatinputarray[i] = (float) inputarray[i];
	scigl_ImportMap(floatinputarray);
	delete floatinputarray;
	scigl_ShowHelp();
	scigl_startGLUT();
} }}}
void plotcomplexfloatmovie(char* filename) {{{
{
	FILE *fp;
	fp=fopen(filename, "r+");
	if (fp==NULL)
	{
		cerr << "SciGL FATAL ERROR in scigl_plotcomplexfloatmovie(): ";
		cerr << "Cannot open file " << filename << endl;
		exit(1);
	}
	int NbrOfFrames;
	int xmax;
	int ymax;
	int irc;
	irc = fread(&NbrOfFrames, sizeof(int), 1, fp);
	irc = fread(&xmax, sizeof(int), 1, fp);
	irc = fread(&ymax, sizeof(int), 1, fp);
	cout << "Reading " << NbrOfFrames << " frames of size " << xmax << "*" << ymax << endl;
	float* movie;
	movie = new float[2*NbrOfFrames*xmax*ymax];
	irc = fread(movie, sizeof(float), 2*NbrOfFrames*xmax*ymax, fp);
	plotcomplexmovie(NbrOfFrames, xmax, ymax, movie);
	delete movie;
} }}}

void scigl_InitDefaultVariables(int maxx, int maxy) {{{
{
	if (maxx>0)
	{
		scigl_NbrOfPointsX = maxx;
		scigl_Xmin = (float) 0;
		scigl_Xmax = (float) scigl_NbrOfPointsX;
	} else {
		cerr << "SciGL FATAL ERROR in scigl_InitDefaultVariables(): ";
		cerr << "First argument (width) needs to be greater than zero." << endl;
		exit(1);
	}
	if (maxy>0)
	{
		scigl_NbrOfPointsY = maxy;
		scigl_Ymin = (float) 0;
		scigl_Ymax = (float) scigl_NbrOfPointsY;
	} else {
		cerr << "SciGL FATAL ERROR in scigl_InitDefaultVariables(): ";
		cerr << "Second argument (height) needs to be greater than zero." << endl;
		exit(1);
	}
	
	scigl_Zmin					= 0.0;
	scigl_Zmax					= 0.0;
	scigl_Zminre				= 0.0;
	scigl_Zmaxre				= 0.0;
	scigl_Zminim				= 0.0;
	scigl_Zmaxim				= 0.0;
	scigl_Zminnorm				= 0.0;
	scigl_Zmaxnorm				= 0.0;
	scigl_Zminphase				= 0.0;
	scigl_Zmaxphase				= 0.0;
	scigl_Zminnorm2				= 0.0;
	scigl_Zmaxnorm2				= 0.0;

	scigl_WindowWidth			= 1200;
	scigl_WindowHeight			= 800;
	scigl_WindowTimer			= 25;
	//scigl_WindowTimer			= 100;
	
	scigl_WindowTitle 			= new char[100];
	strcpy(scigl_WindowTitle, "libSciGL - Version 0.1 beta");
	
	scigl_PlayMovie				= 0;
	scigl_NbrOfFrames			= 0;
	
	scigl_DefaultViewingParameters();
} }}}	
void scigl_DefaultViewingParameters(void) {{{
{
	scigl_zoomfactor			= 100.0;
	scigl_scaleX				= 0.02;
	scigl_scaleY				= 0.02;
	scigl_scaleZ				= 0.00005;
	scigl_translateX			= 2.5;
	scigl_translateY			= 0.0;
	scigl_translateZ			= 0.0;
	scigl_angleHorizontal		= -10.0;
	scigl_angleVertical 		= 30.0;
	scigl_RotationCenterX		= scigl_NbrOfPointsX/2.0f;
	scigl_RotationCenterY		= scigl_NbrOfPointsY/2.0f;
	scigl_RotationCenterZ		= 0.0f;;
	scigl_ColorPrefix			= 3.1415/2.0;
	scigl_CurrentFrame			= 0;
	scigl_ShowWireframe			= 0;
	scigl_ShowAxis				= 1;
	scigl_NormalizeZscaling		= 0;
	scigl_dynZoomfactor			= 0;
	scigl_dynScaleX				= 0;
	scigl_dynScaleY				= 0;
	scigl_dynScaleZ				= 0;
	scigl_dynTranslateX			= 0;
	scigl_dynTranslateY			= 0;
	scigl_dynTranslateZ			= 0;
	scigl_dynAngleHorizontal	= 0;
	scigl_dynAngleVertical 		= 0;
	scigl_dynColorPrefix		= 0;
	
	if (scigl_NbrOfPointsX > scigl_NbrOfPointsY)
	{
		scigl_scaleX *= 1.0f / ((float) (scigl_NbrOfPointsX - 1));
		scigl_scaleY *= 1.0f / ((float) (scigl_NbrOfPointsX - 1));
	} else {
		scigl_scaleX *= 1.0f / ((float) (scigl_NbrOfPointsY - 1));
		scigl_scaleY *= 1.0f / ((float) (scigl_NbrOfPointsY - 1));
	}
} }}}	
void scigl_ImportMap(float* inputarray) {{{
{
	scigl_heightmap = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
	if (scigl_IsMovie)
	{
		scigl_PlayMovie = 1;
		if (scigl_NbrOfFrames>0)
		{
			scigl_heightmapmovie = new float*[scigl_NbrOfFrames];
			for (int f=0; f<scigl_NbrOfFrames; f++) scigl_heightmapmovie[f] = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
			if (scigl_IsComplex)
			{
				scigl_heightmapremovie    = new float*[scigl_NbrOfFrames];
				scigl_heightmapimmovie    = new float*[scigl_NbrOfFrames];
				scigl_heightmapnormmovie  = new float*[scigl_NbrOfFrames];
				scigl_heightmapphasemovie = new float*[scigl_NbrOfFrames];
				scigl_heightmapnorm2movie = new float*[scigl_NbrOfFrames];
				for (int f=0; f<scigl_NbrOfFrames; f++)
				{
					scigl_heightmapremovie[f]    = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
					scigl_heightmapimmovie[f]    = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
					scigl_heightmapnormmovie[f]  = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
					scigl_heightmapphasemovie[f] = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
					scigl_heightmapnorm2movie[f] = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
					for (int i=0; i<scigl_NbrOfPointsX*scigl_NbrOfPointsY; i++)
					{
						scigl_heightmapremovie[f][i]    = inputarray[f*2*scigl_NbrOfPointsX*scigl_NbrOfPointsY+2*i];
						scigl_heightmapimmovie[f][i]    = inputarray[f*2*scigl_NbrOfPointsX*scigl_NbrOfPointsY+2*i+1];
						scigl_heightmapnorm2movie[f][i] = sqr(scigl_heightmapremovie[f][i])+sqr(scigl_heightmapimmovie[f][i]);
						float znorm = sqrt(scigl_heightmapnorm2movie[f][i]);
						scigl_heightmapnormmovie[f][i]  = znorm;
						float zphase = 0.0;
						if (znorm>0.0f)
						{
							float zre = scigl_heightmapremovie[f][i];
							float zim = scigl_heightmapimmovie[f][i];
							if (zre>=0.0f)
							{
								if (zre*zre>=zim*zim)
								{
									if (zim>=0.0f)
										zphase = acos(zre/znorm);
									else
										zphase = -acos(zre/znorm);
								} else {
									zphase = asin(zim/znorm);
								}
							} else {
								if (zre*zre>=zim*zim)
								{
									if (zim>=0.0f)
										zphase = acos(zre/znorm);
									else
										zphase = -acos(zre/znorm);
								} else {
									if (zim>=0.0f)
										zphase = 2.0*acos(0.0) - asin(zim/znorm);
									else
										zphase = -2.0*acos(0.0) - asin(zim/znorm);
								}
							}
						}
						scigl_heightmapphasemovie[f][i] = zphase;
						if (scigl_heightmapremovie[f][i]    < scigl_Zminre)    scigl_Zminre    = scigl_heightmapremovie[f][i];
						if (scigl_heightmapremovie[f][i]    > scigl_Zmaxre)    scigl_Zmaxre    = scigl_heightmapremovie[f][i];
						if (scigl_heightmapimmovie[f][i]    < scigl_Zminim)    scigl_Zminim    = scigl_heightmapimmovie[f][i];
						if (scigl_heightmapimmovie[f][i]    > scigl_Zmaxim)    scigl_Zmaxim    = scigl_heightmapimmovie[f][i];
						if (scigl_heightmapnormmovie[f][i]  < scigl_Zminnorm)  scigl_Zminnorm  = scigl_heightmapnormmovie[f][i];
						if (scigl_heightmapnormmovie[f][i]  > scigl_Zmaxnorm)  scigl_Zmaxnorm  = scigl_heightmapnormmovie[f][i];
						if (scigl_heightmapphasemovie[f][i] < scigl_Zminphase) scigl_Zminphase = scigl_heightmapphasemovie[f][i];
						if (scigl_heightmapphasemovie[f][i] > scigl_Zmaxphase) scigl_Zmaxphase = scigl_heightmapphasemovie[f][i];
						if (scigl_heightmapnorm2movie[f][i] < scigl_Zminnorm2) scigl_Zminnorm2 = scigl_heightmapnorm2movie[f][i];
						if (scigl_heightmapnorm2movie[f][i] > scigl_Zmaxnorm2) scigl_Zmaxnorm2 = scigl_heightmapnorm2movie[f][i];
					}
				}
				scigl_loadheightmap(1);
			} else {
				for (int f=0; f<scigl_NbrOfFrames; f++)
				{
					for (int i=0; i<scigl_NbrOfPointsX*scigl_NbrOfPointsY; i++)
					{
						scigl_heightmapmovie[f][i] = inputarray[f*scigl_NbrOfPointsX*scigl_NbrOfPointsY+i];
						if (scigl_heightmapmovie[f][i] < scigl_Zmin) scigl_Zmin = scigl_heightmapmovie[f][i];
						if (scigl_heightmapmovie[f][i] > scigl_Zmax) scigl_Zmax = scigl_heightmapmovie[f][i];
					}
				}
			}
		} else {
			cerr << "SciGL FATAL ERROR in scigl_ImportMap(): ";
			cerr << "Variable scigl_NbrOfFrames is zero." << endl;
			exit(1);
		}
	} else {
		if (scigl_IsComplex)
		{
			scigl_heightmapre    = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
			scigl_heightmapim    = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
			scigl_heightmapnorm  = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
			scigl_heightmapphase = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
			scigl_heightmapnorm2 = new float[scigl_NbrOfPointsX*scigl_NbrOfPointsY];
			for (int i=0; i<scigl_NbrOfPointsX*scigl_NbrOfPointsY; i++)
			{
				scigl_heightmapre[i]    = inputarray[2*i];
				scigl_heightmapim[i]    = inputarray[2*i+1];
				scigl_heightmapnorm2[i] = sqr(scigl_heightmapre[i])+sqr(scigl_heightmapim[i]);
				float znorm = sqrt(scigl_heightmapnorm2[i]);
				scigl_heightmapnorm[i]  = znorm;
				float zphase = 0.0;
				if (znorm>0.0f)
				{
					float zre = scigl_heightmapre[i];
					float zim = scigl_heightmapim[i];
					if (zre>=0.0f)
					{
						if (zre*zre>=zim*zim)
						{
							if (zim>=0.0f)
								zphase = acos(zre/znorm);
							else
								zphase = -acos(zre/znorm);
						} else {
							zphase = asin(zim/znorm);
						}
					} else {
						if (zre*zre>=zim*zim)
						{
							if (zim>=0.0f)
								zphase = acos(zre/znorm);
							else
								zphase = -acos(zre/znorm);
						} else {
							if (zim>=0.0f)
								zphase = 2.0*acos(0.0) - asin(zim/znorm);
							else
								zphase = -2.0*acos(0.0) - asin(zim/znorm);
						}
					}
				}
				scigl_heightmapphase[i] = zphase;
				if (scigl_heightmapre[i]    < scigl_Zminre)    scigl_Zminre    = scigl_heightmapre[i];
				if (scigl_heightmapre[i]    > scigl_Zmaxre)    scigl_Zmaxre    = scigl_heightmapre[i];
				if (scigl_heightmapim[i]    < scigl_Zminim)    scigl_Zminim    = scigl_heightmapim[i];
				if (scigl_heightmapim[i]    > scigl_Zmaxim)    scigl_Zmaxim    = scigl_heightmapim[i];
				if (scigl_heightmapnorm[i]  < scigl_Zminnorm)  scigl_Zminnorm  = scigl_heightmapnorm[i];
				if (scigl_heightmapnorm[i]  > scigl_Zmaxnorm)  scigl_Zmaxnorm  = scigl_heightmapnorm[i];
				if (scigl_heightmapphase[i] < scigl_Zminphase) scigl_Zminphase = scigl_heightmapphase[i];
				if (scigl_heightmapphase[i] > scigl_Zmaxphase) scigl_Zmaxphase = scigl_heightmapphase[i];
				if (scigl_heightmapnorm2[i] < scigl_Zminnorm2) scigl_Zminnorm2 = scigl_heightmapnorm2[i];
				if (scigl_heightmapnorm2[i] > scigl_Zmaxnorm2) scigl_Zmaxnorm2 = scigl_heightmapnorm2[i];
			}
			scigl_loadheightmap(1);
		} else {
			for (int i=0; i<scigl_NbrOfPointsX*scigl_NbrOfPointsY; i++)
			{
				scigl_heightmap[i] = inputarray[i];
				if (scigl_heightmap[i] < scigl_Zmin) scigl_Zmin = scigl_heightmap[i];
				if (scigl_heightmap[i] > scigl_Zmax) scigl_Zmax = scigl_heightmap[i];
			}
		}
	}
} }}}
void scigl_ShowHelp(void) {{{
{
	cout << "SciGL - The scientific visualization library based on OpenGL, Version 0.1 beta" << endl;
	cout << "(c) 2010 by Armand Niederberger <Armand.Niederberger@opfocus.org>" << endl << endl;
	cout << "Command keys in graphic mode" << endl;
	cout << "A          toggle axis on/off" << endl;
	cout << "W          toggle Wireframe on/off. Default: off" << endl;
	cout << "N          toggle Normalized heights on/off. Default: off" << endl;
	cout << "R          restore default viewing parameters" << endl;
	cout << "+          zoom in " << endl;
	cout << "-          zoom out" << endl;
	cout << "up         rotate up" << endl;
	cout << "down       rotate down" << endl;
	cout << "left       rotate left" << endl;
	cout << "right      rotate right" << endl;
	cout << "page-up    move up" << endl;
	cout << "page-down  move down" << endl;
	cout << "home       move left" << endl;
	cout << "end        move right" << endl;
	cout << "X          inflate x axis" << endl;
	cout << "x          deflate x axis" << endl;
	cout << "Y          inflate y axis" << endl;
	cout << "y          deflate y axis" << endl;
	cout << "Z          inflate z axis" << endl;
	cout << "z          deflate z axis" << endl;
	
	if (scigl_IsComplex)
	{
		cout << "1          Plot real-part" << endl;
		cout << "2          Plot imaginary-part" << endl;
		cout << "3          Plot norm" << endl;
		cout << "4          Plot complex phase" << endl;
		cout << "5          Plot intensity (i.e. the square of thenorm)" << endl;
	}
	if (scigl_IsMovie)
	{
	cout << "(space)    Play/Pause movie" << endl;
		cout << ">          Show next movie frame" << endl;
		cout << "<          Show former movie frame" << endl;
	}

	cout << "ESC        Quit" << endl;
} }}}
void scigl_loadheightmap(int mapid) {{{
{
	if (scigl_IsComplex)
	{
		if (scigl_NormalizeZscaling) scigl_scaleZ *= (scigl_Zmax-scigl_Zmin)/100.0f;
		if (scigl_IsMovie)
		{
			switch (mapid)
			{
				case 1:	scigl_heightmapmovie=scigl_heightmapremovie;
						scigl_Zmin = scigl_Zminre;
						scigl_Zmax = scigl_Zmaxre;
						break;
				case 2:	scigl_heightmapmovie=scigl_heightmapimmovie;
						scigl_Zmin = scigl_Zminim;
						scigl_Zmax = scigl_Zmaxim;
						break;
				case 3:	scigl_heightmapmovie=scigl_heightmapnormmovie;
						scigl_Zmin = scigl_Zminnorm;
						scigl_Zmax = scigl_Zmaxnorm;
						break;
				case 4:	scigl_heightmapmovie=scigl_heightmapphasemovie;
						scigl_Zmin = scigl_Zminphase;
						scigl_Zmax = scigl_Zmaxphase;
						break;
				case 5:	scigl_heightmapmovie=scigl_heightmapnorm2movie;
						scigl_Zmin = scigl_Zminnorm2;
						scigl_Zmax = scigl_Zmaxnorm2;
						break;
			}
		} else {
			switch (mapid)
			{
				case 1:	scigl_heightmap=scigl_heightmapre;
						scigl_Zmin = scigl_Zminre;
						scigl_Zmax = scigl_Zmaxre;
						break;
				case 2:	scigl_heightmap=scigl_heightmapim;
						scigl_Zmin = scigl_Zminim;
						scigl_Zmax = scigl_Zmaxim;
						break;
				case 3:	scigl_heightmap=scigl_heightmapnorm;
						scigl_Zmin = scigl_Zminnorm;
						scigl_Zmax = scigl_Zmaxnorm;
						break;
				case 4:	scigl_heightmap=scigl_heightmapphase;
						scigl_Zmin = scigl_Zminphase;
						scigl_Zmax = scigl_Zmaxphase;
						break;
				case 5:	scigl_heightmap=scigl_heightmapnorm2;
						scigl_Zmin = scigl_Zminnorm2;
						scigl_Zmax = scigl_Zmaxnorm2;
						break;
			}
		}
		if (scigl_NormalizeZscaling) scigl_scaleZ *= 100.0f/(scigl_Zmax-scigl_Zmin);
	}
} }}}
void scigl_nextframe(void) {{{
{
	if (scigl_IsMovie)
	{
		if (scigl_PlayMovie) scigl_CurrentFrame = (scigl_CurrentFrame+1)%scigl_NbrOfFrames;
		scigl_heightmap=scigl_heightmapmovie[scigl_CurrentFrame];
	}
} }}}
void scigl_startGLUT(void) {{{
{	int argc=0;
	char** argv=0;
	glutInit(&argc, argv);										// ??
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// ??
	glutInitWindowSize(scigl_WindowWidth, scigl_WindowHeight);	// Define width and size of graphics window
	glutCreateWindow(scigl_WindowTitle);						// Define title line of graphics window
	glEnable(GL_DEPTH_TEST);									// Makes sure that depth is controlled, not only sequence of drawing
	
	glEnable(GL_COLOR_MATERIAL);	// Necessary for the Surface to receive light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
		
	glShadeModel(GL_SMOOTH);
	GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos0[] = {0.6f, 1.0f, .5, 0.0f};
	//GLfloat lightPos0[] = {0.5f, 0.6f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	GLfloat lightColor1[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat lightPos1[] = {1.0f, 0.3f, .5, 0.0f};
	//GLfloat lightPos1[] = {0.5f, 1.0f, 0.3f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	glutDisplayFunc(scigl_DisplayFunc);
	glutKeyboardFunc(scigl_KeyboardFunc);
	glutSpecialFunc(scigl_SpecialFunc);
	glutMouseFunc(scigl_MouseFunc);
	glutMotionFunc(scigl_MotionFunc);
	glutReshapeFunc(scigl_ReshapeFunc);
	glutTimerFunc(scigl_WindowTimer, scigl_TimerFunc, 0);
	
	glutMainLoop();
} }}}

void scigl_DisplayFunc(void) {{{
{
	// Restore defaults and clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (scigl_ShowWireframe)
	{
		glPolygonMode(GL_FRONT,GL_LINE);
		glPolygonMode(GL_BACK,GL_LINE);
	} else {
		
		glPolygonMode(GL_FRONT,GL_FILL);
		glPolygonMode(GL_BACK,GL_FILL);
	}
	
	// Transform original OpenGL graphics designer coordinate system
	// into scientifically used coordinate system.
	// OpenGL uses:      x=horizontal, y=vertical, z=depth
	// Scientists use:   x=depth, y=horizontal, z=vertical
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	
	// Translate away from coordinate origin to view the scene
	glTranslatef(-scigl_translateX, -scigl_translateY, -scigl_translateZ);
	
	// Rotate scene according to viewing angle
	glRotatef(scigl_angleVertical, 0.0f, 1.0f, 0.0f);
	glRotatef(scigl_angleHorizontal, 0.0f, 0.0f, 1.0f);
	
	// Draw Heightmap array
	glPushMatrix();
	glScalef(scigl_zoomfactor*scigl_scaleX, scigl_zoomfactor*scigl_scaleY, scigl_zoomfactor*scigl_scaleZ);
	glTranslatef(-scigl_RotationCenterX, -scigl_RotationCenterY, -scigl_RotationCenterZ);
	float h, hp;
	for(int x = 0; x < scigl_NbrOfPointsX - 1; x++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(int y = 0; y < scigl_NbrOfPointsY; y++)
		{
			glColor3f(0.5, 0.6, 1.0);
			h=0.8*(sin(scigl_ColorPrefix/(scigl_Zmax-scigl_Zmin)*(scigl_heightmap[x*scigl_NbrOfPointsY+y]-scigl_Zmin)));
			hp=0.8*(sin(scigl_ColorPrefix/(scigl_Zmax-scigl_Zmin)*(scigl_heightmap[(x+1)*scigl_NbrOfPointsY+y]-scigl_Zmin)));
			float NormalZ1 = 0.0f;
			float NormalZ2 = 0.0f;
			float NormalZ3 = 0.0f;
			float NormalZ4 = 0.0f;
			if (y+1<scigl_NbrOfPointsY)
				NormalZ1 = scigl_heightmap[(x+0)*scigl_NbrOfPointsY + (y+1)];
			if (x+1<scigl_NbrOfPointsX)
				NormalZ2 = scigl_heightmap[(x+1)*scigl_NbrOfPointsY + (y+0)];
			if (y>0)
				NormalZ3 = scigl_heightmap[(x+0)*scigl_NbrOfPointsY + (y-1)];
			if (x>0)
				NormalZ4 = scigl_heightmap[(x-1)*scigl_NbrOfPointsY + (y+0)];
			float NormalX=(NormalZ4 - NormalZ2) / 2.0f;
			float NormalY=(NormalZ3 - NormalZ1) / 2.0f;
			float NormalZ=1.0f;
			glNormal3f(NormalX, NormalY, NormalZ);
			glColor3f(h+0.2, h+0.2, sqrt(h)+0.2);
			glVertex3f(x, y, scigl_heightmap[x*scigl_NbrOfPointsY+y]);
			NormalZ1 = 0.0f;
			NormalZ2 = 0.0f;
			NormalZ3 = 0.0f;
			NormalZ4 = 0.0f;
			if (y+1<scigl_NbrOfPointsY)
				NormalZ1 = scigl_heightmap[(x+1)*scigl_NbrOfPointsY + (y+1)];
			if (x+2<scigl_NbrOfPointsX)
				NormalZ2 = scigl_heightmap[(x+2)*scigl_NbrOfPointsY + (y+0)];
			if (y>0)
				NormalZ3 = scigl_heightmap[(x+1)*scigl_NbrOfPointsY + (y-1)];
			if (x+1>0)
				NormalZ4 = scigl_heightmap[(x+0)*scigl_NbrOfPointsY + (y+0)];
			NormalX=(NormalZ4 - NormalZ2) / 2.0f;
			NormalY=(NormalZ3 - NormalZ1) / 2.0f;
			NormalZ=1.0f;
			glNormal3f(NormalX, NormalY, NormalZ);
			glColor3f(hp+0.2, hp+0.2, sqrt(hp)+0.2);
			glVertex3f(x+1, y, scigl_heightmap[(x+1)*scigl_NbrOfPointsY+y]);
		}
		glEnd();
	}
	glPopMatrix();
		
	// Draw coorinate axis if scigl_ShowAxis is 1
	if (scigl_ShowAxis)
	{
		// Draw red X-Axis
		glPushMatrix();
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f,0.0f,0.0f);
		GLUquadricObj* xaxe;
		xaxe = gluNewQuadric();
		gluCylinder(xaxe,0.01,0.01,0.2,20,5);
		glTranslatef(0.0f, 0.0f, 0.2f);
		GLUquadricObj* xcyl;
		xcyl = gluNewQuadric();
		gluCylinder(xcyl,0.02,0.0,0.05,20,5);
		glPopMatrix();

		// Draw green Y-Axis
		glPushMatrix();
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		GLUquadricObj* yaxe;
		yaxe = gluNewQuadric();
		gluCylinder(yaxe,0.01,0.01,0.2,20,5);
		glTranslatef(0.0f, 0.0f, 0.2f);
		GLUquadricObj* ycyl;
		ycyl = gluNewQuadric();
		gluCylinder(ycyl,0.02,0.0,0.05,20,5);
		glPopMatrix();

		// Draw blue Z-Axis
		glPushMatrix();
		glColor3f(0.0f,0.0f,1.0f);
		GLUquadricObj* zaxe;
		zaxe = gluNewQuadric();
		gluCylinder(zaxe,0.01,0.01,0.2,20,5);
		glTranslatef(0.0f, 0.0f, 0.2f);
		GLUquadricObj* zcyl;
		zcyl = gluNewQuadric();
		gluCylinder(zcyl,0.02,0.0,0.05,20,5);
		glPopMatrix();
	}
	glutSwapBuffers();
} }}}
void scigl_KeyboardFunc(unsigned char key, int ScreenPosX, int ScreenPosY) {{{
{
	switch (key) {
		case '1':	scigl_loadheightmap(1); break;
		case '2':	scigl_loadheightmap(2); break;
		case '3':	scigl_loadheightmap(3); break;
		case '4':	scigl_loadheightmap(4); break;
		case '5':	scigl_loadheightmap(5); break;
		case 'A':	scigl_ShowAxis			 = 1-scigl_ShowAxis; break;
		case ' ':	scigl_PlayMovie			 = 1-scigl_PlayMovie; break;
		case '>':	scigl_CurrentFrame = (scigl_CurrentFrame+1)%scigl_NbrOfFrames; break;
		case '<':	scigl_CurrentFrame = (scigl_CurrentFrame+scigl_NbrOfFrames-1)%scigl_NbrOfFrames; break;
		case 'R':	scigl_DefaultViewingParameters(); break;
		case 'W':	scigl_ShowWireframe		 = 1-scigl_ShowWireframe; break;
		case 'N':	scigl_NormalizeZscaling	 = 1-scigl_NormalizeZscaling;
					if (scigl_Zmax-scigl_Zmin > 0.0)
					{
						if (scigl_NormalizeZscaling) 
							scigl_scaleZ *= 100.0f/(scigl_Zmax-scigl_Zmin);
						else 
							scigl_scaleZ *= (scigl_Zmax-scigl_Zmin)/100.0f;
					}
					break;
		case 'X':	scigl_dynScaleX			+=  10; break;
		case 'x':	scigl_dynScaleX			+= -10; break;
		case 'Y':	scigl_dynScaleY			+=  10; break;
		case 'y':	scigl_dynScaleY			+= -10; break;
		case 'Z':	scigl_dynScaleZ			+=  10; break;
		case 'z':	scigl_dynScaleZ			+= -10; break;
		case '+':	scigl_dynZoomfactor		+=  10; break;
		case '-':	scigl_dynZoomfactor		+= -10; break;
		case  27:	cout << "Quitting." << endl; exit(0);
	}
	glutPostRedisplay();
} }}}
void scigl_SpecialFunc(int key, int ScreenPosX, int ScreenPosY) {{{
{
	switch (key) {
		case 100:	scigl_dynAngleHorizontal	+=	 10;	break;	// left
		case 101:	scigl_dynAngleVertical		+=	 10;	break;	// up
		case 102:	scigl_dynAngleHorizontal	+=	-10;	break;	// right
		case 103:	scigl_dynAngleVertical 		+=	-10;	break;	// down
		case 104:	scigl_dynTranslateZ			+=	 10;	break; 	// fn+up
		case 105:	scigl_dynTranslateZ			+=	-10;	break;	// fn+down
		case 106:	scigl_dynTranslateY			+=	-10;	break;	// fn+left
		case 107:	scigl_dynTranslateY			+=	 10;	break;	// fn+right
	}
	glutPostRedisplay();
} }}}
void scigl_MouseFunc(int button, int state, int ScreenPosX, int ScreenPosY) {{{
{
	if (state==GLUT_DOWN)
	{
		scigl_MouseButton |= 1 << button;
	} else if (state==GLUT_UP)
	{
		scigl_MouseButton = 0;
	}
	scigl_OldMousePosX = ScreenPosX;
	scigl_OldMousePosY = ScreenPosY;
	glutPostRedisplay();
} }}}
void scigl_MotionFunc(int ScreenPosX, int ScreenPosY) {{{
{
	float DeltaX, DeltaY;
	DeltaX = ScreenPosX - scigl_OldMousePosX;
	DeltaY = ScreenPosY - scigl_OldMousePosY;
	if (scigl_MouseButton & 1)
	{
		scigl_angleHorizontal += 0.2*DeltaX;
		scigl_angleVertical   += 0.2*DeltaY;
	} else if (scigl_MouseButton & 4)
	{
		scigl_translateZ += 0.01*DeltaY;
	}
	scigl_OldMousePosX = ScreenPosX;
	scigl_OldMousePosY = ScreenPosY;
	glutPostRedisplay();
} }}}
void scigl_ReshapeFunc(int NewWidth, int NewHeight) {{{
{
	glViewport(0, 0, NewWidth, NewHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)NewWidth / (double)NewHeight, 0.1, 200.0);
} }}}
void scigl_TimerFunc(int value) {{{
{
	scigl_nextframe();
	if (scigl_dynAngleHorizontal>0)
	{
		scigl_angleHorizontal		+= 1.0;
		scigl_dynAngleHorizontal	-= 1;
	}
	if (scigl_dynAngleHorizontal<0)
	{
		scigl_angleHorizontal		-= 1.0;
		scigl_dynAngleHorizontal	+= 1;
	}
	if (scigl_dynAngleVertical>0)
	{
		scigl_angleVertical		+= 1.0;
		scigl_dynAngleVertical	-= 1;
	}
	if (scigl_dynAngleVertical<0)
	{
		scigl_angleVertical		-= 1.0;
		scigl_dynAngleVertical	+= 1;
	}
	if (scigl_dynTranslateX>0)
	{
		scigl_translateX	+= 0.05;
		scigl_dynTranslateX	-= 1;
	}
	if (scigl_dynTranslateX<0)
	{
		scigl_translateX	-= 0.05;
		scigl_dynTranslateX	+= 1;
	}
	if (scigl_dynTranslateY>0)
	{
		scigl_translateY	+= 0.05;
		scigl_dynTranslateY	-= 1;
	}
	if (scigl_dynTranslateY<0)
	{
		scigl_translateY	-= 0.05;
		scigl_dynTranslateY	+= 1;
	}
	if (scigl_dynTranslateZ>0)
	{
		scigl_translateZ	+= 0.05;
		scigl_dynTranslateZ	-= 1;
	}
	if (scigl_dynTranslateZ<0)
	{
		scigl_translateZ	-= 0.05;
		scigl_dynTranslateZ	+= 1;
	}
	if (scigl_dynZoomfactor > 0)
	{
		scigl_zoomfactor	*= 1.02;
		scigl_dynZoomfactor	-= 1;
	}
	if (scigl_dynZoomfactor < 0)
	{
		scigl_zoomfactor	/= 1.02;
		scigl_dynZoomfactor	+= 1;
	}
	if (scigl_dynScaleX > 0)
	{
		scigl_scaleX		*= 1.02;
		scigl_dynScaleX		-= 1;
	}
	if (scigl_dynScaleX < 0)
	{
		scigl_scaleX		/= 1.02;
		scigl_dynScaleX		+= 1;
	}
	if (scigl_dynScaleY > 0)
	{
		scigl_scaleY		*= 1.02;
		scigl_dynScaleY		-= 1;
	}
	if (scigl_dynScaleY < 0)
	{
		scigl_scaleY		/= 1.02;
		scigl_dynScaleY		+= 1;
	}
	if (scigl_dynScaleZ > 0)
	{
		scigl_scaleZ		*= 1.02;
		scigl_dynScaleZ		-= 1;
	}
	if (scigl_dynScaleZ < 0)
	{
		scigl_scaleZ		/= 1.02;
		scigl_dynScaleZ		+= 1;
	}

	if (scigl_angleHorizontal>360.f)	scigl_angleHorizontal = scigl_angleHorizontal - 360.f;
	if (scigl_angleHorizontal<0.f)		scigl_angleHorizontal = scigl_angleHorizontal + 360.f;
	if (scigl_angleVertical>360.f)		scigl_angleVertical   = scigl_angleVertical - 360.f;
	if (scigl_angleVertical<0.f)		scigl_angleVertical   = scigl_angleVertical + 360.f;
	glutPostRedisplay();
	glutTimerFunc(scigl_WindowTimer, scigl_TimerFunc, 0);
} }}}

