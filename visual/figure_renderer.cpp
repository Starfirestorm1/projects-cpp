#include "renderer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Figure_renderer: public Renderer{
    public:
    glm::vec3 *position = new glm::vec3(0.0f);
    glm::mat4 trans;
    unsigned int transformLoc;

    Figure_renderer(){
    };
    void load_date_to_shader(float (*data)[12], int pos, int quantity, int size){
        // std::cout << "load data " << sizeof(*data) << std::endl;
        std::string name = "VBO" + std::to_string(pos);
        glBindBuffer(GL_ARRAY_BUFFER, map.at(name));
        glBufferData(GL_ARRAY_BUFFER, size, *data, GL_STATIC_DRAW);
        glVertexAttribPointer(pos, quantity, GL_FLOAT, GL_FALSE, quantity*sizeof(float), (void*)0);
        glEnableVertexAttribArray(pos);
    };
    void load_indices(int (*data)[6], int size){
        
        // std::cout << "load data indices " << *data << " " << data[0] << " " << *data + 1 << " " << data  << std::endl;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, map.at("EBO"));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, *data, GL_STATIC_DRAW); 
    };
    void bind_vertex_array(){
        glBindVertexArray(map.at("VAO"));
    };
    void render(){
        glClearColor(0.5f, 0.6f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        bind_vertex_array();
        ourShader->use();
        trans = glm::translate(trans, *position);
        // position.x += 0.0001;
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };
    void bind_move_direction(glm::vec3 *vec){
        position = vec;
    }
    void init(){
        ourShader = new Shader("/home/sky/dev/projects/cpp/visual/vertex1.vert", "/home/sky/dev/projects/cpp/visual/fragment1.frag");
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        map.insert({"VAO", VAO});
        // glBindVertexArray(VO);

        unsigned int VBO0;
        glGenBuffers(1, &VBO0);
        map.insert({"VBO0", VBO0});
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);

        unsigned int VBO1;
        glGenBuffers(1, &VBO1);
        map.insert({"VBO1", VBO1});

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        map.insert({"EBO", EBO});

        trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.1f, 0.1f, 1.0f));
        transformLoc = glGetUniformLocation(ourShader->ID, "transform");
    };
};

