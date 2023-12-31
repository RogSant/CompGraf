#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Point {
  float x;
  float y;
  float z;
};

GLfloat pontos[][11] = {{2.0f, 3.0f, 0.0f, -1.0f, 3.0f, 0.0f, 1.0f, -1.0f, 0.0f, -2.0f, -1.0f}, 
{-2.0f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 1.0f, -2.0f, 0.0f, 2.0f, 2.0f}, {-2.0f, -1.0f, 0.0f, -2.0f, 2.0f, 0.0f, 2.0f, 2.0f, 0.0f, 2.0f, 3.0f}};

int caso = 0;

int n = 10;
float t = 0.0;
float tstep = 1.0/10.0;
struct Point P0;
struct Point P1;
struct Point P2;
struct Point P3;
struct Point P;

struct Point a;
struct Point b;
struct Point c;
struct Point d;
struct Point e;

GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat angleZ = 0.0f;

void lightning(){
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

  //Fonte de Luz Direcional - Efeito de Holofote
  GLfloat light1_pos[] = {-2.0, -2.0, -2.0f, 1.0f};
  glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
  glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1,GL_SPECULAR, white);
  GLfloat direction[] = {2.0f, 2.0f, 2.0f};
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0f);               //espalhamento angular
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.5f);    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}

void init(){
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 8.0);
    glViewport(0, 0, 500, 500);
    glShadeModel(GL_SMOOTH);
    lightning();
}

void pista(GLfloat *p){
  GLfloat shininess;
  GLfloat diffuse[4];
  GLfloat specular[4];

  P0.x = p[0];
  P0.y = p[1];
  P0.z = p[2];
  P1.x = p[3];
  P1.y = p[4];
  P1.z = p[5];
  P2.x = p[6];
  P2.y = p[7];
  P2.z = p[8];
  P3.x = p[9];
  P3.y = p[10];
  
  shininess = 65.0;
  diffuse[0] = 0.65;
  diffuse[1] = 0.65;
  diffuse[2] = 0.65;
  diffuse[3] = 1.0;
  specular[0] = 1.0;
  specular[1] = 1.0;
  specular[2] = 1.0;
  specular[3] = 1.0;
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
  glMaterialf(GL_FRONT,GL_SHININESS,shininess);
  glBegin(GL_TRIANGLE_STRIP);
  t = 0.0;
  for(int i=0;i<n;i++){
    a.x = (1.0-t)*P0.x+t*P1.x;
    a.y = (1.0-t)*P0.y+t*P1.y;
    a.z = (1.0-t)*P0.z+t*P1.z;
    b.x = (1.0-t)*P1.x+t*P2.x;
    b.y = (1.0-t)*P1.y+t*P2.y;
    b.z = (1.0-t)*P1.z+t*P2.z;
    c.x = (1.0-t)*P2.x+t*P3.x;
    c.y = (1.0-t)*P2.y+t*P3.y;
    c.z = (1.0-t)*P2.z+t*P3.z;
    d.x = (1.0-t)*a.x+t*b.x;
    d.y = (1.0-t)*a.y+t*b.y;
    d.z = (1.0-t)*a.z+t*b.z;
    e.x = (1.0-t)*b.x+t*c.x;
    e.y = (1.0-t)*b.y+t*c.y;
    e.z = (1.0-t)*b.z+t*c.z;

    P.x = (1.0-t)*d.x+t*e.x;
    P.y = (1.0-t)*d.y+t*e.y;
    P.z = (1.0-t)*d.z+t*e.z;
    glNormal3f(0.0,P.y,0.0);
    glVertex3f(P.x,P.y,P.z-0.2);
    glNormal3f(P.x,P.y,P.z+0.2);
    glVertex3f(P.x,P.y,P.z+0.2);
    t+=tstep;
  }
  glEnd();
  glBegin(GL_TRIANGLE_STRIP);
  t = 0.0;
  for(int i=0;i<n;i++){
    a.x = (1.0-t)*P0.x+t*P1.x;
    a.y = (1.0-t)*P0.y+t*P1.y;
    a.z = (1.0-t)*P0.z+t*P1.z;
    b.x = (1.0-t)*P1.x+t*P2.x;
    b.y = (1.0-t)*P1.y+t*P2.y;
    b.z = (1.0-t)*P1.z+t*P2.z;
    c.x = (1.0-t)*P2.x+t*P3.x;
    c.y = (1.0-t)*P2.y+t*P3.y;
    c.z = (1.0-t)*P2.z+t*P3.z;
    d.x = (1.0-t)*a.x+t*b.x;
    d.y = (1.0-t)*a.y+t*b.y;
    d.z = (1.0-t)*a.z+t*b.z;
    e.x = (1.0-t)*b.x+t*c.x;
    e.y = (1.0-t)*b.y+t*c.y;
    e.z = (1.0-t)*b.z+t*c.z;

    P.x = (1.0-t)*d.x+t*e.x;
    P.y = (1.0-t)*d.y+t*e.y;
    P.z = (1.0-t)*d.z+t*e.z;
    glNormal3f(0.0,P.y,0.0);
    glVertex3f(P.x,P.y-1,P.z-0.2);
    glNormal3f(P.x,P.y-1,P.z+0.2);
    glVertex3f(P.x,P.y-1,P.z+0.2);
    t+=tstep;
  }
  glEnd();
  glBegin(GL_TRIANGLE_STRIP);
  t = 0.0;
  for(int i=0;i<n;i++){
    a.x = (1.0-t)*P0.x+t*P1.x;
    a.y = (1.0-t)*P0.y+t*P1.y;
    a.z = (1.0-t)*P0.z+t*P1.z;
    b.x = (1.0-t)*P1.x+t*P2.x;
    b.y = (1.0-t)*P1.y+t*P2.y;
    b.z = (1.0-t)*P1.z+t*P2.z;
    c.x = (1.0-t)*P2.x+t*P3.x;
    c.y = (1.0-t)*P2.y+t*P3.y;
    c.z = (1.0-t)*P2.z+t*P3.z;
    d.x = (1.0-t)*a.x+t*b.x;
    d.y = (1.0-t)*a.y+t*b.y;
    d.z = (1.0-t)*a.z+t*b.z;
    e.x = (1.0-t)*b.x+t*c.x;
    e.y = (1.0-t)*b.y+t*c.y;
    e.z = (1.0-t)*b.z+t*c.z;

    P.x = (1.0-t)*d.x+t*e.x;
    P.y = (1.0-t)*d.y+t*e.y;
    P.z = (1.0-t)*d.z+t*e.z;
    glNormal3f(0.0,P.y,0.0);
    glVertex3f(P.x,P.y,P.z-0.2);
    glNormal3f(P.x,P.y-1,P.z-0.2);
    glVertex3f(P.x,P.y-1,P.z-0.2);
    t+=tstep;
  }
  glEnd();
  glBegin(GL_TRIANGLE_STRIP);
  t = 0.0;
  for(int i=0;i<n;i++){
    a.x = (1.0-t)*P0.x+t*P1.x;
    a.y = (1.0-t)*P0.y+t*P1.y;
    a.z = (1.0-t)*P0.z+t*P1.z;
    b.x = (1.0-t)*P1.x+t*P2.x;
    b.y = (1.0-t)*P1.y+t*P2.y;
    b.z = (1.0-t)*P1.z+t*P2.z;
    c.x = (1.0-t)*P2.x+t*P3.x;
    c.y = (1.0-t)*P2.y+t*P3.y;
    c.z = (1.0-t)*P2.z+t*P3.z;
    d.x = (1.0-t)*a.x+t*b.x;
    d.y = (1.0-t)*a.y+t*b.y;
    d.z = (1.0-t)*a.z+t*b.z;
    e.x = (1.0-t)*b.x+t*c.x;
    e.y = (1.0-t)*b.y+t*c.y;
    e.z = (1.0-t)*b.z+t*c.z;

    P.x = (1.0-t)*d.x+t*e.x;
    P.y = (1.0-t)*d.y+t*e.y;
    P.z = (1.0-t)*d.z+t*e.z;
    glNormal3f(0.0,P.y,0.0);
    glVertex3f(P.x,P.y,P.z+0.2);
    glNormal3f(P.x,P.y-1,P.z+0.2);
    glVertex3f(P.x,P.y-1,P.z+0.2);
    t+=tstep;
  }
  glEnd();
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(angleX,1.0,0.0,0.0);
  glRotatef(angleY,0.0,1.0,0.0);
  glRotatef(angleZ,0.0,0.0,1.0);
  pista(pontos[caso]);
  glPopMatrix();
  lightning();
  glFlush();
}

void keyboard (unsigned char key, int x, int y){
    switch(key){
       case 'x':
       case 'X':
            angleX+=5.0f;
          break;
       case 'y':
       case 'Y':
            angleY+=5.0f;
          break;
      case 'z':
      case 'Z':
            angleZ+=5.0f;
          break;
      case '1':
            caso = 0;
            break;
      case '2':
            caso = 1;
            break;
      case '3':
            caso = 2;
            break;
      default:
          break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Pista");
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
