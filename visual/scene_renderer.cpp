#include <glad/glad.h>
#include "renderer.hpp"
class Scene_renderer: public Renderer{
    public:
    Scene_renderer(){};
    void render_begin();
};
void Scene_renderer::render_begin(){
        glClearColor(0.5f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
};
