#include <app.h>

int WinMain(int* argc, char* argv[]){
    App app = App();

    app.run();

    return app.status;
}