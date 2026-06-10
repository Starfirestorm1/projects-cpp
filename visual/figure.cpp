#include <iostream>
#include "component.hpp"
#include <map>
#include "figure_renderer.cpp"
class Figure: public Component {

    public:
    std::map<std::string, Component> components;
    float (*vertices)[12];
    float (*vert) [12];
    // int *indices = new int[]{0, 1, 3, 1, 2, 3};
    int (*indices)[6];
    float (*color)[12];
    Figure_renderer *figure_renderer = new Figure_renderer();
    Figure(){
        float vertices1[]={-0.5f, -0.5f,  1.0f,
                           -0.5f,  0.5f,  1.0f,
                            0.5f,  0.5f,  1.0f,
                            0.5f, -0.5f,  1.0f
                          };

        vertices = &vertices1;
        vert = &vertices1;
        int indices1[] = {0, 1, 3,
                          1, 2, 3,
                         };
        indices = &indices1;

        //                  0.0f, 1.0f,
        //                  1.0f, 1.0f,
        //                  1.0f, 0.0f
        // };
        float color1[] = { 0.5f,  0.0f,  0.5f,
                           0.5f,  0.0f,  0.5f,
                           0.5f,  0.0f,  0.5f,
                           0.5f,  0.0f,  0.5f
                         };
        color = &color1;
        init();
    };
    void render();
    void hello();
    void init();
    void bind_move_direction(glm::vec3*);
};
void Figure::init(){
    figure_renderer->init();
    figure_renderer->bind_vertex_array();
    figure_renderer->load_date_to_shader(vertices, 0, 3, 48);
    // std::cout << sizeof(*vert) << std::endl;
    figure_renderer->load_date_to_shader(color, 1, 3, 48);
    figure_renderer->load_indices(indices, 24);
    // figure_renderer->load_date_to_shader1();
    // figure_renderer->load_date_to_shader2();
    // figure_renderer->load_indices2();
};
void Figure::render(){
    // figure_renderer->error_check();
    figure_renderer->bind_vertex_array();
    figure_renderer->render();
};
void Figure::hello(){
    std::cout<<"hello"<<std::endl;
};
void Figure::bind_move_direction(glm::vec3 *vec){
    figure_renderer->bind_move_direction(vec);
}
