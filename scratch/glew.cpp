#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

namespace scratch 
{

    void glew_initializer()
    {
        glewExperimental = GL_TRUE;
        glewInit();
    }

}