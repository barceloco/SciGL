// XXX XXX XXX     C O M P I L E   C O M M A N D     XXX XXX XXX
//  g++ 01_minimalistic.cpp -framework OpenGL -framework GLUT;
// XXX XXX XXX     C O M P I L E   C O M M A N D     XXX XXX XXX


/* File for "Terrain" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */


#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>


float* hmap;
int iheight;
int iwidth;

float _angleX = 0.0f;
float _angleY = 0.0f;
float translX = 0.0f;
float translY = 0.0f;;
float translZ = -9.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;
float zoom = 1.0f;
int zoomnr=10;
float zoominc=0.02f;
int zoomcnt=0;
float zsc = 1.0f;
int rotnr=10;
float rotinc=1.5f;
int rotx=0;
int roty=0;
int tranr=10;
float trainc=0.1f;
int tx=0;
int ty=0;
int defaultrefresh=50;
int Fill=1;
int mouse_old_x, mouse_old_y;
int mouse_buttons=0;


void DisplayMode_Fill(void)
{
	glPolygonMode(GL_FRONT,GL_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	
	GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
	//GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	GLfloat lightColor0[] = {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat lightPos0[] = {1.0f, 1.8f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}


void handleMouse(int button, int state, int x, int y)
{
	if (state==GLUT_DOWN)
	{
		mouse_buttons |= 1 << button;
	} else if (state==GLUT_UP)
	{
		mouse_buttons = 0;
	}
	mouse_old_x=x;
	mouse_old_y=y;
	glutPostRedisplay();
}

void handleMotion(int x, int y)
{
	float dx, dy;
	dx=x-mouse_old_x;
	dy=y-mouse_old_y;
	if (mouse_buttons & 1)
	{
		_angleX += dy*0.2;
		_angleY += dx*0.2;
	} else if (mouse_buttons & 4)
	{
		translZ += dy*0.01;
	}
	mouse_old_x=x;
	mouse_old_y=y;
}


void handleKeypress(unsigned char key, int x, int y) {
	// printf("%d %d %d\n", x, y, key);
	switch (key) {
		case 'X': scaleX+=0.1; break;
		case 'x': scaleX+=-0.1; break;
		case 'Y': scaleY+=0.1; break;
		case 'y': scaleY+=-0.1; break;
		case 'Z': scaleZ+=0.1; break;
		case 'z': scaleZ+=-0.1; break;
		//case  43: zoom+=0.1; break;
		//case  45: zoom+=-0.1; break;
		case '+': zoomcnt+=zoomnr; break;
		case '-': zoomcnt+=-zoomnr; break;
		case '>': zsc+=0.1; break;
		case '<': zsc+=-0.1; break;
		//case 'W': glPolygonMode(GL_FRONT,GL_LINE);break;
		case 'F': Fill=1-Fill;	break;
		//case 'F': DisplayMode_Fill();break;
		case  27: //Escape key
			exit(0);
	}
	glutPostRedisplay();
}

void handleSpecialKey(int key, int x, int y) {
	// printf("  %d %d %d\n", x, y, key);
	switch (key) {
	//	case 100:	translX	+=	 0.2f;	break;	// left
	//	case 101:	translY	+=	-0.2f;	break;	// up
	//	case 102:	translX	+=	-0.2f;	break;	// right
	//	case 103:	translY	+=	 0.2f;	break;	// down
	//	case 104:	_angleX	+=	 5.f;	break;	// fn+up
	//	case 105:	_angleX	+=	-5.f;	break;	// fn+down
	//	case 106:	_angleY	+=	 5.f;	break;	// fn+left
	//	case 107:	_angleY	+=	-5.f;	break;	// fn+right
//		case 100:	_angleY	+=	 5.f;	break;	// left
//		case 101:	_angleX	+=	 5.f;	break;	// up
//		case 102:	_angleY	+=	-5.f;	break;	// right
//		case 103:	_angleX	+=	-5.f;	break;	// down
//		case 104:	translY	+=	-0.2f;	break; 	// fn+up
//		case 105:	translY	+=	 0.2f;	break;	// fn+down
//		case 106:	translX	+=	 0.2f;	break;	// fn+left
//		case 107:	translX	+=	-0.2f;	break;	// fn+right
		case 100:	roty	+=	 rotnr;	break;	// left
		case 101:	rotx	+=	 rotnr;	break;	// up
		case 102:	roty	+=	-rotnr;	break;	// right
		case 103:	rotx	+=	-rotnr;	break;	// down
		case 104:	ty		+=	-tranr;	break; 	// fn+up
		case 105:	ty		+=	 tranr;	break;	// fn+down
		case 106:	tx		+=	 tranr;	break;	// fn+left
		case 107:	tx		+=	-tranr;	break;	// fn+right
	}
	if (_angleX>360.f)	_angleX = _angleX - 360.f;
	if (_angleX<0.f)	_angleX = _angleX + 360.f;
	if (_angleY>360.f)	_angleY = _angleY - 360.f;
	if (_angleY<0.f)	_angleY = _angleY + 360.f;
	glutPostRedisplay();
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT,GL_LINE); // XXX added by me
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (Fill) DisplayMode_Fill();
	else glPolygonMode(GL_FRONT,GL_LINE);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -10.0f); // rotation to my viewpoint
	glTranslatef(translX, translY, translZ); // rotation to my viewpoint
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // initial rotation downwards
	glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
	

	float scale;
	if (iwidth - 1> iheight - 1) scale = 5.0f / ((float) (iwidth - 1));
	else scale = 5.0f / ((float) (iheight - 1));
	scale*=zoom;
	glScalef(scale*scaleX, scale*scaleY, scale*scaleZ);
	glTranslatef(-(float)(iwidth - 1) / 2,
				 0.0f,
				 -(float)(iheight - 1) / 2);

	int z;
	float h, hp;
	for(z = 0; z < iheight - 1; z++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		int x;
		for(x = 0; x < iwidth; x++)
		{
			h=0.5f*(1.0f+sin(zsc*hmap[x*iheight+z]));
			hp=0.5f*(1.0f+sin(zsc*hmap[x*iheight+z+1]));
			
			//if (h>0.5f) h=1.0f;
			//if (hp>0.5f) hp=1.0f;
			//if (hp<0.5f) hp=0.0f;
			//if (h<0.5f) h=0.0f;
			glColor3f(h, h, 1.0f);
			glVertex3f(x, hmap[x*iheight+z], z);
			glColor3f(hp, hp, 1.0f);
			glVertex3f(x, hmap[x*iheight+z+1], z + 1);
		}
		glEnd();
	}
	
	glutSwapBuffers();
}

void update(int value) {
	//_angleY += -0.2f;
	if (rotx>0)
	{
		//_angleX +=rotx*rotx*rotinc;
		_angleX +=rotinc;
		rotx--;
	}
	if (rotx<0)
	{
		//_angleX += -rotx*rotx*rotinc;
		_angleX += -rotinc;
		rotx++;
	}
	if (roty>0)
	{
		//_angleY += roty*roty*rotinc;
		_angleY += rotinc;
		roty--;
	}
	if (roty<0)
	{
		//_angleY +=-roty*roty*rotinc;
		_angleY +=-rotinc;
		roty++;
	}
	if (tx>0)
	{
		translX += trainc;
		tx--;
	}
	if (tx<0)
	{
		translX +=-trainc;
		tx++;
	}
	if (ty>0)
	{
		translY += trainc;
		ty--;
	}
	if (ty<0)
	{
		translY +=-trainc;
		ty++;
	}
	if (zoomcnt>0)
	{
		zoom += zoominc;
		zoomcnt--;
	}
	if (zoomcnt<0)
	{
		zoom +=-zoominc;
		zoomcnt++;
	}
	
	if (_angleY > 360) {
		_angleY -= 360;
	}
	
	glutPostRedisplay();
	int nexttime=(int) (defaultrefresh/sqrt(rotx*rotx+roty*roty+tx*tx+ty*ty+zoomcnt*zoomcnt+1));
	glutTimerFunc(nexttime, update, 0);
	//glutTimerFunc(25, update, 0);
}

void showhelp(void) {
	printf("SciGL - The Scientific visualization library based on OpenGL, Version 0.0-1 beta\n");
	printf("(c) 2010 by Armand Niederberger <Armand.Niederberger@opfocus.net>\n");
	printf("\n");
	printf("Command keys in graphic mode\n");
	printf("F\ttoggle fill mode: show wireframe or show solid frame (default)\n");
	printf("+\tzoom in \n");
	printf("-\tzoom out\n");
	printf("up\trotate up\n");
	printf("down\trotate down\n");
	printf("left\trotate left\n");
	printf("right\trotate right\n");
	printf("fn+up\tmove up\n");
	printf("fn+dwn\tmove down\n");
	printf("fn+lft\tmove left\n");
	printf("fn+rgt\tmove right\n");
	printf(">\tincrease frequency of equipotential lines\n");
	printf("<\tdecrease frequency of equipotential lines\n");
	printf("X\tinflate x axis\n");
	printf("x\tdeflate x axis\n");
	printf("Y\tinflate y axis\n");
	printf("y\tdeflate y axis\n");
	printf("Z\tinflate z axis\n");
	printf("z\tdeflate z axis\n");
	printf("ESC\tQuit\n");
}
void plothmap(void) {
	int argc=0;
	char** argv=0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	
	glutCreateWindow("Minimalistic function viewer (adapted from 'Terrain - videotutorialsrock.com')");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKey);
	glutMouseFunc(handleMouse);
	glutMotionFunc(handleMotion);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	showhelp();
	
	glutMainLoop();
	free(hmap);
}

void plot(int xmax, int ymax, double* zmap) {
	hmap = (float*) malloc(xmax*ymax*sizeof(float));
	iwidth=xmax;
	iheight=ymax;
	int i; for (i=0; i<xmax*ymax; i++) hmap[i] = (float) zmap[i];
	plothmap();
	free(hmap);
}

void plotcomplex(int xmax, int ymax, double* zmap) {
	hmap = (float*) malloc(xmax*ymax*sizeof(float));
	iwidth=xmax;
	iheight=ymax;
	int i;
	for (i=0; i<2*xmax*ymax; i+=2) hmap[i/2] = (float) zmap[i];
	plothmap();	
	free(hmap);
}


