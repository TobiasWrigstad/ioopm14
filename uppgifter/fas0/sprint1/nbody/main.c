#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef ANIMATE
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X_SIZE 800
#define Y_SIZE 800
#endif

#define prec float
#define PI 3.14159265359


static prec gdt = 0.0001;

typedef struct {
} body;


static void update(body* a, prec dt)
{
}


static void resetForce(body* b) {} 

static void addForce(body* a, body* b)
{
}

static prec newRand() 
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}


void init(int N, body* star)
{

}

static void updateForces(int N, body* star)
{
}

// Manually copy coordinates from stars into points (to be drawn).
// Look at the manual file for XPoint to see which 
// format XPoint accepts its coordinates in.
#ifdef ANIMATE
static void copyToXBuffer(body* star, XPoint* points, int N)
{
}
#endif

int main(int argc, char* argv[]) {

  int N = 200;
  int iter = 1000;

  if(argc == 3)
    {
      N = atoi(argv[1]);
      iter = atoi(argv[2]);
    }

#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint)*N);
  Display* disp;
  Window window, rootwin;
  int screen;

  disp = XOpenDisplay(NULL);
  screen = DefaultScreen(disp);
  rootwin = RootWindow(disp,screen);
  window = XCreateSimpleWindow(disp,rootwin,
                               0,0,X_SIZE,Y_SIZE,1,0,0);
  GC gc = XCreateGC(disp, window, 0, 0);
  XSetForeground(disp, gc, WhitePixel(disp, screen));
  XSetBackground(disp, gc, BlackPixel(disp, screen));
  XMapWindow(disp,window);

  XClearWindow(disp,window);	
	
  copyToXBuffer(star, points, N);
  XDrawPoints(disp, window, gc, points, N, 0);

  XFlush(disp);

#endif

  clock_t start = clock();
  for(int i = 0; i < iter; i++)
    {

#ifdef ANIMATE
      copyToXBuffer(star, points, N);
      XDrawPoints(disp, window, gc, points, N, CoordModeOrigin);
      XClearWindow(disp,window);	
#endif
    }
  clock_t stop = clock();
  float diff = (float)(stop - start)/CLOCKS_PER_SEC;
  printf("Total: %lf seconds\n",diff);
  printf("Bodies: %d\n",N);
  printf("Iterations: %d\n", iter);

#ifdef ANIMATE
  XCloseDisplay(disp);
#endif

  return 0;
}
