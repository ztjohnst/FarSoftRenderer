#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <string>
#include <stdio.h>
#include <algorithm>

#include "model.h"
#include "vector.h"

#define RED 0xffff0000
#define BLUE 0xff0000ff
#define GREEN 0xff00ff00

// Pixel is ARGB -> 0xffff0000 is RED
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + (y) * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  *target_pixel = pixel;
}

void drawLine(int x0, int x1, int y0, int y1, Uint32 color, SDL_Surface* surface)
{
  // Calculate bound
  int xdiff = std::abs(x0-x1);
  int ydiff = std::abs(y0-y1);
  int error = 0;

  if(xdiff > ydiff)
  {
    if(x0 > x1) 
    {
      std::swap(x0,x1);
      std::swap(y0,y1);
    }
    int y = y0;
    int derror = std::abs(ydiff) * 2;
    for(int x = x0 ; x <= x1 ; x++)
    {
      error += derror;
      if(error > xdiff)
      {
        y += (y1>y0?1:-1);
        error -= xdiff*2;
      }
      setPixel(surface, x, y, color);
    }
  }
  else
  {
    if(y0 > y1) 
    {
      std::swap(x0,x1);
      std::swap(y0,y1);
    }
    int x = x0;
    int derror = std::abs(xdiff) * 2;
    for(int y = y0 ; y <= y1 ; y++)
    {
      error += derror;
      if(error > xdiff)
      {
        x += (x1>x0?1:-1);
        error -= ydiff*2;
      }
      setPixel(surface, x, y, color);
    }
  }
}

void drawTriangle(Vector2Di v0, Vector2Di v1, Vector2Di v2, Uint32 color, SDL_Surface* surface)
{
  drawLine(v0.x, v1.x, v0.y, v1.y, color, surface);  
  drawLine(v1.x, v2.x, v1.y, v2.y, color, surface);  
  drawLine(v2.x, v0.x, v2.y, v0.y, color, surface);  
}

void drawModelWireFrame(Model* m, int width, int height, Uint32 color, SDL_Surface* surface)
{
  for(unsigned long int i = 0 ; i < m->indices.size() ; i++)
  {
    Index ind = m->indices[i]; 
    for(int j = 0 ; j < 3 ; j++)
    {
      Vector3Df v0 = m->vertices[ind[j]];
      Vector3Df v1 = m->vertices[ind[(j+1)%3]];
      int x0 = (v0.x+1)*width / 2.;
      int x1 = (v1.x+1)*width / 2.;
      int y0 = (v0.y+1)*height / 2.;
      int y1 = (v1.y+1)*height / 2.;
      drawLine(x0,x1,y0,y1,color,surface);
    }
  }
}


int main(int argc, char** args) 
{

  int width = 1280;
  int height = 720;

  SDL_version compiled;
  SDL_version linked;

  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  printf("We compiled against SDL version %d.%d.%d ...\n", compiled.major, compiled.minor, compiled.patch);
  printf("But we are linking against SDL version %d.%d.%d.\n", linked.major, linked.minor, linked.patch);

  SDL_Window* window = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow("FarSoftRenderer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_SHOWN);
  if (window == NULL) 
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  // Get Surface
  SDL_Surface* window_surface = SDL_GetWindowSurface(window);

  Model m("data/african_head.obj");
  //Model m("data/kitten.obj");

  printf("# vertices in model: %lu\n", m.vertices.size());

  // Drawing.... TODO: move inside of loop
  //drawLine(50, 300, 50, 60, GREEN, window_surface);
  //drawLine(300, 50, 300, 50, RED, window_surface);
  
  drawModelWireFrame(&m, width, height, GREEN, window_surface);

  Vector2Di t0[3] = { Vector2Di(10, 70),   Vector2Di(50, 160),  Vector2Di(70, 80) };
  //Vector2D t1[3] = { Vector2D(180, 50),   Vector2D(150, 1),  Vector2D(70, 180) };
  //Vector2D t2[3] = { Vector2D(180, 150),   Vector2D(120, 160),  Vector2D(130, 180) };

  //drawTriangle(t0[0], t0[1], t0[2], GREEN, window_surface);

  SDL_UpdateWindowSurface(window);

  bool quit = false;
  SDL_Event e;
  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
