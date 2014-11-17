#include <windows.h>
#include "glut.h"
#include "graph.h"

static int WindowNumber;
static int Width,Height;
static void (*AppliDraw)(void);
static void (*AppliKey)(int);

static void GlutReshape(const int w,const int h)
{
  Width=w;
  Height=h;
  glViewport(0,0,Width,Height);
}

static void GlutIdle(void)
{
//  glutPostRedisplay();
}

static void GlutKey(const unsigned char c,const int x,const int y)
{
  switch(c)
  {
    default:
      if (AppliKey) (*AppliKey)(c);
      break;
  }
  glutPostRedisplay();
}
      

static void Begin2DDisplay(void)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(-1,1,-1.0,1.0,0.5,1.5);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0.0F,0.0F,-1.0F);
}

static void End2DDisplay(void)
{
  /* Fin du trace, retour au parametres normaux */
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

static void InitDisplay(void)
{
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glClearColor(0.0F,0.0F,0.0F,0.0F);
}

static void GlutDraw(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  Begin2DDisplay();
  if (AppliDraw) (*AppliDraw)();
  End2DDisplay();
  glutSwapBuffers();
}

void InitGraph(int ac,char *av[],
               const char *WinName,const int w,const int h,void (*Draw)(void),
               void (*Key)(int))
{
  glutInit(&ac,av);
  Width=w;
  Height=h;
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(Width,Height);
  WindowNumber=glutCreateWindow(WinName);
  glutReshapeFunc(GlutReshape);
  glutIdleFunc(GlutIdle);
  AppliKey=Key;
  glutKeyboardFunc(GlutKey);
  AppliDraw=Draw;
  glutDisplayFunc(GlutDraw);
  InitDisplay();  
  glutMainLoop();  
}

void setcolor(const float r,const float v,const float b)
{
  glColor3f(r,v,b);
}


void line(const float x0,const float y0,const float x1,const float y1)
{
  glBegin(GL_LINES);
    glVertex2f(x0,y0);
    glVertex2f(x1,y1);
  glEnd();
}

void beginlines(const float x0,const float y0)
{
  glBegin(GL_LINE_STRIP);
  glVertex2f(x0,y0);
}

void lineto(const float x,const float y)
{
  glVertex2f(x,y);  
}

void finishlines(void)
{
  glEnd();
}

void bar(const float x0,const float y0,const float x1,const float y1)
{
  glBegin(GL_QUADS);
    glVertex2f(x0,y0);
    glVertex2f(x0,y1);
    glVertex2f(x1,y1);
    glVertex2f(x1,y0);
  glEnd();
}

void outtextxy(const float x,const float y,const char *str)
{
  const char *s=str;
  
  glRasterPos2f(x,y);
  while(*s!='\0')
  {
    //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*s++);
	  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*s++);//changement de police
  }
}


