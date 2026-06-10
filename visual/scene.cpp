#include "component.hpp"
#include "scene_renderer.cpp"
class Scene: public Component {
    public:
    Scene_renderer *scene_renderer = new Scene_renderer();
    Scene(){}
    void render_begin(){
       scene_renderer->render_begin();
    }
};
