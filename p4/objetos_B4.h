//**************************************************************************
// Práctica 2
//**************************************************************************

#include <GL/gl.h>
#include <stdlib.h>

#include <vector>

#include "vertex.h"

const float AXIS_SIZE = 5000;
typedef enum {
  POINTS,
  EDGES,
  SOLID,
  SOLID_COLORS,
  SOLID_COLORS_VERTEX,
  SOLID_COLORS1
} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D {
 public:
  _puntos3D();
  void draw_puntos(float r, float g, float b, int grosor);

  vector<_vertex3f> vertices;
  vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D {
 public:
  _triangulos3D();
  void draw_aristas(float r, float g, float b, int grosor);
  void draw_solido(float r, float g, float b);
  void draw_solido_colores();
  void draw_solido_colores_vertices();
  void draw_solido_colors1();
  void draw(_modo modo, float r, float g, float b, float grosor);

  /* asignación de colores */
  void colors_random();
  void colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);

  //l_{x,y,z} coordenas del foco
  //Depende del angula entre la normal de la cara y el vector normalizado que va desde el centro de la cara hasta el foco
  void color_lambert_c(float l_x, float l_y, float l_z, float r, float g, float b);

  void calcular_normales_caras();
  void calcular_normales_vertices();

  vector<_vertex3i> caras;
  vector<_vertex3f> colores_caras;

  //Vectores para las normales
  vector<_vertex3f> normales_caras;
  vector<_vertex3f> normales_vertices;
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D {
 public:
  _cubo(float tam = 0.5);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D {
 public:
  _piramide(float tam = 0.5, float al = 1.0);
};

class _objPrueba1 : public _triangulos3D {
  public:
    _objPrueba1(float tam = 0.5, float al = 1.0);
};


//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply : public _triangulos3D {
 public:
  _objeto_ply();

  void parametros(char *archivo);  //
};

//************************************************************************
// objeto por revolución
//************************************************************************
// tipo indica si es una figura por revolución normal o bien un cono o una
// esfera tipo=0 normal, tipo=1 cono, tipo=2 esfera tapa_in=0 sin tapa,
// tapa_in=1 con tapa tapa_su=0 sin tapa, tapa_su=1 con tapa
class _rotacion : public _triangulos3D {
 public:
  _rotacion();

  void parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in,
                  int tapa_su);
};

// cilindro
class _cilindro : public _rotacion {
 public:
   _cilindro(float radio = 1.0, float altura = 2.0, int num = 12,int tapa_in=1, int tapa_su=1);
  float _radio;
};

// cono
class _cono : public _rotacion {
 public:
  _cono(float radio = 1.0, float altura = 2.0, int num=12);
};

// esfera
class _esfera : public _rotacion {
 public:
  _esfera(float radio, int num1, int num2);
};

// esfera
class _objPrueba2 : public _rotacion {
 public:
  _objPrueba2(float r1=0.4, float r2=0.6, int num1=8, int num2=8);
};

//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion : public _triangulos3D {
 public:
  _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};

//************************************************************************
// rotacion archivo PLY
//************************************************************************
class _rotacion_PLY : public _rotacion {
 public:
  _rotacion_PLY();
  void parametros_PLY(char *archivo, int num);
};

//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

class _pala : public _triangulos3D {
 public:
  _pala(float radio = 1.0, float ancho = 2.0, int num = 8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo : public _triangulos3D {
 public:
  _brazo();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina : public _triangulos3D {
 public:
  _cabina();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion : public _triangulos3D {
 public:
  _sustentacion();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

  float radio;

 protected:
  _cilindro rueda;
  _cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora : public _triangulos3D {
 public:
  _excavadora();

  void draw(_modo modo, float r, float g, float b, float grosor);

  float giro_cabina;
  float giro_primer_brazo;
  float giro_segundo_brazo;
  float giro_pala;

  float giro_primer_brazo_max;
  float giro_primer_brazo_min;
  float giro_segundo_brazo_max;
  float giro_segundo_brazo_min;
  float giro_pala_max;
  float giro_pala_min;

  float tamanio_pala;

 protected:
  _pala pala;
  _brazo brazo;
  _cabina cabina;
  _sustentacion sustentacion;
};

////////////////////////////////////
//Mi objeto
class _cabeza : public _triangulos3D{
 public:
  _cabeza();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
};

class _tronco : public _triangulos3D{
 public:
  _tronco();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
};

class _escudo : public _triangulos3D{
public:
  _escudo();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
  _cilindro*  cilindro = new _cilindro(0.7,0.5,4,0,0);

};

class _brazoIzq : public _triangulos3D{
 public:
  _brazoIzq();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
  _escudo escudo;
};

class _espada : public _triangulos3D{
  public:
  _espada();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cruz;
  _cubo cuerpo;
  _cubo punta;

};

class _brazoDch: public _triangulos3D{
 public:
  _brazoDch();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
  _espada espada;
};

class _piernaIzq : public _triangulos3D{
 public:
  _piernaIzq();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
};

class _piernaDch : public _triangulos3D{
 public:
  _piernaDch();
  void draw(_modo modo, float r, float g, float b, float grosor);

  float ancho;
  float alto;
  float fondo;

 protected:
  _cubo cubo;
};

class _soldado : public _triangulos3D{
  public:
    float giro_cabeza;
    float giro_brazoIzq;
    float giro_piernas;
    float giro_brazoIzq_lateral;

    float giro_cabeza_max;
    float giro_brazo_max;
    float giro_brazo_min;
    float giro_piernas_max;
    float giro_brazoIzq_lateral_max;
    float giro_brazoIzq_lateral_min;

    //animacion
    int piernas_signo;
    float giro_brazos_animacion_max;
    int giro_brazos_animacion_signo;
    float giro_brazos_animacion;
    bool animacion;
    float rotacion_animacion;
    bool activadaRotacion;



    _soldado();
    void draw(_modo modo, float r, float g, float b, float grosor);

  protected:
    _cabeza cabeza;
    _tronco tronco;
    _piernaIzq piernaIzq;
    _piernaDch piernaDch;
    _brazoIzq brazoIzq;
    _brazoDch brazoDch;
    _escudo escudo;
    _espada espada;

};

class _objPrueba3 : public _triangulos3D{
  public:
    float ancho;
    float alto;
    float fondo;

    _objPrueba3();
    void draw(_modo modo, float r, float g, float b, float grosor);

  protected:
   _cubo base;
   _cubo arriba;
   _cilindro vertical;
   _cilindro horizontal;
};

class _objPrueba4 : public _triangulos3D{
  public:
    float ancho;
    float alto;
    float fondo;

    float giro1;
    float transformacion2;

    _objPrueba4();
    void draw(_modo modo, float r, float g, float b, float grosor);

  protected:
   _cubo base;
   _cubo arriba;
   _cilindro tumbado;
   _cono cono;
};


