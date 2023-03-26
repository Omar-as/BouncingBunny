// #include <GL/glew.h>
#include <cmath>
#include "scratch/glew.cpp"
#include "scratch/glfw.cpp"
#include "innitShadder.cpp"
#include "scratch/load_model.cpp"

void processInput(GLFWwindow *window);

#define WIDTH 800
#define HEIGHT 600

int main()
{
	// Initializes GLFW
	scratch::glfw_initializer();

	// Creates Window
	auto window = scratch::window(WIDTH,HEIGHT,"test");
	glfwMakeContextCurrent(window);

	// Initializes GLEW
	scratch::glew_initializer();

	// Creates a model with the vertices and indices vectors
	auto model = scratch::model_loader("dotoff/bunny.off");
	// scratch::model_loader("dotoff/bunny.off");

	// Binds the shaders and returns Program to use 
	auto program = test::InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

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
		// input
		processInput(window);

		// render
    	// clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// be sure to activate the shader
		glUseProgram(program);

		// update the uniform color
		double  timeValue = glfwGetTime();
        float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
        int vertexColorLocation = glGetUniformLocation(program, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// now render the triangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, model.indices_number, GL_UNSIGNED_INT, 0);
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
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

