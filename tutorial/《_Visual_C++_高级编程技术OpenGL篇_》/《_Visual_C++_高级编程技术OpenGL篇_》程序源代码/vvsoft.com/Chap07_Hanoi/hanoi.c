#include "GL/glaux.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

float WIDTH = 400;
float HEIGHT = 400;
GLboolean motion = GL_TRUE;
GLboolean back_wall = GL_FALSE;
GLint xangle = 0, yangle = 0;
GLint xlangle = 0, ylangle = 0;

#define other(i,j) (6-(i+j))
#define wallz -(WIDTH/2)
#define DISK_HEIGHT 20
int NUM_DISKS = 11;
#define CONE NUM_DISKS+1
#define WALL CONE + 1
#define HANOI_SOLVE 0
#define HANOI_QUIT 1
#define HANOI_LIGHTING 2
#define HANOI_WALL 3
#define HANOI_FOG 4

GLfloat lightOneDirection[] = {0.0f, 0.0f, -1.0f};
GLfloat lightOnePosition[] = {200.0f, 100.0f, 300.0f, 1.0f};
GLfloat lightOneColor[] = {1.0f, 1.0f, 0.5f, 1.0f};

GLfloat lightTwoDirection[] = {0.0f, 0.0f, -1.0f};
GLfloat lightTwoPosition[] = {600.0f, 100.0f, 300.0f, 1.0f};
GLfloat lightTwoColor[] = {1.0f, 0.0f, 0.3f, 1.0f};

GLfloat lightZeroPosition[] = {400.0f, 200.0f, 300.0f, 1.0f};
GLfloat lightZeroColor[] = {0.6f, 0.6f, 0.0f, 0.0f};

GLfloat diskColor[] = {1.0f, 1.0f, 1.0f, 0.8f}, 
        poleColor[] = {1.0f, 0.2f, 0.2f, 0.8f};

typedef struct stack_node {
  int size;
  struct stack_node *next;
} stack_node;

typedef struct stack {
  struct stack_node *head;
  int depth;
} stack;

stack poles[4];

void push(int which, int size)
{
  stack_node *new_node = malloc(sizeof(stack_node));
  if (!new_node) {
    printf("out of memory!\n");
    exit(-1);
  }
  new_node->size = size;
  new_node->next = poles[which].head;
  poles[which].head = new_node;
  poles[which].depth++;
}

int pop(int which)
{
  int retval = poles[which].head->size;
  stack_node *temp = poles[which].head;
  poles[which].head = poles[which].head->next;
  poles[which].depth--;
  free(temp);
  return retval;
}

typedef struct move_node {
  int t, f;
  struct move_node *next;
  struct move_node *prev;
} move_node;

typedef struct move_stack {
  int depth;
  struct move_node *head, *tail;
} move_stack;

move_stack moves;

void GenLists(void)
{
  int i;
  for (i = 0; i < 4; i++) {
    poles[i].head = NULL;
    poles[i].depth = 0;
  }
  moves.head = NULL;
  moves.tail = NULL;
  moves.depth = 0;

  for (i = 1; i <= NUM_DISKS; i++) {
    glNewList(i, GL_COMPILE);
    {
      auxSolidTorus(DISK_HEIGHT / 2.0f, 4 * i);
    }
    glEndList();
  }
  glNewList(CONE, GL_COMPILE);
  {
    auxSolidCone(8.0f, (NUM_DISKS + 1) * DISK_HEIGHT);
  }
  glEndList();
}

void Init(void)
{
  glViewport(0, 0, (int)WIDTH, (int)HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, 0, HEIGHT, -10000, 10000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClearDepth(1.0);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightOneDirection);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, lightTwoPosition);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightTwoColor);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightTwoDirection);
  glEnable(GL_LIGHT2);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
}

void mpop(void)
{
  move_node *temp = moves.head;
  moves.head = moves.head->next;
  free(temp);
  moves.depth--;
}

void move(int t, int f)
{
  move_node *new = malloc(sizeof(move_node));
  if (!new) {
    fprintf(stderr, "Out of memory!\n");
    exit(-1);
  }
  new->t = t;
  new->f = f;
  new->next = NULL;
  new->prev = moves.tail;
  if (moves.tail)
    moves.tail->next = new;
  moves.tail = new;
  if (!moves.head)
    moves.head = moves.tail;
  moves.depth++;
}

void DrawPost(int xcenter)
{
  glPushMatrix();
  {
    glTranslatef((float)xcenter, 0.0f, 0.0f);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glCallList(CONE);
  } glPopMatrix();
}

void DrawPosts(void)
{
  glColor3fv(poleColor);
  glLineWidth(1.0f);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, poleColor);
  DrawPost((int)WIDTH / 4);
  DrawPost(2 * (int)WIDTH / 4);
  DrawPost(3 * (int)WIDTH / 4);
}

void DrawDisk(int xcenter, int ycenter, int size)
{
  glPushMatrix();
  {
    glTranslatef((float)xcenter, (float)ycenter, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glCallList(size);
  } glPopMatrix();
}

void DrawDooDads(void)
{
  int i;
  stack_node *temp;
  int xcenter, ycenter;
  glColor3fv(diskColor);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diskColor);
  for (i = 1; i <= 3; i++) {
    xcenter = i * (int)WIDTH / 4;
	ycenter = DISK_HEIGHT * poles[i].depth - DISK_HEIGHT / 2;
    for (temp = poles[i].head; temp; temp = temp->next) {
	  ycenter -= DISK_HEIGHT;
      DrawDisk(xcenter, ycenter, temp->size);
    }
  }
}

static void hanoi(int n, int f, int t)
{
  int o;

  if (n == 1) {
    move(t,f);
    return;
  }
  o = other(f, t);
  hanoi(n - 1, f, o);
  hanoi(1, f, t);
  hanoi(n - 1, o, t);
}

GLfloat wallcolor[] = {0.0f, 0.3f, 1.0f, 1.0f};

void CALLBACK draw(void)
{
  int t, f;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  {
    glTranslatef(WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f);
    glRotatef((float)xlangle, 0.0f, 1.0f, 0.0f);
    glRotatef((float)ylangle, 1.0f, 0.0f, 0.0f);
    glTranslatef(-WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
  }
  glPopMatrix();

  glPushMatrix();
  {
    glTranslatef(WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f);
    glRotatef((float)xangle, 0.0f, 1.0f, 0.0f);
    glRotatef((float)yangle, 1.0f, 0.0f, 0.0f);
    glTranslatef(-WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f);
    DrawPosts();
    DrawDooDads();
  }
  glPopMatrix();
  if (motion && moves.depth) {
    t = moves.head->t;
    f = moves.head->f;
    push(t, pop(f));
    mpop();
  }
  auxSwapBuffers();
}

void CALLBACK update(void)
{
  draw();
}

void CALLBACK reshape(int w, int h)
{
  glViewport(0,0,w,h);
}

int oldx, oldy;

GLboolean leftb = GL_FALSE, middleb = GL_FALSE;

void main(int argc, char *argv[])
{
  int i;
  auxInitPosition(0, 0, (int)WIDTH, (int)HEIGHT);
  auxInitDisplayMode(AUX_RGBA | AUX_DOUBLE | AUX_DEPTH);
  auxInitWindow("Hanoi");
  GenLists();
  Init();

  for (i = 0; i < NUM_DISKS; i++)
    push(1, NUM_DISKS - i);
  hanoi(NUM_DISKS, 1, 3);
  auxReshapeFunc(reshape);
  auxIdleFunc(update);
  auxMainLoop(draw);
}
