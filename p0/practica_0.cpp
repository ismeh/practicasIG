#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h> //interfaz gráfico



void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
 
// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6); //carne
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.); //negro
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

//orejas
   //izq
   glBegin(GL_POLYGON);
      glVertex3f(-0.25,0.15,0.0); //abajo izq
      glVertex3f(-0.25,0.35,0.0);  //arriba izq
      glVertex3f(-0.2,0.35,0.0); //arriba dcha
      glVertex3f(-0.2,0.15,0.0); //abajo dcha
   glEnd();

   glColor3f(1.0,0.8,0.6); //carne
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   

   //dcha
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


   
}


static void Init( )
{

   glShadeModel( GL_FLAT); // Flat -> Coge el ultimo color activado
                           // smooth -> mezcla colores
}


static void Reshape( int width, int height ) //Modificar el tamaño de la ventana
{
    glViewport(0, 0, (GLint)width, (GLint)height); 
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0); //Indica el espacio del mundo
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0); //Color de fondo
  glClear( GL_COLOR_BUFFER_BIT ); //Borra lo que habia (actualiza la imagen (hace que se vea bien al redimensionar la ventana))
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 500, 500 );
   glutInitWindowSize(800, 800 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape); //Modificar el tamaño de la ventana
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

