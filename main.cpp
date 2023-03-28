// #include <GL/glew.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "scratch/glew.cpp"
#include "scratch/glfw.cpp"
#include "innitShadder.cpp"
#include "scratch/load_model.cpp"
#include "scratch/color.cpp"
#include "scratch/trans.cpp"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#define WIDTH 800
#define HEIGHT 800

int colorIndex = 0;
int vertexColorLocation = 1;

int modelIndex = 0;
std::vector <scratch::Model> models;

int drawIndex = 0;
std::vector <GLenum> drawInstance = {GL_LINE, GL_FILL, GL_POINT};

int main()
{
	// Initializes GLFW
	scratch::glfw_initializer();

	// Creates Window
	auto window = scratch::window(WIDTH,HEIGHT,"test");
	glfwMakeContextCurrent(window);

	// Call-Backs
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Initializes GLEW
	scratch::glew_initializer();

	// Adds all the models
	models.push_back(scratch::model_loader("dotoff/bunny.tlst"));
	models.push_back(scratch::model_loader("dotoff/cube.tlst"));
	models.push_back(scratch::model_loader("dotoff/sphere.tlst"));

	// Binds the shaders and returns Program to use 
	auto program = innitshader::InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

	// Set initial color
	int vertexColorLocation = glGetUniformLocation(program, "ourColor");
	glUniform4f(vertexColorLocation, 0.9568627451f, 0.2627450980f, 0.2117647059f, 1.0f); // Red

	// Binds all the buffers for all the models
	for (int i = 0; i < models.size(); i++){

		glGenVertexArrays(1, &models[i].VAO);
		glGenBuffers	 (1, &models[i].VBO);
		glGenBuffers	 (1, &models[i].EBO);

		glBindVertexArray(models[i].VAO);
		glBindBuffer(GL_ARRAY_BUFFER, models[i].VBO);
		glBufferData(GL_ARRAY_BUFFER, models[i].vertices.size() * sizeof(float), &models[i].vertices.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, models[i].EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, models[i].indices.size() * sizeof(int), &models[i].indices.front(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0); 
	}
	 
	glViewport(0, 0, WIDTH, HEIGHT);
	while(!glfwWindowShouldClose(window))
	{
		// create the model
		modelIndex = modelIndex % models.size();
		auto model = models[modelIndex];

		// render
    	// clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// create transformations
		unsigned int transformLoc = glGetUniformLocation(program, "transform");
		scratch::transform(transformLoc, modelIndex);

		// be sure to activate the shader
		glUseProgram(program);

		// now render the model
		glBindVertexArray(models[modelIndex].VAO);
		glDrawElements(GL_TRIANGLES, model.indices_number, GL_UNSIGNED_INT, 0);
		drawIndex = drawIndex % drawInstance.size();
		glPolygonMode(GL_FRONT_AND_BACK, drawInstance[drawIndex]);
		glBindVertexArray(0);

		// swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------- //
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Terminates the program when Q is pressed
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        exit(EXIT_SUCCESS);
	}
	// Changes the color when C is pressed
	else if (key == GLFW_KEY_C && action == GLFW_PRESS){
        float* row = scratch::colors(colorIndex);
		colorIndex = int(row[3]);
		scratch::update_colors(vertexColorLocation, row[0], row[1], row[2]);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	// changes between models
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		modelIndex++;
	}
	// changes between interpretation of polygons
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		drawIndex++;
	}

}

