//**************************************************************************
// Práctica 2
//**************************************************************************
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>

#include <vector>

#include "objetos_B5.h"

using namespace std;

// tipos
typedef enum {
  CUBO,
  PIRAMIDE,
  OBJETO_PLY,
  ROTACION,
  EXTRUSION,
  CILINDRO,
  ROTACION_PLY,
  CONO,
  ESFERA,
  EXCAVADORA,
  SOLDADO,
  OBJ_PRUEBA1,
  OBJ_PRUEBA2,
  OBJ_PRUEBA3,
  OBJ_PRUEBA4,
  OBJ_EXAMEN1,
  OBJ_EXAMEN2,
  OBJ_EXAMEN3
} _tipo_objeto;
_tipo_objeto t_objeto = CUBO;
_modo modo = POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 650, Window_high = 650;
float movimiento_camara = 0;
bool activada_luz2 = false;

// objetos
_cubo cubo;
_piramide piramide(0.85, 1.3);
_objeto_ply ply;
_rotacion rotacion;
_extrusion *extrusion;
_cilindro cilindro(1, 2, 6, 1, 1);
_cono cono(1, 2, 6);
_esfera esfera(1, 6, 6);
_rotacion_PLY mi_ply;
_excavadora excavadora;
_soldado soldado;
_objPrueba1 objPrueba1;
_objPrueba2 objPrueba2;
_objPrueba3 objPrueba3;
_objPrueba4 objPrueba4;
_objExamen1 objExamen1;
_objExamen2 objExamen2;
_objExamen3 objExamen3;

// _objeto_ply *ply;

int estadoRaton, xc, yc;
float factor = 1.0;
int cambio_orto = 0;
int desplazamiento_x = 0,
      desplazamiento_y = 0;
float Ancho;
float Alto;

void movimientoPiernas(float cantidad_movimiento) {
  if (soldado.giro_piernas >= soldado.giro_piernas_max)
    soldado.piernas_signo = -1;
  if (soldado.giro_piernas <= -soldado.giro_piernas_max)
    soldado.piernas_signo = 1;

  soldado.giro_piernas += cantidad_movimiento * soldado.piernas_signo;
}

void movimientoBrazos(float cantidad_movimiento) {
  if (soldado.giro_brazos_animacion >= soldado.giro_brazos_animacion_max)
    soldado.giro_brazos_animacion_signo = -1;
  if (soldado.giro_brazos_animacion <= -soldado.giro_brazos_animacion_max)
    soldado.giro_brazos_animacion_signo = 1;

  float incremento = cantidad_movimiento * soldado.giro_brazos_animacion_signo;

  soldado.giro_brazos_animacion += incremento;
  if (soldado.giro_brazoIzq_lateral >= 0 || soldado.giro_brazoIzq < -55)
    soldado.giro_brazoIzq += incremento;
}

// animacion
void animacion() {
  if (soldado.animacion) {
    float velocidad = 0.3;
    float vel_rot = velocidad / 2;
    movimientoPiernas(velocidad);
    movimientoBrazos(velocidad);
    if (soldado.activadaRotacion) soldado.rotacion_animacion += vel_rot;
    glutPostRedisplay();
  }
}

//**************************************************************************
//
//***************************************************************************

void clean_window() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero,
  // plano_traser)
  //  plano_delantero>0  plano_trasero>PlanoDelantero)
  glFrustum(-Size_x*factor, Size_x*factor, -Size_y*factor, Size_y*factor, Front_plane, Back_plane); //Vista en perspectiva 1º forma de hacer zoom (multiplicar los 4 primeros parametros * 'factor')
  //3º forma de hacer zoom (multiplicar el plano frontal y rasero por 'factor' siendo este ¿ >1 ó < -1 ?)
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer() {
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -Observer_distance); //Cambiar el centro de proyección //sumar acerca 2º forma
  glRotatef(Observer_angle_x, 1, 0, 0);
  glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis() {
  glDisable(GL_LIGHTING);
  glLineWidth(2);
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1, 0, 0);
  glVertex3f(-AXIS_SIZE, 0, 0);
  glVertex3f(AXIS_SIZE, 0, 0);
  // eje Y, color verde
  glColor3f(0, 1, 0);
  glVertex3f(0, -AXIS_SIZE, 0);
  glVertex3f(0, AXIS_SIZE, 0);
  // eje Z, color azul
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, -AXIS_SIZE);
  glVertex3f(0, 0, AXIS_SIZE);
  glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects() {
  switch (t_objeto) {
    case CUBO:
      cubo.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case PIRAMIDE:
      piramide.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case OBJETO_PLY:
      ply.draw(modo, 1.0, 0.6, 0.0, 5);
      break;
    case ROTACION:
      rotacion.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case CILINDRO:
      cilindro.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case ESFERA:
      esfera.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case CONO:
      cono.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case EXTRUSION:
      extrusion->draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case ROTACION_PLY:
      mi_ply.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case EXCAVADORA:
      excavadora.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case SOLDADO:
      soldado.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case OBJ_EXAMEN1:
      objExamen1.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case OBJ_EXAMEN2:
      objExamen2.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
    case OBJ_EXAMEN3:
      objExamen3.draw(modo, 1.0, 0.0, 0.0, 5);
      break;
      // case OBJ_PRUEBA4:
      //   objPrueba4.draw(modo, 1.0, 0.0, 0.0, 5);
      //   break;
  }
}

//**************************************************************************
//  Función que gestiona la luz
//***************************************************************************
// Alpha = Rotacion luz 2
// La luz 2 se activa con la I y se rota con la O y la P
void luces(float alpha) {
  // Luz blanca
  GLfloat luz_ambiente[] = {0.2, 0.2, 0.2,
                            1.0},  // luz indirecta - rgb, transparencia
      luz_difusa[] = {1.0, 1.0, 1.0, 1.0},     // color
      luz_especular[] = {1.0, 1.0, 1.0, 1.0},  // brillo
      luz_posicion[] = {X_LAMBERT, Y_LAMBERT, Z_LAMBERT,
                        1.0};  // xyz, ultimo parametro = 0 si luz en el
                               // infinito, rayos paralelos | luz puntual = 1

  glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
  glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular);

  glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion);

  // 2º luz - con movimiento
  if (activada_luz2) {
    // luz roja
    GLfloat luz_ambiente2[] = {0.0, 0.0, 0.0, 1.0},  // rgb, transparencia -
        luz_difusa2[] = {1.0, 0.0, 0.0, 1.0},
            luz_especular2[] = {1.0, 0.0, 0.0, 1.0},  // reflejo
        luz_posicion2[] = {0.0, 5.0, 20.0,
                           1.0};  // xyz, ultimo parametro = 0 si luz en el
                                  // infinito, rayos paralelos | luz puntual = 1

    glLightfv(GL_LIGHT2, GL_AMBIENT, luz_ambiente2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, luz_difusa2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular2);

    glPushMatrix();
    glRotatef(alpha, 0, 1, 0);  // Rotacion de la luz
    glLightfv(GL_LIGHT2, GL_POSITION, luz_posicion2);
    glPopMatrix();

    // luz azul
    GLfloat luz_ambiente3[] = {0.0, 0.0, 0.0, 1.0},  // rgb, transparencia -
        luz_difusa3[] = {0.0, 0.0, 1.0, 1.0},
            luz_especular3[] = {0.0, 0.0, 1.0, 1.0},  // reflejo
        luz_posicion3[] = {0.0, 5.0, 20.0,
                           1.0};  // xyz, ultimo parametro = 0 si luz en el
                                  // infinito, rayos paralelos | luz puntual = 1

    glLightfv(GL_LIGHT3, GL_AMBIENT, luz_ambiente3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, luz_difusa3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, luz_especular3);

    glPushMatrix();
    glRotatef(alpha, 0, 1, 0);  // Rotacion de la luz
    glRotatef(180, 0, 1, 0);    // Rotacion de la luz
    glLightfv(GL_LIGHT3, GL_POSITION, luz_posicion3);
    glPopMatrix();

    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
  } else {
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
  }
  glEnable(GL_LIGHT1);
  glDisable(GL_LIGHT0);
}

void vista_orto(){
  //Primera vista 
  glViewport(Ancho/2, Alto/2, Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  draw_axis();
  draw_objects();

  //Segunda vista Planta
  glViewport(0, Alto/2, Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100);

  glRotatef(90,1,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  draw_axis();
  draw_objects();

  //Tercera vista (abajo izq)
  glViewport(0, 0, Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100);
  glRotatef(90,0,1,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  draw_axis();
  draw_objects();
}

//**************************************************************************
//  Función que pinta los objetos
//***************************************************************************

void draw(void) {
  // Dibujamos en el buffer delantero
  glDrawBuffer(GL_FRONT);
  clean_window();
  luces(movimiento_camara);

  if(cambio_orto==0){
    glViewport(0,0,Ancho,Alto);
    change_projection();
    change_observer();
    draw_axis();
    draw_objects();
    // glFlush();
  }
  else
    vista_orto();

  // Dibujamos en el buffer trasero
  // No hacen falta ejes ni luces
  if (t_objeto == SOLDADO) {
    glDrawBuffer(GL_BACK);
    clean_window();
    if(cambio_orto==0){
      change_projection();
      change_observer();
      soldado.seleccion();
    }
  }
  glFlush();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1) {
  float Aspect_ratio;
  Ancho = Ancho1;
  Alto = Alto1;

  Aspect_ratio = (float)Alto1 / (float)Ancho1;
  Size_y = Size_x * Aspect_ratio;
  change_projection();
  glViewport(0, 0, Ancho1, Alto1);
  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y) {
  switch (toupper(Tecla1)) {
    case 'Q':
      exit(0);
    case '1':
      modo = POINTS;
      break;
    case '2':
      modo = EDGES;
      break;
    case '3':
      modo = SOLID;
      break;
    case '4':
      modo = SOLID_COLORS;
      break;
    case '5':
      modo = SOLID_FLAT;
      break;
    case '6':
      modo = SOLID_SMOOTH;
      break;
    case '7':
      modo = SOLID_COLORS1;
      break;
    case '8':
      modo = SOLID_COLORS_VERTEX;
      break;
    case '9':
      cambio_orto = cambio_orto == 1 ? 0 : 1;
      break;
    case 'P':
      t_objeto = PIRAMIDE;
      break;
    case 'C':
      t_objeto = CUBO;
      break;
    case 'O':
      t_objeto = OBJETO_PLY;
      break;
    case 'R':
      t_objeto = ROTACION;
      break;
    case 'X':
      t_objeto = EXTRUSION;
      break;
    case 'L':
      t_objeto = CILINDRO;
      break;
    case 'E':
      t_objeto = ESFERA;
      break;
    case 'N':
      t_objeto = CONO;
      break;
    case 'M':
      t_objeto = ROTACION_PLY;
      break;
    case 'B':
      t_objeto = EXCAVADORA;
      break;
    case 'A':
      t_objeto = SOLDADO;
      break;
    case 'S':
      if (soldado.animacion == false)
        soldado.animacion = true;
      else
        soldado.animacion = false;
      break;
    case 'D':
      if (soldado.activadaRotacion == false)
        soldado.activadaRotacion = true;
      else
        soldado.activadaRotacion = false;
      break;
    case 'F':
      t_objeto = OBJ_EXAMEN1;
      break;
    case 'G':
      t_objeto = OBJ_EXAMEN2;
      break;
    case 'H':
      t_objeto = OBJ_EXAMEN3;
      break;
    case 'I':
      activada_luz2 = activada_luz2 == true ? false : true;
      break;
      // case 'J':
      //   t_objeto = OBJ_PRUEBA4;
      //   break;
    
  }
  glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y) {
  switch (Tecla1) {
    case GLUT_KEY_LEFT:
      Observer_angle_y--;
      break;
    case GLUT_KEY_RIGHT:
      Observer_angle_y++;
      break;
    case GLUT_KEY_UP:
      Observer_angle_x--;
      break;
    case GLUT_KEY_DOWN:
      Observer_angle_x++;
      break;
    case GLUT_KEY_PAGE_UP:
      Observer_distance *= 1.2;
      break;
    case GLUT_KEY_PAGE_DOWN:
      Observer_distance /= 1.2;
      break;

    case GLUT_KEY_F1:
      excavadora.giro_cabina += 5;
      soldado.giro_cabeza += 5;
      if (soldado.giro_cabeza > soldado.giro_cabeza_max)
        soldado.giro_cabeza = soldado.giro_cabeza_max;

      objPrueba4.giro1 += 5;
      objExamen3.transformacion1 += 0.1;
      break;
    case GLUT_KEY_F2:
      excavadora.giro_cabina -= 5;
      soldado.giro_cabeza -= 5;
      if (soldado.giro_cabeza < -soldado.giro_cabeza_max)
        soldado.giro_cabeza = -soldado.giro_cabeza_max;

      objPrueba4.giro1 -= 5;
      objExamen3.transformacion1 -= 0.1;
      break;
    case GLUT_KEY_F3:
      excavadora.giro_primer_brazo += 1;
      if (soldado.giro_brazoIzq_lateral >= 0 || soldado.giro_brazoIzq < -55)
        soldado.giro_brazoIzq += 2.5;
      if (soldado.giro_brazoIzq > soldado.giro_brazo_max)
        soldado.giro_brazoIzq = soldado.giro_brazo_max;

      objPrueba4.transformacion2 += 0.1;
      objExamen3.giro1 += 5;

      break;
    case GLUT_KEY_F4:
      excavadora.giro_primer_brazo -= 1;
      soldado.giro_brazoIzq -= 2.5;
      if (soldado.giro_brazoIzq < soldado.giro_brazo_min)
        soldado.giro_brazoIzq = soldado.giro_brazo_min;
      if (excavadora.giro_primer_brazo < excavadora.giro_primer_brazo_min)
        excavadora.giro_primer_brazo = excavadora.giro_primer_brazo_min;

      objPrueba4.transformacion2 -= 0.1;
      objExamen3.giro1 -= 5;
      break;
    case GLUT_KEY_F5:
      excavadora.giro_segundo_brazo += 1;
      if (excavadora.giro_segundo_brazo > excavadora.giro_segundo_brazo_max)
        excavadora.giro_segundo_brazo = excavadora.giro_segundo_brazo_max;

      movimientoPiernas(2.5);

      break;
    case GLUT_KEY_F6:
      excavadora.giro_segundo_brazo -= 1;
      if (excavadora.giro_segundo_brazo < excavadora.giro_segundo_brazo_min)
        excavadora.giro_segundo_brazo = excavadora.giro_segundo_brazo_min;

      soldado.giro_brazoIzq_lateral += 2;
      if (soldado.giro_brazoIzq_lateral > soldado.giro_brazoIzq_lateral_max)
        soldado.giro_brazoIzq_lateral = soldado.giro_brazoIzq_lateral_max;
      break;
    case GLUT_KEY_F7:
      excavadora.giro_pala += 1;
      if (excavadora.giro_pala > excavadora.giro_pala_max)
        excavadora.giro_pala = excavadora.giro_pala_max;

      if (soldado.giro_brazoIzq <= -55 || soldado.giro_brazoIzq_lateral > 0)
        soldado.giro_brazoIzq_lateral -= 2;
      if (soldado.giro_brazoIzq_lateral < soldado.giro_brazoIzq_lateral_min)
        soldado.giro_brazoIzq_lateral = soldado.giro_brazoIzq_lateral_min;
      break;
    case GLUT_KEY_F8:
      excavadora.giro_pala -= 1;
      if (excavadora.giro_pala < excavadora.giro_pala_min)
        excavadora.giro_pala = excavadora.giro_pala_min;
      break;
    case GLUT_KEY_F9:
      movimiento_camara += 5;
      break;
    case GLUT_KEY_F10:
      movimiento_camara -= 5;
      break;
  }
  glutPostRedisplay();
}

//***************************************************************************
// Funciones para la selección por color
//***************************************************************************

void procesar_color(unsigned char color[3]) {
  int i;

  for (i = 0; i < soldado.piezas; i++) {
    if (color[0] == soldado.color_select[i].r &&
        color[1] == soldado.color_select[i].g &&
        color[2] == soldado.color_select[i].r) {
      if (soldado.activo[i] == 0) {
        soldado.activo[i] = 1;
      } else {
        soldado.activo[i] = 0;
      }
      glutPostRedisplay();
    }
  }
}

//***************************************************************************

void pick_color(int x, int y) {
  GLint viewport[4];  // variable pa el tamaño del dispositivo de salida
  unsigned char pixel[3];

  glGetIntegerv(GL_VIEWPORT, viewport);  // lee el tamaño del disp de sali
  glReadBuffer(GL_BACK);                 // seleccionamos leer el buffer trasero
  glReadPixels(
      x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE,
      (GLubyte *)&pixel[0]);  // x=punto del raton, -y porque el 0,0 del raton
                              // esta abajo a la izq, num pixels a leer 1*1,
                              // formato color, formato pixels
  printf(" valor x %d, valor y %d, color %d, %d, %d \n", x, y, pixel[0],
         pixel[1], pixel[2]);

  procesar_color(pixel);  // modifica el color
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton(int boton, int estado, int x, int y) {
  if (boton == GLUT_RIGHT_BUTTON) {
    if (estado == GLUT_DOWN) {
      estadoRaton = 1;
      xc = x;
      yc = y;
    } else
      estadoRaton = 0;
  }
  if (boton == GLUT_LEFT_BUTTON) {
    if (estado == GLUT_DOWN) {
      estadoRaton = 2;
      xc = x;
      yc = y;
      pick_color(xc, yc);
    }
  }

  if(boton==3){
    factor*=1.1;
    glutPostRedisplay();
  }
  if (boton==4){
    factor*=0.9;
    glutPostRedisplay();
  }
  
}

/*************************************************************************/

void RatonMovido(int x, int y) {
  if (estadoRaton == 1) {
    Observer_angle_y = Observer_angle_y - (x - xc);
    Observer_angle_x = Observer_angle_x + (y - yc);
    xc = x;
    yc = y;
    glutPostRedisplay();
  }
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void) {
  // se inicalizan la ventana y los planos de corte
  Size_x = 0.5;
  Size_y = 0.5;
  Front_plane = 1;
  Back_plane = 1000;

  // se incia la posicion del observador, en el eje z
  Observer_distance = 4 * Front_plane;
  Observer_angle_x = 0;
  Observer_angle_y = 0;

  // se indica el color para limpiar la ventana	(r,v,a,al)
  // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
  glClearColor(1, 1, 1, 1);

  // se habilita el z-bufer
  glEnable(GL_DEPTH_TEST);
  change_projection();
  glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[]) {
  // perfil

  vector<_vertex3f> perfil, poligono;
  _vertex3f aux;

  aux.x = 1.0;
  aux.y = -1.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 1.5;
  aux.y = 0.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 1.0;
  aux.y = 1.0;
  aux.z = 0.0;
  perfil.push_back(aux);

  rotacion.parametros(perfil, 6, 0, 1, 1);

  aux.x = 1.0;
  aux.y = 0.0;
  aux.z = 1.0;
  poligono.push_back(aux);
  aux.x = 1.0;
  aux.y = 0.0;
  aux.z = -1.0;
  poligono.push_back(aux);
  aux.x = -1.2;
  aux.y = 0.0;
  aux.z = -1.0;
  poligono.push_back(aux);
  aux.x = -0.8;
  aux.y = 0.0;
  aux.z = 0.0;
  poligono.push_back(aux);
  aux.x = -1.2;
  aux.y = 0.0;
  aux.z = 1.0;
  poligono.push_back(aux);

  extrusion = new _extrusion(poligono, 0.25, 1.0, 0.25);

  // se llama a la inicialización de glut
  glutInit(&argc, argv);

  // se indica las caracteristicas que se desean para la visualización con
  // OpenGL Las posibilidades son: GLUT_SIMPLE -> memoria de imagen simple
  // GLUT_DOUBLE -> memoria de imagen doble
  // GLUT_INDEX -> memoria de imagen con color indizado
  // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada
  // pixel GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y
  // alfa para cada pixel GLUT_DEPTH -> memoria de profundidad o z-bufer
  // GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  // posicion de la esquina inferior izquierdad de la ventana
  glutInitWindowPosition(Window_x, Window_y);

  // tamaño de la ventana (ancho y alto)
  glutInitWindowSize(Window_width, Window_high);

  // llamada para crear la ventana, indicando el titulo (no se visualiza hasta
  // que se llama al bucle de eventos)
  glutCreateWindow("PRACTICA - 5");

  // asignación de la funcion llamada "dibujar" al evento de dibujo
  glutDisplayFunc(draw);
  // asignación de la funcion llamada "change_window_size" al evento
  // correspondiente
  glutReshapeFunc(change_window_size);
  // asignación de la funcion llamada "normal_key" al evento correspondiente
  glutKeyboardFunc(normal_key);
  // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
  glutSpecialFunc(special_key);

  // funcion de inicialización
  initialize();

  // creación del objeto ply - codigo beethoven
  ply.parametros(argv[2]);

  // creación del objeto ply - codigo mi_archivo.ply
  mi_ply.parametros_PLY(argv[1], 8);

  // ply = new _objeto_ply(argv[1]);

  // Animación automatica
  glutIdleFunc(animacion);

  //Raton
  glutMouseFunc(clickRaton);
  glutMotionFunc(RatonMovido);


  // inicio del bucle de eventos
  glutMainLoop();
  return 0;
}
