// #include <GL/glew.h>
#include <cmath>
#include "scratch/glew.cpp"
#include "scratch/glfw.cpp"
#include "innitShadder.cpp"
#include "scratch/load_model.cpp"
#include "scratch/color.cpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#define WIDTH 800
#define HEIGHT 600

int colorIndex = 0;
int vertexColorLocation = 0;

int main()
{
	// Initializes GLFW
	scratch::glfw_initializer();

	// Creates Window
	auto window = scratch::window(WIDTH,HEIGHT,"test");
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	// Initializes GLEW
	scratch::glew_initializer();

	// Creates a model with the vertices and indices vectors
	auto model = scratch::model_loader("dotoff/cube.tlst");

	// Binds the shaders and returns Program to use 
	auto program = innitshader::InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

	// Set initial color
	int vertexColorLocation = glGetUniformLocation(program, "ourColor");
	glUniform4f(vertexColorLocation, 0.9568627451f, 0.2627450980f, 0.2117647059f, 1.0f); // Red

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO); 

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// ..:: Initialization code :: ..
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(float), &model.vertices.front(), GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(int), &model.indices.front(), GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 
	 
	glViewport(0, 0, WIDTH, HEIGHT);
	while(!glfwWindowShouldClose(window))
	{
		// render
    	// clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// be sure to activate the shader
		glUseProgram(program);

		// now render the model
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, model.indices_number, GL_UNSIGNED_INT, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(0);

		// swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------- //
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
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

