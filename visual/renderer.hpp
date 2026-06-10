#ifndef RENDERER
#pragma message("RENDERER defining")
#include <iostream>
#include <map>
#include "shader.hpp"
class Renderer{
    public:
        Renderer();
        Shader *ourShader;
        std::map<std::string, unsigned int> map;
        void init();
        void hello();
        void error_check();


};

#define RENDERER
#endif
#ifdef RENDERER
#pragma message("RENDERER already defined")
#endif
