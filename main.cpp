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

// ***********************************************************************************************
// Functions

void key_callback			(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback	(GLFWwindow* window, int button, int action, int mods);

void update(GLuint program, scratch::Model model);
void reset(GLuint program);
void help();

// ***********************************************************************************************
// Macros

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Bouncing Objects"

#define colorinput 	 "incolor"
#define transformVal "transform"

#define vshader "vshader.glsl"
#define fshader "fshader.glsl"

#define bunny 	"dotoff/new_bunny.tlst"
#define cube  	"dotoff/new_cube.tlst"
#define sphere	"dotoff/new_sphere.tlst"

// ***********************************************************************************************
// Global Variables 

int colorIndex = 0;
int vertexColorLocation = 1;

int modelIndex = 0;
std::vector <scratch::Model> models;

int drawIndex = 0;
std::vector <GLenum> drawInstance = {GL_LINE, GL_FILL, GL_POINT};

float xPos = 0.0;
float yPos = 0.0;
float xVelo = 0.003;
float yVelo = 0.0;
float yAcc = -0.001;

int resetVal = 0;

// ***********************************************************************************************


int main()
{
	// Initializes GLFW
	scratch::glfw_initializer();

	// Creates Window
	auto window = scratch::window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	glfwMakeContextCurrent(window);

	// Call-Backs
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Initializes GLEW
	scratch::glew_initializer();
	
	// Binds the shaders and returns Program to use 
	auto program = innitshader::InitShader( vshader, fshader );
    glUseProgram( program );

	// Adds all the models
	models.push_back(scratch::model_loader(bunny));
	models.push_back(scratch::model_loader(cube));
	models.push_back(scratch::model_loader(sphere));

	// Set initial color
	int vertexColorLocation = glGetUniformLocation(program, colorinput);
	glUniform4f(vertexColorLocation, 0.9568627451f, 0.2627450980f, 0.2117647059f, 1.0f); // Red

	// Binds all the buffers for all the models
	for (size_t i = 0; i < models.size(); i++)
	{
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
	 
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	while(!glfwWindowShouldClose(window))
	{
		// create the model
		modelIndex = modelIndex % models.size();
		auto model = models[modelIndex];

		// render
    	// clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Updates the model or resets it
		if(resetVal == 0){
			update(program, model);
		}else{
			reset(program);
			resetVal = 0;
		}

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

	// Terminates the program
	glfwTerminate();
	return EXIT_SUCCESS;
}

// ***********************************************************************************************

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Terminates the program with Q
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        exit(EXIT_SUCCESS);
	}
	// Changes the color with C
	else if (key == GLFW_KEY_C && action == GLFW_PRESS){
        float* row = scratch::colors(colorIndex);
		colorIndex = int(row[3]);
		scratch::update_colors(vertexColorLocation, row[0], row[1], row[2]);
	}
	// Resets the model to initial postion with I
	else if (key == GLFW_KEY_I && action == GLFW_PRESS){
        resetVal++;
	}
	// Prints the HELP screen with H
	else if (key == GLFW_KEY_H && action == GLFW_PRESS){
        help();
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	// changes between models
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		modelIndex++;
	}
	// changes between interpretation of polygons
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		drawIndex++;
	}

}

void update(GLuint program, scratch::Model model){

	// Updates the model position and yVelo
	xPos += xVelo;
	yVelo += yAcc;
	yPos += yVelo;

	// Creates the transform with the new positions
	unsigned int transformLoc = glGetUniformLocation(program, transformVal);
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(xPos, yPos,0.0f));

	// Calculates the new Y minimum of the model
	auto yMin = transform * glm::vec4(1.0f, model.minYval, 1.0f, 1.0f);

	// Checks if Y is below the ground or not and updates it correspondingly
	if (yMin.y < -1) {
		yVelo *= -1 * 0.9;
		yPos = -1 - model.minYval;
	}
	
	// Applies the transform
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void reset(GLuint program){
	
	// Resets the values of the model
	xPos = 0.0;
	yPos = 0.0;
	yVelo = 0.0;

	// Resets position to original position
	unsigned int transformLoc = glGetUniformLocation(program, transformVal);
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(xPos, yPos,0.0f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void help(){
	std::cout << "Welcome to the Help" << std::endl;
	std::cout << "****************************************************************************" << std::endl;
	std::cout << "I -- Initialize the pose (top left corner of the window)" << std::endl;
	std::cout << "C -- Switch between colors, which is used to draw lines or triangles." << std::endl;
	std::cout << "H -- Help; print explanation of input control" << std::endl;
	std::cout << "Q -- Quit (exit) the program" << std::endl;
	std::cout << "Right Mouse Button -- Changes between the objects to be drawn" << std::endl;
	std::cout << "Left  Mouse Button -- Changes how the triangles are drawn" << std::endl;
	std::cout << "****************************************************************************" << std::endl;
}