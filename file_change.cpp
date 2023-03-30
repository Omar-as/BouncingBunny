#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

#include "scratch/glew.cpp"
#include "scratch/glfw.cpp"
#include "innitShadder.cpp"
#include "scratch/load_model.cpp"
#include "scratch/color.cpp"
#include "scratch/trans.cpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Bouncing Objects"

#define colorinput 	 "incolor"
#define transformVal "transform"

#define vshader "vshader.glsl"
#define fshader "fshader.glsl"

#define bunny 	"dotoff/bunny.tlst"
#define cube  	"dotoff/cube.tlst"
#define sphere	"dotoff/sphere.tlst"

#define new_bunny 	"dotoff/new_bunny.tlst"
#define new_cube  	"dotoff/new_cube.tlst"
#define new_sphere	"dotoff/new_sphere.tlst"

int main()
{
	// Initializes GLFW
	scratch::glfw_initializer();

	// Creates Window
	auto window = scratch::window(800, 600, "change");
	glfwMakeContextCurrent(window);

	// Initializes GLEW
	scratch::glew_initializer();
	
	// Binds the shaders and returns Program to use 
	auto program = innitshader::InitShader( vshader, fshader );
    glUseProgram( program );

    auto model = scratch::model_loader(sphere, program);
    	
    int vertexColorLocation = glGetUniformLocation(program, colorinput);
	glUniform4f(vertexColorLocation, 0.9568627451f, 0.2627450980f, 0.2117647059f, 1.0f);

    glGenVertexArrays(1, &model.VAO);
    glGenBuffers	 (1, &model.VBO);
    glGenBuffers	 (1, &model.EBO);

    glBindVertexArray(model.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, model.VBO);
    glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(float), &model.vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(int), &model.indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glViewport(0, 0, 800, 600);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int transformLoc = glGetUniformLocation(program, "transform");
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(model.xTranslate,model.yTranslate,0.0f));   //position = 0,0,0
    transform = glm::rotate(transform, glm::radians(model.xRotate),glm::vec3(1,0,0));   //rotation x = 0.0 degrees
    transform = glm::rotate(transform, glm::radians(model.yRotate),glm::vec3(0,1,0));   //rotation y = 0.0 degrees
    transform = glm::rotate(transform, glm::radians(model.zRotate),glm::vec3(0,0,1));   //rotation z = 0.0 degrees
    transform = glm::scale(transform, glm::vec3(model.xScale,model.yScale,model.zScale)); 
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform)); 

    std::ofstream updatedModel;
    updatedModel.open(new_sphere);

    updatedModel << model.no_lines_vertices << " " << model.no_lines_indices << std::endl;
    updatedModel << std::endl;

    for (int i = 0; i < model.vertices.size() - 2; i += 3){
            auto oldVertex = glm::vec4(model.vertices[i], model.vertices[i + 1], model.vertices[i + 2], 1.0f);
            auto newVertex = transform * oldVertex;
            updatedModel << newVertex.x << " " << newVertex.y << " " << newVertex.z << std::endl;
    }

    updatedModel << std::endl;
	for (int i = 0; i < model.indices.size() - 2; i += 3) {
			updatedModel << model.indices[i] << " " << model.indices[i + 1] << " " << model.indices[i + 2] << std::endl;
	}
    while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
    glfwTerminate();
	return EXIT_SUCCESS;
}