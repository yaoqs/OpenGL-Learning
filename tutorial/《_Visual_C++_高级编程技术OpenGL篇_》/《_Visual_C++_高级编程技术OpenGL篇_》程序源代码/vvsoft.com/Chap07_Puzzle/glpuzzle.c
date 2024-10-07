#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include "GL/glaux.h"

#define WIDTH 4
#define HEIGHT 5
#define PIECES 10
#define OFFSETX -2
#define OFFSETY -2.5
#define OFFSETZ -0.5

typedef char Config[HEIGHT][WIDTH];

struct puzzle {
  struct puzzle *backptr;
  struct puzzle *solnptr;
  Config pieces;
  struct puzzle *next;
  unsigned hashvalue;
};

#define HASHSIZE 10691

struct puzzlelist {
  struct puzzle *puzzle;
  struct puzzlelist *next;
};

static char convert[PIECES + 1] = {0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4};

static unsigned char colors[PIECES + 1][3] =
{
	{  0,   0,   0},{255, 255, 127},{255, 255, 127},{255, 255, 127},
	{255, 255, 127},{255, 127, 255},{255, 127, 255},{255, 127, 255},
	{255, 127, 255},{255, 127, 127},{255, 255, 255}
};

static struct puzzle *hashtable[HASHSIZE];
static struct puzzle *startPuzzle;
static struct puzzlelist *puzzles;
static struct puzzlelist *lastentry;

int curX, curY, visible;

#define MOVE_SPEED 0.2
static unsigned char movingPiece;
static float move_x, move_y;
static float curquat[4];
static int doubleBuffer = 1;
static int depth = 1;

static char xsize[PIECES + 1] = {0,1,1,1,1,1,1,1,1,2,2};
static char ysize[PIECES + 1] = {0,1,1,1,1,2,2,2,2,1,2};
static float zsize[PIECES + 1] = {0.0f,1.0f,1.0f,1.0f,1.0f,1.0f, 
                                  1.0f,1.0f,1.0f,1.0f,0.6f};

static Config startConfig =
{
  {8,10,10,7}, {8,10,10,7}, {6,9,9,5},{6,4,3,5}, {2,0,0,1}
};

static Config thePuzzle =
{
  {8,10,10,7},{8,10,10,7},{6,9,9,5},{6,4,3,5},{2,0,0,1}
};

static int xadds[4] = {-1, 0, 1, 0};
static int yadds[4] = {0, -1, 0, 1};
static long W = 400, H = 300;
static GLint viewport[4];

unsigned hash(Config config)
{
  int i, j, value;

  value = 0;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      value = value + convert[config[i][j]];
      value *= 6;
    }
  }
  return (value);
}

float boxcoords[][3] =
{
  {0.2f, 0.2f, 0.9f},  {0.8f, 0.2f, 0.9f},
  {0.8f, 0.8f, 0.9f},  {0.2f, 0.8f, 0.9f},
  {0.2f, 0.1f, 0.8f},  {0.8f, 0.1f, 0.8f},
  {0.9f, 0.2f, 0.8f},  {0.9f, 0.8f, 0.8f},
  {0.8f, 0.9f, 0.8f},  {0.2f, 0.9f, 0.8f},
  {0.1f, 0.8f, 0.8f},  {0.1f, 0.2f, 0.8f},
  {0.2f, 0.1f, 0.2f},  {0.8f, 0.1f, 0.2f},
  {0.9f, 0.2f, 0.2f},  {0.9f, 0.8f, 0.2f},
  {0.8f, 0.9f, 0.2f},  {0.2f, 0.9f, 0.2f},
  {0.1f, 0.8f, 0.2f},  {0.1f, 0.2f, 0.2f},
  {0.2f, 0.2f, 0.1f},  {0.8f, 0.2f, 0.1f},
  {0.8f, 0.8f, 0.1f},  {0.2f, 0.8f, 0.1f},
};

float boxnormals[][3] =
{
  {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f, 0.0f},
  {1.0f, 0.0f, 0.0f},  {0.0f, 0.0f, -1.0f},
  {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
  {0.7071f, 0.7071f, 0.0000f},  {0.7071f, -0.7071f, 0.0000f},
  {-0.7071f, 0.7071f, 0.0000f}, {-0.7071f, -0.7071f, 0.0000f},
  {0.7071f, 0.0000f, 0.7071f},  {0.7071f, 0.0000f, -0.7071f},
  {-0.7071f, 0.0000f, 0.7071f}, {-0.7071f, 0.0000f, -0.7071f},
  {0.0000f, 0.7071f, 0.7071f},  {0.0000f, 0.7071f, -0.7071f},
  {0.0000f, -0.7071f, 0.7071f}, {0.0000f, -0.7071f, -0.7071f},
  {0.5774f, 0.5774f, 0.5774f},  {0.5774f, 0.5774f, -0.5774f},
  {0.5774f, -0.5774f, 0.5774f}, {0.5774f, -0.5774f, -0.5774f},
  {-0.5774f, 0.5774f, 0.5774f}, {-0.5774f, 0.5774f, -0.5774f},
  {-0.5774f, -0.5774f, 0.5774f},{-0.5774f, -0.5774f, -0.5774f},
};

int boxfaces[][4] =
{
  {0, 1, 2, 3},   {9, 8, 16, 17},
  {6, 14, 15, 7}, {20, 23, 22, 21},
  {12, 13, 5, 4}, {19, 11, 10, 18},
  {7, 15, 16, 8}, {13, 14, 6, 5},
  {18, 10, 9, 17},{19, 12, 4, 11},
  {1, 6, 7, 2},   {14, 21, 22, 15},
  {11, 0, 3, 10}, {20, 19, 18, 23},
  {3, 2, 8, 9},   {17, 16, 22, 23},
  {4, 5, 1, 0},   {20, 21, 13, 12},
  {2, 7, 8, -1},  {16, 15, 22, -1},
  {5, 6, 1, -1},  {13, 21, 14, -1},
  {10, 3, 9, -1}, {18, 17, 23, -1},
  {11, 4, 0, -1}, {20, 12, 19, -1},
};

#define NBOXFACES (sizeof(boxfaces)/sizeof(boxfaces[0]))

/* Draw a box.  Bevel as desired. */
void drawBox(int piece, float xoff, float yoff)
{
  int xlen, ylen;
  int i, k;
  float x, y, z;
  float zlen;
  float *v;

  xlen = xsize[piece];
  ylen = ysize[piece];
  zlen = zsize[piece];

  glColor3ubv(colors[piece]);
  glBegin(GL_QUADS);
  for (i = 0; i < 18; i++) {
    glNormal3fv(boxnormals[i]);
    for (k = 0; k < 4; k++) {
      if (boxfaces[i][k] == -1)
        continue;
      v = boxcoords[boxfaces[i][k]];
      x = v[0] + OFFSETX;
      if (v[0] > 0.5)
        x += xlen - 1;
      y = v[1] + OFFSETY;
      if (v[1] > 0.5)
        y += ylen - 1;
      z = v[2] + OFFSETZ;
      if (v[2] > 0.5)
        z += zlen - 1;
      glVertex3f(xoff + x, yoff + y, z);
    }
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  for (i = 18; i < NBOXFACES; i++) {
    glNormal3fv(boxnormals[i]);
    for (k = 0; k < 3; k++) {
      if (boxfaces[i][k] == -1)
        continue;
      v = boxcoords[boxfaces[i][k]];
      x = v[0] + OFFSETX;
      if (v[0] > 0.5)
        x += xlen - 1;
      y = v[1] + OFFSETY;
      if (v[1] > 0.5)
        y += ylen - 1;
      z = v[2] + OFFSETZ;
      if (v[2] > 0.5)
        z += zlen - 1;
      glVertex3f(xoff + x, yoff + y, z);
    }
  }
  glEnd();
}

float containercoords[][3] =
{
  {-0.1f, -0.1f, 1.0f}, {-0.1f, -0.1f, -0.1f},
  {4.1f, -0.1f, -0.1f}, {4.1f, -0.1f, 1.0f},
  {1.0f, -0.1f, 0.6f},  {3.0f, -0.1f, 0.6f},
  {1.0f, -0.1f, 0.0f},  {3.0f, -0.1f, 0.0f},
  {1.0f, 0.0f, 0.0f},   {3.0f, 0.0f, 0.0f},
  {3.0f, 0.0f, 0.6f},   {1.0f, 0.0f, 0.6f},
  {0.0f, 0.0f, 1.0f},   {4.0f, 0.0f, 1.0f},
  {4.0f, 0.0f, 0.0f},   {0.0f, 0.0f, 0.0f},
  {0.0f, 5.0f, 0.0f},   {0.0f, 5.0f, 1.0f},
  {4.0f, 5.0f, 1.0f},   {4.0f, 5.0f, 0.0f},
  {-0.1f, 5.1f, -0.1f}, {4.1f, 5.1f, -0.1f},
  {4.1f, 5.1f, 1.0f},   {-0.1f, 5.1f, 1.0f},
};

float containernormals[][3] =
{
  {0.0f, -1.0f, 0.0f},  {0.0f, -1.0f, 0.0f},
  {0.0f, -1.0f, 0.0f},  {0.0f, -1.0f, 0.0f},
  {0.0f, -1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},   {0.0f, 1.0f, 0.0f},
  {1.0f, 0.0f, 0.0f},   {1.0f, 0.0f, 0.0f},
  {1.0f, 0.0f, 0.0f},   {-1.0f, 0.0f, 0.0f},
  {-1.0f, 0.0f, 0.0f},  {-1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},   {0.0f, 0.0f, -1.0f},
  {0.0f, 0.0f, -1.0f},  {0.0f, 0.0f, 1.0f},
  {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 1.0f},
  {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 1.0f},
  {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f, 1.0f},
};

int containerfaces[][4] =
{
  {1, 6, 4, 0},     {0, 4, 5, 3},
  {1, 2, 7, 6},     {7, 2, 3, 5},
  {16, 19, 18, 17}, {23, 22, 21, 20},
  {12, 11, 8, 15},  {10, 13, 14, 9},
  {15, 16, 17, 12}, {2, 21, 22, 3},
  {6, 8, 11, 4},    {1, 0, 23, 20},
  {14, 13, 18, 19}, {9, 7, 5, 10},
  {12, 13, 10, 11}, {1, 20, 21, 2},
  {4, 11, 10, 5},   {15, 8, 19, 16},
  {19, 8, 9, 14},   {8, 6, 7, 9},
  {0, 3, 13, 12},   {13, 3, 22, 18},
  {18, 22, 23, 17}, {17, 23, 0, 12},
};

#define NCONTFACES (sizeof(containerfaces)/sizeof(containerfaces[0]))

/* Draw the container */
void drawContainer(void)
{
  int i, k;
  float *v;

  /* Y is reversed here because the model has it reversed */
  /* Arbitrary bright wood-like color */
  glColor3ub(209, 103, 23);
  glBegin(GL_QUADS);
  for (i = 0; i < NCONTFACES; i++) {
    v = containernormals[i];
    glNormal3f(v[0], -v[1], v[2]);
    for (k = 3; k >= 0; k--) {
      v = containercoords[containerfaces[i][k]];
      glVertex3f(v[0] + OFFSETX, -(v[1] + OFFSETY), v[2] + OFFSETZ);
    }
  }
  glEnd();
}

void drawAll(void)
{
  int i, j;
  int piece;
  char done[PIECES + 1];

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -10);
  glRotatef(180, 0, 0, 1);

  if (depth) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  } else {
    glClear(GL_COLOR_BUFFER_BIT);
  }
  for (i = 1; i <= PIECES; i++) {
    done[i] = 0;
  }
  glLoadName(0);
  drawContainer();
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      piece = thePuzzle[i][j];
      if (piece == 0)
        continue;
      if (done[piece])
        continue;
      done[piece] = 1;
      glLoadName(piece);
      if (piece == movingPiece) {
        drawBox(piece, move_x, move_y);
      } else {
        drawBox(piece, j, i);
      }
    }
  }
}

void CALLBACK redraw(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1.0, 0.1, 100.0);

  drawAll();

  if (doubleBuffer)
    auxSwapBuffers();
  else
    glFinish();
}

/* Checks if a space can move */
int canmove0(Config pieces, int x, int y, int dir, Config newpieces)
{
  char piece;
  int xadd, yadd;
  int l, m;

  xadd = xadds[dir];
  yadd = yadds[dir];

  if (x + xadd < 0 || x + xadd >= WIDTH ||
    y + yadd < 0 || y + yadd >= HEIGHT)
    return 0;
  piece = pieces[y + yadd][x + xadd];
  if (piece == 0)
    return 0;
  memcpy(newpieces, pieces, HEIGHT * WIDTH);
  for (l = 0; l < WIDTH; l++) {
    for (m = 0; m < HEIGHT; m++) {
      if (newpieces[m][l] == piece)
        newpieces[m][l] = 0;
    }
  }
  xadd = -xadd;
  yadd = -yadd;
  for (l = 0; l < WIDTH; l++) {
    for (m = 0; m < HEIGHT; m++) {
      if (pieces[m][l] == piece) {
        int newx, newy;

        newx = l + xadd;
        newy = m + yadd;
        if (newx < 0 || newx >= WIDTH ||
          newy < 0 || newy >= HEIGHT)
          return 0;
        if (newpieces[newy][newx] != 0)
          return 0;
        newpieces[newy][newx] = piece;
      }
    }
  }
  return 1;
}

/* Checks if a piece can move */
int canmove(Config pieces, int x, int y, int dir, Config newpieces)
{
  int xadd, yadd;

  xadd = xadds[dir];
  yadd = yadds[dir];

  if (x + xadd < 0 || x + xadd >= WIDTH ||
    y + yadd < 0 || y + yadd >= HEIGHT)
    return 0;
  if (pieces[y + yadd][x + xadd] == pieces[y][x]) {
    return canmove(pieces, x + xadd, y + yadd, dir, newpieces);
  }
  if (pieces[y + yadd][x + xadd] != 0)
    return 0;
  return canmove0(pieces, x + xadd, y + yadd, (dir + 2) % 4, newpieces);
}

int selectPiece(int mousex, int mousey)
{
  long hits;
  GLuint selectBuf[1024];
  GLuint closest;
  GLuint dist;

  glSelectBuffer(1024, selectBuf);
  (void) glRenderMode(GL_SELECT);
  glInitNames();

  /* Because LoadName() won't work with no names on the stack */
  glPushName(-1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPickMatrix(mousex, H - mousey, 4, 4, viewport);
  gluPerspective(45, 1.0, 0.1, 100.0);

  drawAll();

  hits = glRenderMode(GL_RENDER);
  if (hits <= 0) {
    return 0;
  }
  closest = 0;
  dist = 4294967295;
  while (hits) {
    if (selectBuf[(hits - 1) * 4 + 1] < dist) {
      dist = selectBuf[(hits - 1) * 4 + 1];
      closest = selectBuf[(hits - 1) * 4 + 3];
    }
    hits--;
  }
  return closest;
}

void nukePiece(int piece)
{
  int i, j;

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if (thePuzzle[i][j] == piece) {
        thePuzzle[i][j] = 0;
      }
    }
  }
}

void multMatrices(const GLfloat a[16], const GLfloat b[16], GLfloat r[16])
{
  int i, j;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      r[i * 4 + j] =
        a[i * 4 + 0] * b[0 * 4 + j] +
        a[i * 4 + 1] * b[1 * 4 + j] +
        a[i * 4 + 2] * b[2 * 4 + j] +
        a[i * 4 + 3] * b[3 * 4 + j];
    }
  }
}

void makeIdentity(GLfloat m[16])
{
  m[0 + 4 * 0] = 1;
  m[0 + 4 * 1] = 0;
  m[0 + 4 * 2] = 0;
  m[0 + 4 * 3] = 0;
  m[1 + 4 * 0] = 0;
  m[1 + 4 * 1] = 1;
  m[1 + 4 * 2] = 0;
  m[1 + 4 * 3] = 0;
  m[2 + 4 * 0] = 0;
  m[2 + 4 * 1] = 0;
  m[2 + 4 * 2] = 1;
  m[2 + 4 * 3] = 0;
  m[3 + 4 * 0] = 0;
  m[3 + 4 * 1] = 0;
  m[3 + 4 * 2] = 0;
  m[3 + 4 * 3] = 1;
}

/*
   ** inverse = invert(src)
 */
int invertMatrix(const GLfloat src[16], GLfloat inverse[16])
{
  int i, j, k, swap;
  double t;
  GLfloat temp[4][4];

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      temp[i][j] = src[i * 4 + j];
    }
  }
  makeIdentity(inverse);

  for (i = 0; i < 4; i++) {
    /* 
       ** Look for largest element in column */
    swap = i;
    for (j = i + 1; j < 4; j++) {
      if (fabs(temp[j][i]) > fabs(temp[i][i])) {
        swap = j;
      }
    }
    if (swap != i) {
      /* 
         ** Swap rows. */
      for (k = 0; k < 4; k++) {
        t = temp[i][k];
        temp[i][k] = temp[swap][k];
        temp[swap][k] = t;

        t = inverse[i * 4 + k];
        inverse[i * 4 + k] = inverse[swap * 4 + k];
        inverse[swap * 4 + k] = t;
      }
    }
    if (temp[i][i] == 0) {
      /* 
         ** No non-zero pivot.  The matrix is singular, which
         shouldn't ** happen.  This means the user gave us a
         bad matrix. */
      return 0;
    }
    t = temp[i][i];
    for (k = 0; k < 4; k++) {
      temp[i][k] /= t;
      inverse[i * 4 + k] /= t;
    }
    for (j = 0; j < 4; j++) {
      if (j != i) {
        t = temp[j][i];
        for (k = 0; k < 4; k++) {
          temp[j][k] -= temp[i][k] * t;
          inverse[j * 4 + k] -= inverse[i * 4 + k] * t;
        }
      }
    }
  }
  return 1;
}

/*
   ** This is a screwball function.  What it does is the following:
   ** Given screen x and y coordinates, compute the corresponding object space 
   **   x and y coordinates given that the object space z is 0.9 + OFFSETZ.
   ** Since the tops of (most) pieces are at z = 0.9 + OFFSETZ, we use that 
   **   number.
 */
int computeCoords(int piece, int mousex, int mousey,
  GLfloat * selx, GLfloat * sely)
{
  GLfloat modelMatrix[16];
  GLfloat projMatrix[16];
  GLfloat finalMatrix[16];
  GLfloat in[4];
  GLfloat a, b, c, d;
  GLfloat top, bot;
  GLfloat z;
  GLfloat w;
  GLfloat height;

  if (piece == 0)
    return 0;
  height = zsize[piece] - 0.1 + OFFSETZ;

  glGetFloatv(GL_PROJECTION_MATRIX, projMatrix);
  glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);
  multMatrices(modelMatrix, projMatrix, finalMatrix);
  if (!invertMatrix(finalMatrix, finalMatrix))
    return 0;

  in[0] = (2.0 * (mousex - viewport[0]) / viewport[2]) - 1;
  in[1] = (2.0 * ((H - mousey) - viewport[1]) / viewport[3]) - 1;

  a = in[0] * finalMatrix[0 * 4 + 2] +
    in[1] * finalMatrix[1 * 4 + 2] +
    finalMatrix[3 * 4 + 2];
  b = finalMatrix[2 * 4 + 2];
  c = in[0] * finalMatrix[0 * 4 + 3] +
    in[1] * finalMatrix[1 * 4 + 3] +
    finalMatrix[3 * 4 + 3];
  d = finalMatrix[2 * 4 + 3];
  top = height * c - a;
  bot = b - height * d;
  if (bot == 0.0)
    return 0;
  z = top / bot;
  w = c + d * z;
  *selx = (in[0] * finalMatrix[0 * 4 + 0] +
    in[1] * finalMatrix[1 * 4 + 0] +
    z * finalMatrix[2 * 4 + 0] +
    finalMatrix[3 * 4 + 0]) / w - OFFSETX;
  *sely = (in[0] * finalMatrix[0 * 4 + 1] +
    in[1] * finalMatrix[1 * 4 + 1] +
    z * finalMatrix[2 * 4 + 1] +
    finalMatrix[3 * 4 + 1]) / w - OFFSETY;
  return 1;
}

static int selected;
static int selectx, selecty;
static float selstartx, selstarty;

void grabPiece(int piece, float selx, float sely)
{
  int hit;

  selectx = selx;
  selecty = sely;
  if (selectx < 0 || selecty < 0 || selectx >= WIDTH || selecty >= HEIGHT) {
    return;
  }
  hit = thePuzzle[selecty][selectx];
  if (hit != piece)
    return;
  if (hit) {
    movingPiece = hit;
    while (selectx > 0 && thePuzzle[selecty][selectx - 1] == movingPiece) {
      selectx--;
    }
    while (selecty > 0 && thePuzzle[selecty - 1][selectx] == movingPiece) {
      selecty--;
    }
    move_x = selectx;
    move_y = selecty;
    selected = 1;
    selstartx = selx;
    selstarty = sely;
  } else {
    selected = 0;
  }
}

void moveSelection(float selx, float sely)
{
  float deltax, deltay;
  int dir;
  Config newpieces;

  if (!selected)
    return;
  deltax = selx - selstartx;
  deltay = sely - selstarty;

  if (fabs(deltax) > fabs(deltay)) {
    deltay = 0;
    if (deltax > 0) {
      if (deltax > 1)
        deltax = 1;
      dir = 2;
    } else {
      if (deltax < -1)
        deltax = -1;
      dir = 0;
    }
  } else {
    deltax = 0;
    if (deltay > 0) {
      if (deltay > 1)
        deltay = 1;
      dir = 3;
    } else {
      if (deltay < -1)
        deltay = -1;
      dir = 1;
    }
  }
  if (canmove(thePuzzle, selectx, selecty, dir, newpieces)) {
    move_x = deltax + selectx;
    move_y = deltay + selecty;
    if (deltax > 0.5) {
      memcpy(thePuzzle, newpieces, HEIGHT * WIDTH);
      selectx++;
      selstartx++;
    } else if (deltax < -0.5) {
      memcpy(thePuzzle, newpieces, HEIGHT * WIDTH);
      selectx--;
      selstartx--;
    } else if (deltay > 0.5) {
      memcpy(thePuzzle, newpieces, HEIGHT * WIDTH);
      selecty++;
      selstarty++;
    } else if (deltay < -0.5) {
      memcpy(thePuzzle, newpieces, HEIGHT * WIDTH);
      selecty--;
      selstarty--;
    }
  } else {
    if (deltay > 0 && thePuzzle[selecty][selectx] == 10 &&
      selectx == 1 && selecty == 3) {
      /* Allow visual movement of solution piece outside of the 
         box */
      move_x = selectx;
      move_y = sely - selstarty + selecty;
    } else {
      move_x = selectx;
      move_y = selecty;
    }
  }
}

void dropSelection(void)
{
  if (!selected)
    return;
  movingPiece = 0;
  selected = 0;
}

static int solving;
static float lastquat[4];
static int sel_piece;

static void CALLBACK Reshape(int width, int height)
{

  W = width;
  H = height;
  glViewport(0, 0, W, H);
  glGetIntegerv(GL_VIEWPORT, viewport);
}

void CALLBACK mousedown(AUX_EVENTREC *event)
{
  float selx, sely;
  int x, y;

  x = event->data[AUX_MOUSEX];
  y = event->data[AUX_MOUSEY];
  curX = x;
  curY = y;
  if (solving) {
    solving = 0;
    movingPiece = 0;
  }
  sel_piece = selectPiece(x, y);
  if (computeCoords(sel_piece, x, y, &selx, &sely)) {
    grabPiece(sel_piece, selx, sely);
  }
}

void CALLBACK mouseup(AUX_EVENTREC *event)
{
  int x, y;
  float selx, sely;

  x = event->data[AUX_MOUSEX];
  y = event->data[AUX_MOUSEY];
  computeCoords(sel_piece, x, y, &selx, &sely);
  moveSelection(selx, sely);
  dropSelection();
  redraw();
}

void init(void)
{
  static float lmodel_ambient[] =  {0.0f, 0.0f, 0.0f, 0.0f};
  static float lmodel_twoside[] =  {GL_FALSE};
  static float lmodel_local[] =  {GL_FALSE};
  static float light0_ambient[] =  {0.1f, 0.1f, 0.1f, 1.0f};
  static float light0_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};
  static float light0_position[] =  {0.8660254f, 0.5f, 1.0f, 0.0f};
  static float light0_specular[] =  {0.0f, 0.0f, 0.0f, 0.0f};
  static float bevel_mat_ambient[] =  {0.0f, 0.0f, 0.0f, 1.0f};
  static float bevel_mat_shininess[] =  {40.0f};
  static float bevel_mat_specular[] =  {0.0f, 0.0f, 0.0f, 0.0f};
  static float bevel_mat_diffuse[] =  {1.0f, 0.0f, 0.0f, 0.0f};

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);

  glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glEnable(GL_LIGHT0);

  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodel_local);
  glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glEnable(GL_LIGHTING);

  glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
  glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);

  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_FLAT);
}

void main(int argc, char **argv)
{
  long i;

  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 's':
        doubleBuffer = 0;
        break;
      default:
		break;
      }
    } else {
      break;
    }
  }
  auxInitPosition(0, 0, W, H);
  if (doubleBuffer) {
    auxInitDisplayMode(AUX_DEPTH | AUX_RGB | AUX_DOUBLE);
  } else {
    auxInitDisplayMode(AUX_DEPTH | AUX_RGB | AUX_SINGLE);
  }
  auxInitWindow("glpuzzle");
  init();
  glGetIntegerv(GL_VIEWPORT, viewport);
  auxReshapeFunc(Reshape);
  auxMouseFunc(AUX_LEFTBUTTON,AUX_MOUSEDOWN,mousedown);
  auxMouseFunc(AUX_LEFTBUTTON,AUX_MOUSEUP,mouseup);
  auxMainLoop(redraw);
}
