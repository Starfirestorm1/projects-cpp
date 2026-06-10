#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ostream>
#include "figure.cpp"
#include "map"
#include "string"
#include "glm/glm.hpp"
class Initializer {
    public:
    GLFWwindow *window;
    bool windowShoudClose = false;
    std::map<std::string, bool> active_keys;
    std::map<std::string, int> holder_of_constants;
    glm::vec3 move_direction = glm::vec3(0.0f, 0.0f, 0.0f);
    float speed = 0.05f;
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void processInput(GLFWwindow *window);
    static void hello(GLFWwindow * w, int a, int b);
    Initializer(){
        init();
    }
    int init(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        
            std::cout << "Failed to initialize Glad" << std::endl;
            return -1;
        }
        // while(!glfwWindowShouldClose(window)){ 
        //     processInput(window);
        //     glfwSwapBuffers(window);
        //     glfwPollEvents();
        //
        // }
        active_keys.insert({"key_w", false});
        active_keys.insert({"key_d", false});
        active_keys.insert({"key_s", false});
        active_keys.insert({"key_a", false});
        
        holder_of_constants.insert({"key_w", GLFW_KEY_W});
        holder_of_constants.insert({"key_d", GLFW_KEY_D});
        holder_of_constants.insert({"key_s", GLFW_KEY_S});
        holder_of_constants.insert({"key_a", GLFW_KEY_A});
        // holder_of_constants.inser;
        return 0;

    };
    void terminate(){
        glfwTerminate();
    };
    void begin(){
        processInput(window);
    };
    void end(){
        glfwSwapBuffers(window);
        glfwPollEvents();
    };
    bool windowShouldClose(){
        return glfwWindowShouldClose(window);
    }

};

void Initializer::processInput(GLFWwindow *window) {
    //std::cout<<"hey"<<std::endl;
    auto key_escape = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if(key_escape == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        active_keys.at("key_w") = true;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        active_keys.at("key_d") = true;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        active_keys.at("key_s") = true;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        active_keys.at("key_a") = true;
    }
    if(active_keys.at("key_w")==true){
       if(glfwGetKey(window, holder_of_constants.at("key_w"))==GLFW_RELEASE){
           active_keys.at("key_w") = false;
           move_direction.y = 0.0f;
       } else {
           move_direction.y = speed;
       } 
    }
    if(active_keys.at("key_d")==true){
       if(glfwGetKey(window, holder_of_constants.at("key_d"))==GLFW_RELEASE){
           active_keys.at("key_d") = false;
           move_direction.x = 0.0f;
       } else {
           move_direction.x = speed;
       } 
    }
    if(active_keys.at("key_s")==true){
       if(glfwGetKey(window, holder_of_constants.at("key_s"))==GLFW_RELEASE){
           active_keys.at("key_s") = false;
           move_direction.y = 0.0f;
       } else {
           move_direction.y = -speed;
       } 
    }
    if(active_keys.at("key_a")==true){
       if(glfwGetKey(window, holder_of_constants.at("key_a"))==GLFW_RELEASE){
           active_keys.at("key_a") = false;
           move_direction.x = 0.0f;
       } else {
           move_direction.x = -speed;
       } 
    }
    // std::map<std::string, bool>::iterator it;
    // for(it = active_keys.begin(); it!=active_keys.end(); it++){
    //     if(it->second == true){
    //        if(glfwGetKey(window, holder_of_constants.at(it->first))==GLFW_RELEASE){
    //            std::cout << " released " << it->first << std::endl;
    //            active_keys.at(it->first) = false;
    //        } 
    //     }
    // }
}
void Initializer::framebuffer_size_callback(GLFWwindow *window, int width, int height){
    
    std::cout<<"hey"<<std::endl;
    glViewport(0, 0, width, height);
}
void Initializer::hello(GLFWwindow * w, int a, int b){
}
