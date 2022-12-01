//**************************************************************************
// Práctica 2
//**************************************************************************

#include "objetos_B4.h"

#include "file_ply_stl.hpp"



void _triangulos3D::cambiarMaterial(_vertex4f dif, _vertex4f esp, float b){
  ambiente_difuso = dif;
  ambiente_especular = esp;
  brillo = b;
}

void _triangulos3D::cambiarMaterial(material m){
  ambiente_difuso = m.ambiente_difuso;
  ambiente_especular = m.ambiente_especular;
  brillo = m.brillo;
}

double gradosARadianes(double grados)
{
    return grados * M_PI / 180;
}

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D() {}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor) {
  //**** usando vertex_array ****
  glPointSize(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawArrays(GL_POINTS, 0, vertices.size());

  /*int i;
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
          glVertex3fv((GLfloat *) &vertices[i]);
          }
  glEnd();*/
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D() {
  ambiente_difuso=_vertex4f(1.0,0.8,0,1.0);
  ambiente_especular=_vertex4f(0.5,0.5,0.5,1.0);
  brillo=110; //Entre 0 y 127
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor) {
  //**** usando vertex_array ****
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);

  /*int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
          glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
          glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
          glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
          }
  glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b) {
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++) {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores() {
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  for (i = 0; i < caras.size(); i++) {
    glColor3f(colores_caras[i].r, colores_caras[i].g, colores_caras[i].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

void _triangulos3D::draw_solido_colores_vertices() {
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++) {
    glColor3f(colores_vertices[caras[i]._0].r, colores_vertices[caras[i]._0].g,
              colores_vertices[caras[i]._0].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);

    glColor3f(colores_vertices[caras[i]._1].r, colores_vertices[caras[i]._1].g,
              colores_vertices[caras[i]._1].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);

    glColor3f(colores_vertices[caras[i]._2].r, colores_vertices[caras[i]._2].g,
              colores_vertices[caras[i]._2].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

void _triangulos3D::draw_solido_colors1() {
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);

  for (i = 0; i < caras.size(); i++) {
    glColor3f(rand() % 1000 / 1000.0, rand() % 1000 / 1000.0,
              rand() % 1000 / 1000.0);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo solido con iluminación plana
//*************************************************************************
  void _triangulos3D::draw_solido_plano(){
    int i;
    glEnable(GL_LIGHTING); //Activamos la iluminación
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &ambiente_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_TRIANGLES);

    for (i = 0; i < caras.size(); i++) {
      glNormal3f(normales_caras[i].x, normales_caras[i].y, normales_caras[i].z);
      glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
      glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
      glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
    }
    glEnd();
    glDisable(GL_LIGHTING); //Una vez dibujado desactivamos la iluminación para que no afecte a otros objetos

  }
  void _triangulos3D::draw_solido_suave(){
    //normal para cada vertice
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *)&ambiente_difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat*)&ambiente_especular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);  // este es solo float

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    int num_tot_caras = caras.size();

    for (int i = 0; i < num_tot_caras; i++) {
        glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
        glVertex3fv((GLfloat*)&vertices[caras[i]._0]);

        glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
        glVertex3fv((GLfloat*)&vertices[caras[i]._1]);

        glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
        glVertex3fv((GLfloat*)&vertices[caras[i]._2]);
    }
    glDisable(GL_LIGHTING);
    glEnd();
  }

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor) {
  switch (modo) {
    case POINTS:
      draw_puntos(r, g, b, grosor);
      break;
    case EDGES:
      draw_aristas(r, g, b, grosor);
      break;
    case SOLID:
      draw_solido(r, g, b);
      break;
    case SOLID_COLORS:
      draw_solido_colores();
      break;
    case SOLID_COLORS_VERTEX:
      draw_solido_colores();
      break;
    case SOLID_COLORS1:
      draw_solido_colors1();
      break;
    case SOLID_FLAT:
      draw_solido_plano();
      break;
    case SOLID_SMOOTH:
      draw_solido_suave();
      break;
  }
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random() {
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  srand(time(NULL));
  for (i = 0; i < n_c; i++) {
    colores_caras[i].r = rand() % 1000 / 1000.0;
    colores_caras[i].g = rand() % 1000 / 1000.0;
    colores_caras[i].b = rand() % 1000 / 1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2,
                                 float g2, float b2) {
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  for (i = 0; i < n_c; i++) {
    if (i % 2 == 0) {
      colores_caras[i].r = r1;
      colores_caras[i].g = g1;
      colores_caras[i].b = b1;
    } else {
      colores_caras[i].r = r2;
      colores_caras[i].g = g2;
      colores_caras[i].b = b2;
    }
  }
}

//*************************************************************************
//  Calcular normales
//*************************************************************************

  void _triangulos3D::calcular_normales_caras(){
    int n_c;
    _vertex3f vector_a, vector_b, aux;
    float modulo;

    n_c = caras.size();
    normales_caras.resize(n_c);

    for (int i=0; i < n_c; i++){
      vector_a = vertices[caras[i]._1]-vertices[caras[i]._0];
      vector_b = vertices[caras[i]._2]-vertices[caras[i]._0];

      //Producto vectorial (determinante)
      aux.x = vector_a.y * vector_b.z - vector_a.z * vector_b.y;
      aux.y = vector_a.z * vector_b.x - vector_a.x * vector_b.z;
      aux.z = vector_a.x * vector_b.y - vector_a.y * vector_b.x;

      //Normalizar el vector
      modulo = sqrt(aux.x*aux.x + aux.y*aux.y + aux.z*aux.z);
      normales_caras[i].x = aux.x/modulo;
      normales_caras[i].y = aux.y/modulo;
      normales_caras[i].z = aux.z/modulo;
    }
  }

  void _triangulos3D::calcular_normales_vertices(){
     int i, n_v;
    float norma;
    n_v = vertices.size();
    normales_vertices.resize(n_v);

    for(i=0; i < n_v; i++){
        normales_vertices[i].x = 0;
        normales_vertices[i].y = 0;
        normales_vertices[i].z = 0;
    }

    for(i = 0; i < caras.size(); i++){
        normales_vertices[caras[i]._0] += normales_caras[i];
        normales_vertices[caras[i]._1] += normales_caras[i];
        normales_vertices[caras[i]._2] += normales_caras[i];
    }

    for(i=0; i < n_v; i++){
        norma = sqrt(normales_vertices[i].x*normales_vertices[i].x +
                    normales_vertices[i].y*normales_vertices[i].y +
                    normales_vertices[i].z*normales_vertices[i].z);
        normales_vertices[i].x /= norma;
        normales_vertices[i].y /= norma;
        normales_vertices[i].z /= norma;
    }

  }

//*************************************************************************
// Color lamber
//*************************************************************************
  void _triangulos3D::color_lambert_c(float l_x, float l_y, float l_z, float r, float g, float b){
    int i, n_c;
    n_c = caras.size();
    colores_caras.resize(n_c);
    normales_caras.resize(n_c);
    _vertex3f aux_luz, luz;
    float modulo, p_escalar;

    aux_luz.x = l_x; 
    aux_luz.y = l_y; 
    aux_luz.z = l_z; 

    for(i = 0; i < n_c; i++){
      luz = aux_luz - vertices[caras[i]._0];
      modulo = sqrt(luz.x*luz.x + luz.y*luz.y + luz.z*luz.z);

      luz.x = luz.x/modulo;
      luz.y = luz.y/modulo;
      luz.z = luz.z/modulo;

      p_escalar = luz.x*normales_caras[i].x + luz.y*normales_caras[i].y + luz.z*normales_caras[i].z;
      if(p_escalar < 0)
        p_escalar = 0;

      colores_caras[i].r=r * p_escalar + r*0.2; //r*0.2 componente ambiental - da un color minimo
      colores_caras[i].g=g * p_escalar + g*0.2;
      colores_caras[i].b=b * p_escalar + b*0.2 + 0.01;
    }
  }


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam) {
  // vertices
  vertices.resize(8);
  vertices[0].x = -tam;
  vertices[0].y = -tam;
  vertices[0].z = -tam;
  vertices[1].x = tam;
  vertices[1].y = -tam;
  vertices[1].z = -tam;
  vertices[2].x = tam;
  vertices[2].y = -tam;
  vertices[2].z = tam;
  vertices[3].x = -tam;
  vertices[3].y = -tam;
  vertices[3].z = tam;

  vertices[4].x = -tam;
  vertices[4].y = tam;
  vertices[4].z = -tam;
  vertices[5].x = tam;
  vertices[5].y = tam;
  vertices[5].z = -tam;
  vertices[6].x = tam;
  vertices[6].y = tam;
  vertices[6].z = tam;
  vertices[7].x = -tam;
  vertices[7].y = tam;
  vertices[7].z = tam;

  // Colores para los vertices
  colores_vertices.resize(8);  // color entre 0 y 1
  for (int i = 0; i < 8; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  // // triangulos
  caras.resize(12);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 4;
  caras[1]._2 = 5;
  caras[2]._0 = 1;
  caras[2]._1 = 5;
  caras[2]._2 = 6;
  caras[3]._0 = 1;
  caras[3]._1 = 2;
  caras[3]._2 = 6;
  caras[4]._0 = 2;
  caras[4]._1 = 3;
  caras[4]._2 = 6;
  caras[5]._0 = 3;
  caras[5]._1 = 7;
  caras[5]._2 = 6;
  caras[6]._0 = 0;
  caras[6]._1 = 3;
  caras[6]._2 = 4;
  caras[7]._0 = 3;
  caras[7]._1 = 4;
  caras[7]._2 = 7;
  caras[8]._0 = 0;
  caras[8]._1 = 1;
  caras[8]._2 = 3;
  caras[9]._0 = 1;
  caras[9]._1 = 2;
  caras[9]._2 = 3;
  caras[10]._0 = 4;
  caras[10]._1 = 5;
  caras[10]._2 = 7;
  caras[11]._0 = 5;
  caras[11]._1 = 6;
  caras[11]._2 = 7;


  //normales caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores para las caras
  // colors_random();
  color_lambert_c(X_LAMBERT , Y_LAMBERT , Z_LAMBERT , 1.0, 0.8, 0);

}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al) {
  // vertices
  vertices.resize(5);
  vertices[0].x = -tam;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = -tam;
  vertices[3].x = -tam;
  vertices[3].y = 0;
  vertices[3].z = -tam;
  vertices[4].x = 0;
  vertices[4].y = al;
  vertices[4].z = 0;

  // Colores para los vertices
  colores_vertices.resize(5);  // color entre 0 y 1
  for (int i = 0; i < 5; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  caras.resize(6);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 2;
  caras[1]._2 = 4;
  caras[2]._0 = 2;
  caras[2]._1 = 3;
  caras[2]._2 = 4;
  caras[3]._0 = 3;
  caras[3]._1 = 0;
  caras[3]._2 = 4;
  caras[4]._0 = 3;
  caras[4]._1 = 1;
  caras[4]._2 = 0;
  caras[5]._0 = 3;
  caras[5]._1 = 2;
  caras[5]._2 = 1;

  // colores para las caras
  // colors_random();
  calcular_normales_caras();
  calcular_normales_vertices();
  color_lambert_c(X_LAMBERT , Y_LAMBERT , Z_LAMBERT , 1.0, 0.8, 0);

}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply() {
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::parametros(char *archivo) {
  int n_ver, n_car;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car = car_ply.size() / 3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);

  // vertices
  for (int i = 0; i < n_ver; i++) {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
  }

  // Colores para los vertices
  colores_vertices.resize(n_ver);  // color entre 0 y 1
  for (int i = 0; i < n_ver; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  // caras
  for (int i = 0; i < n_car; i++) {
    caras[i].x = car_ply[3 * i];
    caras[i].y = car_ply[3 * i + 1];
    caras[i].z = car_ply[3 * i + 2];
  }

  //normales a caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores para las caras
  // colors_random();
  color_lambert_c (-20, 20, 10, 1.0 ,0.8, 0); // luz picada
  // color_lambert_c (0, 10, 40, 1.0 ,0.8, 0);

}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion() {}

/*
                num = numero de giros
                Tipo-> Esfera cono...
                        Tipo 0 normal, 1 cono, 2 esfera
                tapa_inferior=0 sin tapa, 1 con tapa
                tapa_superior=0 sin tapa, 1 con tapa
        */
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo,
                           int tapa_in, int tapa_su) {
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;  // Tamaño del perfil
  float radio;

  // tratamiento de los vértice

  num_aux = perfil.size();

  if (tipo == 1)
    num_aux -= 1;  // Si es un cono el número de vertices del perfil = 1
  if (tipo == 2)
    radio = sqrt(perfil[0].x * perfil[0].x +
                 perfil[0].y * perfil[0].y);  // Para el circulo

  vertices.resize(num_aux * num);  //+1 = vertice central de las tapaderas = +2

  // giro en el eje X, pa programar otros ejes mirar diapositiva
  for (j = 0; j < num; j++) {
    for (i = 0; i < num_aux; i++) {
      vertice_aux.x =
          perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +  // 360º (en radianes) /num
          perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.z = 
          -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
          perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].y;
      
      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  // tratamiento de las caras
  // caras[0]._0=0;
  // caras[0]._1=num_aux;
  // caras[0]._2=1;

  // caras[1]._0=num_aux;
  // caras[1]._1=num_aux+1;
  // caras[1]._2=1;
  int num_caras = 2 * (num_aux - 1) * num + 2 * num;
  caras.resize(num_caras);  //+num?
  int c = 0;

  for (int j = 0; j < num; j++) {
    for (int i = 0; i < num_aux - 1; i++) {  // -1 porque es el número de segmentos que se pueden crear entre los puntos del perfil.
      caras[c]._0 = i + j * num_aux;
      caras[c]._1 = ((j + 1) % num) * num_aux + i;
      caras[c]._2 = 1 + i + j * num_aux;

      c++;

      caras[c]._0 = ((j + 1) % num) * num_aux + i;
      caras[c]._1 = ((j + 1) % num) * num_aux + i + 1;
      caras[c]._2 = 1 + i + j * num_aux;
      c++;
    }
  }

  int total_matriz = num_aux * num;

  // tapa inferior
  /*Consiste en colocar un punto en medio y crear triangulos a partir de los
   * vertices y el punto medio*/
  if (tapa_in == 1) {
    vertices.resize(vertices.size() + 1);
    vertices[total_matriz].x = 0.0;
    vertices[total_matriz].y = vertices[0].y;  // perfil[0] o vertices[]
    vertices[total_matriz].z = 0.0;

    if (tipo == 2) vertices[total_matriz].y = -radio;

    for (int j = 0; j < num; j++) {
      caras[c]._0 = j * num_aux;
      caras[c]._2 = ((j + 1) % num) * num_aux;
      caras[c]._1 = total_matriz;

      c++;
    }
  }

  // tapa superior
  if (tapa_su == 1) {
    vertices.resize(vertices.size() + 1);
    vertices[total_matriz + 1].x = 0.0;
    vertices[total_matriz + 1].y = vertices[num_aux - 1].y;
    vertices[total_matriz + 1].z = 0.0;

    if (tipo == 1) vertices[total_matriz + 1].y = perfil[perfil.size() - 1].y;
    if (tipo == 2) vertices[total_matriz + 1].y = radio;

    for (int j = 0; j < num; j++) {
      caras[c]._0 = total_matriz + 1;
      caras[c]._2 = ((j + 1) % num) * num_aux + num_aux - 1;
      caras[c]._1 = j * num_aux + num_aux - 1;

      c++;
    }
  }

  // Colores para los vertices
  colores_vertices.resize(total_matriz);  // color entre 0 y 1
  for (int i = 0; i < total_matriz; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  //normales a caras
  calcular_normales_caras();
  calcular_normales_vertices();

  // colores para las caras
  // colors_random();
  color_lambert_c (0, 10, 40, 1.0 ,0.8, 0);
}

//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z) {
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice

  num_aux = poligono.size();
  vertices.resize(num_aux * 2);
  for (i = 0; i < num_aux; i++) {
    vertices[2 * i] = poligono[i];
    vertices[2 * i + 1].x = poligono[i].x + x;
    vertices[2 * i + 1].y = poligono[i].y + y;
    vertices[2 * i + 1].z = poligono[i].z + z;
  }

  // tratamiento de las caras

  caras.resize(num_aux * 2);
  int c = 0;
  for (i = 0; i < num_aux; i++) {
    caras[c]._0 = i * 2;
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
    caras[c]._0 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2) + 1;
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
  }

  // colores caras
  int num_caras = caras.size();
  colores_caras.resize(num_caras);
  // srand(10);
  // for (int i = 0; i < num_caras; i++) {
  //   colores_caras[i].r = rand() % 1000 / 1000.0;
  //   colores_caras[i].g = rand() % 1000 / 1000.0;
  //   colores_caras[i].b = rand() % 1000 / 1000.0;
  // }

  // Colores para los vertices
  colores_vertices.resize(num_aux);  // color entre 0 y 1
  for (int i = 0; i < num_aux; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  calcular_normales_caras();
  calcular_normales_vertices();
  color_lambert_c(X_LAMBERT , Y_LAMBERT , Z_LAMBERT , 1.0, 0.8, 0);
}


// cilindro
_cilindro::_cilindro(float radio, float altura, int num, int tapa_in, int tapa_su) {
  vector<_vertex3f> perfil;
  _vertex3f vert_aux;
  _radio = radio;

  vert_aux.x = radio;
  vert_aux.y = -altura / 2.0;
  vert_aux.z = 0.0;

  perfil.push_back(vert_aux);

  vert_aux.x = radio;
  vert_aux.y = altura / 2.0;
  vert_aux.z = 0.0;

  perfil.push_back(vert_aux);

  parametros(perfil, num, 0, tapa_in, tapa_su);
}

// cono
_cono::_cono(float radio, float altura, int num) {
  vector<_vertex3f> perfil;
  _vertex3f vert_aux;
  vert_aux.x = radio;
  vert_aux.y = 0.0;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);
  vert_aux.x = 0.0;
  vert_aux.y = altura;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);

  parametros(perfil, num, 1, 1, 1);
}

// esfera
// num1 -> Numero lineas paralelas (puntos del perfil)
_esfera::_esfera(float radio, int num1, int num2) {
  vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;

  // Empezamos en 1 pa no repetir el punto inferior muchas veces
  for (i = 1; i < num1; i++) {
    aux.x = radio * cos(M_PI * i / num1 * 1.0 - M_PI / 2.0);  // Media vuelta empezando en -pi/2
    aux.y = radio * sin(M_PI * i / num1 * 1.0 - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);
  }

  parametros(perfil, num2, 2, 1, 1);
}

_rotacion_PLY::_rotacion_PLY() {}

void _rotacion_PLY::parametros_PLY(char *archivo, int num) {
  int n_ver, n_car;
  vector<_vertex3f> perfil;
  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3;
  n_car=car_ply.size()/3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver + 2);

  // vertices
  for (int i = 0; i < n_ver; i++) {
    vertices[i].x = ver_ply[3 * i];
    vertices[i].y = ver_ply[3 * i + 1];
    vertices[i].z = ver_ply[3 * i + 2];
    perfil.push_back(vertices[i]);
  }

  // Colores para los vertices
  colores_vertices.resize(n_ver);  // color entre 0 y 1
  for (int i = 0; i < 5; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  _vertex3f vert_aux;
  vert_aux.x = 1.04;
  vert_aux.y = 0.0;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);
  vert_aux.x = 0.0;
  vert_aux.y = 13.84;
  vert_aux.z = 0.0;
  perfil.push_back(vert_aux);

  parametros(perfil, num, 1, 1, 1);
}

//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

_pala::_pala(float radio, float ancho, int num) {
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int i, j;

  vertice_aux.x = radio;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  perfil.push_back(vertice_aux);
  vertice_aux.z = ancho / 2.0;
  perfil.push_back(vertice_aux);

  // tratamiento de los vértices

  for (j = 0; j <= num; j++) {
    for (i = 0; i < 2; i++) {
      vertice_aux.x = perfil[i].x * cos(M_PI * j / (1.0 * num)) -
                      perfil[i].y * sin(M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].x * sin(M_PI * j / (1.0 * num)) +
                      perfil[i].y * cos(M_PI * j / (1.0 * num));
      vertice_aux.z = perfil[i].z;
      vertices.push_back(vertice_aux);
    }
  }

  // tratamiento de las caras

  for (j = 0; j < num; j++) {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = (j + 1) * 2 + 1;
    caras.push_back(cara_aux);

    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = j * 2 + 1;
    caras.push_back(cara_aux);
  }

  // tapa inferior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++) {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  // tapa superior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++) {
    cara_aux._0 = j * 2 + 1;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

//************************************************************************
// brazo
//************************************************************************

_brazo::_brazo() {
  ancho = 0.6;
  alto = 0.1;
  fondo = 0.1;
  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  glTranslatef(0.5, 0, 0);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina() {
  ancho = 0.4;
  alto = 0.6;
  fondo = 0.4;
  cubo.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion() {
  ancho = 1.2;
  alto = 0.3;
  fondo = 0.8;
  radio = 0.15;
  base.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glTranslatef(2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora() {
  giro_cabina = 0.0;
  giro_primer_brazo = 0.0;
  giro_primer_brazo_max = 0;
  giro_primer_brazo_min = -90;
  giro_segundo_brazo = 0.0;
  giro_segundo_brazo_max = 30;
  giro_segundo_brazo_min = 0;
  giro_pala = 0.0;
  giro_pala_max = 50.0;
  giro_pala_min = -90.0;

  tamanio_pala = 0.15;
};

void _excavadora::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();

  sustentacion.draw(modo, r, g, b, grosor);

  glTranslatef(0, (cabina.alto + sustentacion.alto) / 2.0, 0);
  glRotatef(giro_cabina, 0, 1, 0);
  cabina.draw(modo, r, g, b, grosor);

  glTranslatef(cabina.ancho / 2.0, 0, 0);
  glRotatef(giro_segundo_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_primer_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_pala, 0, 0, 1);
  glTranslatef(tamanio_pala, 0, 0);
  glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
  pala.draw(modo, r, g, b, grosor);

  glPopMatrix();
};

//Mi objeto
_cabeza::_cabeza() {
  ancho = 1;
  alto = 1;
  fondo = 1.2;

  //Carne
  // cubo.colors_chess(0.89, 0.76, 0.6, 0.88, 0.72, 0.55);
  cubo.colors_chess(0.59, 0.56, 0.56, 0.57, 0.54, 0.54);

  cubo.cambiarMaterial(gold);

};

void _cabeza::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_tronco::_tronco() {
  ancho = 1.5;
  alto = 3;
  fondo = 1;
  cubo.colors_chess(0.56, 0.56, 0.56, 0.58, 0.57, 0.59);
  cubo.cambiarMaterial(gold);

};

void _tronco::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_brazoIzq::_brazoIzq() {
  ancho = 0.5;
  alto = 4;
  fondo = 1;
  cubo.colors_chess(0.56, 0.56, 0.56, 0.58, 0.57, 0.59);
  cubo.cambiarMaterial(gold);

};

void _brazoIzq::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();

  ////Escudo
  glPushMatrix();
  glTranslatef(0, -1, 0);
  escudo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_brazoDch::_brazoDch() {
  ancho = 0.5;
  alto = 4;
  fondo = 1;
  cubo.colors_chess(0.56, 0.56, 0.56, 0.58, 0.57, 0.59);
  cubo.cambiarMaterial(gold);

};

void _brazoDch::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,-alto/3.5,0);
  espada.draw(modo, r, g, b, grosor);
  glPopMatrix();
};



_piernaIzq::_piernaIzq() {
  ancho = 0.75;
  alto = 4;
  fondo = 1;
  cubo.colors_chess(0.56, 0.56, 0.56, 0.58, 0.57, 0.59);
  cubo.cambiarMaterial(gold);

};

void _piernaIzq::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_piernaDch::_piernaDch() {
  ancho = 0.75;
  alto = 4;
  fondo = 1;
  cubo.colors_chess(0.56, 0.56, 0.56, 0.58, 0.57, 0.59);
  cubo.cambiarMaterial(gold);

};

void _piernaDch::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_escudo::_escudo(){
  ancho = 2;
  alto = 4;
  fondo = 0.1;
  cubo.colors_chess(0.73,0.01,0.03,0.73,0.01,0.03);
  cilindro->colors_chess(0.29,0.16,0.1,0.29,0.16,0.1);

  cubo.cambiarMaterial(madera);
  cilindro->cambiarMaterial(cuero);
  
}

void _escudo::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
    glRotatef(90,0,1,0);
    glPushMatrix();
      glRotatef(45,0,1,0);
      cilindro->draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
      glRotatef(90,0,0,1);
      glTranslatef(0,0,cilindro->_radio * cos(M_PI/4));
      glScalef(ancho, alto, fondo);
      cubo.draw(modo, r, g, b, grosor);
    glPopMatrix();
  glPopMatrix();
};

_espada::_espada(){
  ancho = 0.3;
  alto = 4.0;
  fondo = 0.1;
  cuerpo.colors_chess(0.58, 0.77, 0.84, 0.6, 0.78, 0.85);
  punta.colors_chess(0.58, 0.77, 0.84, 0.6, 0.78, 0.85);
  cruz.colors_chess(0.78, 0.58, 0.39, 0.79, 0.6, 0.4);

  cuerpo.cambiarMaterial(silver);
  punta.cambiarMaterial(silver);
  cruz.cambiarMaterial(jade);

}

void _espada::draw(_modo modo, float r, float g, float b, float grosor) {
  glPushMatrix();
  glRotatef(90,1,0,0);
  glRotatef(90,0,1,0);
    glPushMatrix();
      glTranslatef(0,alto/2,0);
      glScalef(ancho, alto, fondo);
      cuerpo.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,ancho/2+alto/7,0);
      glScalef(ancho*3, ancho, ancho);
      cruz.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
      float lado = ancho/sqrt(2);
      glTranslatef(0,alto,0);
      glScalef(lado, lado, fondo);
      glRotatef(45,0,0,1);
      punta.draw(modo, r, g, b, grosor);
    glPopMatrix();
  glPopMatrix();
}


_soldado::_soldado(){
  giro_cabeza = 0.0;
  giro_brazoIzq = 0.0;
  giro_piernas = 0.0;
  giro_brazoIzq_lateral = 0.0;


  giro_cabeza_max = 90;
  giro_brazo_max = 90;
  giro_brazo_min = -180;
  giro_piernas_max = 30;
  giro_brazoIzq_lateral_max = 90;
  giro_brazoIzq_lateral_min = -30;

  //Animacion
  piernas_signo=1;
  giro_brazos_animacion_signo=1;
  giro_brazos_animacion=0;
  giro_brazos_animacion_max = giro_piernas_max;
  animacion = false;
  rotacion_animacion = 0;

};

void _soldado::draw(_modo modo, float r, float g, float b, float grosor){
  
  glPushMatrix();
    //Rotacion del soldado en la animacion
    glRotatef(rotacion_animacion,0,1,0);
    
    //Altura de las piernas
    glTranslatef(0, piernaIzq.alto, 0);

    glPushMatrix();
      glTranslatef(-piernaIzq.ancho/2, 0, 0);
      glRotatef(giro_piernas,1,0,0);
      glTranslatef(0,-piernaIzq.alto/2,0);
      piernaIzq.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(piernaDch.ancho/2, 0, 0);
      glRotatef(-giro_piernas,1,0,0);
      glTranslatef(0,-piernaIzq.alto/2,0);
      piernaDch.draw(modo, r, g, b, grosor);
    glPopMatrix();

    //Altura del tronco
    glTranslatef(0, tronco.alto/2, 0);
    tronco.draw(modo, r, g, b, grosor);

    //Altura brazos
    glTranslatef(0, tronco.alto/2, 0);

    //Brazo Derecho
    glPushMatrix();
      glTranslatef(-tronco.ancho/2 , 0, 0);
      glRotatef(-giro_brazos_animacion,1,0,0);
      glTranslatef(-brazoIzq.ancho/2,-brazoIzq.alto/2,0);
      brazoDch.draw(modo, r, g, b, grosor);
    glPopMatrix();

    //Brazo Izquierda
    glPushMatrix();
      glTranslatef(tronco.ancho/2 + brazoIzq.ancho/2  -brazoIzq.ancho/2,0,0);
      glRotatef(giro_brazoIzq,1,0,0);
      glRotatef(giro_brazoIzq_lateral,0,0,1);
      glTranslatef(brazoIzq.ancho/2,-brazoIzq.alto/2,0);
      brazoIzq.draw(modo, r, g, b, grosor);
    glPopMatrix();

    //Altura cabeza
    glTranslatef(0, cabeza.alto/2, 0);
    
    glPushMatrix();
      glRotatef(giro_cabeza,0,1,0);
      cabeza.draw(modo, r, g, b, grosor);
    glPopMatrix();
  glPopMatrix();
}

///////////////////////
//Examen de prueba
///////////////////////
//Ejercicio 1

_objPrueba1::_objPrueba1(float tam, float al) {
  // vertices
  int n_vertices = 5+4;
  vertices.resize(n_vertices);
  vertices[0].x = -tam;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = -tam;
  vertices[3].x = -tam;
  vertices[3].y = 0;
  vertices[3].z = -tam;
  vertices[4].x = 0;
  vertices[4].y = al;
  vertices[4].z = 0;
  ////
  vertices[5].x = -tam/2;
  vertices[5].y = -al/2;
  vertices[5].z = tam/2;
  vertices[6].x = tam/2;
  vertices[6].y = -al/2;
  vertices[6].z = tam/2;
  vertices[7].x = tam/2;
  vertices[7].y = -al/2;
  vertices[7].z = -tam/2;
  vertices[8].x = -tam/2;
  vertices[8].y = -al/2;
  vertices[8].z = -tam/2;

  // Colores para los vertices
  colores_vertices.resize(n_vertices);  // color entre 0 y 1
  for (int i = 0; i < n_vertices; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  int n_caras = 13;
  caras.resize(n_caras);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 2;
  caras[1]._2 = 4;
  caras[2]._0 = 2;
  caras[2]._1 = 3;
  caras[2]._2 = 4;
  caras[3]._0 = 3;
  caras[3]._1 = 0;
  caras[3]._2 = 4;
  // caras[4]._0 = 3;
  // caras[4]._1 = 1;
  // caras[4]._2 = 0;
  // caras[5]._0 = 3;
  // caras[5]._1 = 2;
  // caras[5]._2 = 1;
  caras[4]._0 = 5;
  caras[4]._1 = 6;
  caras[4]._2 = 0;
  caras[5]._0 = 0;
  caras[5]._1 = 1;
  caras[5]._2 = 6;

  caras[6]._0 = 6;
  caras[6]._1 = 7;
  caras[6]._2 = 1;
  caras[7]._0 = 1;
  caras[7]._1 = 2;
  caras[7]._2 = 7;

  caras[8]._0 = 2;
  caras[8]._1 = 3;
  caras[8]._2 = 7;
  caras[9]._0 = 7;
  caras[9]._1 = 3;
  caras[9]._2 = 8;

  caras[10]._0 = 0;
  caras[10]._1 = 3;
  caras[10]._2 = 8;
  caras[11]._0 = 8;
  caras[11]._1 = 5;
  caras[11]._2 = 0;

  caras[12]._0 = 5;
  caras[12]._1 = 6;
  caras[12]._2 = 8;
  caras[13]._0 = 8;
  caras[13]._1 = 6;
  caras[13]._2 = 7;

  // colores para las caras
  colors_random();

}


//Ejercicio 2
// num1 -> Numero lineas paralelas (puntos del perfil)
// num2 -> Numero giros 
_objPrueba2::_objPrueba2(float r1, float r2, int num1, int num2) {
  //vector<_vertex3f> perfil1;
  //vector<_vertex3f> perfil2;
  vector<_vertex3f> perfil3;

  _vertex3f aux;
  int i;
  //parametros(perfil1, num2, 0, 0, 1);

  //Esfera de abajo
  for (i = 1; i <= num1/2; i++) {
    aux.x = r2 * cos(M_PI * i / num1 * 1.0 - M_PI / 2.0);
    aux.y = -r1 + r2 * sin(M_PI * i / num1 * 1.0 - M_PI / 2.0);
    aux.z = 0.0;
    //perfil2.push_back(aux);
    perfil3.push_back(aux);
  }

  //Esfera de arriba (pequeña)
  // Empezamos en 1 pa no repetir el punto inferior muchas veces
  for (i = 1; i <= num1/2; i++) {
    aux.x = r2 + r1 * cos(M_PI * i / num1 * 1.0 - M_PI / 2.0);
    aux.y = r1 * sin(M_PI * i / num1 * 1.0 - M_PI / 2.0);
    aux.z = 0.0;
    //perfil1.push_back(aux);
    perfil3.push_back(aux);
  }

  perfil3.push_back({0,0,0});
  parametros(perfil3, num2, 2, 0, 0);
}

//Ejercicio 3
_objPrueba3::_objPrueba3(){
  ancho = alto = fondo = 1;

  base.colors_random();
  arriba.colors_random();
  vertical.colors_random();
  horizontal.colors_random();
}

void _objPrueba3::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

    glTranslatef(0, alto/2, 0);
    glPushMatrix();
      glScalef(ancho,alto,fondo);
      base.draw(modo,r,g,b,grosor);
    glPopMatrix();

    glTranslatef(ancho/2, alto/2 + alto/4, fondo/2);
    glPushMatrix();
      glScalef(ancho/2,alto/2,fondo/2);
      arriba.draw(modo,r,g,b,grosor);
    glPopMatrix();

    glTranslatef(0, alto/4 + alto/4, 0);
    glPushMatrix();
      glScalef(ancho/8,alto/2,fondo/8);
      vertical.draw(modo,r,g,b,grosor);
    glPopMatrix();

    glTranslatef(0, alto/4 + alto/4, 0);
    glPushMatrix();
      glTranslatef(-alto/2 + ancho/8, ancho/6,0);
      glRotatef(90,0,0,1);
      glScalef(ancho/6,alto/2,fondo/6);
      horizontal.draw(modo,r,g,b,grosor);
    glPopMatrix();


  glPopMatrix();
}

// Ejercicio prueba 4
_objPrueba4::_objPrueba4(){
  ancho = alto = fondo = 1;
  giro1 = 0;
  transformacion2 = 0;

  base.colors_random();
  arriba.colors_random();
  tumbado.colors_random();
  cono.colors_random();
}

void _objPrueba4::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

    glTranslatef(0, alto/2, 0);
    glPushMatrix();
      glScalef(ancho,alto,fondo);
      base.draw(modo,r,g,b,grosor);
    glPopMatrix();

    glPushMatrix();

      glTranslatef(ancho/2, alto/2 + alto/4, fondo/2);
      glRotatef(giro1,0,1,0);
      glPushMatrix();
        glScalef(ancho/2,alto/2,fondo/2);
        arriba.draw(modo,r,g,b,grosor);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0, alto/4 + alto/4 + transformacion2*cos(45), fondo/4 + transformacion2*cos(45));
        glRotatef(45,1,0,0);
        glPushMatrix();
          glScalef(ancho/12,alto/2 + transformacion2,fondo/12);
          tumbado.draw(modo,r,g,b,grosor);
        glPopMatrix();

        glTranslatef(0, alto/4 + alto/4, 0);
        glPushMatrix();
          glTranslatef(0, -ancho/12 + transformacion2*cos(45),-fondo/6 + transformacion2*cos(45));
          glRotatef(90,1,0,0);
          glScalef(ancho/6,alto/2,fondo/6);
          cono.draw(modo,r,g,b,grosor);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
}


///////////////////////////////
//  Examen 10-11-2022
///////////////////////////////

_objExamen1::_objExamen1(float tam, float al) {
  // vertices
  int n_vertices = 7;
  vertices.resize(n_vertices);
  vertices[0].x = -tam;
  vertices[0].y = -tam;
  vertices[0].z = -tam;

  vertices[1].x = tam;
  vertices[1].y = -tam;
  vertices[1].z = -tam;

  vertices[2].x = tam;
  vertices[2].y = -tam;
  vertices[2].z = tam;

  vertices[3].x = -tam;
  vertices[3].y = -tam;
  vertices[3].z = tam;



  vertices[4].x = -tam;
  vertices[4].y = tam;
  vertices[4].z = -tam;
  
  vertices[5].x = tam;
  vertices[5].y = tam;
  vertices[5].z = tam;

  vertices[6].x = -tam;
  vertices[6].y = 2*tam;
  vertices[6].z = tam;


  // Colores para los vertices
  colores_vertices.resize(n_vertices);  // color entre 0 y 1
  for (int i = 0; i < n_vertices; i++) {
    colores_vertices[i].r = rand() % 1000 / 1000.0;
    colores_vertices[i].g = rand() % 1000 / 1000.0;
    colores_vertices[i].b = rand() % 1000 / 1000.0;
  }

  // caras triangulos
  int n_caras = 10;
  caras.resize(n_caras);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 4;
  caras[1]._1 = 1;
  caras[1]._2 = 5;

  caras[2]._0 = 5;
  caras[2]._1 = 1;
  caras[2]._2 = 2;

  caras[3]._0 = 5;
  caras[3]._1 = 2;
  caras[3]._2 = 3;
  caras[4]._0 = 3;
  caras[4]._1 = 5;
  caras[4]._2 = 6;
  caras[5]._0 = 6;
  caras[5]._1 = 4;
  caras[5]._2 = 3;
  caras[6]._0 = 3;
  caras[6]._1 = 4;
  caras[6]._2 = 0;
  caras[7]._0 = 0;
  caras[7]._1 = 1;
  caras[7]._2 = 2;
  caras[8]._0 = 2;
  caras[8]._1 = 3;
  caras[8]._2 = 0;
  caras[9]._0 = 4;
  caras[9]._1 = 5;
  caras[9]._2 = 6;

  // colores para las caras
  colors_random();
}

_objExamen2::_objExamen2(float radio, int num1, int num2){
    vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;

  perfil.push_back({0,0,0});
  perfil.push_back({0.8,0,0});
  perfil.push_back({0.8,0.3,0});

  // Empezamos en 1 pa no repetir el punto inferior muchas veces
  for (i = 0; i < num1/2+1; i++) {
    aux.x = 0.2 + radio * cos(M_PI * i / num1 * 1.0);
    aux.y = 0.3 + radio * sin(M_PI * i / num1 * 1.0);
    aux.z = 0.0;
    perfil.push_back(aux);
  }
  
  perfil.push_back({0.2,1,0});

  parametros(perfil, num2, 2, 0, 0);
}


_objExamen3::_objExamen3(){
  ancho = 1;
  alto  = 3;
  fondo = 2;

  giro1 = 0;
  transformacion1 = 3;

  base.colors_random();
  horizontal.colors_random();
  ala.colors_chess(0.58, 0.77, 0.84, 0.6, 0.78, 0.85);

}

void _objExamen3::draw(_modo modo, float r, float g, float b, float grosor){

  float h_ancho = 0.3;
  float h_alto = transformacion1;
  float h_fondo = 0.3;

  glPushMatrix();
    glTranslatef(0,alto/2,0);
    glScalef(ancho,alto,fondo);
    base.draw(modo,r,g,b,grosor);
  glPopMatrix();

  glTranslatef(ancho/2,alto*6/8,0);
  glPushMatrix();
    glRotatef(-90,0,0,1);
    glTranslatef(0,h_alto/2,0);
    glScalef(h_ancho,h_alto,h_fondo);
    glScalef(1,0.5,1);
    horizontal.draw(modo,r,g,b,grosor);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(h_alto-0.2, 0, h_fondo);
    glRotatef(giro1,0,0,1);
    glScalef(1.2,0.2,0.1);
    ala.draw(modo,r,g,b,grosor);
  glPopMatrix();
}
