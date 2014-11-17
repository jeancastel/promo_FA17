
#ifndef _GRAPH_OPENGL_2D_
#define _GRAPH_OPENGL_2D_

void InitGraph(int ac,char *av[],const char *WinName,
               const int w,const int h,void (*Draw)(void),
               void (*Key)(int c));
void line(const float x0,const float y0,const float x1,const float y1);
void setcolor(const float r,const float v,const float b);
void beginlines(const float x0,const float y0);
void lineto(const float x,const float y);
void finishlines(void);
void bar(const float x0,const float y0,const float x1,const float y1);
void outtextxy(const float x,const float y,const char *s);

#endif /* _GRAPH_OPENGL_2D_ */


