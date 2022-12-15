#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

const float AxisSize=10000;
// ----------------------------------------------------------------------
// NECESARIO PARA CARGAR LAS IMÁGENES DE DISCO
#include "CImg.h"
using namespace cimg_library;
// ----------------------------------------------------------------------

using namespace std;

//Functions declarations
void Init();
void OnDraw();
void SpecialKeys(int key,int x,int y);

// FUNCIÓN QUE PREPARA LA TEXTURA
void prepara_textura(char *file, GLuint *tex_id);

// FUNCIÓN QUE DIBUJA
void dibuja(void);

// FUNCIÓN QUE LIBERA LA TEXTURA DE GPU
void libera_textura(GLuint *tex_id);


// IDENTIFICADOR DE TEXTURA
GLuint textura_id;

// OBJETO A DIBUJAR
// GLfloat vertices[] = {0, 0,
// 		      10, 0,
// 		      10, 5,
// 		      0, 5};
//piramide
GLfloat vertices[] = {-1, 0, 1,    1, 0, 1, 0, 2, 0,
             1, 0, 1, 1, 0, -1, 0, 2, 0,
             1, 0, -1, -1, 0, -1, 0, 2, 0,
             -1, 0, -1, -1, 0, 1, 0, 2, 0,
             -1, 0, 1, 1, 0, 1, 1, 0, -1, 
             1, 0, -1, -1, 0, -1, -1, 0, 1};
GLfloat texVertices[] = {0.07, 0.6,  0.15, 0.38,  0.23, 0.6,
            0.3, 0.3,  0.38, 0.1,     0.46, 0.3,
            0.52, 0.3,  0.6, 0.1,  0.7, 0.3,
            0.76, 0.3,  0.86, 0.1,  0.92, 0.3,
            0.52, 0.3,  0.6, 0.1,  0.7, 0.3,
            0.52, 0.3,  0.6, 0.1,  0.7, 0.3,}; 
// GLfloat texVertices[] = {0.0,1.0,
// 			 1.0,1.0,
// 			 1.0,0.0,
// 			 0.0,0.0};

float latitud=0.0,longitud=0.0,radio=24;


void Init(int argc, char **argv){
   //Initialize GLUT windows manager
   //Create the window
   glutInit(&argc, argv);
   glutInitWindowSize(800,600);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("My World");

   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_COLOR_MATERIAL);
   glMatrixMode(GL_PROJECTION);
   gluPerspective( 40.0, 800/600.0f, 0.1, 150);
  
   prepara_textura("./mi_textura3.jpg", &textura_id);
}

void draw_axis(){
   glLineWidth(2);
   glBegin(GL_LINES);
       // eje X, color rojo
       glColor3f(1,0,0);
       glVertex3f(-AxisSize,0,0);
       glVertex3f(AxisSize,0,0);
       // eje Y, color verde
       glColor3f(0,1,0);
       glVertex3f(0,-AxisSize,0);
       glVertex3f(0,AxisSize,0);
       // eje Z, color azul
       glColor3f(0,0,1);
       glVertex3f(0,0,-AxisSize);
       glVertex3f(0,0,AxisSize);
   glEnd();
   glLineWidth(1);
   glColor3f(1,1,1);
}

void OnDraw(void){

   // cámara orbital
   float observador[3];
   float phir,thetar;
   phir=latitud*M_PI/180.0; 
   thetar=longitud*M_PI/180.0;
   observador[0]=radio*sin(thetar)*cos(phir);
   observador[1]=radio*sin(phir);
   observador[2]=radio*cos(phir)*cos(thetar);

   //cleaning the screen
   glClearColor(0.5,0.5,0.5,1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //Define view
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // eye position -> observador
   // target -> (0,0,0)
   // define positive Y axis  -> (0.0, 1.0, 0.0)		
   gluLookAt (observador[0],observador[1],observador[2],0.0,0.0,0.0,0.0,1.0*cos(phir),0.0);

   draw_axis();
   //Put your code here to draw objects
   dibuja();

   //no delete this line
   glutSwapBuffers();
}


void SpecialKeys(int key,int x,int y) {
    switch (key){
	case GLUT_KEY_LEFT:longitud +=2.0;break;
	case GLUT_KEY_RIGHT:longitud -=2.0;break;
	case GLUT_KEY_UP:latitud +=2.0;break;
	case GLUT_KEY_DOWN:latitud -=2.0;break;
	case GLUT_KEY_PAGE_UP:radio +=1.0;break;
	case GLUT_KEY_PAGE_DOWN:radio -=1.0;if (radio<1) radio=1;break;
	}
    glutPostRedisplay();
}

int main(int argc, char** argv) {
   Init(argc, argv);
   //Enter the callbacks
   glutDisplayFunc(OnDraw);
   glutSpecialFunc(SpecialKeys);

   glutMainLoop(); // begin the loop

   // LIBERA LA TEXTURA
   libera_textura(&textura_id);
   return 0;
}


// ----------------------------------------------------------------------
void prepara_textura (char *file, GLuint *tex_id )
{
   vector<unsigned char> data; 
   CImg<unsigned char> image;

   image.load(file);

   // empaquetamos bien los datos
   for (long y = 0; y < image.height(); y ++)
      for (long x = 0; x < image.width(); x ++)
      {
	 unsigned char *r = image.data(x, y, 0, 0);
	 unsigned char *g = image.data(x, y, 0, 1);
	 unsigned char *b = image.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, tex_id);
   glBindTexture(GL_TEXTURE_2D, *tex_id);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}


void dibuja (void)
{
   glEnable(GL_TEXTURE_2D);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

   glBindTexture(GL_TEXTURE_2D, textura_id);

   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
   glDrawArrays(GL_TRIANGLES, 0, 18);
   
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
}

void libera_textura (GLuint *tex_id)
{
   glDeleteTextures(1, tex_id);
}

