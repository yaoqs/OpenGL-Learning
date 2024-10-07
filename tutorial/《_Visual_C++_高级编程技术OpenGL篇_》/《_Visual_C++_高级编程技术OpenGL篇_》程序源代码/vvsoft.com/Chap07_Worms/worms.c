#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include "GL/glaux.h"

#ifdef WIN32
#define drand48() (((float) rand())/((float) RAND_MAX)) 
#define srand48() (srand(time(NULL)))
#endif

/* operational constants */
#define RADIAN .0174532
#define CIRCLE_POINTS 25
#define PI 3.1415926535897
#define SIDETOLERANCE .01
#define INITH 500
#define INITW 500

/* worm options */
#define SEGMENTS 20
#define SEG_RADIUS 0.01
#define STEPSIZE 0.01
#define MAXTURN (20 * RADIAN)        /* in radians */
#define MAXWORMS 400
#define INITWORMS 40
#define MARKTICKS 100

typedef struct worm_s {
  float dir;                   /* direction in radians */
  float segx[SEGMENTS];        /* location of segments. */
  float segy[SEGMENTS];
  GLfloat *color;              /* pointer to the RGB color of the worm */
  int head;                    /* which elt of seg[xy] is currently head */
                               /* the tail is always (head+1 % SEGMENTS) */
} worm_t;


const GLfloat colors[][3] = {
  { 255,   0,   0},  { 238,   0,   0},  { 205,   0,   0},  
  {   0, 255,   0},  {   0, 238,   0},  {   0, 205,   0},
  {   0,   0, 255},  {   0,   0, 238},  {   0,   0, 205},
  { 255, 255,   0},  { 238, 238,   0},  { 205, 205,   0},
  {   0, 255, 255},  {   0, 238, 238},  {   0, 205, 205},
  { 255,   0, 255},  { 238,   0, 238},  { 205,   0, 205},
};

#define COLORS 18

/* define's for the menu item numbers */
#define MENU_NULL          0
#define MENU_FILLED        1
#define MENU_UNFILLED      2
#define MENU_QUIT          3

/* flag to determine how to draw worms; set by popup menu -- starts out
   filled in
 */
int filled = 1;

/* the global worm array */
worm_t worms[MAXWORMS];
int curworms = 0;

/* global window extent variables */
GLfloat gleft = -1.0, gright = 1.0, gtop = 1.0, gbottom = -1.0;
GLint wsize, hsize;

/* globals for marking */
float markx, marky;
int marktime;

void drawCircle(float x0, float y0, float radius)
{
  int i;
  float angle;

  /* a table of offsets for a circle (used in drawCircle) */
  static float circlex[CIRCLE_POINTS];
  static float circley[CIRCLE_POINTS];
  static int   inited = 0;

  if (! inited) {
    for (i = 0; i < CIRCLE_POINTS; i++) {
      angle = 2.0 * PI * i / CIRCLE_POINTS;
      circlex[i] = cos(angle);
      circley[i] = sin(angle);
    }
    inited++;
  };

  if (filled)
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  for(i = 0; i < CIRCLE_POINTS; i++)
    glVertex2f((radius * circlex[i]) + x0, (radius * circley[i]) + y0);
  glEnd();

  return;
}

void drawWorm(worm_t *theworm)
{
  int i;

  glColor3fv(theworm->color);
  for (i = 0; i < SEGMENTS; i++)
    drawCircle(theworm->segx[i], theworm->segy[i], SEG_RADIUS);
  return;
}

void myinit(void)
{
  int i, j, thecolor;
  float thedir;

  srand48(time(NULL));

  curworms = INITWORMS;
  
  for (j = 0; j < curworms; j++) {
    /* divide the circle up into a number of pieces, and send one worm
       each direction.
     */
    worms[j].dir = ((2.0 * PI) / curworms) * j;
    thedir = worms[j].dir;

    worms[j].segx[0] = 0.0;
    worms[j].segy[0] = 0.0;

    for (i = 1; i < SEGMENTS; i++) {
      worms[j].segx[i] = worms[j].segx[i-1] + (STEPSIZE * cos(thedir));
      worms[j].segy[i] = worms[j].segx[i-1] + (STEPSIZE * sin(thedir));
    };
    worms[j].head = (SEGMENTS - 1);

    /* make this worm one of the predefined colors */
    thecolor = (int) COLORS * drand48();
    worms[j].color = (GLfloat *)colors[thecolor];
  };
}

void warpWorms(void)
{
  register int j, head;

  for (j = 0; j < curworms; j++) {
    head = worms[j].head;

    if (worms[j].segx[head] < gleft)
      worms[j].segx[head] = gleft;
    if (worms[j].segx[head] > gright)
      worms[j].segx[head] = gright;
    if (worms[j].segx[head] > gtop)
      worms[j].segx[head] = gtop;
    if (worms[j].segx[head] < gbottom)
      worms[j].segx[head] = gbottom;      
  }
}

void CALLBACK myreshape (GLsizei w, GLsizei h)
{
  float ratiow = (float) w/INITW;
  float ratioh = (float) h/INITH;

  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gleft = -1 * ratiow;
  gright = 1 * ratiow;
  gbottom = -1 * ratioh;
  gtop = 1 * ratioh;

  gluOrtho2D(gleft, gright, gbottom, gtop);
  warpWorms();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  wsize = w; hsize = h;

  return;
}

void updateWorm(worm_t *theworm)
{
  int newhead;
  float prevx, prevy;
  float newh = -1, newv = -1;
  float num, denom;

  newhead = (theworm->head + 1) % SEGMENTS;

  prevx = theworm->segx[theworm->head];
  prevy = theworm->segy[theworm->head];

  if (marktime) {
    num = marky - prevy;
    denom = markx - prevx;
    theworm->dir = atan2(num,denom);
  };

  theworm->dir += (MAXTURN - (2 * MAXTURN * (float) drand48()));

  theworm->segx[newhead] = prevx + (STEPSIZE * cos(theworm->dir));
  theworm->segy[newhead] = prevy + (STEPSIZE * sin(theworm->dir));

  if (theworm->segx[newhead] <= gleft)
    theworm->dir = 0;
  if (theworm->segx[newhead] >= gright)
    theworm->dir = (180 * RADIAN);
  if (theworm->segy[newhead] >= gtop)
    theworm->dir = (270 * RADIAN);
  if (theworm->segy[newhead] <= gbottom)
    theworm->dir = (90 * RADIAN);

  if ((newv >= 0) || (newh >= 0)) {
    newh = (newh<0) ? 0 : newh;
    newv = (newv<0) ? 0 : newv;
  };

  theworm->head = newhead;
}  

void CALLBACK myidle (void)
{
  register int i, tail;

  if (marktime)
    marktime--;

  for (i = 0; i < curworms; i++) {
    /* first find tail */
    tail = (worms[i].head + 1) % SEGMENTS;
  
    /* erase tail */
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(worms[i].segx[tail], worms[i].segy[tail], SEG_RADIUS);

    /* update head segment position and head pointer */
    updateWorm(&worms[i]);

    /* draw head */
    glColor3f(worms[i].color[0]/255.0f, worms[i].color[1]/255.0f, worms[i].color[2]/255.0f);
    drawCircle(worms[i].segx[worms[i].head], worms[i].segy[worms[i].head],
	       SEG_RADIUS);
  };
  glFlush();
  auxSwapBuffers();
  return;
}

void markSpot(int x, int y)
{
  /* map into the corridinate space I am using */
  markx = (float)((x - wsize/2)*(gright - gleft)/wsize);
  marky = -(float)((y - hsize/2)*(gtop - gbottom)/hsize);

  marktime = MARKTICKS;
}

void CALLBACK mouse(AUX_EVENTREC *event)
{
  GLint x, y;

  x = event->data[AUX_MOUSEX];
  y = event->data[AUX_MOUSEY];
  markSpot(x,y);
}

int main(int argc, char **argv)
{
  int fillmenu = 0;

  auxInitDisplayMode(AUX_DOUBLE | AUX_RGB);
  auxInitPosition(0, 0, INITW, INITH);
  auxInitWindow("Worms");
  auxIdleFunc(myidle);
  myinit();
  auxReshapeFunc(myreshape);
  auxMouseFunc(AUX_LEFTBUTTON,AUX_MOUSEDOWN,mouse);
  auxMainLoop(myidle);
  return 0;
}