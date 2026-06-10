#include <glad/glad.h>
#include <iostream>
#include <map>
#include "shader.hpp"
#include "renderer.hpp"
#include <stdio.h>
Renderer::Renderer(){
    std::cout << "renderer constructor" << std::endl;
};
void Renderer::init(){
};
void Renderer::hello(){
    std::cout << "renderer hello" << std::endl;
};
void Renderer::error_check(){
    GLenum code;
    const GLubyte* string;
    code = glGetError();
    if(code != GL_NO_ERROR){
        std::cout << "ERROR: " << code << std::endl;
    } else {
        std::cout << "NO ERRORS" << std::endl;
    }
};
