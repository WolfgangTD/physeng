#include "Vec3.h"
#include <cmath>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct Circle{
    float radius;
    Vec3 point;
};

Vec3 getCirclePos (Circle a){
    return getVecPos(a.point);
}

bool circlevsCircleUnoptimized( Circle a, Circle b )
{
  float r = a.radius + b.radius;
  return r < distance( getCirclePos(a), getCirclePos(b) );
}
bool circlevsCircleOptimized( Circle a, Circle b )
{
  float r = a.radius + b.radius;
  r *= r;
  return r < ((a.point.x + b.point.x)*(a.point.x + b.point.x)) + ((a.point.y + b.point.y)*(a.point.y + b.point.y));
}

void drawCircle(SDL_Renderer* renderer, Circle circle){
    const int32_t diameter = circle.radius * 2;
    int32_t x = (circle.radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y){
         //  Each of the following renders an octant of the circle
        SDL_RenderPoint(renderer, circle.point.x + x, circle.point.y - y);
        SDL_RenderPoint(renderer, circle.point.x + x, circle.point.y + y);
        SDL_RenderPoint(renderer, circle.point.x - x, circle.point.y - y);
        SDL_RenderPoint(renderer, circle.point.x - x, circle.point.y + y);
        SDL_RenderPoint(renderer, circle.point.x + y, circle.point.y - x);
        SDL_RenderPoint(renderer, circle.point.x + y, circle.point.y + x);
        SDL_RenderPoint(renderer, circle.point.x - y, circle.point.y - x);
        SDL_RenderPoint(renderer, circle.point.x - y, circle.point.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void drawCircleFilled(SDL_Renderer* renderer, Circle circle){
    const int32_t diameter = circle.radius * 2;
    int32_t x = (circle.radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y){
         //  Each of the following renders an octant of the circle
        SDL_RenderLine(renderer, circle.point.x - y, circle.point.y + x, circle.point.x + y, circle.point.y + x);
        SDL_RenderLine(renderer, circle.point.x - x, circle.point.y + y, circle.point.x + x, circle.point.y + y);
        SDL_RenderLine(renderer, circle.point.x - x, circle.point.y - y, circle.point.x + x, circle.point.y - y);
        SDL_RenderLine(renderer, circle.point.x - y, circle.point.y - x, circle.point.x + y, circle.point.y - x);
        
        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}