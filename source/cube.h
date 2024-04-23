#include <SDL2/SDL.h>
#include <point.h>
#include <settings.h>
#include <iostream>

using namespace std;

class Cube{
private:
    vector<Point> points = {
        Point(-1, 1, 1),
        Point(1, 1, 1),
        Point(1, -1, 1),
        Point(-1, -1, 1),
        Point(-1, 1, -1),
        Point(1, 1, -1),
        Point(1, -1, -1),
        Point(-1, -1, -1)
    };
public:
    int x, y;
    Point screenShift = Point(WIDTH / 2, HEIGHT / 2);
    Point screenShiftOpposite = Point(-WIDTH / 2, -HEIGHT / 2);
    int scale = 170;

    SDL_Renderer* window;

    Matrix rotationXYZ;

    Cube(int x, int y, SDL_Renderer* renderer){
        this->x = x;
        this->y = y;

        this->window = renderer;

        for (Point& p : this->points) {
            p.x = (scale * p.x + screenShift.x);
            p.y = (scale * p.y + screenShift.y);
            p.z = (scale * p.z + screenShift.z);
        }

        this->rotationXYZ = getRotationMatrix(0.001,0.001,0.001);
    }

    void connect(const vector<Point> &points, int i, int j) {
        // SDL_Point p_[2];
        // p_[0].x = this->x+points[i].x;
        // p_[0].y = this->y+points[i].y;

        // p_[1].x = this->x+points[j].x;
        // p_[1].y = this->y+points[j].y;

        // SDL_RenderDrawPoints(this->window, p_, 2);

        SDL_RenderDrawLine(
            this->window,
            this->x+points[i].x,
            this->y+points[i].y,
            this->x+points[j].x,
            this->y+points[j].y
        );
    }

    void draw(){
        for (Point &p : this->points) {
            p = translate(this->screenShiftOpposite, p);
            p = transform(this->rotationXYZ, p);
            p = translate(this->screenShift, p);
        }

        // SDL_RenderSetScale(this->window, 3, 3);
        SDL_SetRenderDrawColor(this->window, 200, 100, 200, 255);
        for (int i=0; i<4; i++) {
            connect(points, i, (i + 1) % 4);
            connect(points, i + 4, ((i + 1) % 4) + 4);
            connect(points, i, i + 4);            
        }
        // SDL_RenderSetScale(this->window, 1, 1);
    }
};