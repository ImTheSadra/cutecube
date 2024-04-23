#include <SDL2/SDL.h>
#include <cube.h>
#include <vector>
// #include <settings.h>

class App
{
private:
public:
    double angles[3]{0,0,0};
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running = true;

    Cube cube = Cube(0,0,NULL);

    SDL_GLContext glc;

    int status = EXIT_SUCCESS;
    App(){
        this->window = SDL_CreateWindow(
            "recraft",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            0
        );
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetSwapInterval(0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        this->glc = SDL_GL_CreateContext(window);
        
        this->renderer = SDL_CreateRenderer(this->window, -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
        this->cube = Cube(0,0, this->renderer);
    };

    void run(){
        SDL_Event event;
        while (this->running){
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){this->running = false;}
                if (event.type == SDL_KEYDOWN){
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RIGHT:
                        this->angles[1] -= 0.001;
                        break;
                    
                    case SDLK_LEFT:
                        this->angles[1] += 0.001;
                        break;

                    case SDLK_DOWN:
                        this->angles[0] += 0.001;
                        break;

                    case SDLK_UP:
                        this->angles[0] -= 0.001;
                        break;

                    default:
                        break;
                    }
                }
            }

            SDL_SetRenderDrawColor(this->renderer, 100, 200, 100, 255);
            SDL_RenderClear(this->renderer);

            this->cube.draw();

            SDL_RenderPresent(this->renderer);

            SDL_Delay(1);
        }
    }
};