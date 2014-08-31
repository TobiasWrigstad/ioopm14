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
  prec rx, ry; prec vx, vy; prec fx, fy;
  prec mass;
} body;


static void update(body* a, prec dt)
{
  a->rx = a->rx + dt*a->vx + 0.5*dt*dt*a->fx;
  a->ry = a->ry + dt*a->vy + 0.5*dt*dt*a->fy;
  a->vx += dt*a->fx;
  a->vy += dt*a->fy;
}


static void resetForce(body* b) { b->fx = 0.0; b->fy = 0.0; }

static void addForce(body* a, body* b)
{
  prec dx = b->rx - a->rx;
  prec dy = b->ry - a->ry;

  prec dist = sqrt(dx*dx + dy*dy);
  prec inv = 1.0/dist;
  prec inv2 = inv*inv;

  prec F = b->mass*inv2;
  a->fx += F * dx;
  a->fy += F * dy;
}

static prec newRand()
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}


void init(int N, body* star)
{

  prec radius = 1e18;
  srand((unsigned)time(NULL));

  for(int i = 0; i < N; i++)
    {
      prec ang = 360*newRand();
      prec px = 2.0/exp(newRand())*cos( ang )*newRand();
      prec py = 1.0/exp(newRand())*sin( ang )*newRand();

      // compute initial speed (vortex)
      prec vy = 20.0*px;
      prec vx = -20.0*py;

      prec mass = newRand()*2.0;

      star[i].rx = px;
      star[i].ry = py;
      star[i].vx = vx;
      star[i].vy = vy;
      star[i].mass = mass;
    }

}

static void updateForces(int N, body* star)
{
  for( int i = 0; i < N; i++ )
    {
      resetForce( &star[i] );
      for( int j = 0; j < N; j++ )
	{
	  if( i != j ) addForce( &star[i], &star[j] ); // jmf mål G16
	}
    }

  for( int i = 0; i < N; i++ )
    update( &star[i], gdt );
}

void writeToFile(char* name, int N, body* star)
{
  FILE* f = fopen(name,"w");

  for(int i = 0; i < N; i++)
    {
      fprintf(f,"%e %e\n", star[i].rx, star[i].ry);
    }
  fclose(f);
}

#ifdef ANIMATE
static void copyToXBuffer(body* star, XPoint* points, int N)
{
  for(int i = 0; i < N; i++)
    {
      points[i].x = 100 * star[i].rx + X_SIZE / 2.0;
      points[i].y = 100 * star[i].ry + Y_SIZE / 2.0;
    }
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

  body* star = malloc(sizeof(body) * N);

  init(N, star);

#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint) * N);
  Display* disp;
  Window window, rootwin;
  int screen;

  disp = XOpenDisplay(NULL);
  screen = DefaultScreen(disp);
  rootwin = RootWindow(disp, screen);
  window = XCreateSimpleWindow(disp, rootwin, 0, 0, X_SIZE, Y_SIZE, 1, 0, 0);
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
      updateForces(N, star);

#ifdef ANIMATE
      copyToXBuffer(star, points, N);
      XDrawPoints(disp, window, gc, points, N, CoordModeOrigin);
      XClearWindow(disp,window);
#endif
    }
  clock_t stop = clock();
  float diff = (stop - start) / 1.0 * CLOCKS_PER_SEC;
  printf("Total: %lf seconds\n",diff);
  printf("Bodies: %d\n",N);
  printf("Iterations: %d\n", iter);

#ifdef ANIMATE
  XCloseDisplay(disp);
#endif

  return 0;
}
