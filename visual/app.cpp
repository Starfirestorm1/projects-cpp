
#include <iostream>
#include "initializer.cpp"
// #include "figure.cpp"
#include "scene.cpp"
class App {
    public:
    App(){
        init();
    };
    void init(){
        Initializer* initializer = new Initializer();
        Figure *figure = new Figure();
        figure->bind_move_direction(&initializer->move_direction);

        while(!initializer->windowShouldClose()){
            initializer->begin();

            figure->render();

            initializer->end();
        }
        initializer->terminate();

    }
};
