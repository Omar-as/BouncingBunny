#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

// Name Needs Changing. ASK.
namespace scratch 
{

	void glfw_initializer(){

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	}

	// how to pass a string in argument in a function
	GLFWwindow* window(int width, int height, const char* title){

		auto window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		return window;
	}
}
